#include "src/Resultor.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "src/Robot.h"
#include "bin/Config.h"

using std::cout, std::endl;
using std::vector;

Resultor::Resultor() {
  Resultor(Conf());
}

Resultor::Resultor(Config conf) {
  this->conf = conf;
  this->trys = stoi(conf.getValue(TIME_TRY));
  int areas = stoi(conf.getValue(AREA_NUM));
  int gen = stoi(conf.getValue(TIME_GENERATIONS));
  minGenToStepLog = stoi(conf.getValue(MINGENLOG));
  maxGenToStepLog = stoi(conf.getValue(MAXGENLOG));
  results =
    std::vector<std::vector<std::vector<int> > >(gen,
      std::vector<std::vector<int> >(areas,
        std::vector<int>(3)));
}

void Resultor::byPartitioning(int area, bool increase) {
  if (increase) {
    results[currGen][area][data::tokenInNestByPartitioning]++;
  } else {
    results[currGen][area][data::tokenInNestByPartitioning]--;
  }
}

void Resultor::tokenInNest(int area) {
  results[currGen][area][data::tokenInNest]++;
  results[currGen][area][data::tokenOnArea]--;
}

void Resultor::tokenCreated(int area) {
  results[currGen][area][data::tokenOnArea]++;
}

void Resultor::nextGen() {
  writeLog();
  ++currGen;
}

std::vector<int> Resultor::getResults(int area, int gen) {
  if (gen == -1) {
    gen = currGen;
  }
  if (area == -1) {
    area = getBestArea(gen);
  }
  return results[gen][area];
}

void Resultor::printResults(int gen) {
  if (gen == -1) {
    gen = currGen;
  }
  int bI = getBestArea(gen);
  fprintf(stdout, "Best Area with fitness %i (InNest: %f, ByPart: %f, OnArea: %f) averaged over %i runs\n",
    getFitness(bI, gen),
    static_cast<float>(results[gen][bI][data::tokenInNest])/trys,
    static_cast<float>(results[gen][bI][data::tokenInNestByPartitioning])/trys,
    static_cast<float>(results[gen][bI][data::tokenOnArea])/trys,
    trys);
}

int Resultor::getBestArea(int gen) {
  if (gen == -1) {
    gen = currGen;
  }
  int bestIndex = 0;
  int best = 0;
  for (int a = 0; a < results[gen].size(); a++) {
    if (best < getFitness(a, gen)) {
      best = getFitness(a, gen);
      bestIndex = a;
    }
  }
  return bestIndex;
}

int Resultor::getFitness(int area, int gen) {
  if (gen == -1) {
    return results[currGen][area][data::tokenInNest] + 1;
  }
  return results[gen][area][data::tokenInNest] + 1;
}

int Resultor::log(vector< vector<Robot> > robs) {
  if (currGen >= minGenToStepLog && currGen <= maxGenToStepLog) {
    vector<int> row;
    for (Robot rob : robs[0]) { // only log first area
      row.push_back(rob.getY());
      row.push_back(rob.carrying);
    }
    this->logs.push_back(row);
  }
}

int Resultor::writeLog() {
  if (currGen >= minGenToStepLog && currGen <= maxGenToStepLog) {
    cout << "writing runLog" << endl;
    std::string filename = conf.getValue(STEPSAVEFILE) + std::to_string(currGen);
    std::ofstream ofs(filename, std::ios::out|std::ios::trunc);
    if (ofs.is_open()) {
      //ofs << "step; [robot.y; robot.carrying]*" << endl;
      for (int step = 0; step < logs.size(); step++) {
        ofs << step << "; ";
        for (int val : logs[step]) {
          ofs << val << "; ";
        }
        ofs << endl;
      }
      ofs << endl;
      ofs.close();
      logs.clear();
    } else {
      std::cerr << "error opening file for write " << filename << endl;
    }
  }
}
