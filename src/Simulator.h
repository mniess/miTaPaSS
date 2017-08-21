#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include <string>
#include <vector>

#include "bin/Config.h"
#include "src/Area.h"
#include "src/Robot.h"
#include "src/RobotEngine.h"

class Simulator{
 public:
  Simulator();
  explicit Simulator(Config &conf);

  ~Simulator();
  int init();
  int init(int width, int length, int num, int robotsPerArea);
  int simulate();

 private:
  bool inited = false;
  int width = 0, height = 0;
  int num_area = 0, num_robot = 0;
  int zones[4];
  int time[3];

  RobotEngine *engine = NULL;
  std::vector< Area > areas;
  std::vector< std::vector<Robot> > robots;

  int setConfig(Config &conf);
  bool checkConfig();
  int init_areas(int width, int length, int num);
  int init_robots(int numberOnArea);

  int step_robot(Robot &rob, int area);
  int dropItem(Robot &rob, int area);
  int pickUpItem(Robot &rob, int area);

  int getZone(int x);
  int getZone(Robot &r);
  bool hasRobotAt(int areaIndex, int x, int y);

  void printArea(int index);
};

#endif  // SRC_SIMULATOR_H_
