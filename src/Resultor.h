#ifndef SRC_RESULTOR_H_
#define SRC_RESULTOR_H_

#include <vector>
#include "src/Robot.h"

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
  int log(std::vector< std::vector<Robot> > robs);
 private:
  int minGenToLog=1990;
  int maxGenToLog=2000;
  int trys = 0;
  int currGen = 0;
  std::vector<std::vector<std::vector<int> > > results;
  std::vector<std::vector<std::vector<int> > > logs;

  int writeLog();
};

#endif  // SRC_RESULTOR_H_
