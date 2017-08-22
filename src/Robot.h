#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

#include <iostream>

class Robot {
 public:
  bool carrying = false;
  bool drop = false;
  int dir = 0;

  Robot(int x, int y, int x_min, int x_max, int y_min, int y_max) :
    x(x), y(y), x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max) {}

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  void setPos(int newX, int newY) {
    if (newX <= x_max && newX >= x_min) {
      x = newX;
    }
    if (newY <= y_max && newY >= y_min) {
      y = newY;
    }
  }

  void moveForward() {
    setPos(x, y+1);
  }

  void moveBackward() {
    setPos(x, y-1);
  }


  int getDir() {
    return dir;
    }

  void setDir(int i) {
    dir = i;
  }


  bool isCarrying() {
    return carrying;
  }

  void carry(bool c) {
    if (carrying && !c) {
      drop = false;
    }
    carrying = c;
  }

  float getMotivation1() {
    return motivation1;
  }

  void setMotivation1(bool increase) {
    if (increase) {
      motivation1 += 0.1;
    } else {
      motivation1 -= 0.1;
    }
  }

  float getMotivation2() {
    return motivation2;
  }

  void setMotivation2(bool increase) {
    if (increase) {
      motivation2 += 0.1;
    } else {
      motivation2 -= 0.1;
    }
  }

  bool getDrop() {
    return drop;
  }

  void setDrop(bool d) {
    drop = d;
  }

 private:
  int x, y;
  int x_min, x_max, y_min, y_max;
  float motivation1 = 0, motivation2 = 0;
};

#endif  // SRC_ROBOT_H_
