#include "point.h"
#include "shape.h"
#include "math.h"
#include "layer.h"
#include "logger.h"


Shape::Shape(Point *point) {
  this->point = point;

  y = -2; //translation (experiment)
}

void Shape::rotate(int degrees) {
  for (int i = 0; i < 4; i++) {
    this->point[i].rotate(degrees);
  }
}

Layer* Shape::toLayer() {
  Layer *layer = new Layer();

  for (int i = 0; i < 4; i++) {
    int row = 3 + this->point[i].y + this->y;  // <---vertical translation
    int col = 3 - this->point[i].x;

    int mypow = round(pow(2,col));
    layer->digVal[row] += mypow;
  }

  return layer;
}


void Shape::dump() {
  for (int i = 0; i < 4; i++) {
    int x = this->point[i].x;
    int y = this->point[i].y;

    int vars[] = {x, y};
    Logger::log("(x = ?, y = ?)", vars, 2);

  }
}
