#include "MenuParameters.hpp"

MenuParameters::MenuParameters() {

	m_tabStringText = { "Size", "Framerate", "V-Sync", "Fullscreen" };

	m_tabPossibleResolution = { "854x480", "960x540", "1024x576", "1280x720", "1366x768",
		"1600x900", "1920x1080", "2048x1152", "2560x1440", "3200x1800", "3840x2160"};

	m_tabPossibleFramerate = { "30", "60", "120", "Illimited" };

	m_maxIndexRes = m_tabPossibleResolution.size()-1;

	m_indexTabRes = 0;

	m_indexTabFrame = 0;

	m_parametersState = INIT_GRAPHICS;

	//Create Function for creating rendertextures
	//
	//
	m_menuPlan = new sf::RenderTexture;
	m_menuPlan->create(1920, 1080);
	m_menuSprite = new sf::Sprite;

	std::vector<std::string> tabNameTextures{"Graphic", "Keybinds", "Actions", "Titles", "Choose"};
	for (int i(0); i < tabNameTextures.size(); i++) {
		m_tabTextures[tabNameTextures[i]] = new sf::RenderTexture;
	}

	m_staticGraphicSprite = new sf::Sprite;
	m_staticKeybindsSprite = new sf::Sprite;
	m_staticActionSprite = new sf::Sprite;
	m_staticTitlesSprite = new sf::Sprite;
	m_staticChooseSprite = new sf::Sprite;
	//
	//
	//

	m_configFile.loadFromFileGraphic("Config/Graphic.ini"); 
	m_configFile.loadFromFileKeys("Config/Keybinds.ini");
	getSettings();

}

MenuParameters::~MenuParameters() {
	delete m_menuPlan;
	m_menuPlan = 0;
	delete m_menuSprite;
	m_menuSprite = 0;
	std::cout << "MenuParameters pointer and content destroyed" << std::endl;

	std::map<std::string, std::vector<Button*>>::iterator itr;

	for (itr = m_tabButtons.begin(); itr != m_tabButtons.end(); ++itr){
		delete itr->second[0];
		itr->second[0] = 0;
		delete itr->second[1];
		itr->second[1] = 0;
	}
	m_tabButtons.clear();


	//Create Function here too
	//
	//
	delete m_staticGraphicSprite;
	m_staticGraphicSprite = 0;

	delete m_staticTitlesSprite;
	m_staticTitlesSprite = 0;

	delete m_staticKeybindsSprite;
	m_staticKeybindsSprite = 0;

	delete m_staticTitlesSprite;
	m_staticTitlesSprite = 0;

	delete m_staticChooseSprite;
	m_staticChooseSprite = 0;

	std::vector<std::string> tabNameTextures{ "Graphic", "Keybinds", "Actions", "Titles", "Choose" };
	for (int i(0); i < tabNameTextures.size(); i++) {
		delete m_tabTextures[tabNameTextures[i]];
		m_tabTextures[tabNameTextures[i]] = 0;
	}
	m_tabTextures.clear();

	//delete m_localPlayerTwoControl;
	//m_localPlayerTwoControl->clear();
	
	//
	//
	//

}

