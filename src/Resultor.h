#ifndef SRC_RESULTOR_H_
#define SRC_RESULTOR_H_

#include <vector>

enum data { tokenInNest, tokenInNestByPartitioning, tokenOnArea};

class Resultor {
 public:
  Resultor();
  explicit Resultor(int areas);
  void byPartitioning(int area, bool increase);
  void tokenInNest(int area);
  void tokenCreated(int area);
  void step();
  std::vector<int> getResults(int area);
  void printResults();
  int getBestArea();
 private:
  std::vector<std::vector<int> > results;
};

#endif  // SRC_RESULTOR_H_
