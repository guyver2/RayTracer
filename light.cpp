#include "light.h"


Spot::Spot(const Eigen::Vector3d& pos, const color& c) : _position(pos), _color(c){

};

Eigen::Vector3d& Spot::position() {
  return _position;
}

color Spot::col() {
  return _color;
}

// check wether there is a direct line between a point and the spot that doesn't
// cross any object of the scene
bool Spot::sees(const Eigen::Vector3d& pt, const Scene& scene){
  double dist = (_position-pt).norm();
  Line3d line = Line3d::Through(pt, _position);
  intersection it = scene.intersect(line, pt, _position);
  if (!it.valid() || it.depth() > dist) return true;
  return false;
}
Spot::~Spot  (){};
