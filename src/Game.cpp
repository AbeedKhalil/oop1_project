#include "Game.h"

// Initialize window and game components
Game::Game()
	: m_gameState(GameState::MainMenu), m_score(), m_scoreAmount(0), m_keyAmount(0),
	m_livesAmount(3), m_levelNum(1), m_totalGameTime(0), m_timeLimit(61.0f), m_currentTime(m_timeLimit) {
	initWindow();
	displayStartupImage();
	initAssets();
	initMenus();
	initLevel();
}

// Initialize the SFML window
void Game::initWindow() {
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(960, 840), "Mouse VS Cats", sf::Style::Close | sf::Style::Titlebar);
	m_window->setFramerateLimit(60);
	m_window->setVerticalSyncEnabled(false);
}

// Initialize the menus
void Game::initMenus() {
	m_menu = std::make_unique<Menu>();
	m_winMenu = std::make_unique<WinMenu>();
}

// Load and set up the Backgrounds
void Game::initAssets() {
	auto& tm = TextureManager::getInstance();
	m_tileSheet = tm.getTexture("TileSheet.png");
	m_spriteGame.setTexture(m_tileSheet);
	m_menuSheet = tm.getTexture("MenuBackground.png");
	m_spriteMenu.setTexture(m_menuSheet);
	m_winSheet = tm.getTexture("Win.png");
	m_spriteWin.setTexture(m_winSheet);
	m_gameOverSheet = tm.getTexture("GameOver.png");
	m_spriteGameOver.setTexture(m_gameOverSheet);

	if (!m_catDies.loadFromFile("CatDies.ogg")) {
		std::cerr << "ERROR::GAME::Could not load sound\n";
	}
	m_cat.setBuffer(m_catDies);
	if (!m_pauseCats.loadFromFile("PuaseCats.ogg")) {
		std::cerr << "ERROR::GAME::Could not load sound\n";
	}
	m_pause.setBuffer(m_pauseCats);
	if (!m_timeEnds.loadFromFile("TimeEnds.ogg")) {
		std::cerr << "ERROR::GAME::Could not load sound\n";
	}
	m_time.setBuffer(m_timeEnds);
	if (!m_addTimer.loadFromFile("AddTime.ogg")) {
		std::cerr << "ERROR::GAME::Could not load sound\n";
	}
	m_addTime.setBuffer(m_addTimer);
	if (!m_unlockDoor.loadFromFile("DoorUnlock.ogg")) {
		std::cerr << "ERROR::GAME::Could not load sound\n";
	}
	m_unlock.setBuffer(m_unlockDoor);
}

// Initialize the level
void Game::initLevel() {
	m_level.reset();
	m_level = std::make_shared<Level>(*m_window);
	m_level->loadFromFile(m_levelNum);
	receiveObjectsFromLevel();
	m_timeLimit = 61.0f; // 1 min
	m_currentTime = m_timeLimit;
}

// the intro
void Game::displayStartupImage() {
	// Load sound buffer and sound
	sf::SoundBuffer intro;
	if (!intro.loadFromFile("Intro.ogg")) {
		std::cerr << "ERROR::GAME::Could not load startup sound\n";
	}

	sf::Sound sound;
	sound.setBuffer(intro);

	sound.play();

	sf::Texture startupTexture1;
	if (!startupTexture1.loadFromFile("Intro1.png")) {
		std::cerr << "ERROR::GAME::Could not load startup image\n";
		return;
	}

	sf::Sprite startupSprite1(startupTexture1);

	sf::Clock time;
	float fadeDuration = 3.f;
	float alpha = 255;

	while (alpha > 0) {
		float deltaTime = time.restart().asSeconds();
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
		float deltaTime = time.restart().asSeconds();
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
		if (event.type == sf::Event::MouseButtonPressed) {
			if (m_gameState == GameState::GameOver) {
				m_livesAmount = 3;
				m_gameState = GameState::InGame;
				initLevel();
			}
		}
	}
}

// Main game loop
void Game::run() {
	while (m_window->isOpen()) {
		pollEvents();
		updateInput();

		updateGameLogic();

		render();
	}
}

// recive the objects from the file
void Game::receiveObjectsFromLevel() {
	m_staticObjects = m_level->getStaticObjectPointers(m_timer);
	m_movingObjects = m_level->getMovingObjectPointers();
}

