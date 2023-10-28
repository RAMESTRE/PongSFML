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
	void setPosition(sf::Vector2f positionPlayer = sf::Vector2f(100.f, 120.f)) const;
	sf::RectangleShape& display();
	void movePlayer(double& deltaTime) const; //To modify later for player 1 and 2 to have differents controls

private:

	sf::RectangleShape *m_playerShape;
	sf::Vector2u m_sizeWindow;
	double m_speed;

};

#endif // !DEF_PLAYER
