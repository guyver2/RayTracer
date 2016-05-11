#include "camera.h"
#include "scene.h"
#include <Eigen/Dense>
#include <algorithm>
#include <string>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "json.h"

using namespace Eigen;
//using namespace cv;
using json = nlohmann::json;


Vector3d hemisphereRandomRay(){
  const float u1 = (float)rand() / RAND_MAX;
  const float u2 = (float)rand() / RAND_MAX;
  const float r = sqrt(u1);
  const float theta = 2 * M_PI * u2;

  const float x = r * cos(theta);
  const float y = r * sin(theta);

  Vector3d res = Vector3d(x, y, sqrt(fmax(0.0f, 1 - u1)));
  res.normalize();
  return res;
}


Matrix3d NormalToRotation(Vector3d normal) {
    // Find a vector in the plane
    Vector3d tangent0 = normal.cross(Vector3d(1, 0, 0));
    // if result tangent is too small it means normal was roughly colinear with
    // chosen vector (1,0,0)
    if (tangent0.dot(tangent0) < 0.001)
        tangent0 = normal.cross(Vector3d(0, 1, 0));
    tangent0.normalize();
    // Find another vector in the plane
    Vector3d tangent1 = normal.cross(tangent0);
    tangent1.normalize();
    // Construct a 3x3 matrix by storing three vectors in the columns of the matrix
    Matrix3d res;
    res.col(0) = tangent0;
    res.col(1) = tangent1;
    res.col(2) = normal;
    //std::cout << res << std::endl;
    //std::cout << "==========" << std::endl;
    return res;
}



Camera::Camera (Vector3d center, Vector3d up,
        Vector3d dir, double f, double w, double h) :
        _center(center),
        _up(up),
        _dir(dir),
        _f(f), _width(w), _height(h)
        {}

Camera::Camera(std::string filename){
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "Could not open file " << filename << std::endl;
    return;
  }
  json dict;
  ifs >> dict;
  try{
    json camdata = dict["camera"];
    _f = camdata["focal"];
    _width = camdata["width"];
    _height = camdata["height"];
    _center = Vector3d(camdata["position"][0], camdata["position"][1], camdata["position"][2]);
    _dir = Vector3d(camdata["dir"][0], camdata["dir"][1], camdata["dir"][2]);
    _up = Vector3d(camdata["up"][0], camdata["up"][1], camdata["up"][2]);
  } catch (std::domain_error e) {
    std::cerr << "Error while loading camera data from file: " << filename << std::endl;
    _center = Vector3d(0,0,0);
    _up = Vector3d(0,1,0);
    _dir = Vector3d(0,0,1);
    _f = 0.035;
    _width = _height = 0.025;
  }
}


Camera::~Camera(){}


cv::Mat Camera::renderDepth(const Scene &scene, int w, int h){
  double dx = _width/w;
  double dy = _height/h;
  std::vector<double> depth(w*h,0);
  IOFormat singleLine(FullPrecision, DontAlignCols, ", ", ", ", "", "", " [ ", " ] ");
  Vector3d screen_ori(_center+Vector3d(-_width/2,_height/2, _f));
  #pragma omp parallel for
  for (size_t i = 0; i < w; i++) {
    #pragma omp parallel for
    for (size_t j = 0; j < h; j++) {
      Vector3d pix = screen_ori + Vector3d(dx*i, -dy*j, 0);
      Line3d line = Line3d::Through(_center, pix);
      intersection pt = scene.intersect(line, _center, pix);
      if (pt.valid()) depth[j*w+i] = pt.depth();
      else depth[j*w+i] = 1500;
    }
  }

  // remap values between 0 and 1 based on max min depth of the scene (800, 1500)
  std::vector<char> buffer(w*h,0);
  int i = 0;
  for (auto e : depth) buffer[i++] = 255 - 255*(e-800)/(1500-800);

  cv::Mat image(cv::Size(w, h), CV_8UC1, buffer.data(), cv::Mat::AUTO_STEP);
  return image.clone();
}

