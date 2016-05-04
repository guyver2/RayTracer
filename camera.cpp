#include "camera.h"
#include "scene.h"
#include <Eigen/Dense>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace Eigen;
using namespace cv;

Camera::Camera (Vector3d center, Vector3d up,
        Vector3d dir, double f, double w, double h) :
        _center(center),
        _up(up),
        _dir(dir),
        _f(f), _width(w), _height(h)
        {}

Camera::~Camera(){}


Mat Camera::renderDepth(const Scene &scene, int w, int h){
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

  Mat image(Size(w, h), CV_8UC1, buffer.data(), Mat::AUTO_STEP);
  return image.clone();
}




Mat Camera::renderBounceOnce(const Scene &scene, int w, int h){
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
      Line3d line = Line3d::Through(_center, pix);
      intersection pt = scene.intersect(line, _center, pix);
      if (pt.valid()){
        Spot* spot = (Spot*)scene._lights[0];
        //check if the spot and the origin point are on the same size of the
        // supporting plane of the intersection
        bool sameSide = pt.element()->sameSide(_center, spot->position());
        // check if the spot sees the intersection
        bool sees = (sameSide && spot->sees(pt.point(), scene));
        if (sees){
            colorImg[3*(j*w+i)] = 255*(pt.col().r*spot->col().r);
            colorImg[3*(j*w+i)+1] = 255*(pt.col().g*spot->col().g);
            colorImg[3*(j*w+i)+2] = 255*(pt.col().b*spot->col().b);
          } else {
            colorImg[3*(j*w+i)] = 255 - 255*(pt.depth()-800)/(1500-800);
            colorImg[3*(j*w+i)+1] = 255 - 255*(pt.depth()-800)/(1500-800);
            colorImg[3*(j*w+i)+2] = 255 - 255*(pt.depth()-800)/(1500-800);
          }

      } else {
        colorImg[3*(j*w+i)] = 0;
        colorImg[3*(j*w+i)+1] = 0;
        colorImg[3*(j*w+i)+2] = 0;
      }
    }
  }

  Mat image(Size(w, h), CV_8UC3, colorImg.data(), Mat::AUTO_STEP);
  return image.clone();
}




Mat Camera::renderDirect(const Scene &scene, int w, int h){
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
      Line3d line = Line3d::Through(_center, pix);
      intersection pt = scene.intersect(line, _center, pix);
      if (pt.valid()){
        Spot* spot = (Spot*)scene._lights[0];
        //check if the spot and the origin point are on the same size of the
        // supporting plane of the intersection
        bool sameSide = pt.element()->sameSide(_center, spot->position());
        // check if the spot sees the intersection
        bool sees = (sameSide && spot->sees(pt.point(), scene));
        if (sees){
            double dist = 1-fabs(((pt.point()-spot->position()).norm())/800.0);
            color resCol = spot->col()*pt.col()*dist;
            colorImg[3*(j*w+i)] = 255*resCol.r;
            colorImg[3*(j*w+i)+1] = 255*resCol.g;
            colorImg[3*(j*w+i)+2] = 255*resCol.b;
          } else {
            double dist = 1-fabs(((pt.point()-spot->position()).norm())/800.0);
            colorImg[3*(j*w+i)] = 255*dist/1.5;
            colorImg[3*(j*w+i)+1] = 255*dist/1.5;
            colorImg[3*(j*w+i)+2] = 255*dist/1.5;
          }

      } else {
        colorImg[3*(j*w+i)] = 0;
        colorImg[3*(j*w+i)+1] = 0;
        colorImg[3*(j*w+i)+2] = 0;
      }
    }
  }

  Mat image(Size(w, h), CV_8UC3, colorImg.data(), Mat::AUTO_STEP);
  return image.clone();
}
