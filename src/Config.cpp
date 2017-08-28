#include "bin/Config.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

Config::Config() {
}

Config::Config(std::string configFile) {
  readConfig(configFile);
}

int Config::setOption(std::string key, std::string value) {
  std::cout << key << "=" << value << std::endl;
  values[key] = value;
  return 1;
}

std::string Config::getValue(std::string key) {
  return values[key];
}

int Config::readConfig(std::string file) {
  std::cout <<"using config file '" << file << "'" << std::endl;

  std::ifstream ifs(file, std::ifstream::in);
  if (ifs.is_open()) {
    std::string line;
    while ( std::getline(ifs, line) ) {
      std::istringstream iss(line);
      std::string key;
      if ( std::getline(iss, key, '=') ) {
        std::string value;
        if ( std::getline(iss, value) ) {
          setOption(key, value);
        }
      }
    }
    ifs.close();
    return 1;
  } else {
    std::cerr << "error opening configfile" << std::endl;
    return 0;
  }
}

int Config::saveWeights(std::string filename, vector<vector<float> > weights) {
  std::ofstream ofs;
  ofs.open(filename, std::ios::out|std::ios::trunc);
  if (ofs.is_open()) {
    for (int i = 0; i < weights.size(); i++) {
      for (int j = 0; j < weights[i].size(); j++) {
        ofs << weights[i][j] << " ";
      }
      ofs << std::endl;
    }
    ofs.close();
    return 1;
  } else {
    std::cerr << "error opening configfile" << std::endl;
    return 0;
  }


}
vector<vector<float> > Config::loadWeights(std::string file) {

}
