#include "Player.hpp"


Player::Player() {
	
}

Player::~Player() {}

sf::RectangleShape Player::drawPlayer() const {
	sf::RectangleShape rectangle(sf::Vector2f(10.f, 50.f));
	rectangle.setFillColor(sf::Color::White);
	return rectangle;
}

void Player::movePlayer(sf::RectangleShape& rectangle, sf::Vector2u sizeWindow) const {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && rectangle.getPosition().y > 30) {
		rectangle.move(0.f, -1.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && rectangle.getPosition().y < sizeWindow.y - 30 - rectangle.getSize().y) 
	{
		rectangle.move(0.f, 1.f);
	}
}