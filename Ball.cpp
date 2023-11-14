#include "Ball.hpp"

Ball::Ball() {
	m_ballShape = new sf::RectangleShape(sf::Vector2f(20.f, 20.f));
	m_speed = 1000.f;
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

sf::RectangleShape Ball::getBallShape() const {
	return *m_ballShape;
}

void Ball::firstMove() {
	srand(time(NULL));
	m_angle = rand() % 361;
}

void Ball::move(double& dt) {
	//Point A = position balle ou 0 car pas important l'origine est la balle donc A(0,0);
	m_movement.x = m_speed * dt; //Point xB Vecteur AB
	m_movement.y = m_speed * dt; //Point yB Vecteur AB
	//std::cout << m_angle << std::endl;
	double hypothenuse = sqrt(m_movement.x * m_movement.x + m_movement.y * m_movement.y);
	//std::cout << hypothenuse << std::endl;
	//std::cout << cos(m_angle) << std::endl;
	//std::cout << sin(m_angle) << std::endl;
	//std::cout << cos(m_angle) * hypothenuse << std::endl;
	//std::cout << sin(m_angle) * hypothenuse << std::endl;
	//std::cout << m_movement.x << std::endl;
	//std::cout << m_movement.y << std::endl;
	m_ballShape->move(cos(m_angle) * hypothenuse, sin(m_angle) * hypothenuse); //speed = 2160
}

void Ball::changeDirection(int x, int y){
	m_angle = 0;
}

sf::Vector2f Ball::getMovement() {
	return sf::Vector2f(m_movement.x, m_movement.y);
}