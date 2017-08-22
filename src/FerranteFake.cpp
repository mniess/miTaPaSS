#include "src/FerranteFake.h"
#include "src/Robot.h"

#define GO_TO_SOURCE 1;
#define RANDOM_WALK 0;
#define GO_TO_NEST -1;
void FerranteFake::nextAction(int zone, Robot &rob) {
  // Evolved controller 20
  // R1
  if (zone == 0 && rob.dir <= 0) {
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.05) {
      rob.dir = GO_TO_SOURCE;
    }
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.025) {
      rob.dir = RANDOM_WALK;
    }
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.05) {
      rob.drop = true;
    }
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.025) {
      rob.setMotivation1(false);
    }
  }
  // R2
  if (zone != 0 && rob.dir >= 0) {
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.025) {
      rob.dir = RANDOM_WALK;
    }
  }
  // R3
  if (rob.carrying) {
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.01) {
      rob.dir = GO_TO_SOURCE;
    }
  }
  // R4
  if (!rob.carrying && rob.dir >= 0) {
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.025) {
      rob.dir = GO_TO_SOURCE;
    }
  }
  // R5
  if (rob.carrying && zone != 0 && rob.getMotivation2() <= 0.5 && rob.dir >= 0) {
    rob.dir = GO_TO_NEST;
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.005) {
      rob.setMotivation1(true);
    }
  }
  // R6
  if (zone == 2 && rob.getMotivation2() <= 0.5 && rob.dir != 0) {
    rob.dir = GO_TO_SOURCE;
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.05) {
      rob.drop = true;
    }
  }
  // R7
  if (zone != 3 && rob.dir == 0) {
    if ((static_cast<double>(rand()) / (RAND_MAX)) <= 0.1) {
      rob.setMotivation2(false);
    }
  }
  // R8
  //DOES NOT APPLY
}
