#ifndef DEF_BALL
#define DEF_BALL

#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>

class Ball {

public:

	Ball(sf::Vector2u& sizeWindow);
	~Ball();
	void draw(sf::RenderWindow* window) const;
	void setPosition(sf::RenderWindow* window);
	sf::RectangleShape getBallShape() const;
	void firstMove();
	void move(double dt);

private:
	sf::Vector2u m_sizeWindow;

	sf::RectangleShape* m_ballShape;
	sf::Vector2f m_spawnMoveDirection;
};

#endif // !DEF_BALL
