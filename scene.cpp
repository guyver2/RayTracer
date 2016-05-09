#include "element.h"
#include "plane.h"
#include "scene.h"
#include <vector>
#include <Eigen/Dense>
#include <iostream>
#include <fstream>
#include <string>
#include "json.h"

using namespace Eigen;
using json = nlohmann::json;

Scene::Scene(): _elements(std::vector<Element*>()),_lights(std::vector<Light*>()) {
}

Scene::Scene(std::string filename): _elements(std::vector<Element*>()),
                                    _lights(std::vector<Light*>()) {
  std::ifstream ifs(filename);
  if (!ifs.is_open()) {
    std::cerr << "Could not open file " << filename << std::endl;
    return;
  }
  json dict;
  ifs >> dict;
  try{
    // load lights
    for (const auto &lightData : dict["lights"]){
      if (lightData["type"] == "spot") {
        auto pos = lightData["position"];
        auto col = lightData["color"];
        addLight(new Spot(Vector3d(pos[0], pos[1], pos[2]), color(col[0], col[1], col[2])));
      } else {
        std::cout << "Cannot handle light type [" << lightData["type"] << "] yet." << std::endl;
      }
    }
    // load elements
    for (const auto &eltData : dict["elements"]){
      if (eltData["type"] == "quad") {
        auto ptsdata = eltData["pts"];
        auto col = eltData["color"];
        std::string name = eltData["name"];
        std::vector<Vector3d> pts;
        for (const auto &pt : ptsdata) {
          pts.push_back(Vector3d(pt[0], pt[1], pt[2]));
        }
        addElt(new Plane(pts, name, color(col[0], col[1], col[2])));
      } else {
        std::cout << "Cannot handle element type [" << eltData["type"] << "] yet." << std::endl;
      }
    }

  } catch (std::domain_error e) {
    std::cerr << "Error while loading scene data from file: " << filename << std::endl;
    _elements = std::vector<Element*>();
    _lights = std::vector<Light*>();
  }

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
