#include "element.h"
#include "scene.h"
#include <vector>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

Scene::Scene(): _elements(std::vector<Element*>()),_lights(std::vector<Light*>()) {
}

int Scene::addElt(Element* elt){
  _elements.push_back(elt);
  return _elements.size();
}

int Scene::addLight(Light* light){
  _lights.push_back(light);
  return _lights.size();
}


Scene::~Scene (){
  for (auto e : _elements) delete e;
  for (auto l : _lights) delete l;
}

intersection Scene::intersect(const Line3d &line, const Vector3d &p0, const Vector3d &p1) const{
  intersection res;
  for (auto &e : _elements){
    intersection it = e->intersect(line, p0, p1);
    //std::cout << e->_name << " " << d << std::endl;
    if (it.valid()) {
      if (!res.valid() || res.depth() > it.depth()) res = it;
    }
  }
  if (!res.valid()) return intersection();
  else return res;
};
