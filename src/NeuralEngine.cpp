#include "src/NeuralEngine.h"

#include "iostream"
#include "math.h"
#include "vector"

#include "src/Robot.h"
#include "src/Resultor.h"
#include "bin/Config.h"

using std::vector;
using std::cout, std::endl;

void NeuralEngine::init(int areas) {
  popSize = areas;
  weight =
    vector<vector<vector<float> > >(popSize,
      vector<vector<float> >(LAYERS,
        vector<float>(CONNECTIONS)));
  newWeight = vector<vector<vector<float> > >(weight);

  // random weights [-0.5;0.5]
  for (int ind=0; ind < popSize; ind++) {
    for (int j=0; j < LAYERS; j++) {
      for (int k=0; k < CONNECTIONS; k++) {
        weight[ind][j][k] = (float)rand()/(float)RAND_MAX - 0.5;
      }
    }
  }
  // TODO Load old weights
}

void NeuralEngine::nextAction(int area, int zone, Robot &rob) {
  float input0 = zone+1;
  float input1 = rob.carrying;
  float input2 = rob.getMotivation1();
  propagate(area, input0, input1, input2);
  rob.dir = output0;
  rob.drop = output1;
  rob.addMotivation1(output2);
}

void NeuralEngine::train(Resultor r) {
  int i = r.getBestArea();
  Config conf;
  conf.saveWeights("weights.txt", weight[i]);
  selectAndMutate(i, r);
}

float NeuralEngine::activation(float x) {
  return 2.0/(1.0+exp(-2.0*x))-1.0;
}


void NeuralEngine::propagate(int ind, float input0, float input1, float input2) {
  float hidden_net0, hidden_net1;
  float i_layer_0, i_layer_1, i_layer_2;
  float o_layer_0, o_layer_1, o_layer_2;
  // fprintf(stdout, "Input:  %f %f %f\n",input0,input1,input2);
  i_layer_0 = activation(input0*weight[ind][0][0]);  // -weight[ind][0][3]);
  i_layer_1 = activation(input1*weight[ind][0][1]);  // -weight[ind][0][4]);
  i_layer_2 = activation(input2*weight[ind][0][2]);  // -weight[ind][0][5]);
  // fprintf(stdout, "ILayer: %f %f %f\n",i_layer_0,i_layer_1,i_layer_2);
  hidden_net0 =
    i_layer_0*weight[ind][1][0] +
    i_layer_1*weight[ind][1][1] +
    i_layer_2*weight[ind][1][2];
  hidden_net1 =
    i_layer_0*weight[ind][1][3] +
    i_layer_1*weight[ind][1][4] +
    i_layer_2*weight[ind][1][5];
  // fprintf(stdout, "Hidden: %f %f\n",hidden_net0,hidden_net1);
  o_layer_0 =
    activation(hidden_net0)*weight[ind][2][0] +
    activation(hidden_net1)*weight[ind][2][1];
  o_layer_1 =
    activation(hidden_net0)*weight[ind][2][2] +
    activation(hidden_net1)*weight[ind][2][3];
  o_layer_2 =
    activation(hidden_net0)*weight[ind][2][4] +
    activation(hidden_net1)*weight[ind][2][5];
  // fprintf(stdout, "OLayer: %f %f %f\n",o_layer_0,o_layer_1,o_layer_2);
  output0 = static_cast<int>(round(activation(o_layer_0)));
  output1 = o_layer_1 > 0;
  output2 = activation(o_layer_2);
  // fprintf(stdout, "Out: %i %s %f\n",output0,output1?"true":"false",output2);
}

void NeuralEngine::selectAndMutate(int maxID, Resultor res) {
  float sum1 = 0.0;
  float sum2 = 0.0;
  float p[popSize], r;
  int i, j, k, ind;

  for (ind=0; ind < popSize; ind++) {
    sum1 += res.getFitness(ind);
  }

  for (ind=0; ind < popSize; ind++) {
    sum2 += res.getFitness(ind);
    p[ind] = sum2/sum1;
  }

  for (ind=0; ind < popSize; ind++) {
    if (ind == maxID) {
      // elitism:
      for (j=0; j < LAYERS; j++) {
        for (k=0; k < CONNECTIONS; k++) {
          newWeight[ind][j][k] = weight[maxID][j][k];
        }
      }
    } else {
      r = (float)rand()/(float)RAND_MAX;
      i = 0;
      while (r > p[i]) {  // choose weighted rand IND based on fitness
        i++;
      }
      for (j=0; j < LAYERS; j++) {
        for (k=0; k < CONNECTIONS; k++) {
          newWeight[ind][j][k] = weight[i][j][k];  // copy chosen IND
        }
      }
      j = rand() % LAYERS;
      k = rand() % CONNECTIONS;
      newWeight[ind][j][k] += 0.4 * (float)rand()/(float)RAND_MAX - 0.2;  // mutate a weight
    }
  }

  // Copy weights
  weight = vector<vector<vector<float>>>(newWeight);
}

void NeuralEngine::printWeights() {
  for (int ind=0; ind < weight.size(); ind++) {
    for (int j=0; j < weight[ind].size(); j++) {
      for (int k=0; k < weight[ind][j].size(); k++) {
        cout << weight[ind][j][k]<< " ";
      }
      cout << "  ";
      for (int k=0; k < weight[ind][j].size(); k++) {
        cout << newWeight[ind][j][k]<< " ";
      }
      cout << endl;
    }
    cout << endl;
  }
}
