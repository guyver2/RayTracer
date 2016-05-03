#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <Eigen/Dense>
#include "scene.h"

typedef Eigen::ParametrizedLine<double, 3> Line3d;

class Camera {
private:
  Eigen::Vector3d _center;
  Eigen::Vector3d _dir;
  Eigen::Vector3d _up;
  double _f;
  double _width;
  double _height;



public:
  Camera (Eigen::Vector3d, Eigen::Vector3d, Eigen::Vector3d, double, double, double);
  virtual ~Camera ();
  void render(const Scene&, int w, int h);
};


#endif
