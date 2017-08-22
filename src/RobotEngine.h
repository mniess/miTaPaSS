#ifndef SRC_ROBOTENGINE_H_
#define SRC_ROBOTENGINE_H_

#include "src/Robot.h"

class RobotEngine{
 public:
  virtual void nextAction(int zone, Robot &rob) = 0;
};

#endif  // SRC_ROBOTENGINE_H_
