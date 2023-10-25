#ifndef DEF_BALL
#define DEF_BALL

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

class Ball {

public:

	Ball();
	virtual ~Ball();

	virtual sf::RectangleShape drawBall() const;
	virtual void setBallPosition() const;
	virtual void firstBallMovement() ;
	virtual void ballMove(sf::RectangleShape& ball, double* deltaTime);
	virtual void ballWindowCollision(double x, double y);
	//virtual void setPosition();
	//virtual void collision();
	
private:

	double m_x;
	double m_y;
	sf::RectangleShape m_square;

};

#endif // !DEF_BALL
