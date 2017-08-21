#include "src/FerranteFake.h"
#include "src/Action.h"
#include "src/Robot.h"

Action FerranteFake::nextAction(int zone, bool holding) {
  Action res;
  res.dir = 1;
  res.pickUp = 0;
  return res;
}
