#include "src/Simulator.h"

#include <assert.h>

#include <iostream>
#include <algorithm>
#include <vector>

#include "bin/Config.h"
#include "src/Robot.h"
#include "src/Area.h"
#include "src/RobotEngine.h"
#include "src/FerranteFake.h"

using std::vector;
using std::cerr, std::cout, std::endl;

Simulator::Simulator() {
}

Simulator::Simulator(Config &conf) {
  setConfig(conf);
}

Simulator::~Simulator() {
  delete engine;
}

int Simulator::setConfig(Config &conf) {
  zones[0] = stoi(conf.getValue(ZONE_NEST_END));
  zones[1] = stoi(conf.getValue(ZONE_CACHE_END));
  zones[2] = stoi(conf.getValue(ZONE_SLOPE_END));
  zones[3] = stoi(conf.getValue(ZONE_SOURCE_END));
  width = stoi(conf.getValue(AREA_WIDTH));
  height = zones[3];

  num_area = stoi(conf.getValue(AREA_NUM));
  num_robot = stoi(conf.getValue(ROBOT_NUM));
  num_token = stoi(conf.getValue(TOKEN_NUM));

  time[0] = stoi(conf.getValue(TIME_TRY));
  time[1] = stoi(conf.getValue(TIME_GENERATIONS));
  time[2] = stoi(conf.getValue(TIME_RUN));

  if (conf.getValue(ENGINE) == ENGINE_FERRANTE) {
    engine = new FerranteFake();
  }

  return checkConfig();
}

bool Simulator::checkConfig() {
  if (zones[0] <= 0 || zones[1] <= 0 || zones[2] <= 0 || zones[3] <= 0 ||
      width <= 0 || num_area <= 0 || num_robot <= 0 || num_token <= 0 ||
      time[0] <= 0 || time[1] <= 0 || time[2] <= 0) {
    cerr << "error checkConfig: a parameter lowerequals zero" << endl;
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
            for (auto &rob : robots[area]) {
              step_robot(rob, area);
            }
          }
          printArea(0);
        }
        printf("Generation %i of %i finished!\n", gen+1, time[1]);
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
  for (auto &area : areas) {
    for (int t = 0; t < num_token; t++) {
      newToken(area);
    }
  }
  return 1;
}

int Simulator::init_robots(int numberOnArea) {
  Robot r(0, 0, 0, width, 0, height);
  std::vector<Robot> vr(numberOnArea, r);
  robots.resize(areas.size(), vr);
cout << areas.size() << " " << robots.size() << " " << robots[0].size() << endl;
  for (int i = 0; i < areas.size(); i++) {
    int robs = 0;
    while (robs < numberOnArea) {
      int x = rand() % width;
      int y = rand() % zones[0];
      if (hasRobotAt(i, x, y)) {
        continue;
      } else {
        robots.at(i).at(robs).setPos(x, y);
        ++robs;
      }
    }
  }
  return 1;
}

int Simulator::getZone(int y) {
  for (int i = 0; i < 4; i++) {
    if (y < zones[i]) {
      return i;
    }
  }
  return -1;
}

int Simulator::getZone(Robot &r) {
  return getZone(r.getY());
}

bool Simulator::hasRobotAt(int area, int x, int y) {
  if (robots.size() > area) {
    for (auto &rob : robots[area]) {
      if (rob.getX() == x && rob.getY() == y) {
        return true;
      }
    }
    return false;
  } else {
    cerr << "error has_robot: there is no area " << area << endl;
    return false;
  }
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
  cout << endl;
}

int Simulator::step_robot(Robot &rob, int area) {
  engine -> nextAction(getZone(rob), rob);
  if (rob.getDir() != 0) {
    if (!hasRobotAt(area, rob.getX(), rob.getY() + rob.getDir())) {
      rob.getDir() > 0 ? rob.moveForward() : rob.moveBackward();
    }
  } else {  // random walk
    int newX = rob.getX() + (rand()%2 -1);
    int newY = rob.getY() + (rand()%2 -1);
    if (!hasRobotAt(area, newX, newY)) {
      rob.setPos(newX, newY);
    }
  }

  if (rob.isCarrying() && rob.getDrop()) {
    dropItem(rob, area);
  } else if (!rob.isCarrying() && !rob.getDrop()) {
    pickUpItem(rob, area);
  }
  return 1;
}

int Simulator::dropItem(Robot &rob, int area) {
  rob.carry(false);
  int x = rob.getX();
  int y = rob.getY();
  int dropZone = getZone(y);
  if (dropZone == 2) {
    y = zones[1];
  }
  if (dropZone == 0) {
    newToken(areas[area]);
    // TODO result +1
  } else {
    ++areas[area][x][y];
  }
  return 1;
}

int Simulator::pickUpItem(Robot &rob, int area) {
  if (areas.at(area)[rob.getX()][rob.getY()] > 0) {
    rob.carry(true);
    --areas.at(area)[rob.getX()][rob.getY()];
  }
  return 1;
}

int Simulator::newToken(Area &area) {
  int x = rand() % width;
  int y = rand() % (zones[3] - zones[2]) + zones[2];
  ++area[x][y];
}
