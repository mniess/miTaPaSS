#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>

class Config{
	public:
		simulate();
	private:
		init_areas(int number);
		step_areas();
		init_robots(int numberOnArea);
		step_robots();
		getGroundType();
};

#endif
