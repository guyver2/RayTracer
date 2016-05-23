#include "plane.h"
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace Eigen;

Plane::Plane(std::vector<Vector3d> pts, std::string name, colorRGB col) :
             _points(pts){
  _reflection = -1;
  _refraction = -1;
  _name = name;
  _color = col;
  _plane = Hyperplane<double,3>::Through( _points[0],_points[1],_points[2]);
}

Plane::~Plane(){}


intersection Plane::intersect(const Line3d &line, const Vector3d &p0, const Vector3d &p1){
  double d = line.intersection(_plane);
  // check if intersection is not at infinity nor extremly close to the original point
  if (std::isfinite(d) && (d>0.0001)) {
    // check wether the point lies INSIDE the plane
    Vector3d m = d*((p1-p0).normalized()) + p0;
    double u = (m - _points[0]).dot(_points[1] - _points[0]);
    double v = (m - _points[0]).dot(_points[3] - _points[0]);
    if ((0 <= u) && (u <= pow((_points[1] - _points[0]).norm(),2)) &&
        (0 <= v) && (v <= pow((_points[3] - _points[0]).norm(),2))) {
      return intersection(true, p0, m, p1, d, &_color, this);
    } else {
       return intersection();
    }
  } else {
    return intersection();
  }
}


bool Plane::sameSide(const Vector3d &p0, const Vector3d &p1){
  double d0 = _plane.signedDistance(p0);
  double d1 = _plane.signedDistance(p1);
  // check for same sign
  return ((d0<0) == (d1<0));
}

bool Plane::side(const Vector3d &p){
  return _plane.signedDistance(p) > 0;
}

// assumes p is ON the plane
Eigen::Vector3d Plane::normal(const Eigen::Vector3d &p){
  return _plane.normal();
}