// handle collisions
void Game::handleCollisions() {
	Mouse* mouse = nullptr;
	// Find the mouse object among the moving objects
	for (auto& obj : m_movingObjects) {
		mouse = dynamic_cast<Mouse*>(obj.get());
		if (mouse) break; // Stop searching once the mouse is found
	}

	if (!mouse) return; // If there's no mouse, no need to check for collisions

	sf::FloatRect mouseBounds = mouse->getBounds();

	// Check collisions with cats
	for (auto& obj : m_movingObjects) {
		Cat* cat = dynamic_cast<Cat*>(obj.get());

		// Check if it's a cat, it's visible, and there's an intersection
		if (cat && cat->isVisible() && mouseBounds.intersects(cat->getBounds())) {
			// Logic when mouse collides with a cat
			m_time.play();
			this->m_livesAmount--;
			this->m_scoreAmount -= 10;
			m_level->resetMoving();
		}
	}

	// search the static objects
	for (auto& obj : m_staticObjects) {
		if (!obj->isVisible()) continue; // Skip invisible objects

		Cheese* cheese = dynamic_cast<Cheese*>(obj.get());
		Key* key = dynamic_cast<Key*>(obj.get());
		RemoveCat* removeCat = dynamic_cast<RemoveCat*>(obj.get());
		Door* door = dynamic_cast<Door*>(obj.get());
		Heart* heart = dynamic_cast<Heart*>(obj.get());
		PuseCats* puseCats = dynamic_cast<PuseCats*>(obj.get());
		AddTime* addTime = dynamic_cast<AddTime*>(obj.get());


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
			m_cat.play();
			removeCat->setVisible(false); // Hide the key
			m_scoreAmount += 5; // Increase the score
			// Logic to hide one cat
			for (auto& catObj : m_movingObjects) {
				Cat* cato = dynamic_cast<Cat*>(catObj.get());
				if (cato && cato->isVisible()) {
					cato->setVisible(false); // Hide the cat
					break; // Stop after hiding one cat
				}
			}
		}
		else if (door && mouseBounds.intersects(door->getBounds()) && m_score.youHaveKey()) {
			m_unlock.play();
			door->setVisible(false); // Hide the key
			m_scoreAmount += 5; // Increase the score
			this->m_keyAmount--; // minus one from the keys counter
		}
		else if (heart && mouseBounds.intersects(heart->getBounds())) {
			heart->setVisible(false); // Hide the heart
			m_scoreAmount += 5; // Increase the score
			this->m_livesAmount++; // add one to the heart counter
		}
		else if (puseCats && mouseBounds.intersects(puseCats->getBounds())) {
			m_pause.play();
			puseCats->setVisible(false); // Hide the PuseCats item
			m_scoreAmount += 5; // Increase the score
			m_catPauseTime = 10.0f; // Start the pause timer
		}
		else if (addTime && mouseBounds.intersects(addTime->getBounds())) {
			m_addTime.play();
			m_currentTime += 10.f; // add 10 sec to the timer
			m_scoreAmount += 5; // Increase the score
			addTime->setVisible(false); //hide the add time icon 
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
	mouse->moveMouse(m_movingObjects, m_staticObjects, moveX, moveY, m_score);
}

// Update game logic based on the current state
void Game::updateGameLogic() 
{
	pollEvents();

    // Update this variable whenever the game state changes
	static GameState lastGameState = GameState::None; // Initialize with an invalid state or a state that represents "no previous state"

	// Music handling based on the game state
	switch (m_gameState) {
	case GameState::MainMenu:
	case GameState::Help:
		if (m_backgroundMusic.getStatus() != sf::Music::Playing) {
			playBackgroundMusic("MainMenu.ogg"); // Plays music for MainMenu and Help
		}
		m_backgroundMusic.setVolume(100);
		break;

	case GameState::InGame:
		if (lastGameState != m_gameState && m_backgroundMusic.getStatus() == sf::Music::Playing) {
			m_backgroundMusic.stop(); // Stop the music if the state has changed and music is playing
		}
		if (m_backgroundMusic.getStatus() != sf::Music::Playing) {
			playBackgroundMusic("InGame.ogg"); // Plays music for InGame
		}
		m_backgroundMusic.setVolume(10);
		break;

	case GameState::Win:
		if (lastGameState != m_gameState && m_backgroundMusic.getStatus() == sf::Music::Playing) {
			m_backgroundMusic.stop(); // Stop the music if the state has changed and music is playing
		}
		if (m_backgroundMusic.getStatus() != sf::Music::Playing) {
			playBackgroundMusic("Win.ogg"); // Plays music for win
		}
		m_backgroundMusic.setVolume(100);
		break;

	case GameState::GameOver:
		if (lastGameState != m_gameState && m_backgroundMusic.getStatus() == sf::Music::Playing) {
			m_backgroundMusic.stop(); // Stop the music if the state has changed and music is playing
		}
		if (m_backgroundMusic.getStatus() != sf::Music::Playing) {
			playBackgroundMusic("GameOver.ogg"); // Plays music for win
		}
		m_backgroundMusic.setVolume(100);
		break;

	default:
		if (m_backgroundMusic.getStatus() == sf::Music::Playing) {
			m_backgroundMusic.stop(); // Stops music if it's playing and the state doesn't require music
		}
		break;
	}

	// Update the lastGameState to the current state after handling the music
	lastGameState = m_gameState;


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

			if (m_livesAmount <= 0)
			{
				m_gameState = GameState::GameOver;
			}

			float deltaTime = clock.restart().asSeconds();
			m_totalGameTime += deltaTime;
		    m_currentTime -= deltaTime; // Decrement the current time by the elapsed time
			if (m_currentTime <= 0 && m_timer) {
				m_time.play();
				m_livesAmount--; // Decrease player's life by one
				m_currentTime = m_timeLimit; // reset the timer
				m_keyAmount = 0; // all levels should start with 0 keys
				std::cout << "Time ends, You lost one Life\n" << "Score: -200\n" << "Restart Level: " << m_levelNum << std::endl << std::endl;
				m_scoreAmount -= 200;
				initLevel();
			}

			if (m_catPauseTime > 0) {
				m_catPauseTime -= deltaTime;
				if (m_catPauseTime < 0) m_catPauseTime = 0;
			}

			m_score.updateScore(m_scoreAmount, m_keyAmount, m_livesAmount, m_levelNum, m_currentTime, m_totalGameTime, m_timer);

			// Correctly find the mouse
			Mouse* mouse = nullptr;
			for (auto& obj : m_movingObjects) {
				if (!mouse) mouse = dynamic_cast<Mouse*>(obj.get());
				if (mouse) break;
			}

			if (mouse) {
				sf::Vector2f mousePos = mouse->getPosition();
				// Iterate over all moving objects to move each cat
				for (auto& obj : m_movingObjects) {
					Cat* cat = dynamic_cast<Cat*>(obj.get());
					if (cat && cat->isVisible()) { // Check if it's a cat and it's visible
						if (m_catPauseTime <= 0) { // Only move cats if pause time has elapsed
							sf::Vector2f catPos = cat->getPosition();
							// Move cat
							cat->moveCat(m_staticObjects, mousePos, catPos, m_score);
						}
					}
				}
			}
		    // Check for level completion
		    if (m_level->therIsNoCheese()) {
				m_levelNum++;
				m_level->updateLevel(m_gameState);
				m_scoreAmount += 20; // Increase the score
				m_scoreAmount += (m_level->m_catNum * 5); // Increase the score
				receiveObjectsFromLevel();
				m_currentTime = 61.f;
		    }
			break;
	    }

	    case GameState::Help:
	    {
		    this->m_menu->update(*this->m_window, m_gameState);
			break;
	    }

		case GameState::Win:
		{
			this->m_winMenu->update(*this->m_window, m_gameState);
			m_levelNum = 0;
			initLevel();

			break;
		}
	}
}

// to play the Background music
void Game::playBackgroundMusic(const std::string& filePath) {
	if (!m_backgroundMusic.openFromFile(filePath)) {
		std::cerr << "ERROR::GAME::Could not load background music file: " << filePath << "\n";
		return;
	}
	m_backgroundMusic.setLoop(true); // Loop the music
	m_backgroundMusic.play();
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
	case GameState::Win:
	{
		m_window->draw(m_spriteWin);
		m_winMenu->draw(*m_window);
		break;
	}
	case GameState::GameOver:
	{
		m_window->draw(m_spriteGameOver);
		break;
	}
	default:
		break;
	}

	m_window->display();
}