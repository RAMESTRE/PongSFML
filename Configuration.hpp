#ifndef DEF_CONFIGURATION
#define DEF_CONFIGURATION

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
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

	void saveChange(int width, int height, int framerate, bool vsync, bool fullscreen);

	void defaultGraphicParameters();

	//Controls Methods

	void saveToFileKeys(std::string path);
	void loadFromFileKeys(std::string path);

	std::map<std::string, sf::Keyboard::Key> getControl(int player) const;

	void defaultControlsParameters();

	


private:

	//Graphic Attributes

	int m_widthWindow, m_heightWindow, m_framerate;
	bool m_vsync, m_fullscreen; 

	//Controls Attributes

	std::vector<std::string> m_playerActions;

	std::map<std::string, sf::Keyboard::Key> m_playerOneControls;
	std::map<std::string, sf::Keyboard::Key> m_playerTwoControls;


};

#endif // !DEF_CONFIGURATION
