#include "point.h"
#include "math.h"


#define PI 3.14159265

Point::Point(int x, int y) {
  this->x = x;
  this->y = y;
};

void Point::rotate(int degrees) {
  float theta = Point::toRadians(degrees);
  float s = sin(theta);
  float c = cos(theta);

  int x = this->x;
  int y = this->y;

  this->x = round(x * c - y * s);
  this->y = round(x * s + y * c);
};


float Point::toRadians(int degrees) {
  return degrees * (PI/180);
}
