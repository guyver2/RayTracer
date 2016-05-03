#include "camera.h"
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


void Camera::render(const Scene &scene, int w, int h){
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
      auto pt = scene.intersect(line, _center, pix);
      depth[j*w+i] = (pt-_center).norm();
    }
  }

  double max = *(std::max_element(depth.begin(), depth.end()));
  double min = *(std::min_element(depth.begin(), depth.end()));
  std::cout << "min max " << min << " " << max << std::endl;
  std::vector<char> buffer(w*h,0);
  int i = 0;
  for (auto e : depth) buffer[i++] = 255 - 255*(e-800)/(1500-800);

  Mat image(Size(w, h), CV_8UC1, buffer.data(), Mat::AUTO_STEP);
  imwrite("render.png", image);
}
