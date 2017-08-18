#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

struct Robot {
  int x;
  int y;
  bool carrying;

  Robot(int x, int y):x(x), y(y) {}

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  bool isCarrying() {
    return carrying;
  }

  void setPos(int x, int y) {
    this->x = x;
    this->y = y;
  }

  void carry(bool c) {
    carrying = c;
  }
};

#endif  // SRC_ROBOT_H_
