#ifndef TYPES_RAY_H
#define TYPES_RAY_H


class color;
class intersection;

#include <Eigen/Dense>
#include <utility>

typedef Eigen::ParametrizedLine<double, 3> Line3d;

class color {
  public:
    double r,g,b;
    color():r(0), g(0), b(0){}
    color(const color& c): r(c.r), g(c.g), b(c.b){}
    color(double v): r(v), g(v), b(v){}
    color(double r, double g, double b): r(r), g(g), b(b){}
    color operator* (const color &x) { return color(r*x.r, g*x.g, b*x.b); }
    color operator* (const double x) { return color(r*x, g*x, b*x); }
};


class intersection {
  private:
    Eigen::Vector3d _pt;
    bool _valid;
    double _depth;
    color* _color;
    Element* _element;
  public:
    intersection(): _valid(false), _pt(Eigen::Vector3d(0,0,0)), _depth(-1),
                    _color(NULL), _element(NULL){}
    intersection (bool v, Eigen::Vector3d p, double d, color* col, Element* elt) :
                  _valid(v), _pt(p), _depth(d), _color(col), _element(elt){}
    bool valid(){ return _valid; }
    color col(){ return *_color; }
    Element* element() { return _element;}
    Eigen::Vector3d &point() { return _pt;}
    double depth() {return _depth;}
};




#endif
