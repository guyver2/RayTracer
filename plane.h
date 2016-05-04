#ifndef PLANE_H
#define PLANE_H

class Plane;

#include <Eigen/Dense>
#include <vector>
#include <string>
#include "element.h"
#include "types.h"

class Plane : public Element {
private:
  std::vector<Eigen::Vector3d> _points;
  Eigen::Hyperplane<double,3> _plane;

public:
  Plane (std::vector<Eigen::Vector3d>, std::string, color&);
  virtual intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &);
  virtual bool sameSide(const Eigen::Vector3d&, const Eigen::Vector3d&);
  virtual ~Plane ();
};



#endif
