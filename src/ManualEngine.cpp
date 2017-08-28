#include "iostream"

#include "src/ManualEngine.h"
#include "src/Robot.h"

void ManualEngine::nextAction(int area, int zone, Robot rob) {
  if (rob.isCarrying()) {
    rob.dir = -1;
    if (zone == 0) {
      rob.drop = true;
    }
  } else {
    rob.drop = false;
    if (zone == 3) {
      rob.dir = 0;
    } else {
      rob.dir = 1;
    }
  }
  if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.1) {
    rob.dir = 0;
  }
}
