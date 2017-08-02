#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config{
	public:
		int readConfig(std::string file);
		std::string getValue(std::string key);
	private:
		int setOption(std::string key, std::string value);
};

#endif