void MenuParameters::displayMenu(sf::RenderWindow* window, sf::Font font, sf::Event* evenmt) {
	
	sf::Vector2i mousePosition; //Put in hpp
	mousePosition = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(mousePosition, m_menuPlan->getView()); //Put in hpp

	std::map<std::string, std::vector<Button*>>::iterator it;

	std::map<std::string, Button*>::iterator itControlsButtons = m_keybindsButtonsPlayerOne.begin();
	std::map<std::string, Button*>::iterator itControlsButtons2 = m_keybindsButtonsPlayerTwo.begin();

	switch (m_parametersState) {

	case(INIT_GRAPHICS): //Create own rendertexture that initialized only one time (static)

		createStaticTitlePlan(font);
		createStaticGraphicPlan(font);
		createStaticKeybindPlan(font);
		createStaticChoosePlan(font);

		displayActualSettings();
		createButtons();

		for (int i(0); i < m_tabStringText.size(); i++) {
			if (m_tabStringText[i] == "Size") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabPossibleResolution[m_indexTabRes]);
			else if (m_tabStringText[i] == "Framerate") textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabPossibleFramerate[m_indexTabFrame]);
			else if (m_tabStringText[i] == "V-Sync") {
				if (m_localVsync) textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Enabled");
				else textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Disabled");
			}
			else if (m_tabStringText[i] == "Fullscreen") {
				if (m_localFullscreen) textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Enabled");
				else textOptions(&m_tabChosenSettings[m_tabStringText[i]], font, 50, sf::Color::White, "Disabled");
			}

			m_tabTextSettingsBoxs[m_tabStringText[i]] = m_tabChosenSettings[m_tabStringText[i]].getGlobalBounds();
			
			m_tabChosenSettings[m_tabStringText[i]].setOrigin(m_tabTextSettingsBoxs[m_tabStringText[i]].width / 2, m_tabTextSettingsBoxs[m_tabStringText[i]].top + m_tabTextSettingsBoxs[m_tabStringText[i]].height / 2);
			m_tabChosenSettings[m_tabStringText[i]].setPosition(1920 / 2 / 4 * 3, 300 + (116 * (1 + i)));
		}

		m_parametersState = GRAPHICS;

		break;

	case(GRAPHICS):

		m_menuPlan->clear();

		//Graphics Settings Buttons update and draw
		//
		//

		it = m_tabButtons.begin();
		while (it != m_tabButtons.end()) {
			it->second[0]->update(worldPos);

			if (it->second[0]->isPressed()) {
				if (it->first == "Size" && m_indexTabRes > 0) {
					m_indexTabRes -= 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleResolution[m_indexTabRes]);

					m_localWidthWindow = std::stoi(m_tabChosenSettings[it->first].getString().toAnsiString().substr(0, m_tabChosenSettings[it->first].getString().toAnsiString().find('x')));
					m_localHeightWindow = std::stoi(m_tabChosenSettings[it->first].getString().toAnsiString().substr(m_tabChosenSettings[it->first].getString().toAnsiString().find('x')+1));
				}
				else if (it->first == "Framerate" && m_indexTabFrame > 0) {
					m_indexTabFrame -= 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleFramerate[m_indexTabFrame]);

					if (m_tabChosenSettings[it->first].getString().toAnsiString() == "Illimited") m_localFramerate = 0;
					else m_localFramerate = std::stoi((m_tabChosenSettings[it->first].getString().toAnsiString()));
					
				} 
				else if (it->first == "V-Sync") {
					m_localVsync = !(m_localVsync);
					if (m_localVsync) m_tabChosenSettings[it->first].setString("Enabled");
					else m_tabChosenSettings[it->first].setString("Disabled");
				}
				else if (it->first == "Fullscreen") {
					m_localFullscreen = !(m_localFullscreen);
					if (m_localFullscreen) m_tabChosenSettings[it->first].setString("Enabled");
					else m_tabChosenSettings[it->first].setString("Disabled");
				}

				m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
				m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabChosenSettings[it->first].getOrigin().y);

			}

			it->second[1]->update(worldPos);
			if (it->second[1]->isPressed()) {

				if (it->first == "Size" && m_indexTabRes < m_maxIndexRes) {
					m_indexTabRes += 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleResolution[m_indexTabRes]);

					m_localWidthWindow = std::stoi(m_tabChosenSettings[it->first].getString().toAnsiString().substr(0, m_tabChosenSettings[it->first].getString().toAnsiString().find('x')));
					m_localHeightWindow = std::stoi(m_tabChosenSettings[it->first].getString().toAnsiString().substr(m_tabChosenSettings[it->first].getString().toAnsiString().find('x') + 1));

				}
				else if (it->first == "Framerate" && m_indexTabFrame < m_tabPossibleFramerate.size() - 1) {
					m_indexTabFrame += 1;
					m_tabChosenSettings[it->first].setString(m_tabPossibleFramerate[m_indexTabFrame]);

					if (m_tabChosenSettings[it->first].getString().toAnsiString() == "Illimited") m_localFramerate = 0;
					else m_localFramerate = std::stoi((m_tabChosenSettings[it->first].getString().toAnsiString()));

				}
				else if (it->first == "V-Sync") {
					m_localVsync = !(m_localVsync);
					if (m_localVsync) m_tabChosenSettings[it->first].setString("Enabled");
					else m_tabChosenSettings[it->first].setString("Disabled");
				}
				else if (it->first == "Fullscreen") {
					m_localFullscreen = !(m_localFullscreen);
					if (m_localFullscreen) m_tabChosenSettings[it->first].setString("Enabled");
					else m_tabChosenSettings[it->first].setString("Disabled");
				}

				m_tabTextSettingsBoxs[it->first] = m_tabChosenSettings[it->first].getGlobalBounds();
				m_tabChosenSettings[it->first].setOrigin(m_tabTextSettingsBoxs[it->first].width / 2, m_tabChosenSettings[it->first].getOrigin().y);

			}

			m_menuPlan->draw(m_tabChosenSettings[it->first]);
			it->second[0]->draw(m_menuPlan);
			it->second[1]->draw(m_menuPlan);
			it++;
		}

		//Controls Settings Buttons update and draw (Create a function for it)
		//
		//

		for (itControlsButtons; itControlsButtons != m_keybindsButtonsPlayerOne.end(); itControlsButtons++) { //DO THE SAME FOR P2
			itControlsButtons->second->update(worldPos);
			if (itControlsButtons->second->isPressed()) {
				m_parametersState = CHOOSING_KEY;
				m_choosingKey = itControlsButtons->second;
				m_newKey = &(*m_localPlayerOneControl)[itControlsButtons->first];
				break;
			}
			
			itControlsButtons->second->draw(m_menuPlan);
		}

		for (itControlsButtons2; itControlsButtons2 != m_keybindsButtonsPlayerTwo.end(); itControlsButtons2++) { //DO THE SAME FOR P2
			itControlsButtons2->second->update(worldPos);
			if (itControlsButtons2->second->isPressed()) {
				m_parametersState = CHOOSING_KEY;
				m_choosingKey = itControlsButtons2->second;
				m_newKey = &(*m_localPlayerTwoControl)[itControlsButtons2->first];
				break;
			}

			itControlsButtons2->second->draw(m_menuPlan);
		}

		//Bottom lines buttons update and draw
		//
		//

		for (std::map<std::string, Button*>::iterator itBottomLineButtons(m_bottomLineButtons.begin()); itBottomLineButtons != m_bottomLineButtons.end(); itBottomLineButtons++) {
			itBottomLineButtons->second->update(worldPos);
			if (itBottomLineButtons->second->isPressed()) {

				if (itBottomLineButtons->first == "Back") m_parametersState = BACK;
				if (itBottomLineButtons->first == "Save") {
					m_parametersState = SAVE;
					m_configFile.saveChange(m_localWidthWindow, m_localHeightWindow, m_localFramerate, m_localVsync, m_localFullscreen, *m_localPlayerOneControl, *m_localPlayerTwoControl);
				}
				if (itBottomLineButtons->first == "Default") m_parametersState = DEFAULT;
			}

			itBottomLineButtons->second->draw(m_menuPlan);
		}



		m_menuPlan->draw(*m_staticTitlesSprite);
		m_menuPlan->draw(*m_staticGraphicSprite);
		m_menuPlan->draw(*m_staticKeybindsSprite);
		m_menuPlan->draw(*m_staticActionSprite);
		m_menuPlan->display();
		
		break;

	case(CHOOSING_KEY):

		m_menuPlan->clear();

		
		m_menuPlan->draw(*m_staticTitlesSprite);
		m_menuPlan->draw(*m_staticGraphicSprite);
		m_menuPlan->draw(*m_staticKeybindsSprite);
		m_menuPlan->draw(*m_staticActionSprite);
		m_menuPlan->draw(*m_staticChooseSprite);
		m_menuPlan->display();


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) m_parametersState = GRAPHICS;

		
		if (evenmt->type == sf::Event::KeyReleased)
		{
			m_choosingKey->changeText(sf::Keyboard::getDescription(evenmt->key.scancode).toAnsiString());
			*m_newKey = evenmt->key.scancode;
			m_parametersState = GRAPHICS;
		}
		break;

	case(DEFAULT):
		m_configFile.defaultGraphicParameters();
		m_configFile.defaultControlsParameters();
		getSettings();
		displayActualSettings();
		m_parametersState = GRAPHICS;
		break;
	}

	const sf::Texture& parameterPlanUpdate = m_menuPlan->getTexture();
	*m_menuSprite = sf::Sprite(parameterPlanUpdate);
	m_menuSprite->setScale(sf::Vector2f(window->getSize().x / 1920.f, window->getSize().y / 1080.f)); //To put in display window directly + convert position for button
	window->draw(*m_menuSprite);

}

