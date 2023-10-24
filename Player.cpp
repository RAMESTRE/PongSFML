#include "Player.hpp"


Player::Player() {
	
}

Player::~Player() {}

sf::RectangleShape Player::drawPlayer() const {
	sf::RectangleShape rectangle(sf::Vector2f(10.f, 50.f));
	rectangle.setFillColor(sf::Color::White);
	return rectangle;
}

void Player::movePlayer(sf::RectangleShape& rectangle, sf::Vector2u sizeWindow, sf::Keyboard::Key keyUp, sf::Keyboard::Key keyDown) const {

	if (sf::Keyboard::isKeyPressed(keyUp) && rectangle.getPosition().y > 30) {
		rectangle.move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(keyDown) && rectangle.getPosition().y < sizeWindow.y - 30 - rectangle.getSize().y) 
	{
		rectangle.move(0.f, 1.f);
	}

}

void Player::playerSetPosition(sf::Vector2f& playerPosition, sf::RectangleShape& player) const {
	player.setPosition(playerPosition);
}