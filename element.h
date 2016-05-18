#ifndef ELEMENT_H
#define ELEMENT_H

class Element;

#include <Eigen/Dense>
#include <string>
#include "types.h"


class Element {
public:
  std::string _name;
  colorRGB _color;
  virtual colorRGB col() {return _color;}
  virtual intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &)=0;
  virtual bool sameSide(const Eigen::Vector3d&, const Eigen::Vector3d&)=0;
  virtual bool side(const Eigen::Vector3d &)=0;
  virtual Eigen::Vector3d normal(const Eigen::Vector3d &)=0;
  virtual ~Element(){};
};



#endif