void MenuParameters::textOptions(sf::Text* text, sf::Font& font, int size, sf::Color color, std::string string) {
	text->setFont(font);
	text->setCharacterSize(size);
	text->setFillColor(color);
	text->setStyle(sf::Text::Bold);
	text->setString(string);
}

void MenuParameters::createStaticTitlePlan(sf::Font font) {
	////////////////////////
	sf::RectangleShape outlineTitles;
	outlineTitles = sf::RectangleShape(sf::Vector2f(1920 - 20, 300 - 20));
	outlineTitles.setPosition(10, 10);
	outlineTitles.setFillColor(sf::Color::Transparent);
	outlineTitles.setOutlineThickness(10.f);
	outlineTitles.setOutlineColor(sf::Color::Green);
	/////////////////////////

	m_tabTextures["Titles"]->create(1920, 300);

	sf::Text title;
	textOptions(&title, font, 100, sf::Color::White, "Graphics");
	title.setStyle(sf::Text::Underlined);

	sf::FloatRect titleBox = title.getGlobalBounds();
	title.setOrigin(titleBox.width / 2, titleBox.top + titleBox.height / 2);
	//title.setPosition(m_staticTitlesPlan->getSize().x / 4, 150);
	title.setPosition(m_tabTextures["Titles"]->getSize().x / 4, 150);

	//m_staticTitlesPlan->clear();
	m_tabTextures["Titles"]->clear();

	//m_staticTitlesPlan->draw(title);
	m_tabTextures["Titles"]->draw(title);

	title.setString("Controls");
	//title.setPosition((m_staticTitlesPlan->getSize().x / 4) * 3, 150);
	title.setPosition((m_tabTextures["Titles"]->getSize().x / 4) * 3, 150);
	//m_staticTitlesPlan->draw(title);
	m_tabTextures["Titles"]->draw(title);

	//m_staticTitlesPlan->draw(outlineTitles);////////////////////////

	//m_staticTitlesPlan->display();
	m_tabTextures["Titles"]->display();

	//*m_staticTitlesSprite = sf::Sprite(m_staticTitlesPlan->getTexture());
	*m_staticTitlesSprite = sf::Sprite(m_tabTextures["Titles"]->getTexture());

}

