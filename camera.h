#ifndef CAMERA_H
#define CAMERA_H

class Camera;

#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>

#include "scene.h"
#include "types.h"

class Camera {
private:
  Eigen::Vector3d _center;
  Eigen::Vector3d _dir;
  Eigen::Vector3d _up;
  double _f;
  double _width;
  double _height;
  int _subrays;



public:
  Camera (Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d, double, double, double, int);
  Camera (std::string);
  virtual ~Camera ();
  cv::Mat renderDepth(const Scene&, int, int);
  cv::Mat renderDirect(const Scene&, int, int);
  cv::Mat renderBounceOnce(const Scene &, int, int);
};


#endif
