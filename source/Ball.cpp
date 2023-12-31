#include "Ball.hpp"

Ball::Ball() {
	m_ballShape = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	m_speed = 700.f;
	m_distanceVector = 0.f;
	m_directionx = 1.f;
	m_directiony = 1.f;
}

Ball::~Ball() {
	delete m_ballShape;
	m_ballShape = 0;
}

void Ball::draw(sf::RenderTarget* target) const {
	target->draw(*m_ballShape);
}

void Ball::setPosition(sf::RenderTarget* target) {
	m_ballShape->setPosition((target->getSize().x - m_ballShape->getSize().x)/2, (target->getSize().y - m_ballShape->getSize().y) / 2);
}

void Ball::setPositionBall(sf::Vector2f positionAfterCollision) {
	m_ballShape->setPosition(positionAfterCollision);
}

sf::RectangleShape Ball::getBallShape() const {
	return *m_ballShape;
}

void Ball::firstMove(int minAngle, int maxAngle) {
	m_angle = rand() % (maxAngle - minAngle + 1) + minAngle;

	if (m_angle > 30 && m_angle < 150) m_angle += 120; // For min =0 and max = 361
	if (m_angle > 210 && m_angle < 330) m_angle += 120;

	m_angle *= 3.14 / 180; // Convert to degrees to radians
}

void Ball::move(double& dt) {
	//Point A = position balle ou 0 car pas important l'origine est la balle donc A(0,0);
	m_movement.x = m_speed * dt; //Point xB Vecteur AB
	m_movement.y = m_speed * dt; //Point yB Vecteur AB
;
	m_distanceVector = sqrt(m_movement.x * m_movement.x + m_movement.y * m_movement.y);
	m_ballShape->move(m_directionx * cos(m_angle) * m_distanceVector, m_directiony * sin(m_angle) * m_distanceVector);
}

void Ball::changeDirection(int x, int y){
	m_directionx *= x;
	m_directiony *= y;
}

sf::Vector2f Ball::getMovement() {
	return sf::Vector2f(m_directionx * cos(m_angle) * m_distanceVector, m_directiony * sin(m_angle) * m_distanceVector);
}

int Ball::getAngle() const {
	return m_angle / 3.14 * 180;
}