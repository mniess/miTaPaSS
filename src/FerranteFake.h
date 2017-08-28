#ifndef SRC_FERRANTEFAKE_H_
#define SRC_FERRANTEFAKE_H_

#include "src/RobotEngine.h"
#include "src/Robot.h"
#include "src/Resultor.h"

class FerranteFake: public RobotEngine {
 public:
  void nextAction(int area, int zone, Robot &rob) override;
};
#endif  // SRC_FERRANTEFAKE_H_
