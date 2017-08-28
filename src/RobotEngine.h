#ifndef SRC_ROBOTENGINE_H_
#define SRC_ROBOTENGINE_H_

#include "src/Robot.h"
#include "src/Resultor.h"

class RobotEngine{
 public:
  virtual void init(int areas) = 0;
  virtual void nextAction(int area, int zone, Robot rob) = 0;
  virtual void train(Resultor r) = 0;
};

#endif  // SRC_ROBOTENGINE_H_
