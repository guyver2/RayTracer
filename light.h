#ifndef LIGHT_H
#define LIGHT_H

class Light;
class Spot;

#include <Eigen/Dense>
#include "scene.h"
#include "types.h"

class Light {
public:
  virtual bool sees(const Eigen::Vector3d&, const Scene&)=0;
  virtual ~Light (){};

};


class Spot : public Light {
private:
  Eigen::Vector3d _position;
  color _color;
public:
  Spot (const Eigen::Vector3d&, const color&);
  Eigen::Vector3d& position();
  color col();
  virtual bool sees(const Eigen::Vector3d&, const Scene&);
  virtual ~Spot();

};


#endif
