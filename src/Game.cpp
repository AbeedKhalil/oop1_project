#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "Mouse VS Cats", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initMenu()
{
	this->menu = new Menu();
}


void Game::initObjects()
{
	objects.push_back(std::make_unique<Mouse>());
	objects.push_back(std::make_unique<Cat>());
}

void Game::initTileSheet()
{
	if (!this->tileSheet.loadFromFile("TileSheet.png"))
	{
		std::cout << "ERROR::GAME::TILESHEET::INITTEXTURE::could not load texture file.\n";
	}

	sprite.setTexture(this->tileSheet);
}

void Game::initMap()
{
	this->map = new Map(60, 60, &this->tileSheet, 60);
}

Game::Game()
{
	this->initWindow();
	this->initTileSheet();
	this->initObjects();
	this->initMap();
	this->initMenu();
}

Game::~Game()
{
	delete this->map;
	delete this->menu;
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Game::updatePollEvent()
{
	sf::Event ev;
	while (this->window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
	}
}

void Game::updateInput()
{
	// Move Mouse
	for (auto& obj : objects) {
		Mouse* mouse = dynamic_cast<Mouse*>(obj.get()); // Try to cast to Mouse*
		if (mouse != nullptr) // If it's a Mouse
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				mouse->move(-1.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				mouse->move(1.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				mouse->move(0.f, -1.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
			{
				mouse->move(0.f, 1.f);
			}
		}
	}

}

void Game::updateMap()
{
	this->map->update();
}

void Game::renderMap()
{
	this->map->render(*this->window);
}

void Game::update() {
	updatePollEvent();
	updateInput();

	// Temporary pointers for mouse and cat
	Mouse* mouse = nullptr;
	Cat* cat = nullptr;

	// Iterate through all objects to find the mouse and the cat
	for (auto& obj : objects) {
		if (!mouse) mouse = dynamic_cast<Mouse*>(obj.get());
		if (!cat) cat = dynamic_cast<Cat*>(obj.get());

		// Break early if both are found
		if (mouse && cat) break;
	}

	// If both mouse and cat are found, make the cat follow the mouse
	if (mouse && cat) {
		sf::Vector2f mousePos = mouse->getPosition();
		sf::Vector2f catPos = cat->getPosition();

		// Calculate the vector from cat to mouse and normalize it
		sf::Vector2f direction = mousePos - catPos;
		float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (magnitude > 0) { // Avoid division by zero
			direction.x /= magnitude;
			direction.y /= magnitude;
		}

		// Update cat's position to follow the mouse, adjusting speed as necessary
		cat->move(direction.x * cat->getMovementSpeed(), direction.y * cat->getMovementSpeed());
	}

	// Update logic for all objects
	for (auto& obj : objects) {
		obj->update();
	}

	this->updateMap();
}


void Game::render() {
	window->clear();
	window->draw(sprite);
	this->menu->draw(*this->window);
	this->renderMap();
	// Then render all objects
	for (auto& obj : objects) {
		obj->render(*window);
	}
	window->display();
}