#include "Level.h"

Level::Level(sf::RenderWindow& window) : window(window) { this->tileSize = TILE_SIZE; }

Level::~Level() {}

void Level::loadFromFile() {
    std::ifstream file("Level1.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file 'Level1.txt'\n";
    }
    std::string line;
    int y = 0;
    map.resize(14, std::vector<Objects*>(16, nullptr));

    while (std::getline(file, line)) {
        for (int x = 0; x < line.length(); x++) {
            char ch = line[x];
            Objects* obj = nullptr;
            switch (ch) {
            case WALL: {
                obj = new Wall();
                break;
            }
            case CAT: {
                obj = new Cat();
                break;
            }
            case CHEESE: {
                obj = new Cheese();
                break;
            }
            case MOUSE: {
                obj = new Mouse();
                break;
            }
            case DOOR: {
                obj = new Door();
                break;
            }
            case KEY: {
                obj = new Key();
                break;
            }
            case GIFT: {
                obj = new RemoveCat();
                break;
            }
            }
            if (obj != nullptr) {
                obj->setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
                map[y][x] = obj;
            }
        }
        y++;
    }
}

void Level::render() {
    for (const auto& row : map) {
        for (const auto& obj : row) {
            if (obj != nullptr) {
                obj->render(window);
            }
        }
    }
}