std::pair<colorRGB, intersection> singleRay(const Vector3d &p0, const Vector3d &p1, const Scene &scene){
  Line3d line = Line3d::Through(p0, p1);
  intersection pt = scene.intersect(line, p0, p1);
  colorRGB resCol(0,0,0);
  if (pt.valid()){
    // shoot direct shadow rays
    for (const auto l : scene._lights){
      Spot* spot = (Spot*)l;
      //check if the spot and the origin point are on the same size of the
      // supporting plane of the intersection
      bool sameSide = pt.element()->sameSide(p0, spot->position());
      // check if the spot sees the intersection
      bool sees = (sameSide && spot->sees(pt.point(), scene));
      if (sees){
          //double dist = 1-fabs(((pt.point()-spot->position()).norm())/800.0);
          resCol = resCol + spot->col()*pt.col();//*dist;
        }
    }
    double d = scene._lights.size();
    resCol = resCol / d;
  }
  return std::make_pair(resCol, pt);
}


cv::Mat Camera::renderBounceOnce(const Scene &scene, int w, int h){
  double dx = _width/w;
  double dy = _height/h;
  std::vector<char> colorImg(w*h*3,0);
  Vector3d screen_ori(_center+Vector3d(-_width/2,_height/2, _f));
  #pragma omp parallel for
  for (size_t i = 0; i < w; i++) {
    #pragma omp parallel for
    for (size_t j = 0; j < h; j++) {
      colorRGB resCol(0,0,0);
      Vector3d pix = screen_ori + Vector3d(dx*i, -dy*j, 0);
      std::pair<colorRGB, intersection> res = singleRay(_center, pix, scene);
      colorRGB primaryCol = res.first;
      intersection pt = res.second;
      if (pt.valid()){
        // shoot refracted rays in random directions around surface normal
        // and flip normal if we're looking at the object from 'the other side'
        Vector3d normal = pt.element()->normal();
        if (!pt.element()->side(_center)){
          normal *= -1;
        }
        Matrix3d rot = NormalToRotation(normal);
        colorRGB secondaryCol(0,0,0);
        int nbRays = 1500;
        #pragma omp parallel for
        for (size_t i = 0; i < nbRays; i++) {
          Vector3d randomRay = rot*hemisphereRandomRay();
          randomRay += pt.point();

          std::pair<colorRGB, intersection> resRay = singleRay(pt.point(), randomRay, scene);
          secondaryCol = secondaryCol + resRay.first;
        }
        secondaryCol = secondaryCol / nbRays;
        resCol = (primaryCol + pt.col()*secondaryCol)/2;
      }

      colorImg[3*(j*w+i)] = fmin(255,255*resCol.r);
      colorImg[3*(j*w+i)+1] = fmin(255,255*resCol.g);
      colorImg[3*(j*w+i)+2] = fmin(255,255*resCol.b);
    }
  }

  cv::Mat image(cv::Size(w, h), CV_8UC3, colorImg.data(), cv::Mat::AUTO_STEP);
  return image.clone();
}




cv::Mat Camera::renderDirect(const Scene &scene, int w, int h){
  double dx = _width/w;
  double dy = _height/h;
  std::vector<char> colorImg(w*h*3,0);
  IOFormat singleLine(FullPrecision, DontAlignCols, ", ", ", ", "", "", " [ ", " ] ");
  Vector3d screen_ori(_center+Vector3d(-_width/2,_height/2, _f));
  #pragma omp parallel for
  for (size_t i = 0; i < w; i++) {
    #pragma omp parallel for
    for (size_t j = 0; j < h; j++) {
      Vector3d pix = screen_ori + Vector3d(dx*i, -dy*j, 0);
      std::pair<colorRGB, intersection> res = singleRay(_center, pix, scene);
      colorRGB resCol = res.first;
      colorImg[3*(j*w+i)] = fmin(255,255*resCol.r);
      colorImg[3*(j*w+i)+1] = fmin(255,255*resCol.g);
      colorImg[3*(j*w+i)+2] = fmin(255,255*resCol.b);
    }
  }

  cv::Mat image(cv::Size(w, h), CV_8UC3, colorImg.data(), cv::Mat::AUTO_STEP);
  return image.clone();
}
