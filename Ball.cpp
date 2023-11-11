#include "Ball.hpp"

Ball::Ball(sf::Vector2u& sizeWindow) {
	m_sizeWindow = sizeWindow;
	m_ballShape = new sf::RectangleShape(sf::Vector2f(m_sizeWindow.x*20.f/1920, m_sizeWindow.y*20.f/1080));
}

Ball::~Ball() {
	delete m_ballShape;
	m_ballShape = 0;
}

void Ball::draw(sf::RenderWindow* window) const {
	window->draw(*m_ballShape);
}

void Ball::setPosition(sf::RenderWindow* window) {
	m_ballShape->setPosition((window->getSize().x - m_ballShape->getSize().x)/2, (window->getSize().y - m_ballShape->getSize().y) / 2);
}

sf::RectangleShape Ball::getBallShape() const {
	return *m_ballShape;
}

void Ball::firstMove() {
	srand(time(NULL));
	m_spawnMoveDirection = sf::Vector2f((double)rand() / RAND_MAX * 2 - 1, (double)rand() / RAND_MAX * 2 - 1);
}

void Ball::move(double dt) {
	m_ballShape->move(m_spawnMoveDirection.x * 2160 * dt, m_spawnMoveDirection.y * 2160 * dt);
}