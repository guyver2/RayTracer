#include "sphere.h"
#include <Eigen/Dense>
#include <vector>
#include <cmath>

using namespace Eigen;

Sphere::Sphere(Vector3d center, float radius, std::string name, colorRGB col) :
             _center(center), _radius(radius){
  _name = name;
  _color = col;
}

Sphere::~Sphere(){}


// assumes p0 is outside the sphere
intersection Sphere::intersect(const Line3d &line, const Eigen::Vector3d &p0, const Eigen::Vector3d &p1){
  Vector3d vpc = _center-p0; // vector from p0 to sphere center
  Vector3d d = (p1-p0);
  d.normalize(); // unit direction vector
  if (vpc.dot(d) < 0) return intersection(); // sphere behind line, NO intersection
  Vector3d pc = line.projection(_center); // projection of _center onto the line
  if ((_center - pc).norm() > _radius) return intersection(); // too far, NO intersection
  float dist_pc_it = sqrt(_radius*_radius - pow((pc - _center).norm(),2));
  float dist_p0_it = (pc-p0).norm() - dist_pc_it;
  return intersection(true, p0, p0+d*dist_p0_it, p1, dist_p0_it, &_color, this);
}

bool Sphere::sameSide(const Eigen::Vector3d &p0, const Eigen::Vector3d &p1){
  Line3d line = Line3d::Through(p0, p1);
  Vector3d pc = line.projection(_center);
  if ((_center - pc).norm() > _radius) return true; // NO intersection
  else return false;
}

bool Sphere::side(const Eigen::Vector3d &p) {
  return ((p-_center).norm() >= _radius);
}

// assumes p is on the surface
Vector3d Sphere::normal(const Eigen::Vector3d &p){
  Vector3d res = p-_center;
  res.normalize();
  return res;
}