void MenuParameters::createStaticGraphicPlan(sf::Font font) {
	////////////
	sf::RectangleShape outline;
	outline = sf::RectangleShape(sf::Vector2f(480 - 20, 580 - 20));
	outline.setPosition(10, 10);
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineThickness(10.f);
	outline.setOutlineColor(sf::Color::Blue);
	///////////

	m_tabTextures["Graphic"]->create(1920 / 4, 580);////////////////////////////////////////////////////////////

	sf::FloatRect titleBox;

	//m_staticGraphicPlan->clear();
	m_tabTextures["Graphic"]->clear();

	for (int i(0); i < m_tabStringText.size(); i++) {

		textOptions(&m_tabTextSettings[m_tabStringText[i]], font, 50, sf::Color::White, m_tabStringText[i]);

		titleBox = m_tabTextSettings[m_tabStringText[i]].getGlobalBounds();
		m_tabTextSettings[m_tabStringText[i]].setOrigin(titleBox.width / 2, titleBox.top + titleBox.height / 2);
		m_tabTextSettings[m_tabStringText[i]].setPosition(240, 116 * (1 + i));

		//m_staticGraphicPlan->draw(m_tabTextSettings[m_tabStringText[i]]);
		m_tabTextures["Graphic"]->draw(m_tabTextSettings[m_tabStringText[i]]);

		//m_staticGraphicPlan->draw(outline);/////////////////////////////////////////////

	}

	//m_staticGraphicPlan->display();
	m_tabTextures["Graphic"]->display();

	//*m_staticGraphicSprite = sf::Sprite(m_staticGraphicPlan->getTexture());
	*m_staticGraphicSprite = sf::Sprite(m_tabTextures["Graphic"]->getTexture());
	m_staticGraphicSprite->setPosition(0, 300);
}

