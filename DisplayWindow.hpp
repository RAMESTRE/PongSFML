#ifndef DEF_DISPLAY_WINDOW
#define DEF_DISPLAY_WINDOW

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Hitbox.hpp"
#include "Button.hpp"
#include "Render.hpp"

class DisplayWindow {

public:
	DisplayWindow();
	virtual ~DisplayWindow();
	void runWindow();
	double getDeltaTime() const;

private:
	sf::RenderWindow *m_window;
	sf::Event m_event;
	double* m_deltaTime;
};


#endif // !DEF_DISPLAY_WINDOW
