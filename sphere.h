#ifndef SPHERE_H
#define SPHERE_H

class Sphere;

#include <Eigen/Dense>
#include <string>
#include "element.h"
#include "types.h"


class Sphere : public Element{
  Eigen::Vector3d _center;
  float _radius;


public:
  Sphere(Eigen::Vector3d, float, std::string, colorRGB);
  virtual intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &);
  virtual bool sameSide(const Eigen::Vector3d&, const Eigen::Vector3d&);
  virtual bool side(const Eigen::Vector3d &);
  virtual Eigen::Vector3d normal(const Eigen::Vector3d &);
  virtual ~Sphere();
};



#endif
