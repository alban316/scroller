
#ifndef POINT_H_
#define POINT_H_


class Point {
  int x;
  int y;

public:
  Point(int x, int y);
  virtual ~Point() {};

  static float toRadians(int degrees);

  int xAtTheta(float radians);
  int yAtTheta(float radians);
};

#endif
