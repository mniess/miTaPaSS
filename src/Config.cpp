#include "bin/Config.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int Config::setOption(std::string key, std::string value) {
  std::cout << key << "=" << value << std::endl;
  return 1;
}

std::string Config::getValue(std::string key) {
  return "";
}

int Config::readConfig(std::string file) {
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
    std::perror("error opening file");
    return 0;
  }
}
