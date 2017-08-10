#include <iostream>
#include <string>

#include "bin/config.h"

int checkHelp(int argc, char* argv[]) {
  if ( argc == 2 ) {
    if ( argv[1] == std::string("-h") || argv[1] == std::string("--help") ) {
      fprintf(stdout, "%s Version %d.%d\n",
         argv[0], VERSION_MAJOR, VERSION_MINOR);
      fprintf(stdout, "Usage: %s %s\n", argv[0], "[CONF_FILE]");
      return 1;
    }
  }
}

int main(int argc, char* argv[]) {
  if ( checkHelp(argc, argv) ) {
    return 0;
  }
  std::string configFile = "default.cfg";
  if ( argc == 2 ) {
    configFile = argv[1];
  }
  std::cout <<"using config file '" << configFile << "'" << std::endl;
  return 0;
}
