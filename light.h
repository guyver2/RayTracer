#ifndef LIGHT_H
#define LIGHT_H

class Light;
class Spot;

#include <Eigen/Dense>
#include "scene.h"
#include "types.h"

class Light {
protected:
  colorRGB _color;
  int _type;
public:
  virtual float sees(intersection&, const Scene&)=0;
  virtual colorRGB col() { return _color; }
  virtual int type() {return _type; }
  virtual intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &) { return intersection();}
  virtual ~Light (){};

};


class Spot : public Light {
private:
  Eigen::Vector3d _position;
public:
  Spot (const Eigen::Vector3d&, const colorRGB&);
  Eigen::Vector3d& position();
  virtual float sees(intersection&, const Scene&);
  virtual ~Spot();

};



class AreaLight : public Light {
private:
  std::vector<Eigen::Vector3d> _points;
  Eigen::Hyperplane<double,3> _plane;
  Eigen::Vector3d _u;
  Eigen::Vector3d _v;
  int _sampling;
public:
  AreaLight (std::vector<Eigen::Vector3d>, colorRGB, int);
  virtual ~AreaLight();
  virtual float sees(intersection&, const Scene&);
  virtual intersection intersect(const Line3d&, const Eigen::Vector3d &, const Eigen::Vector3d &);
};


#endif
