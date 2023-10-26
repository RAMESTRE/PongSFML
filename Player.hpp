#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <SFML/Graphics.hpp>
#include "DisplayWindow.hpp"

class Player {

public:

	Player();
	Player(sf::Vector2u& sizeWindow);
	~Player();
	void setPosition(sf::Vector2f positionPlayer = sf::Vector2f(0.f, 30.f)) const;
	sf::RectangleShape& display();

private:

	sf::RectangleShape *m_playerShape;
	sf::Vector2u m_sizeWindow;

};

#endif // !DEF_PLAYER
