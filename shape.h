#ifndef SHAPE_H_
#define SHAPE_H_

#include "shape.h"
#include "point.h"
#include "layer.h"

class Shape {
  int rotationStep;
  int x;
  int y;

public:
  Shape(Point *point, int rotationStep, int x, int y);
  ~Shape();

  int getNextRotationStep();
  void setRotationStep(int step);
  void setRelativeTranslation(int x, int y);
  void setLayer();
  void dump();
  bool trySpawn(Layer *background, int dx = 0, int dy = -2);
  bool tryLeftRight(Layer *background, int dx);
  bool tryDrop(Layer *background, int dy);
  bool tryRotate(Layer *background);

  Layer *layer;
  Point *point;
};

#endif
