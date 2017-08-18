#include "src/Simulator.h"

#include <assert.h>

#include <iostream>
#include <algorithm>
#include <vector>

#include "bin/Config.h"
#include "src/Action.h"
#include "src/Robot.h"
#include "src/Area.h"
#include "src/RobotEngine.h"
#include "src/FerranteFake.h"

using std::vector;
using std::cerr, std::cout, std::endl;

Simulator::Simulator() {
}

Simulator::Simulator(Config conf) {
  setConfig(conf);
}

Simulator::~Simulator() {
}

int Simulator::setConfig(Config conf) {
  zones[0] = stoi(conf.getValue(ZONE_NEST_END));
  zones[1] = stoi(conf.getValue(ZONE_CACHE_END));
  zones[2] = stoi(conf.getValue(ZONE_SLOPE_END));
  zones[3] = stoi(conf.getValue(ZONE_SOURCE_END));
  width = stoi(conf.getValue(AREA_WIDTH));
  height = zones[3];

  num_area = stoi(conf.getValue(AREA_NUM));
  num_robot = stoi(conf.getValue(ROBOT_NUM));

  time[0] = stoi(conf.getValue(TIME_TRY));
  time[1] = stoi(conf.getValue(TIME_GENERATIONS));
  time[2] = stoi(conf.getValue(TIME_RUN));

  if (conf.getValue(ENGINE) == ENGINE_FERRANTE) {
    engine = new FerranteFake();
  }

  return checkConfig();
}

bool Simulator::checkConfig() {
  if (zones[0] == 0 || zones[1] == 0 || zones[2] == 0 || zones[3] == 0 ||
      width == 0 || num_area == 0 || num_robot == 0 ||
      time[0] == 0 || time[1] == 0 || time[2] == 0) {
    cerr << "error checkConfig: a parameter is zero" << endl;
    return false;
  }

  if (zones[0] > zones[1] ||
      zones[1] > zones[2] ||
      zones[2] > zones[3]) {
    cerr << "error checkConfig: order of zones not correct" << endl;
    return false;
  }

  if (num_robot > zones[0]*width) {
    cerr << "error checkConfig: too much robots; cannot be fit in nest" << endl;
    return false;
  }

  if (engine == NULL) {
    cerr << "error checkConfig: no engine found" << endl;
    return false;
  }
  return true;
}

int Simulator::init() {
  cout << "Init Simulation" << endl;
  inited = false;
  if (init_areas(width, height, num_area) && init_robots(num_robot)) {
    inited = true;
    printArea(0);
  }
  return inited;
}

int Simulator::simulate() {
  if (inited || init()) {
    cout << "Simulating" << endl;
    for (int t = 0; t < time[0]; t++) {
      for (int gen = 0; gen < time[1]; gen++) {
        for (int run = 0; run < time[2]; run++) {
          for (int area = 0; area < num_area; area++) {
            step_robot(area);
            step_area(area);
          }
        }
        // printf("Generation %i of %i finished!\n", gen+1, time[1]);
      }
      printf("Try %i of %i finished!\n", t+1, time[0]);
    }
  } else {
    cerr << "error simulate: could not init" << endl;
    return 0;
  }
  return 1;
}

int Simulator::init_areas(int width, int length, int num) {
  Area area(width, length);
  areas.resize(num, area);
  return 1;
}

int Simulator::init_robots(int numberOnArea) {
  for (int i = 0; i < areas.size(); i++) {
    std::vector<Robot> r;
    robots.push_back(r);
    int robs = 0;
    while (robs < numberOnArea) {
      int x = rand() % width;
      int y = rand() % zones[0];
      if (hasRobotAt(i, x, y)) {
        continue;
      } else {
        Robot r(x, y);
        robots[i].push_back(r);
        ++robs;
      }
    }
    return 1;
  }
}

int Simulator::getZone(int x) {
  for (int i = 0; i < 4; i++) {
    if (x < zones[i]) {
      return i;
    }
  }
  return -1;
}

int Simulator::getZone(Robot r) {
  return getZone(r.getX());
}

bool Simulator::hasRobotAt(int area, int x, int y) {
  if (robots.size() > 0) {
    for (auto rob : robots[area]) {
      if (rob.getX() == x && rob.getY() == y)
        return true;
    }
  }
  return false;
}

void Simulator::printArea(int index) {
  Area a = areas.at(index);
  int old = 0;
  for (int i = 0; i < height; i++) {
    int n = getZone(i);
    if (n == old) {
      cout << " " << n;
    } else {
      old = n;
      cout << "|" << n;
    }
  }
  cout << endl;
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      if (hasRobotAt(index, i, j)) {
        cout << " *";
      } else {
        cout << " " << a[i][j];
      }
    }
    cout << endl;
  }
}

int Simulator::step_robot(int area) {
  for (auto rob : robots[area]) {
    Action a = engine->nextAction(getZone(rob), rob.isCarrying());
  }
}

int Simulator::step_area(int area) {
  Area a = areas[area];
}
