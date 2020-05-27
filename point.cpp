#include "point.h"
#include "math.h"


Point::Point(short x, short y) {
  this->x = x;
  this->y = y;
};


//in radians
short Point::xAtTheta(float theta) {
  float s = sin(theta);
  float c = cos(theta);

  return round(x * c - y * s);
}

//in radians
short Point::yAtTheta(float theta) {
  float s = sin(theta);
  float c = cos(theta);

  return round(x * s + y * c);
}
