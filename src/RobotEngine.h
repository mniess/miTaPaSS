#ifndef SRC_ROBOTENGINE_H_
#define SRC_ROBOTENGINE_H_

struct Action {
  int moveDirection = 0;
  bool pickUp = 0;
};

class RobotEngine{
 public:
  Action nextAction(int location, bool item);
};

#endif  // SRC_ROBOTENGINE_H_
