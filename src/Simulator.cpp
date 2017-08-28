#include "src/Simulator.h"

#include <assert.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#include "bin/Config.h"
#include "src/Robot.h"
#include "src/Area.h"
#include "src/RobotEngine.h"
#include "src/FerranteFake.h"
#include "src/ManualEngine.h"
#include "src/NeuralEngine.h"
#include "src/Resultor.h"

using std::vector, std::string;
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
  this->conf = conf;
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

  string s = conf.getValue(ENGINE);
  if (s == ENGINE_FERRANTE) {
    engine = new FerranteFake();
  } else if (s == ENGINE_MANUAL) {
    engine = new ManualEngine();
  } else if (s == ENGINE_NEURAL) {
    engine = new NeuralEngine();
  }

  s = conf.getValue(VISUALIZATION);
  if (s == VIZ_NONE) {
    visualize = 0;
  } else if (s == VIZ_ANIMATE) {
    visualize = 1;
  } else if (s == VIZ_MANUAL) {
    visualize = 2;
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
  res = Resultor(time[1], num_area);
  init_areas(width, height, num_area);
  init_robots(num_robot);
  return 1;
}

int Simulator::simulate() {
  cout << "\e[2J";
    for (int t = 0; t < time[0]; t++) {
      engine ->init(num_area, conf);
      for (int gen = 0; gen < time[1]; gen++) {
        init();
        for (int run = 0; run < time[2]; run++) {
          for (int area = 0; area < num_area; area++) {
            for (auto &rob : robots[area]) {
              step_robot(rob, area);
            }
          }
          if (visualize) {
            viz(run, 0);
          }
        }
        printf("Generation %i of %i finished!\n", gen+1, time[1]);
        res.printResults();
        engine->train(res);
        res.nextGen();
      }
      printf("Run %i of %i finished!\n", t+1, time[0]);
    }
  return 1;
}

int Simulator::init_areas(int width, int length, int num) {
  Area area(width, length);
  areas.resize(num, area);
  for (int a = 0; a < num_area; a++) {
    for (int t = 0; t < num_token; t++) {
      newToken(a);
    }
  }
  return 1;
}

int Simulator::init_robots(int numberOnArea) {
  robots = std::vector<std::vector<Robot> >(areas.size(), std::vector<Robot>(numberOnArea, Robot(0, 0, 0, width, 0, height)));
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
  engine -> nextAction(area, getZone(rob), rob);
  if (rob.getDir() != 0) {
    if (!hasRobotAt(area, rob.getX(), rob.getY() + rob.getDir())) {
      rob.getDir() > 0 ? rob.moveForward() : rob.moveBackward();
    }
  } else {  // random walk
    int newX = rob.getX() + (rand()%3 -1);
    int newY = rob.getY() + (rand()%3 -1);
    if (!hasRobotAt(area, newX, newY)) {
      rob.setPos(newX, newY);
    }
  }

  if (rob.isCarrying() && rob.getDrop()) {
    dropItem(rob, area);
  } else if (!rob.isCarrying() && !rob.getDrop()) {
    pickUpItem(rob, area);
  }
  rob.drop = false;
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
    res.tokenInNest(area);
    newToken(area);
  } else {
    ++areas[area][x][y];
  }
  return 1;
}

int Simulator::pickUpItem(Robot &rob, int area) {
  if (areas.at(area)[rob.getX()][rob.getY()] > 0) {
    rob.carry(true);
    --areas.at(area)[rob.getX()][rob.getY()];
    if (getZone(rob) == 2) {
      res.byPartitioning(area, true);
    }
  }
  return 1;
}

int Simulator::newToken(int area) {
  int x = rand() % width;
  int y = rand() % (zones[3] - zones[2]) + zones[2];
  ++areas[area][x][y];
  res.tokenCreated(area);
}

int Simulator::viz(int step, int area) {
  cout << "\e[0;0H";  // Set pos to 0,0
  cout << "Gen: " << step << endl;
  Area a = areas.at(area);
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
      if (hasRobotAt(area, i, j)) {
        cout << " *";
      } else {
        cout << " " << a[i][j];
      }
    }
    cout << endl;
  }

  for (auto &rob : robots[area]) {
    cout << rob;
  }
  res.printResults();
  if (visualize == 2) {
    std::cin.get();
  }

  return 1;
}
