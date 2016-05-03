#include "plane.h"
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace Eigen;

Plane::Plane(std::vector<Vector3d> pts, std::string name) :
             _points(pts)/*,
             _name(name)*/{
  _name = name;
  _plane = Hyperplane<double,3>::Through( _points[0],_points[1],_points[2]);
}

Plane::~Plane(){}


double Plane::intersect(const Line3d &line, const Vector3d &p0, const Vector3d &p1){
  double d = line.intersection(_plane);
  if (std::isfinite(d)) {
    // check wether the point lies INSIDE the plane
    Vector3d m = d*((p1-p0).normalized()) + p0;
    double u = (m - _points[0]).dot(_points[1] - _points[0]);
    double v = (m - _points[0]).dot(_points[3] - _points[0]);
    if ((0 <= u) && (u <= pow((_points[1] - _points[0]).norm(),2)) &&
        (0 <= v) && (v <= pow((_points[3] - _points[0]).norm(),2))) {
      return d;
    } else {
       return -1;
    }
  } else {
    return -1;
  }
}
