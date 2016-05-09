#ifndef TYPES_RAY_H
#define TYPES_RAY_H


class colorRGB;
class intersection;

#include <Eigen/Dense>
#include <utility>

typedef Eigen::ParametrizedLine<double, 3> Line3d;

class colorRGB {
  public:
    double r,g,b;
    colorRGB():r(0), g(0), b(0){}
    colorRGB(const colorRGB& c): r(c.r), g(c.g), b(c.b){}
    colorRGB(double v): r(v), g(v), b(v){}
    colorRGB(double r, double g, double b): r(r), g(g), b(b){}
    colorRGB operator* (const colorRGB &x) { return colorRGB(r*x.r, g*x.g, b*x.b); }
    colorRGB operator+ (const colorRGB &x) { return colorRGB(r+x.r, g+x.g, b+x.b); }
    colorRGB operator* (const double x) { return colorRGB(r*x, g*x, b*x); }
};


class intersection {
  private:
    Eigen::Vector3d _pt;
    bool _valid;
    double _depth;
    colorRGB* _color;
    Element* _element;
  public:
    intersection(): _valid(false), _pt(Eigen::Vector3d(0,0,0)), _depth(-1),
                    _color(NULL), _element(NULL){}
    intersection (bool v, Eigen::Vector3d p, double d, colorRGB* col, Element* elt) :
                  _valid(v), _pt(p), _depth(d), _color(col), _element(elt){}
    bool valid(){ return _valid; }
    colorRGB col(){ return *_color; }
    Element* element() { return _element;}
    Eigen::Vector3d &point() { return _pt;}
    double depth() {return _depth;}
};




#endif
