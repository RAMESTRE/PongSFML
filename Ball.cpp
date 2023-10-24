#include "Ball.hpp"

Ball::Ball() : m_x(0), m_y(0), m_square(20,4){

	m_square.setFillColor(sf::Color::White);
	m_square.setRotation(45.f);

};

Ball::~Ball() {};

sf::CircleShape Ball::drawBall() const{
	return m_square;
}

void Ball::firstBallMovement() {
	srand(time(NULL));
	m_x = (double)rand() / RAND_MAX *	2 - 1;
	m_y = (double)rand() / RAND_MAX * 2 - 1;
}

void Ball::ballMove(sf::CircleShape& ball) {
	ball.move(m_x, m_y);
}

void Ball::setBallPosition() const{}
