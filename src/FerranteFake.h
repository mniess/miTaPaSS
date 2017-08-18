#ifndef SRC_FERRANTEFAKE_H_
#define SRC_FERRANTEFAKE_H_

#include "src/RobotEngine.h"
#include "src/Action.h"
#include "src/Robot.h"

class FerranteFake: public RobotEngine {
 public:
  Action nextAction(int zone, bool holding);
};
#endif  // SRC_FERRANTEFAKE_H_
