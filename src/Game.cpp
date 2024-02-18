#include "Game.h"

// Initialize window and game components
Game::Game() : m_gameState(GameState::MainMenu) {
	initWindow();
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
	m_level = std::make_unique<Level>(*m_window);
	m_level->loadFromFile();
	receiveObjectsFromLevel();
}

// Handle all events
void Game::pollEvents() {
	sf::Event event;
	while (m_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)) {
			m_window->close();
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
	auto rawObjects = m_level->getRawObjectPointers(); // This assumes getRawObjectPointers is correctly implemented
	for (auto* obj : rawObjects) {
		m_objects.push_back(std::unique_ptr<Objects>(obj)); // Make sure this logic fits your design intentions
	}
}

bool Game::wouldCollide(Objects* obj, float moveX, float moveY) {
	// Calculate the proposed new bounding box for obj after moving
	sf::FloatRect nextPos(obj->getPosition().x + moveX, obj->getPosition().y + moveY, obj->getBounds().width + 1, obj->getBounds().height + 0.5);

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

		Mouse* mouse = nullptr;
		Cat* cat = nullptr;

		// Find the mouse and the cat
		for (auto& obj : m_objects) {
			if (!mouse) mouse = dynamic_cast<Mouse*>(obj.get());
			if (!cat) cat = dynamic_cast<Cat*>(obj.get());
			if (mouse && cat) break;
		}

		if (mouse && cat) {
			sf::Vector2f mousePos = mouse->getPosition();
			sf::Vector2f catPos = cat->getPosition();

			sf::Vector2f direction = mousePos - catPos;
			float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			if (magnitude > 0) {
				direction.x /= magnitude;
				direction.y /= magnitude;
			}

			// Movement increments adjusted for checking collision separately on each axis
			float moveX = direction.x * cat->getMovementSpeed();
			float moveY = direction.y * cat->getMovementSpeed();

			// Check collision for X movement
			if (!checkCollisionWithWalls(cat, moveX, 0)) {
				cat->move(moveX, 0);
			}
			// Check collision for Y movement
			if (!checkCollisionWithWalls(cat, 0, moveY)) {
				cat->move(0, moveY);
			}
		}

		if (mouse) {
			for (auto& obj : m_objects) {
				Cheese* cheese = dynamic_cast<Cheese*>(obj.get());
				if (cheese) {
					sf::FloatRect mouseBounds = mouse->getBounds();
					sf::FloatRect cheeseBounds = cheese->getBounds();
					if (mouseBounds.intersects(cheeseBounds)) {
						// Collision detected, replace cheese with nullptr
						obj->setVisible(false);
					}
				}
			}
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
		// Render other in-game elements here
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