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
  colorRGB _color;
public:
  Spot (const Eigen::Vector3d&, const colorRGB&);
  Eigen::Vector3d& position();
  colorRGB col();
  virtual bool sees(const Eigen::Vector3d&, const Scene&);
  virtual ~Spot();

};


#endif
