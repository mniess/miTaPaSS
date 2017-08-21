#ifndef SRC_ACTION_H_
#define SRC_ACTION_H_

struct Action {
  int dir = 1;  // 1: move towards source, -1: towards nest, 0: random walk
  bool pickUp = false;  // if available
};

#endif  // SRC_ACTION_H_
