#include "src/Resultor.h"

#include <iostream>
#include <vector>

using std::cout, std::endl;

Resultor::Resultor() {
  Resultor(0);
}

Resultor::Resultor(int areas) {
  results = std::vector<std::vector<int> >(areas, std::vector<int>(3));
}

void Resultor::byPartitioning(int area, bool increase) {
  if (increase) {
    results[area][data::tokenInNestByPartitioning]++;
  } else {
    results[area][data::tokenInNestByPartitioning]--;
  }
}

void Resultor::tokenInNest(int area) {
  results[area][data::tokenInNest]++;
  results[area][data::tokenOnArea]--;
}

void Resultor::tokenCreated(int area) {
  results[area][data::tokenOnArea]++;
}

std::vector<int> Resultor::getResults(int area) {
  return results[area];
}

void Resultor::printResults() {
  int bI = getBestArea();
  fprintf(stdout, "Best Area with %i token in Nest\n", results[bI][data::tokenInNest]);
}

int Resultor::getBestArea() {
  int bestIndex = 0;
  int best = 0;
  for (int a = 0; a < results.size(); a++) {
    if (best < results[a][data::tokenInNest]) {
      best = results[a][data::tokenInNest];
      bestIndex = a;
    }
  }
  if (best == 0) {
    bestIndex = rand() % results.size();
  }
  return bestIndex;
}
