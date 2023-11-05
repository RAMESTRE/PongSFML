#include "Button.hpp"

Button::Button(double x, double y, double width, double height, int id, std::string textButton)
{
	m_shapeButton = sf::RectangleShape(sf::Vector2f(width, height));
	m_shapeButton.setPosition(x, y);

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}
	m_textButton.setFont(m_font);
	m_textButton.setCharacterSize(8);
	m_textButton.setString(textButton);
	m_textButton.setPosition(x, y);
	m_textButton.setFillColor(sf::Color::Black);
	m_id = id;
	m_buttonState = BTN_INACTIVE;
}

Button::~Button() {}

bool Button::isPressed() const
{
	if (m_buttonState == BTN_PRESSED) {
		return true;
	}
	return false;
}

void Button::update() 
{
	switch (m_buttonState) {
	case (BTN_INACTIVE):
		//Color, Font color, color text
		break;
	case (BTN_HOVER):

		break;
	case (BTN_PRESSED):

		break;
	default:

		break;
	}
	
}

void Button::draw(sf::RenderWindow* window) const {
	window->draw(m_shapeButton);
	window->draw(m_textButton);
}
