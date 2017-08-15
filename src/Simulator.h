#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include <string>
#include <vector>

#include "bin/Config.h"

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
  std::vector< std::vector< std::vector< int > > > areas;

  int setConfig(Config conf);
  int init_areas(int width, int length, int num);
  int step_areas();
  int init_robots(int numberOnArea);
  int step_robots();
  int getGroundType();
};

#endif  // SRC_SIMULATOR_H_
