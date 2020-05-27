#include "point.h"
#include "math.h"


Point::Point(int x, int y) {
  this->x = x;
  this->y = y;
};


//in radians
int Point::xAtTheta(float theta) {
  float s = sin(theta);
  float c = cos(theta);

  return round(x * c - y * s);
}

//in radians
int Point::yAtTheta(float theta) {
  float s = sin(theta);
  float c = cos(theta);

  return round(x * s + y * c);
}