void MenuParameters::createStaticKeybindPlan(sf::Font font) {
	///////////////////
	sf::RectangleShape outlineKey;
	outlineKey = sf::RectangleShape(sf::Vector2f(960 - 20, 220 - 20));
	outlineKey.setPosition(10, 10);
	outlineKey.setFillColor(sf::Color::Transparent);
	outlineKey.setOutlineThickness(10.f);
	outlineKey.setOutlineColor(sf::Color::Red);

	sf::RectangleShape outlineAct;
	outlineAct = sf::RectangleShape(sf::Vector2f(960/3 - 20, 360 - 20));
	outlineAct.setPosition(10, 10);
	outlineAct.setFillColor(sf::Color::Transparent);
	outlineAct.setOutlineThickness(10.f);
	outlineAct.setOutlineColor(sf::Color::Yellow);
	//////////////////

	m_tabTextures["Keybinds"]->create(1920 / 2, 220);
	m_tabTextures["Actions"]->create(960 / 3, 360);

	sf::Text staticText;
	std::vector<std::string> tabTitles = { "Player", "1", "2"};

	sf::FloatRect titleBox;

	//m_staticKeybindsPlan->clear();
	m_tabTextures["Keybinds"]->clear();

	for (int i(0); i < tabTitles.size(); i++) {

		textOptions(&staticText, font, 50, sf::Color::White, tabTitles[i]);

		titleBox = staticText.getGlobalBounds();
		staticText.setOrigin(titleBox.width / 2, titleBox.height / 2);

		//if (tabTitles[i] == "Player") staticText.setPosition(160, m_staticKeybindsPlan->getSize().y / 2);
		if (tabTitles[i] == "Player") staticText.setPosition(160, m_tabTextures["Keybinds"]->getSize().y / 2);
		//else staticText.setPosition(320 + (640/3*i), m_staticKeybindsPlan->getSize().y/2);
		else staticText.setPosition(320 + (640/3*i), m_tabTextures["Keybinds"]->getSize().y/2);

		//m_staticKeybindsPlan->draw(staticText);
		m_tabTextures["Keybinds"]->draw(staticText);
	}

	
	//m_staticKeybindsPlan->draw(outlineKey);
	//m_staticKeybindsPlan->display();
	m_tabTextures["Keybinds"]->display();

	*m_staticKeybindsSprite = sf::Sprite(m_tabTextures["Keybinds"]->getTexture());
	//*m_staticKeybindsSprite = sf::Sprite(m_staticKeybindsPlan->getTexture());
	m_staticKeybindsSprite->setPosition(1920 / 2, 300);


	tabTitles = { "UP", "DOWN" };

	//m_staticActionPlan->clear();
	m_tabTextures["Actions"]->clear();

	for (int i(0); i < tabTitles.size(); i++) {

		textOptions(&staticText, font, 50, sf::Color::White, tabTitles[i]);

		titleBox = staticText.getGlobalBounds();
		staticText.setOrigin(titleBox.width / 2, titleBox.height / 2);

		//staticText.setPosition(160, m_staticActionPlan->getSize().y/3 * (i+1));
		staticText.setPosition(160, m_tabTextures["Actions"]->getSize().y/3 * (i+1));

		//m_staticActionPlan->draw(staticText);
		m_tabTextures["Actions"]->draw(staticText);
	}

	//m_staticActionPlan->draw(outlineAct);
	//m_staticActionPlan->display();
	m_tabTextures["Actions"]->display();

	//*m_staticActionSprite = sf::Sprite(m_staticActionPlan->getTexture());
	*m_staticActionSprite = sf::Sprite(m_tabTextures["Actions"]->getTexture());
	m_staticActionSprite->setPosition(1920 / 2, 520);

}

