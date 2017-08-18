#ifndef SRC_ROBOTENGINE_H_
#define SRC_ROBOTENGINE_H_

#include "src/Action.h"
#include "src/Robot.h"

class RobotEngine{
 public:
  virtual Action nextAction(int zone, bool holding) = 0;
};

#endif  // SRC_ROBOTENGINE_H_
