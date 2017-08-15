#include <gtkmm.h>

#include <iostream>
#include <string>

#include "bin/Config.h"
#include "src/Simulator.h"
#include "src/Visualization.h"

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

int createVisualization() {
  std::cout << "Starting GUI" << std::endl;
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create("miTaPaSS");

  Gtk::Window window;

  window.set_default_size(400, 200);
  window.set_title("miTaPaSS");

  Visualization area;
  window.add(area);
  area.show();
  return app->run(window);
}

int main(int argc, char* argv[]) {
  if ( checkHelp(argc, argv) ) {
    return 0;
  }
  std::string configFile = "default.cfg";
  if ( argc == 2 ) {
    configFile = argv[1];
  }

  Config conf(configFile);
  Simulator sim(conf);

  createVisualization();
  std::cout << "Simulating" << std::endl;
  if (sim.simulate()) {
    return 0;
  } else {
    return 1;
  }
}
