#ifndef SRC_RESULTOR_H_
#define SRC_RESULTOR_H_

#include <vector>

enum data { tokenInNest, tokenInNestByPartitioning, tokenOnArea};

class Resultor {
 public:
  Resultor();
  Resultor(int gen, int areas, int trys);
  void byPartitioning(int area, bool increase);
  void tokenInNest(int area);
  void tokenCreated(int area);
  void nextGen();
  std::vector<int> getResults(int area = -1, int gen = -1);
  void printResults(int gen = -1);
  int getBestArea(int gen = -1);
  int getFitness(int area, int gen = -1);
 private:
  int trys = 0;
  int currGen = 0;
  std::vector<std::vector<std::vector<int> > > results;
};

#endif  // SRC_RESULTOR_H_
