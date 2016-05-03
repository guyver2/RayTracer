#include "element.h"
#include "scene.h"
#include <vector>
#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

Scene::Scene(): _elements(std::vector<Element*>()) {

}

int Scene::addElt(Element* elt){
  _elements.push_back(elt);
  return _elements.size();
}

Scene::~Scene (){
  for (auto e : _elements) delete e;
}

Vector3d Scene::intersect(const Line3d &line, const Vector3d &p0, const Vector3d &p1) const{
  double res = -1;
  for (auto &e : _elements){
    double d = e->intersect(line, p0, p1);
    //std::cout << e->_name << " " << d << std::endl;
    if (d >= 0) {
      if (res == -1 or res > d) res = d;
    }
  }
  if (res == -1) res = 1500;
  return res*((p1-p0).normalized()) + p1;
};
