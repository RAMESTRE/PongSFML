#ifndef DEF_BALL
#define DEF_BALL

#include "SFML/Graphics.hpp"
#include <iostream>
#include <time.h>

class Ball {

public:

	Ball();
	~Ball();
	void draw(sf::RenderTarget* target) const;
	void setPosition(sf::RenderTarget* target);
	sf::RectangleShape getBallShape() const;
	void firstMove();
	void move(double& dt);
	void changeDirection(int x, int y);
	sf::Vector2f getMovement();

private:

	sf::RectangleShape* m_ballShape;
	double m_angle;
	double m_speed;
	sf::Vector2f m_movement;
};

#endif // !DEF_BALL
