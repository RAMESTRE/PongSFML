#ifndef DEF_CONFIGURATION
#define DEF_CONFIGURATION

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sys/stat.h>
#include <direct.h>
#include <SFML/Graphics.hpp>

class Configuration {

public:
	Configuration();
	~Configuration();

	//Graphics Methods

	void saveToFileGraphic(std::string path);
	void loadFromFileGraphic(std::string path);

	sf::VideoMode getSizeWindow() const;
	int getFramerate() const;
	bool getVSync() const;
	bool getFullscreen() const;

	void saveChange(int width, int height, int framerate, bool vsync, bool fullscreen, std::map<std::string, sf::Keyboard::Scancode> p1, std::map<std::string, sf::Keyboard::Scancode> p2);

	void defaultGraphicParameters();

	//Controls Methods

	void saveToFileKeys(std::string path);
	void loadFromFileKeys(std::string path);

	std::map<std::string, sf::Keyboard::Scancode> getControl(int player) const;

	void defaultControlsParameters();

private:

	bool correctResolutionSetting(std::string res);
	void checkResolutionBelowMax();
	bool correctFramerateSetting(std::string framerate);
	void configFolderExist();

	//Graphic Attributes

	int m_widthWindow, m_heightWindow, m_framerate;
	bool m_vsync, m_fullscreen; 

	//Controls Attributes

	std::map<std::string, sf::Keyboard::Scancode> m_playerOneControls;
	std::map<std::string, sf::Keyboard::Scancode> m_playerTwoControls;


};

#endif // !DEF_CONFIGURATION
