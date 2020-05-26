#include "point.h"
#include "shape.h"
#include "math.h"
#include "layer.h"
#include "logger.h"


Shape::Shape(Point *point) {
  this->point = point;
}

void Shape::rotate(int degrees) {
  for (int i = 0; i < 4; i++) {
    this->point[i].rotate(degrees);
  }
}

Layer* Shape::toLayer() {
  Layer *layer = new Layer();

  for (int i = 0; i < 4; i++) {
    int row = 3 + this->point[i].y;
    int col = 3 - this->point[i].x;

    // since when is pow(2,3) = 7????
    int mypow = round(pow(2,col)); // just for logging
    //int vars[] = {row, col, mypow }; // just for logging
    //Logger::log("row = ?, col = ?, pow = ?", vars, 3); 

    layer->digVal[row] += mypow; //pow(2,col);
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
