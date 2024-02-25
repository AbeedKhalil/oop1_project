#include "Game.h"

// Initialize window and game components
Game::Game() : m_gameState(GameState::MainMenu), m_score(), m_scoreAmount(0), m_keyAmount(0) {

	initWindow();
	displayStartupImage();
	initTileSheet();
	initMenu();
	initLevel();
}

// Initialize the SFML window
void Game::initWindow() {
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(960, 840), "Mouse VS Cats", sf::Style::Close | sf::Style::Titlebar);
	m_window->setFramerateLimit(60);
	m_window->setVerticalSyncEnabled(false);
}

// Initialize the menu
void Game::initMenu() {
	m_menu = std::make_unique<Menu>();
}

// Load and set up the tile sheet
void Game::initTileSheet() {
	if (!m_tileSheet.loadFromFile("TileSheet.png")) {
		std::cerr << "ERROR::GAME::Could not load texture file: TileSheet.png\n";
	}
	m_spriteGame.setTexture(m_tileSheet);

	if (!m_menuSheet.loadFromFile("MenuBackground.png")) {
		std::cerr << "ERROR::GAME::Could not load texture file: MenuBackground.png\n";
	}

	m_spriteMenu.setTexture(m_menuSheet);
}

// Initialize the level
void Game::initLevel() {
	m_level.reset();
	m_level = std::make_shared<Level>(*m_window);
	m_level->loadFromFile();
	receiveObjectsFromLevel();
}

void Game::displayStartupImage() {
	sf::Texture startupTexture1;
	if (!startupTexture1.loadFromFile("Intro1.png")) {
		std::cerr << "ERROR::GAME::Could not load startup image\n";
		return;
	}

	sf::Sprite startupSprite1(startupTexture1);

	sf::Clock clock;
	float fadeDuration = 3.f;
	float alpha = 255;

	while (alpha > 0) {
		float deltaTime = clock.restart().asSeconds();
		alpha -= (255 / fadeDuration) * deltaTime;
		if (alpha < 0) alpha = 0;

		startupSprite1.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		m_window->clear();
		m_window->draw(startupSprite1);
		m_window->display();
	}

	// Repeat the process for the second image
	sf::Texture startupTexture2;
	if (!startupTexture2.loadFromFile("Intro2.png")) {
		std::cerr << "ERROR::GAME::Could not load startup image\n";
		return;
	}

	sf::Sprite startupSprite2(startupTexture2);
	alpha = 255; // Reset alpha for the second image
	while (alpha > 0) {
		float deltaTime = clock.restart().asSeconds();
		alpha -= (255 / fadeDuration) * deltaTime;
		if (alpha < 0) alpha = 0;

		startupSprite2.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		m_window->clear();
		m_window->draw(startupSprite2);
		m_window->display();
	}

	m_window->clear(); // Clear the window one last time before proceeding
}

// Handle all events
void Game::pollEvents() {
	sf::Event event;
	while (m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)) {
			m_window->close();
			std::cout << "Good bye :(\n";
			std::cout << "Press any key to end the game!\n";

			while (true) {
				if (_kbhit()) { // Check if a key has been pressed
					break;
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep to reduce CPU usage
			}
		}
	}
}

// Main game loop
void Game::run() {
	while (m_window->isOpen()) {
		pollEvents();
		updateInput();

		// Update game state and logic only if not paused
		if (m_gameState != GameState::Paused) {
			updateGameLogic();
		}

		render();
	}
}

void Game::receiveObjectsFromLevel() {
	m_sharedObjects.clear();
	auto rawObjects = m_level->getRawObjectPointers();
	for (auto* obj : rawObjects) {
		m_sharedObjects.push_back(std::shared_ptr<Objects>(obj));
	}
}

