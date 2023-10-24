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

	virtual sf::CircleShape drawBall() const;
	virtual void setBallPosition() const;
	virtual void firstBallMovement() ;
	virtual void ballMove(sf::CircleShape& ball);
	//virtual void setPosition();
	//virtual void collision();
	
private:

	double m_x;
	double m_y;
	sf::CircleShape m_square;

};

#endif // !DEF_BALL
