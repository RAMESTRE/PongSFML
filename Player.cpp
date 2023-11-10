#include "Player.hpp"

Player::Player() :m_speed(1080.f), m_movement(0.f){
	m_playerShape = new sf::RectangleShape(sf::Vector2f(20.f, 100.f));
	m_playerShape->setFillColor(sf::Color::White);
	
}

Player::Player(sf::Vector2u& sizeWindow) : m_sizeWindow(sizeWindow), m_speed(sizeWindow.y), m_movement(0.f) {
	m_playerShape = new sf::RectangleShape(sf::Vector2f((m_sizeWindow.x*20.f) / 1920, (m_sizeWindow.y * 100.f) / 1080));
}

Player::~Player() {
	delete m_playerShape;
	m_playerShape = 0;
}

void Player::setPosition(sf::Vector2f positionPlayer) const {
	m_playerShape->setPosition(positionPlayer);
}

sf::RectangleShape& Player::display() {
	return *m_playerShape;
}

void Player::movePlayer(double& deltaTime,sf::Vector2u& sizeWindow){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && m_playerShape->getPosition().y > (m_sizeWindow.y*120/1080)) {
		m_movement = -m_speed * deltaTime;
		m_playerShape->move(0.f, -m_speed * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_playerShape->getPosition().y < m_sizeWindow.y - (m_sizeWindow.y *120/1080) - m_playerShape->getSize().y)
	{
		m_movement = m_speed * deltaTime;
		m_playerShape->move(0.f, m_movement);
	}
}

double Player::getMovement() const{
	return m_movement;
}