void Game::handleCollisions() {
	Mouse* mouse = nullptr;
	// Find the mouse object among the shared objects
	for (auto& obj : m_sharedObjects) {
		mouse = dynamic_cast<Mouse*>(obj.get());
		if (mouse) break; // Stop searching once the mouse is found
	}

	if (!mouse) return; // If there's no mouse, no need to check for collisions

	sf::FloatRect mouseBounds = mouse->getBounds();

	for (auto& obj : m_sharedObjects) {
		if (!obj->isVisible()) continue; // Skip invisible objects

		Cheese* cheese = dynamic_cast<Cheese*>(obj.get());
		Key* key = dynamic_cast<Key*>(obj.get());
		RemoveCat* removeCat = dynamic_cast<RemoveCat*>(obj.get());
		Door* door = dynamic_cast<Door*>(obj.get());

		if (cheese && mouseBounds.intersects(cheese->getBounds())) {
			cheese->setVisible(false); // Hide the cheese
			m_level->updateCheeseNum(); // cheese-- from the cheese num on the level
			m_scoreAmount += 10; // Increase the score
		}
		else if (key && mouseBounds.intersects(key->getBounds())) {
			key->setVisible(false); // Hide the key
			this->m_keyAmount++; // add one to the keys counter
		}
		else if (removeCat && mouseBounds.intersects(removeCat->getBounds())) {
			removeCat->setVisible(false); // Hide the key
			m_scoreAmount += 15; // Increase the score
			// Logic to hide one cat
			for (auto& catObj : m_sharedObjects) {
				Cat* cat = dynamic_cast<Cat*>(catObj.get());
				if (cat && cat->isVisible()) {
					cat->setVisible(false); // Hide the cat
					break; // Stop after hiding one cat
				}
			}
		}
		else if (door && mouseBounds.intersects(door->getBounds()) && m_score.youHaveKey()) {
			door->setVisible(false); // Hide the key
			this->m_keyAmount--; // minus one from the keys counter
		}
	}
}

// Update input handling
void Game::updateInput()
{
	float moveX = 0.f, moveY = 0.f;
	// Determine movement direction
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		moveX -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		moveX += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		moveY -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		moveY += 1.f;
	}

	// Move Mouse
	Mouse* mouse = nullptr;
	mouse->moveMouse(m_sharedObjects, moveX, moveY, m_score);
}

// Update game logic based on the current state
void Game::updateGameLogic() 
{
	pollEvents();

	// Update based on game state
	switch (m_gameState)
	{
	    case GameState::MainMenu:
	    {
		    this->m_menu->update(*this->m_window, m_gameState);

		    break;
	    }

	    case GameState::InGame:
	    {
		    handleCollisions(); // Check and handle collisions
		    updateInput();
		    m_score.updateScore(m_scoreAmount, m_keyAmount);

		    Mouse* mouse = nullptr;
		    Cat* cat = nullptr;

		    // Correctly find the mouse and the cat
		    for (auto& obj : m_sharedObjects) {
			    if (!mouse) mouse = dynamic_cast<Mouse*>(obj.get());
			    if (!cat) cat = dynamic_cast<Cat*>(obj.get());
			    if (mouse && cat) break;
		    }

		    // Find the mouse and the cat
		    if (mouse && cat) {
			    sf::Vector2f mousePos = mouse->getPosition();
			    sf::Vector2f catPos = cat->getPosition();
			    // move cat
			    cat->moveCat(m_sharedObjects, mousePos, catPos, m_score);
		    }

		    // Check for level completion
		    if (m_level->therIsNoCheese()) {
			    initLevel();
		    }

 		    // Update logic for all objects
		    for (auto& obj : m_sharedObjects) {
			    obj->update();
		    }
		    break;
	    }

	    case GameState::Help:
	    {
		    this->m_menu->update(*this->m_window, m_gameState);
	    }
	}
}

// Render all game elements
void Game::render() {
	m_window->clear();

	// Render based on game state
	switch (m_gameState) {
	case GameState::MainMenu:
		m_window->draw(m_spriteMenu);
		m_menu->draw(*m_window);
		break;
	case GameState::InGame:
		m_window->draw(m_spriteGame);
		m_level->render();
		m_score.render(*this->m_window);
		break;
	case GameState::Help:
	{
		m_menu->showHelpWindow(*m_window, m_gameState);
		break;
	}
	default:
		break;
	}

	m_window->display();
}