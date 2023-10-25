#include "Player.hpp"


Player::Player():m_playerSprite(sf::Vector2f(20.f, 200.f)) {

	m_playerSprite.setFillColor(sf::Color::White);
}

Player::~Player() {}

sf::RectangleShape Player::drawPlayer() const {
	return m_playerSprite;
}

void Player::movePlayer(sf::RectangleShape& rectangle, double* deltaTime, sf::Vector2u sizeWindow, sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown) const {

	if (sf::Keyboard::isKeyPressed(keyUp) && rectangle.getPosition().y > 80) {
		rectangle.move(0.f, -1080.f * *deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(keyDown) && rectangle.getPosition().y < sizeWindow.y - 80 - rectangle.getSize().y) 
	{
		rectangle.move(0.f, 1080.f * *deltaTime);
	}

}

void Player::playerSetPosition(sf::Vector2f& playerPosition, sf::RectangleShape& player) const {
	player.setPosition(playerPosition);
}

