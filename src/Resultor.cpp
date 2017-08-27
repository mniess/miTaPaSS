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
  cout << area << " " << results.size() << std::flush;
  results[area][data::tokenOnArea]++;
}

std::vector<int> Resultor::getResults(int area) {
  return results[area];
}

void Resultor::printResults(int area) {
  cout << "Token in Nest:" << results[area][data::tokenInNest] << endl;
  cout << "Token by partitinoning: " << results[area][data::tokenInNestByPartitioning] << endl;
  cout << "Token on Area:" << results[area][data::tokenOnArea] << endl;
}