#include "Hitbox.hpp"

// For hitbox might be better to do a template for both constructor ? 

Hitbox::Hitbox(Player& player)
{
	m_boundingBox = new sf::FloatRect(player.display().getGlobalBounds());
	m_movementEntity = player.getMovement();
}

Hitbox::Hitbox(Ball& ball)
{
	m_boundingBox = new sf::FloatRect(ball.getBallShape().getGlobalBounds());
	m_movementEntity = ball.getMovement();
}

Hitbox::~Hitbox() {
	delete m_boundingBox;
}

void Hitbox::hitboxUpdate(Player& player) {
	*m_boundingBox = player.display().getGlobalBounds();
	m_movementEntity = player.getMovement();
}

void Hitbox::hitboxUpdate(Ball& ball) {
	*m_boundingBox = ball.getBallShape().getGlobalBounds();
	m_movementEntity = ball.getMovement();
}

sf::RectangleShape Hitbox::futureMovement() {
	sf::RectangleShape collision(sf::Vector2f(m_boundingBox->getSize().x, m_boundingBox->getSize().y));
	collision.setOutlineColor(sf::Color::Green);
	collision.setOutlineThickness(1.0f);
	collision.setFillColor(sf::Color::Transparent);
	collision.setPosition((sf::Vector2f(m_boundingBox->getPosition().x + m_movementEntity.x, m_boundingBox->getPosition().y + m_movementEntity.y)));

	return collision;
}
