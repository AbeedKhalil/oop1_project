#include "Game.h"

// Initialize window and game components
Game::Game() : m_gameState(GameState::MainMenu), m_score(), m_scoreAmount(0) {

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
	m_level = std::make_unique<Level>(*m_window);
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
	m_objects.clear();
	auto rawObjects = m_level->getRawObjectPointers();
	for (auto* obj : rawObjects) {
		m_objects.push_back(std::unique_ptr<Objects>(obj));
	}
}

bool Game::wouldCollide(Objects* obj, float moveX, float moveY) {
	// Calculate the proposed new bounding box for obj after moving
	sf::FloatRect nextPos(obj->getPosition().x + moveX, obj->getPosition().y + moveY, obj->getBounds().width + 1, obj->getBounds().height + 1);

	// Check against all wall objects
	for (auto& wallObj : m_objects) {
		Wall* wall = dynamic_cast<Wall*>(wallObj.get());
		if (wall) {
			sf::FloatRect wallBounds = wall->getBounds();
			if (nextPos.intersects(wallBounds)) {
				return true; // Collision detected
			}
		}
	}
	return false; // No collision detected
}

bool Game::checkCollisionWithWalls(Objects* obj, float moveX, float moveY) {
	// Iterate over all objects to find walls
	for (auto& wallObj : m_objects) {
		Wall* wall = dynamic_cast<Wall*>(wallObj.get());
		if (wall) {
			// Here you'd implement the actual collision check
			// For simplicity, assume a function exists that checks if obj moving by (moveX, moveY) would collide with wall
			if (wouldCollide(obj, moveX, moveY)) {
				return true; // Collision detected
			}
		}
	}
	return false; // No collision detected
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
	for (auto& obj : m_objects) {
		Mouse* mouse = dynamic_cast<Mouse*>(obj.get()); // Try to cast to Mouse*
		if (mouse) // If it's a Mouse
		{
			// Check collision for X movement
			if (!checkCollisionWithWalls(mouse, moveX, 0)) {
				mouse->move(moveX, 0);
			}
			// Check collision for Y movement
			if (!checkCollisionWithWalls(mouse, 0, moveY)) {
				mouse->move(0, moveY);
			}
		}
	}
}

// Update game logic based on the current state
void Game::updateGameLogic() {
	pollEvents();
	// Update based on game state
	switch (m_gameState) {
	case GameState::MainMenu:
	{
		this->m_menu->update(*this->m_window, m_gameState);

		break;
	}
	case GameState::InGame:
	{
		updateInput();

		m_score.updateScore(m_scoreAmount);

		Mouse* mouse = nullptr;
		Cat* cat = nullptr;

		// Correctly find the mouse and the cat
		for (auto& obj : m_objects) {
			if (!mouse) mouse = dynamic_cast<Mouse*>(obj.get());
			if (!cat) cat = dynamic_cast<Cat*>(obj.get());
			if (mouse && cat) break;
		}

		// Find the mouse and the cat
		if (mouse && cat) {
			sf::Vector2f mousePos = mouse->getPosition();
			sf::Vector2f catPos = cat->getPosition();

			// Calculate normalized direction vector from cat to mouse
			sf::Vector2f direction = mousePos - catPos;
			float magnitude = std::hypot(direction.x, direction.y); // More precise than std::sqrt(x*x + y*y)
			if (magnitude > 0) {
				direction /= magnitude; // Normalize the direction vector
			}

			// Attempt direct movement towards the mouse
			float moveX = direction.x * cat->getMovementSpeed();
			float moveY = direction.y * cat->getMovementSpeed();

			bool canMoveX = !checkCollisionWithWalls(cat, moveX, 0);
			bool canMoveY = !checkCollisionWithWalls(cat, 0, moveY);

			if (canMoveX) {
				cat->move(moveX, 0);
			}
			else if (canMoveY) {
				cat->move(0, moveY);
			}
			else {
				// If direct movement is blocked, try alternative directions
				for (const auto& altDir : alternativeDirections) {
					if (!checkCollisionWithWalls(cat, altDir.x * cat->getMovementSpeed(), altDir.y * cat->getMovementSpeed())) {
						cat->move(altDir.x * cat->getMovementSpeed(), altDir.y * cat->getMovementSpeed());
						break;
					}
				}
			}
		}


		if (mouse) {
			for (auto& obj : m_objects) {
				Cheese* cheese = dynamic_cast<Cheese*>(obj.get());
				if (cheese) {
					sf::FloatRect mouseBounds = mouse->getBounds();
					sf::FloatRect cheeseBounds = cheese->getBounds();
					if (mouseBounds.intersects(cheeseBounds) && obj->isVisible()) {
						// Collision detected
						obj->setVisible(false);
						m_level->updateCheeseNum();
						m_scoreAmount += 10;
					}
				}
			}
		}
		// Check for level completion
		if (m_level->therIsNoCheese()) {
			initLevel();
		}

		// Update logic for all objects
		for (auto& obj : m_objects) {
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