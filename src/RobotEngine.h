#ifndef SRC_ROBOTENGINE_H_
#define SRC_ROBOTENGINE_H_

#include "src/Robot.h"
#include "src/Resultor.h"
#include "bin/Config.h"

class RobotEngine{
 public:
  virtual void init(int areas, Config &conf) {}
  virtual void nextAction(int area, int zone, Robot &rob) = 0;
  virtual void train(Resultor r) {}
};

#endif  // SRC_ROBOTENGINE_H_
