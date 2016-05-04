#ifndef SCENE_H
#define SCENE_H

class Scene;

#include <vector>
#include <Eigen/Dense>
#include "element.h"
#include "light.h"
#include "types.h"



class Scene {
public:
  std::vector<Element*> _elements;
  std::vector<Light*> _lights;
public:
  Scene();
  int addElt(Element*);
  int addLight(Light*);
  intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &) const;
  virtual ~Scene ();
};


#endif
