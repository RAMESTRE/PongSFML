#ifndef DEF_DISPLAY_WINDOW
#define DEF_DISPLAY_WINDOW

#include <iostream>
#include <SFML/Graphics.hpp>

class DisplayWindow {

public:
	DisplayWindow();
	virtual ~DisplayWindow();
	void runWindow();

private:
	sf::RenderWindow *m_window;
	sf::Event m_event;
};


#endif // !DEF_DISPLAY_WINDOW
