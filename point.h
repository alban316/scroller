
#ifndef POINT_H_
#define POINT_H_


class Point {
public:
  Point(int x, int y);
  virtual ~Point() {};
  void rotate(int degrees);

  static float toRadians(int degrees);

  int x;
  int y;
};

#endif
