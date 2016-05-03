#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <Eigen/Dense>
#include "element.h"

typedef Eigen::ParametrizedLine<double, 3> Line3d;


class Scene {
private:
  std::vector<Element*> _elements;
public:
  Scene();
  int addElt(Element*);
  Eigen::Vector3d intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &) const;
  virtual ~Scene ();
};


#endif