void MenuParameters::createStaticChoosePlan(sf::Font font) {
	m_tabTextures["Choose"]->create(1920, 400);

	sf::RectangleShape outlines(sf::Vector2f(m_tabTextures["Choose"]->getSize().x - 20, m_tabTextures["Choose"]->getSize().y - 20));
	outlines.setFillColor(sf::Color::Transparent);
	outlines.setOutlineColor(sf::Color::White);
	outlines.setOutlineThickness(2.f);
	outlines.setPosition(10, 10);

	sf::Text text;
	sf::FloatRect textBox;

	textOptions(&text, font, 50, sf::Color::White, "Press your new key to bind it or press ESCAPE to quit");
	textBox = text.getGlobalBounds();
	text.setOrigin(textBox.width / 2, textBox.height / 2);
	text.setPosition(m_tabTextures["Choose"]->getSize().x / 2, m_tabTextures["Choose"]->getSize().y / 2);

	m_tabTextures["Choose"]->clear();

	m_tabTextures["Choose"]->draw(outlines);
	m_tabTextures["Choose"]->draw(text);

	m_tabTextures["Choose"]->display();


	*m_staticChooseSprite = sf::Sprite(m_tabTextures["Choose"]->getTexture());
	m_staticChooseSprite->setPosition(0, 1080/3);
}

void MenuParameters::displayActualSettings() {

	for (int i(0); i < m_tabPossibleResolution.size(); i++) {
		if (m_tabPossibleResolution[i].compare((std::to_string(m_localWidthWindow) + "x" + std::to_string(m_localHeightWindow))) == 0) {
			m_indexTabRes = i;
			if (m_parametersState == DEFAULT) {

				m_tabChosenSettings["Size"].setString(m_tabPossibleResolution[i]);
				m_tabTextSettingsBoxs["Size"] = m_tabChosenSettings["Size"].getGlobalBounds();
				m_tabChosenSettings["Size"].setOrigin(m_tabTextSettingsBoxs["Size"].width / 2, m_tabChosenSettings["Size"].getOrigin().y);

			}
		}
		if (m_tabPossibleResolution[i].compare((std::to_string(sf::VideoMode::getDesktopMode().width) + "x" + std::to_string(sf::VideoMode::getDesktopMode().height))) == 0) m_maxIndexRes = i;
	}

	for (int i(0); i < m_tabPossibleFramerate.size(); i++) {
		if (m_tabPossibleFramerate[i].compare(std::to_string(m_localFramerate)) == 0) {
			m_indexTabFrame = i;
			if (m_parametersState == DEFAULT) {

				m_tabChosenSettings["Framerate"].setString(m_tabPossibleFramerate[i]);
				m_tabTextSettingsBoxs["Framerate"] = m_tabChosenSettings["Framerate"].getGlobalBounds();
				m_tabChosenSettings["Framerate"].setOrigin(m_tabTextSettingsBoxs["Framerate"].width / 2, m_tabChosenSettings["Framerate"].getOrigin().y);

			}

			i = m_tabPossibleFramerate.size();
		}
	}

	if (m_parametersState == DEFAULT) {
		if (m_localFullscreen) m_tabChosenSettings["Fullscreen"].setString("Enabled");
		else m_tabChosenSettings["Fullscreen"].setString("Disabled");

		if (m_localVsync) m_tabChosenSettings["V-Sync"].setString("Enabled");
		else m_tabChosenSettings["V-Sync"].setString("Disabled");

		std::vector<std::string> tabAct{ "UP", "DOWN" };

		for (int i(0); i < tabAct.size(); i++) {
			m_keybindsButtonsPlayerOne[tabAct[i]]->changeText(sf::Keyboard::getDescription((*m_localPlayerOneControl)[tabAct[i]]).toAnsiString());
			m_keybindsButtonsPlayerTwo[tabAct[i]]->changeText(sf::Keyboard::getDescription((*m_localPlayerTwoControl)[tabAct[i]]).toAnsiString());
		}
	}
}

