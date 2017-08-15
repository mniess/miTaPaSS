#include "src/Simulator.h"

#include <iostream>
#include <vector>

#include "bin/Config.h"

using std::vector;

Simulator::Simulator() {
}

Simulator::Simulator(Config conf) {
  setConfig(conf);
}

Simulator::~Simulator() {
}

int Simulator::setConfig(Config conf) {
  this->conf = conf;
}

int Simulator::init() {
  int width = stoi(conf.getValue(AREA_WIDTH));
  int height = stoi(conf.getValue(AREA_HEIGHT));
  int num = stoi(conf.getValue(AREA_NUM));
  int robots = stoi(conf.getValue(ROBOT_NUM));

  if (width != 0 && height != 0 && num != 0 && robots != 0) {
    return init(width, height, num, robots);
  } else {
    std::cerr << "error: a value from config is zero" << std::endl;
    return 0;
  }
}

int Simulator::init(int width, int height, int num, int robotsPerArea) {
  if (init_areas(width, height, num) && init_robots(robotsPerArea)) {
    this->inited = true;
    return 1;
  } else {
    return 0;
  }
}

int Simulator::simulate() {
  if (!inited) {
    init();
  }
  return 1;
}

int Simulator::init_areas(int width, int length, int num) {
  // unsigned int i;
  // for (i = 0; i < num; i++) {
  //   vector<vector<int>  > area(width, std::vector<int>(length, 0));
  //   areas.push_back(area);
  // }
  vector<vector<int>  > area(width, std::vector<int>(length, 0));
  areas.resize(num, area);
  return 1;
}

int Simulator::init_robots(int numberOnArea) {
  return 0;
}
