#include "light.h"
#include <cstdlib>
#include <iostream>

using namespace Eigen;


//-----------------------------------------------------------------
// Point LIGHT TODO : RENAME class to PointLight
//-----------------------------------------------------------------

Spot::Spot(const Vector3d& pos, const colorRGB& c) : _position(pos){
  _color = c;
  _type = 0;
};

Spot::~Spot  (){};


Vector3d& Spot::position() {
  return _position;
}

// check wether there is a direct line between a point and the spot that doesn't
// cross any object of the scene
float Spot::sees(intersection& it, const Scene& scene){
  //check if the spot and the origin point are on the same size of the
  // supporting plane of the intersection
  Vector3d &pt = it.point();
  Vector3d &from = it.fromPoint();
  bool sameSide = it.element()->sameSide(from, _position);
  if (!sameSide) return 0;
  // check if the spot sees the intersection
  double dist = (_position-pt).norm();
  Line3d line = Line3d::Through(pt, _position);
  intersection lit = scene.intersect(line, pt, _position, false);
  if (!lit.valid() || lit.depth() > dist) return 1;
  return 0;
}


//------------------------------------------------------------------
// AREA LIGHT
//------------------------------------------------------------------

AreaLight::AreaLight(std::vector<Vector3d> pts, colorRGB c, int sampling)
                     : _points(pts), _sampling(sampling) {
  _color = c;
  _type = 1;
  _plane = Hyperplane<double,3>::Through( _points[0],_points[1],_points[2]);
  _u = _points[1] - _points[0];
  _v = _points[3] - _points[0];
}
AreaLight::~AreaLight  (){};


float AreaLight::sees(intersection& it, const Scene& scene){
  // check if the point faces the right side of the light area
  Vector3d &pt = it.point();
  if (_plane.signedDistance(pt) < 0) return 0;

  Vector3d &from = it.fromPoint();
  float res = 0;
  // sample N random points on the light and then shoot rays from the point
  #pragma omp parallel for
  for (size_t i = 0; i < _sampling*_sampling; i++) {
    // grid random sampling
    float u = (i/_sampling)/(float)_sampling + ((0.5/_sampling) * rand()) / RAND_MAX;
    float v = (i%_sampling)/(float)_sampling + ((0.5/_sampling) * rand()) / RAND_MAX;


    Vector3d lp = _points[0] + u*_u +v*_v; // random light source position on area
    bool sameSide = it.element()->sameSide(from, lp);
    if (sameSide){
      // check if the light point sees the intersection
      double dist = (lp-pt).norm();
      Line3d line = Line3d::Through(pt, lp);
      intersection lit = scene.intersect(line, pt, lp, false);
      if (!lit.valid() || lit.depth() > dist) res+=1;
    }
  }
  return res/(_sampling*_sampling);
 }


 intersection AreaLight::intersect(const Line3d &line, const Vector3d &p0, const Vector3d &p1){
   double d = line.intersection(_plane);
   // check if intersection is not at infinity nor extremly close to the original point
   if (std::isfinite(d) && (d>0.0001)) {
     // check wether the point lies INSIDE the plane
     Vector3d m = d*((p1-p0).normalized()) + p0;
     double u = (m - _points[0]).dot(_points[1] - _points[0]);
     double v = (m - _points[0]).dot(_points[3] - _points[0]);
     if ((0 <= u) && (u <= pow((_points[1] - _points[0]).norm(),2)) &&
         (0 <= v) && (v <= pow((_points[3] - _points[0]).norm(),2))) {
       return intersection(true, p0, m, p1, d, &_color, NULL);
     } else {
        return intersection();
     }
   } else {
     return intersection();
   }
 }
