#ifndef PLANE_H
#define PLANE_H

#include <Eigen/Dense>
#include <vector>
#include <string>
#include "element.h"

typedef Eigen::ParametrizedLine<double, 3> Line3d;

class Plane : public Element {
private:
  std::vector<Eigen::Vector3d> _points;
  Eigen::Hyperplane<double,3> _plane;

public:
  Plane (std::vector<Eigen::Vector3d>, std::string);
  virtual double intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &);
  virtual ~Plane ();
};



#endif
