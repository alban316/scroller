#ifndef SHAPE_H_
#define SHAPE_H_

#include "shape.h"
#include "point.h"
#include "layer.h"

class Shape {
public:
  Shape(Point *point);
  virtual ~Shape() {};

  void rotate(int degrees);
  Layer* toLayer();
  void dump();

  Point *point;

  int y;
};

#endif
