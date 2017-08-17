#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include <string>
#include <vector>
#include <mutex>

#include "bin/Config.h"

struct Area{
  std::vector< std::vector< int > > area;
  std::mutex area_mutex;
  Area(int width, int length) {
    std::vector< std::vector< int > > a(width, std::vector<int>(length, 0));
    area = a;
  }

  Area& operator=(const Area &a) {
    if (this == &a) {
      return *this;
    }
    area = a.area;
    return *this;
  }

  Area(const Area &a) {
    if (this == &a) {
      return;
    }
    area = a.area;
  }


  std::vector< int > operator[](const int i) {
    std::lock_guard<std::mutex> lock(area_mutex);
    return area[i];
  }

  const std::vector< int > operator[](const int i) const{
    return area[i];
  }
};

struct Robot {
  int x;
  int y;
  bool carrying;

  int[] getPos() {
    return [x, y];
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

  bool isCarrying() {
    return carrying;
  }

  void setPos(x, y) {
    this->x = x;
    this->y = y;
  }

  void carry(bool c) {
    carrying = c;
  }
}

class Simulator{
 public:
  Simulator();
  explicit Simulator(Config conf);

  ~Simulator();
  int init();
  int init(int width, int length, int num, int robotsPerArea);
  int simulate();
 private:
  bool inited;
  Config conf;
  std::vector< Area > areas;

  int setConfig(Config conf);
  int init_areas(int width, int length, int num);
  int step_areas();
  int init_robots(int numberOnArea);
  int step_robots();
  int getGroundType();
};

#endif  // SRC_SIMULATOR_H_
