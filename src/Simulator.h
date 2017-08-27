#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include <string>
#include <vector>

#include "bin/Config.h"
#include "src/Area.h"
#include "src/Robot.h"
#include "src/RobotEngine.h"
#include "src/Resultor.h"

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
  int num_area = 0, num_robot = 0, num_token = 0;
  int zones[4];
  int time[3];
  int visualize = 0;

  RobotEngine *engine = NULL;
  Resultor res;
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
  int newToken(int areaIndex);

  void printArea(int index);
  int viz(int index, int area);
};

#endif  // SRC_SIMULATOR_H_
