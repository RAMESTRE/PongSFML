#include "Ball.hpp"

Ball::Ball() : m_x(0), m_y(0), m_square(sf::Vector2f(25, 25)) {

	m_square.setFillColor(sf::Color::White);

};

Ball::~Ball() {};

sf::RectangleShape Ball::drawBall() const{
	return m_square;
}

void Ball::firstBallMovement() {
	srand(time(NULL));
	m_x = (double)rand() / RAND_MAX *	2 - 1;
	m_y = (double)rand() / RAND_MAX * 2 - 1;
}

void Ball::ballMove(sf::RectangleShape& ball, double* deltaTime) {
	ball.move(m_x* 2160.f * *deltaTime, m_y *  2160.f  * *deltaTime);
}

void Ball::ballWindowCollision(double x, double y) {
	m_x *= x;
	m_y *= y;
}

void Ball::setBallPosition() const{
	
}
