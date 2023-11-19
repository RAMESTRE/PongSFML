#ifndef DEF_CONFIGURATION
#define DEF_CONFIGURATION

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Configuration {

public:
	Configuration();
	~Configuration();

	void saveToFileGraphic(std::string path);
	void loadFromFileGraphic(std::string path);

	//void saveToFileKeys(std::string path);
	//void loadFromFileKeys(std::string path);

	void defaultGraphicParameters();

private:
	int m_widthWindow, m_heightWindow, m_framerate;
	bool m_vsync, m_fullscreen; 
};

#endif // !DEF_CONFIGURATION
