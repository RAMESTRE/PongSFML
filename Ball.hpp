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
	void setPositionBall(sf::Vector2f positionAfterCollision);
	sf::RectangleShape getBallShape() const;
	void firstMove(int minAngle, int maxAngle);
	void move(double& dt);
	void changeDirection(int x, int y);
	sf::Vector2f getMovement();

private:

	sf::RectangleShape* m_ballShape;
	double m_angle;
	double m_speed;
	double m_distanceVector; //Hypothenuse
	sf::Vector2f m_movement;

	double m_directionx, m_directiony;
};

#endif // !DEF_BALL
