#include "Game.h"

void Game::initWindow()
{
	this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "Mouse VS Cats", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}


void Game::initObjects()
{
	objects.push_back(std::make_unique<Mouse>());
	objects.push_back(std::make_unique<Cat>());
}

Game::Game()
{
	this->initWindow();
	this->initObjects();
}

Game::~Game() {}

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

void Game::update() {
	updatePollEvent();
	updateInput();
	// Update all objects
	for (auto& obj : objects) {
		obj->update();
	}
}

void Game::render() {
	window->clear();
	levelMap.render(*window); // Render the map first
	// Then render all objects
	for (auto& obj : objects) {
		obj->render(*window);
	}
	window->display();
}