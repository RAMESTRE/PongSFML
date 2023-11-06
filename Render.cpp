#include "Render.hpp"

Render::Render() {

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

}

Render::~Render() {}

void Render::startMenu(sf::RenderWindow* window) {

	double xWindowSize = window->getSize().x;
	double yWindowSize = window->getSize().y;

	sf::Text title, playButton, optionButton, quitButton;

	title.setFont(m_font);
	title.setString("PONG");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	title.setPosition(xWindowSize/2, yWindowSize/10);

	window->draw(title);
}

void Render::pongGame() {

}

void Render::replayMenu() {

}