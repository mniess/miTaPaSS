#ifndef SRC_FERRANTEFAKE_H_
#define SRC_FERRANTEFAKE_H_

#include "RobotEngine.h"

class FerranteFake: public RobotEngine {
 public:
  Action nextAction(int location, bool item);
};
#endif  // SRC_FERRANTEFAKE_H_
