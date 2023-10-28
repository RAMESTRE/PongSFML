#include "Hitbox.hpp"

Hitbox::Hitbox(Player& player)
{
	m_boundingBox = new sf::FloatRect(player.display().getGlobalBounds());
	m_movementEntity = player.getMovement();
}

Hitbox::~Hitbox() {
	delete m_boundingBox;
}

void Hitbox::hitboxUpdate(Player& player) {
	*m_boundingBox = player.display().getGlobalBounds();
	m_movementEntity = player.getMovement();
}

sf::RectangleShape Hitbox::futureCollision(Hitbox& otherEntityHitbox) {
	sf::RectangleShape collision(sf::Vector2f(m_boundingBox->getSize().x, m_boundingBox->getSize().y));
	collision.setFillColor(sf::Color::Blue);
	collision.setPosition((sf::Vector2f(m_boundingBox->getPosition().x, m_boundingBox->getPosition().y + m_movementEntity*2)));
	std::cout << m_movementEntity << std::endl;

	return collision;
}