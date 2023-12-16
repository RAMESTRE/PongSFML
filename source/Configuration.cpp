#include "Configuration.hpp"

Configuration::Configuration() {
	defaultGraphicParameters();
	defaultControlsParameters();
	configFolderExist();
}

Configuration::~Configuration() {
	std::cout << "Config deleted" << std::endl;
	m_playerTwoControls.clear();
}

void Configuration::saveToFileGraphic(std::string path) {

	configFolderExist();

	std::ofstream file(path);
	

	if (file.is_open()) {
		file << "SIZE=" << m_widthWindow << "x" << m_heightWindow <<"\n";
		file << "FRAMERATE=" << m_framerate << "\n";

		if (m_vsync) file << "VSYNC=" << "true" << "\n";
		else file << "VSYNC=" << "false" << "\n";

		if (m_fullscreen) file << "FULLSCREEN=" << "true";
		else file << "FULLSCREEN=" << "false";
	}
	else {
		std::cout << "Cannot open config file" << std::endl;
	}

	file.close();
}

void Configuration::loadFromFileGraphic(std::string path) {

	configFolderExist();

	std::ifstream flux(path);
	std::string line;
	std::string settings;

	if (flux.is_open()) {
		int i = 0;
		while (std::getline(flux, line)) {

			settings = line.substr(line.find('=')+1);
			
			if (line.substr(0, line.find('=')) == "SIZE") {

				if (correctResolutionSetting(settings)) {
					m_widthWindow = std::stoi(settings.substr(0, settings.find('x')));
					m_heightWindow = std::stoi(settings.substr(settings.find('x') + 1));
				}
				else {
					defaultGraphicParameters();
					break;
				}
			}
			else if (line.substr(0, line.find('=')) == "FRAMERATE") {
				if (correctFramerateSetting(settings))	m_framerate = std::stoi(settings);
				else {
					defaultGraphicParameters();
					break;
				}
			}
			else if (line.substr(0, line.find('=')) == "FULLSCREEN") {
				m_fullscreen = (settings == "true");
			}
			else if (line.substr(0, line.find('=')) == "VSYNC") {
				m_vsync = (settings == "true");
			}
		}
	}
	else {
		std::cout << "Cannot open config file" << std::endl;
	}

	flux.close();
}

sf::VideoMode Configuration::getSizeWindow() const {
	return sf::VideoMode(m_widthWindow, m_heightWindow);
}

int Configuration::getFramerate() const {
	return m_framerate;
}

bool Configuration::getFullscreen() const {
	return m_fullscreen;
}

bool Configuration::getVSync() const {
	return m_vsync;
}

void Configuration::defaultGraphicParameters() {

	m_widthWindow = sf::VideoMode::getDesktopMode().width;
	m_heightWindow = sf::VideoMode::getDesktopMode().height;
	m_framerate = 60;
	m_fullscreen = false;
	m_vsync = false;

}

void Configuration::saveChange(int width, int height, int framerate, bool vsync, bool fullscreen, std::map<std::string, sf::Keyboard::Scancode> p1, std::map<std::string, sf::Keyboard::Scancode> p2) {
	m_widthWindow = width;
	m_heightWindow = height;
	m_framerate = framerate;
	m_vsync = vsync;
	m_fullscreen = fullscreen;
	
	m_playerOneControls = p1;

	for (std::map<std::string, sf::Keyboard::Scancode>::iterator it(p2.begin()); it != p2.end(); it++) {
		m_playerTwoControls[it->first] = it->second;
	}

	saveToFileGraphic("Config/Graphic.ini");
	saveToFileKeys("Config/Keybinds.ini");
}


void Configuration::saveToFileKeys(std::string path) {

	configFolderExist();

	std::ofstream file(path);
	std::vector<std::string> toSave{ "[Player 1]", "UP", "DOWN", "[Player 2]", "UP", "DOWN" };

	if (file.is_open()) {
		for (int i(0); i < toSave.size(); i++) {
			if (i == 0 || i == 3) {
				file << toSave[i] << "\n";
			}
			else if (i < 3) {
				file << toSave[i]+ "=" << sf::Keyboard::getDescription(m_playerOneControls[toSave[i]]).toAnsiString() << "\n";
			}
			else if (i>3){
				file << toSave[i] + "=" << sf::Keyboard::getDescription(m_playerTwoControls[toSave[i]]).toAnsiString() << "\n";
			}
		}
	}
	file.close();
}

