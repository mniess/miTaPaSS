#ifndef SRC_SIMULATOR_H_
#define SRC_SIMULATOR_H_

#include <string>

class Simulator{
 public:
  simulate();
 private:
  init_areas(int number);
  step_areas();
  init_robots(int numberOnArea);
  step_robots();
  getGroundType();
};

#endif  // SRC_SIMULATOR_H_
