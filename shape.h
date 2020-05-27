#ifndef SHAPE_H_
#define SHAPE_H_

#include "shape.h"
#include "point.h"
#include "layer.h"

class Shape {
  short rotationStep;
  short x;
  short y;

public:
  Shape(Point *point, short rotationStep, short x, short y);
  ~Shape();

  short getNextRotationStep();
  void setRotationStep(short sstep);
  void setRelativeTranslation(short x, short y);
  void setLayer();
  void dump();
  bool trySpawn(Layer *background, short dx = 0, short dy = -2);
  bool tryLeftRight(Layer *background, short dx);
  bool tryDrop(Layer *background, short dy);
  bool tryRotate(Layer *background);

  Layer *layer;
  Point *point;
};

#endif
