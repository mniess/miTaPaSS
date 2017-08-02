#include <iostream>

#include "config.h"

int main(int argc,char* argv[]) {
	std::string configFile = "default.cfg";
	if(argc==2){
		if( argv[1] == std::string("help") ){
			std::cout << "Usage: " << argv[0] << " [CONF-FILE]" << std::endl;
			return 0;
		} else{
			configFile = argv[1];
		}
	}
	std::cout <<"using config file '" << configFile << "'" << std::endl;
	Config conf;
	conf.readConfig(configFile);
	return 0;
}
