#include "point.h"
#include "shape.h"
#include "math.h"
#include "layer.h"
#include "logger.h"


#define PI 3.14159265
#define TO_RADIANS(degrees) (degrees) * PI/180

const float RotationStep[] = {0, TO_RADIANS(90), PI, TO_RADIANS(270)};

Shape::Shape(Point *point, int rotationStep, int x, int y) {
  this->point = point;
  this->rotationStep = rotationStep;
  this->x = x;
  this->y = y;
  setLayer();
}


Shape::~Shape() {
  delete layer;
}


int Shape::getNextRotationStep() {
  int nextStep = rotationStep + 1;

  if (nextStep < 4)
    return nextStep;

  else
    return 0;
}


void Shape::setRotationStep(int step) {
  rotationStep = step;
  setLayer();
}


void Shape::setRelativeTranslation(int dx, int dy) {
  x += dx;
  y += dy;
  setLayer();
}


bool Shape::trySpawn(Layer *background, int dx, int dy) {

  //int vars[] = {dx, dy};
  //Logger::log("trySpawn dx = ?, dy = ?", vars, 2);

  Shape proposed = Shape(point, rotationStep, x + dx, y + dy);
  //proposed.layer->dump();


  if (proposed.layer->collisionOrBoundary(background))
    return false;

  else {
    setRelativeTranslation(dx, dy);
    return true;
  }

}


bool Shape::tryRotate(Layer *background) {
  Shape proposed = Shape(point, getNextRotationStep(), x, y);

  if (proposed.layer->collisionOrBoundary(background))
    return false;

  else {
    setRotationStep(proposed.rotationStep);
    return true;
  }
}


bool Shape::tryLeftRight(Layer *background, int dx) {
  return trySpawn(background, dx, 0);
}


bool Shape::tryDrop(Layer *background, int dy) {
  if (layer->digVal[7] > 0)
    // we are already as low as we can go
    return false;

  else
    return trySpawn(background, 0, dy);
}


void Shape::setLayer() {
  layer = new Layer();

  for (int i = 0; i < 4; i++) {
    int px = point[i].xAtTheta(RotationStep[rotationStep]);
    int py = point[i].yAtTheta(RotationStep[rotationStep]);

    // where 3, 3 is the approx center of an 8x8 matrix
    // and y is a member indicating vertical translation of the shape
    int row = 3 + py + y;
    int col = 3 - px + x;

    int mypow = round(pow(2,col));

    // check if off the board to right
    if ((col != 0) & (mypow == 0))
      mypow = 256;

    if ((row >= 0) & (row <= 7))
      layer->digVal[row] += mypow;
  }
}


void Shape::dump() {
  for (int i = 0; i < 4; i++) {
    int x = point[i].xAtTheta(RotationStep[rotationStep]);
    int y = point[i].yAtTheta(RotationStep[rotationStep]);

    int vars[] = {x, y};
    Logger::log("(x = ?, y = ?)", vars, 2);
  }
}