void Configuration::loadFromFileKeys(std::string path) {

	configFolderExist();

	std::map<std::string, int> tab;
	
	//Loop limited to Scancode that can't be counted two times as the same key
	//Start at i=1 because tab[settings] return 0 if element don't exist
	for (int i(1); i < (sf::Keyboard::Scancode::NonUsBackslash) + 1; i++) { 
		tab[sf::Keyboard::getDescription(sf::Keyboard::Scancode(i-1)).toAnsiString()] = i;
	}

	std::ifstream flux(path);
	std::string line;
	std::string settings;
	
	bool p1 = false;
	bool p2 = false;

	if (flux.is_open()) {
		while (std::getline(flux, line)) {
			
			if (line == "[Player 1]") p1 = true;
			else if (line == "[Player 2]") {
				p1 = false;
				p2 = true;
			}

			settings = line.substr(line.find('=') + 1);

			if (line.substr(0, line.find('=')) == "UP" || line.substr(0, line.find('=')) == "DOWN") {
				if (!(sf::Keyboard::Scancode(tab[settings]))) {
					defaultControlsParameters();
					flux.close();
					break;
				}
				if (p1) {
					m_playerOneControls[line.substr(0, line.find('='))] = sf::Keyboard::Scancode(tab[settings]-1);
				}
				else if (p2) {
					m_playerTwoControls[line.substr(0, line.find('='))] = sf::Keyboard::Scancode(tab[settings]-1);
				}
			}
		}
	}
	else {
		std::cout << "Cannot open config file" << std::endl;
	}

	flux.close();
}

std::map<std::string, sf::Keyboard::Scancode> Configuration::getControl(int player) const {

	if (player == 1) return m_playerOneControls;
	return m_playerTwoControls;
}

void Configuration::defaultControlsParameters() {

	std::vector<std::string> m_playerActions;
	m_playerActions = {"UP", "DOWN"};

	for (int i(0); i < m_playerActions.size(); i++) {
		if (m_playerActions[i] == "UP") {
			m_playerOneControls[m_playerActions[i]] = sf::Keyboard::Scancode::W;
			m_playerTwoControls[m_playerActions[i]] = sf::Keyboard::Scancode::Up;
		}
		else {
			m_playerOneControls[m_playerActions[i]] = sf::Keyboard::Scancode::S;
			m_playerTwoControls[m_playerActions[i]] = sf::Keyboard::Scancode::Down;
		}
	}

}

void Configuration::configFolderExist() {
	const char* dir = "./Config";
	struct stat metadata;

	int status;

	if (stat(dir, &metadata) == 0) std::cout << "Path valid" << std::endl;
	else {
		std::cout << "Repertory does not exist" << std::endl;
		if (_mkdir("./Config") == 0) std::cout << "Repertory Config created" << std::endl;
		else std::cout << "Couldn't create Config Repertory";
	}
	
}

bool Configuration::correctResolutionSetting(std::string res) {

	std::vector<std::string> resolutions{ "854x480", "960x540", "1024x576", "1280x720", "1366x768",
		"1600x900", "1920x1080", "2048x1152", "2560x1440", "3200x1800", "3840x2160" };

	for (int i(0); i < resolutions.size(); i++) {
		if (resolutions[i].compare(res) == 0) return true;
		
	}
	return false;
}
	
bool Configuration::correctFramerateSetting(std::string res) {

	std::vector<std::string> framerate{ "30", "60", "120", "0" };

	for (int i(0); i < framerate.size(); i++) {
		if (framerate[i].compare(res) == 0) return true;
	}
	return false;
	
}

void Configuration::checkResolutionBelowMax() {
	if (m_widthWindow > sf::VideoMode::getDesktopMode().width || m_heightWindow > sf::VideoMode::getDesktopMode().height) {
		m_widthWindow = sf::VideoMode::getDesktopMode().width;
		m_heightWindow = sf::VideoMode::getDesktopMode().height;
	}
}


	
	