void MenuParameters::getSettings() {

	m_localWidthWindow = m_configFile.getSizeWindow().width;
	m_localHeightWindow = m_configFile.getSizeWindow().height;
	m_localFramerate = m_configFile.getFramerate();
	m_localFullscreen = m_configFile.getFullscreen();
	m_localVsync = m_configFile.getVSync();

	
	m_localPlayerOneControl = new std::map<std::string, sf::Keyboard::Scancode>; 
	*m_localPlayerOneControl = m_configFile.getControl(1);
	m_localPlayerTwoControl = new std::map<std::string, sf::Keyboard::Scancode>;
	*m_localPlayerTwoControl = m_configFile.getControl(2);

}

void MenuParameters::createButtons() {

	//Creation Buttons Graphics Settings
	for (int i(0); i < m_tabStringText.size(); i++) {
		m_tabButtons[m_tabStringText[i]] = { new Button(1920 / 2 / 4 * 3 - 150, 300 + (116 * (1 + i)), 10.f, 40.f, 1,30, "<"), new Button(1920 / 2 / 4 * 3 + 150, 300 + (116 * (1 + i)), 10.f, 40.f, 1,30, ">") };
	}

	//Creation Buttons Keybinds Settings

	std::vector<std::string> tabAct{ "UP", "DOWN" };

	for (int i(0); i < tabAct.size(); i++) {
		m_keybindsButtonsPlayerOne[tabAct[i]] = new Button(1280 + 640 / 3, 530 + (360 / 3 * (i + 1)), 220, 40.f, 2, 30, sf::Keyboard::getDescription((*m_localPlayerOneControl)[tabAct[i]]).toAnsiString());
		m_keybindsButtonsPlayerTwo[tabAct[i]] = new Button(1280 + 640 / 3 * 2.1, 530 + (360 / 3 * (i + 1)), 220, 40.f, 2, 30, sf::Keyboard::getDescription((*m_localPlayerTwoControl)[tabAct[i]]).toAnsiString());
	}

	//Creation Button Bottom Line Settings (save, default, back)
	std::string tabOptions[3] ;
	tabOptions[0] = "Back";
	tabOptions[1] = "Default";
	tabOptions[2] = "Save";

	for (int i(0); i < 3; i++) {
		m_bottomLineButtons[tabOptions[i]] = new Button(480 * (i + 1), 980, 200.f, 100.f, 2, 40, tabOptions[i]);
	}
}

bool MenuParameters::getStateParametersMenu() const {
	return m_parametersState == BACK;
}

bool MenuParameters::getSaved() const {
	return m_parametersState == SAVE;
}

void MenuParameters::setStateParametersMenu() {
	m_parametersState = GRAPHICS;
}