#ifndef SRC_FERRANTEFAKE_H_
#define SRC_FERRANTEFAKE_H_

#include "src/RobotEngine.h"
#include "src/Robot.h"

class FerranteFake: public RobotEngine {
 public:
  void nextAction(int zone, Robot &rob);
};
#endif  // SRC_FERRANTEFAKE_H_
