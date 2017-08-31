#include <gtkmm.h>
#include <time.h>

#include <iostream>
#include <string>


#include "bin/Config.h"
#include "src/Simulator.h"

using std::cout, std::endl;

int checkHelp(int argc, char* argv[]) {
  if ( argc == 2 ) {
    if ( argv[1] == std::string("-h") || argv[1] == std::string("--help") ) {
      fprintf(stdout, "%s Version %d.%d\n",
         argv[0], VERSION_MAJOR, VERSION_MINOR);
      fprintf(stdout, "Usage: %s %s\n", argv[0], "[CONF_FILE]");
      return 1;
    }
  }
  return 0;
}

int main(int argc, char* argv[]) {
  srand(time(NULL));
  if ( checkHelp(argc, argv) ) {
    return 0;
  }
  std::string configFile = "default.cfg";
  if ( argc == 2 ) {
    configFile = argv[1];
    cout << configFile;
  }

  Config conf(configFile);
  Simulator sim(conf);
  sim.simulate();

  return 0;
}
