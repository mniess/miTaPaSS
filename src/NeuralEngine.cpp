#include "src/NeuralEngine.h"

#include <string>
#include "iostream"
#include "fstream"
#include <sstream>
#include "math.h"
#include "vector"

#include "src/Robot.h"
#include "src/Resultor.h"
#include "bin/Config.h"

using std::vector;
using std::cout;
using std::endl;

void NeuralEngine::init(int areas, Config &conf) {
  popSize = areas;
  this->conf = conf;
  initWeights();
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
  saveGen(r);
  selectAndMutate(r);
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

void NeuralEngine::selectAndMutate(Resultor res) {
  int maxID = res.getBestArea(gen);
  gen++;
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
      cout << endl;
    }
    cout << endl;
  }
}


void NeuralEngine::saveGen(Resultor res) {
  std::string sf = conf.getValue(SAVEFILE);
  if (sf != NOFILE && sf != "") {
    std::ofstream ofs;
    ofs.open(sf, std::ios::out|std::ios::app);
    if (ofs.is_open()) {
      ofs << gen << "; ";
      int best = res.getBestArea();
      ofs << best << "; ";
      std::vector<int> stats = res.getResults();
      ofs << stats[0] << "; " << stats[1] << "; " << stats[2] << "; ";
      for (int i = 0; i < weight[best].size(); i++) {
        for (int j = 0; j < weight[best][i].size(); j++) {
          ofs << weight[best][i][j] << "; ";
        }
      }
      ofs << endl;
      ofs.close();
    } else {
      std::cerr << "error opening file for write " << sf << std::endl;
    }
  }
}

void NeuralEngine::initWeights() {

  if (!loadWeights()) {
    weight =
      vector<vector<vector<float> > >(popSize,
        vector<vector<float> >(LAYERS,
          vector<float>(CONNECTIONS)));
    //random weights [-0.5;0.5]
    for (int ind=0; ind < popSize; ind++) {
      for (int j=0; j < LAYERS; j++) {
        for (int k=0; k < CONNECTIONS; k++) {
          weight[ind][j][k] = (float)rand()/(float)RAND_MAX - 0.5;
        }
      }
    }
  }
  newWeight = vector<vector<vector<float> > >(weight);
}

bool NeuralEngine::loadWeights() {
  std::string lf = conf.getValue(LOADFILE);
  if (lf != NOFILE && lf != "") {
    cout << "loading weights from file " << lf << endl;
    std::ifstream ifs(lf, std::ifstream::in);

    if (ifs.is_open()) {
      vector<vector<float> > weights;
      std::string line;
      while ( std::getline(ifs, line) ) {
        vector<float> v;
        std::istringstream iss(line);
        std::string val;
        while ( std::getline(iss, val, ' ') ) {
          v.push_back(std::stof(val));
        }
        weights.push_back(v);
      }
      ifs.close();

      weight = vector<vector<vector<float> > >(popSize, weights);
      return true;
    } else {
      std::cerr << "error opening file " << lf << std::endl;
    }
  }
  return false;
}
