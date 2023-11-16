#include "Player.hpp"

Player::Player() :m_speed(2160.f), m_movement(sf::Vector2f(0.f,0.f)){ //Unused Constructor
	m_playerShape = new sf::RectangleShape(sf::Vector2f(20.f,400.f));
	m_playerShape->setFillColor(sf::Color::White);
	
}

Player::Player(sf::Vector2u& sizeWindow) : m_sizeWindow(sizeWindow), m_speed(sizeWindow.y), m_movement(sf::Vector2f(0.f, 0.f)) { // Problem when change size before the actual game ==> Need to only get the first time the window size is initialized
	m_playerShape = new sf::RectangleShape(sf::Vector2f((m_sizeWindow.x * 20.f) / 1920, (m_sizeWindow.y * 100.f) / 1080));
}

Player::~Player() {
	delete m_playerShape;
	m_playerShape = 0;
}

void Player::setPosition(sf::Vector2f positionPlayer) const {
	m_playerShape->setPosition(sf::Vector2f(positionPlayer.x, positionPlayer.y));
}

sf::RectangleShape& Player::display() {
	return *m_playerShape;
}

void Player::movePlayer(double& deltaTime){

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && m_playerShape->getPosition().y > (120)) {
		m_movement.y = -m_speed * deltaTime;
		m_playerShape->move(0.f, m_movement.y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_playerShape->getPosition().y < 1080 - 120 - m_playerShape->getSize().y)
	{
		m_movement.y = m_speed * deltaTime;
		m_playerShape->move(0.f, m_movement.y);
	}
	else {
		m_movement.y = 0;
	}
}

sf::Vector2f Player::getMovement() const{
	return m_movement;
}