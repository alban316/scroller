
#ifndef POINT_H_
#define POINT_H_


class Point {
  short x;
  short y;

public:
  Point(short x, short y);
  virtual ~Point() {};

  short xAtTheta(float radians);
  short yAtTheta(float radians);
};

#endif
