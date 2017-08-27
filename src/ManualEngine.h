#ifndef SRC_MANUALENGINE_H_
#define SRC_MANUALENGINE_H_

#include "src/RobotEngine.h"
#include "src/Robot.h"

class ManualEngine: public RobotEngine {
 public:
  void nextAction(int zone, Robot &rob);
};
#endif  // SRC_MANUALENGINE_H_
