#include "src/Resultor.h"

#include <iostream>
#include <vector>

using std::cout, std::endl;

Resultor::Resultor() {
  Resultor(0, 0, 0);
}

Resultor::Resultor(int gen, int areas, int trys) {
  this->trys = trys;
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
  currGen++;
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
