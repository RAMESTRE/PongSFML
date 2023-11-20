#include "MenuParameters.hpp"

MenuParameters::MenuParameters() {

	m_menuPlan = new sf::RenderTexture;
	m_menuPlan->create(1920, 1080);
	m_menuSprite = new sf::Sprite;

	m_tabResolution = { "854x480", "960x540", "1024x576", "1280x720", "1366x768", 
		"1600x900", "1920x1080", "2048x1152", "2560x1440", "3200x1800", "3840x2160"};

	m_indexTabRes = 0;

}

MenuParameters::~MenuParameters() {
	delete m_menuPlan;
	m_menuPlan = 0; 
	delete m_menuSprite;
	m_menuSprite = 0;
	std::cout << "MenuParameters pointer and content destroyed" << std::endl;
}

void MenuParameters::displayMenu(sf::RenderWindow* window, sf::Font font) {

	Button leftArrowRes(50.f,50.f, 10.f, 20.f,0, "<"), rightArrowRes(100.f, 50.f, 10.f, 20.f, 0, ">");

	sf::Vector2i mousePosition;
	mousePosition = sf::Mouse::getPosition(*window);

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setString(m_tabResolution[m_indexTabRes]);

	sf::FloatRect titleBox = scoreText.getGlobalBounds();
	scoreText.setOrigin(titleBox.left + titleBox.width / 2, titleBox.top + titleBox.height / 2);
	scoreText.setPosition(960, 40);

	leftArrowRes.update(mousePosition);
	if (leftArrowRes.isPressed()) {
		if (m_indexTabRes > 0) {
			m_indexTabRes -= 1;
			scoreText.setString(m_tabResolution[m_indexTabRes]);
		}
	}
	rightArrowRes.update(mousePosition);
	if (rightArrowRes.isPressed()) {
		if (m_indexTabRes < m_tabResolution.size()-1) {
			m_indexTabRes += 1;
			scoreText.setString(m_tabResolution[m_indexTabRes]);
		}
	}

	m_menuPlan->clear();
	leftArrowRes.draw(m_menuPlan);
	rightArrowRes.draw(m_menuPlan);
	m_menuPlan->draw(scoreText);
	m_menuPlan->display();

	const sf::Texture& parameterPlanUpdate = m_menuPlan->getTexture();
	*m_menuSprite = sf::Sprite(parameterPlanUpdate);
	window->draw(*m_menuSprite);

}