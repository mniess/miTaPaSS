#ifndef SRC_NEURALENGINE_H_
#define SRC_NEURALENGINE_H_

#include <vector>
#include "src/RobotEngine.h"
#include "src/Robot.h"
#include "src/Resultor.h"
#include "bin/Config.h"

#define LAYERS 3
#define CONNECTIONS 6

using std::vector;

class NeuralEngine: public RobotEngine {
 public:
  void init(int areas, Config &conf) override;
  void nextAction(int area, int zone, Robot &rob) override;
  void train(Resultor r) override;
 private:
  int popSize = 0;
  Config conf;
  vector<vector<vector<float> > > weight;
  vector<vector<vector<float> > > newWeight;

  int output0;
  bool output1;
  float output2;

  float activation(float x);
  void propagate(int ind, float input0, float input1, float input2);
  void selectAndMutate(int maxID, Resultor res);
  void printWeights();
};
#endif  // SRC_NEURALENGINE_H_
