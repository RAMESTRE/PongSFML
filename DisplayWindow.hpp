#ifndef DEF_DISPLAY_WINDOW
#define DEF_DISPLAY_WINDOW

#include <iostream>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "Render.hpp"
#include "Configuration.hpp"

class DisplayWindow {

public:
	DisplayWindow();
	virtual ~DisplayWindow();
	void runWindow();
	double getDeltaTime() const;

	void getNewSettings();

private:

	sf::RenderWindow *m_window;
	sf::Event m_event;
	double* m_deltaTime;

	//Property Window
	Configuration configFile;

	sf::VideoMode m_sizeWindow;
	int m_framerate;
	bool m_vsync, m_fullscreen;

	std::map<std::string, sf::Keyboard::Key> m_playerOneControls;
	std::map<std::string, sf::Keyboard::Key> m_playerTwoControls;

};


#endif // !DEF_DISPLAY_WINDOW
