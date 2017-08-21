#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <iostream>

class Robot {
 public:
  Robot(int x, int y, int x_min, int x_max, int y_min, int y_max) :
    x(x), y(y), x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {}

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  bool isCarrying() {
    return carrying;
  }

  void setPos(int newX, int newY) {
    if (x <= x_max && x >= x_min) {
      x = newX;
    }
    if (y <= y_max && y >= y_min) {
      y = newY;
    }
  }

  void moveForward() {
    setPos(x, y+1);
  }

  void moveBackward() {
    setPos(x, y-1);
  }

  void carry(bool c) {
    carrying = c;
  }

 private:
  int x, y;
  int x_min, x_max, y_min, y_max;
  bool carrying = false;
};

#endif  // SRC_ROBOT_H_
