#ifndef ELEMENT_H
#define ELEMENT_H
#include <Eigen/Dense>
#include <string>

typedef Eigen::ParametrizedLine<double, 3> Line3d;

class Element {
public:
  std::string _name;
  virtual double intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &)=0;
  virtual ~Element(){};
};



#endif
