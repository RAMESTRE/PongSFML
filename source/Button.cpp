#include "Button.hpp"

Button::Button(double x, double y, double width, double height, int id, int size, std::string textButton)
{
	m_textButtonString = textButton;

	m_shapeButton = sf::RectangleShape(sf::Vector2f(width, height));
	m_hitboxButton = m_shapeButton.getGlobalBounds();
	m_shapeButton.setOrigin(m_hitboxButton.left + m_hitboxButton.width / 2, m_hitboxButton.top + m_hitboxButton.height / 2);
	m_shapeButton.setPosition(x, y); 
	m_shapeButton.setFillColor(sf::Color::Transparent);

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "ERROR" << std::endl;
	}

	m_textButton.setFont(m_font);
	m_textButton.setCharacterSize(size);
	m_textButton.setString(textButton);
	m_hitboxText = m_textButton.getGlobalBounds();
	
	m_textButton.setOrigin(m_hitboxText.left + m_hitboxText.width / 2, m_hitboxText.top + m_hitboxText.height / 2 );
	m_textButton.setPosition(x, y);
	m_id = id;
	m_buttonState = BTN_INACTIVE;
}

Button::~Button() {
}

bool Button::isPressed() const
{
	if (m_buttonState == BTN_RELEASED) {
		return true;
	}
	return false;
}

void Button::update(sf::Vector2i& mousePosition)
{
	if (m_buttonState == BTN_PRESSED) {
		if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			m_buttonState = BTN_RELEASED;
		}
	}
	else {
		m_buttonState = BTN_INACTIVE;

		m_hitboxButton = m_shapeButton.getGlobalBounds();

		if (m_hitboxButton.contains(sf::Vector2f(mousePosition))) {

			m_buttonState = BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				m_buttonState = BTN_PRESSED;
			}

		}
	}
	

	setStyle();
	
}

void Button::setStyle() {

	//ID 0 = Basic buttons like start game
	//ID 1 = Settings buttons with hook as text
	//ID 2 = Keybinds buttons

	switch (m_buttonState)
	{
	case (BTN_INACTIVE):
		m_shapeButton.setFillColor(sf::Color::Transparent);
		m_textButton.setFillColor(sf::Color::White);
		m_textButton.setStyle(sf::Text::Regular);

		m_textButton.setString(m_textButtonString);

		if (m_id == 2) {
			m_shapeButton.setOutlineColor(sf::Color::White);
			m_shapeButton.setOutlineThickness(1.0f);
		}

		break;

	case (BTN_HOVER):

		if (m_id == 0) {
			m_textButton.setString("> " + m_textButtonString + " <");
		}
		break;

	case (BTN_PRESSED):
		m_textButton.setStyle(sf::Text::Bold);

		break;

	case (BTN_RELEASED):
		m_textButton.setStyle(sf::Text::Regular);

		break;
	default:

		break;
	}

	if (m_id == 0 || m_id == 2) {
		m_hitboxText = m_textButton.getGlobalBounds();

		m_textButton.setOrigin(m_hitboxText.width / 2, m_textButton.getOrigin().y);
	}
	
}

void Button::update(sf::Vector2f& mousePosition)
{
	if (m_buttonState == BTN_PRESSED) {
		if (!(sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
			m_buttonState = BTN_RELEASED;
		}
	}
	else {
		m_buttonState = BTN_INACTIVE;

		m_hitboxButton = m_shapeButton.getGlobalBounds();

		if (m_hitboxButton.contains(sf::Vector2f(mousePosition))) {

			m_buttonState = BTN_HOVER;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				m_buttonState = BTN_PRESSED;
			}

		}
	}
	setStyle();
}

void Button::draw(sf::RenderTarget* window) const {
	window->draw(m_shapeButton);
	window->draw(m_textButton);
}

void Button::changeText(std::string newString) {
	m_textButton.setString(newString);
	m_textButtonString = newString;
}
