#include "Player.hpp"

Player::Player() {
	m_playerShape = new sf::RectangleShape(sf::Vector2f(20.f, 100.f));
	m_playerShape->setFillColor(sf::Color::White);
}

Player::Player(sf::Vector2u& sizeWindow) {
	m_playerShape = new sf::RectangleShape(sf::Vector2f(sizeWindow.x/65, sizeWindow.y/5));
}

Player::~Player() {
	delete m_playerShape;
	m_playerShape = 0;
}

void Player::setPosition(sf::Vector2f positionPlayer ) const {
	
}

sf::RectangleShape& Player::display() {
	return *m_playerShape;
}