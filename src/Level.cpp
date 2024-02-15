#include "Level.h"

Level::Level(sf::RenderWindow& window) : window(window), tileSize(TILE_SIZE) {}

void Level::loadFromFile() {
    std::ifstream file("Level1.txt");
    if (!file) {
        std::cerr << "Error opening file 'Level1.txt'" << std::endl;
        return;
    }

    std::string line;
    int y = 0;
    map.clear();
    while (std::getline(file, line)) {
        std::vector<std::unique_ptr<Objects>> row;
        for (int x = 0; x < static_cast<int>(line.length()); ++x) {
            char ch = line[x];
            std::unique_ptr<Objects> obj = nullptr;
            switch (ch) {
            case WALL: obj = std::make_unique<Wall>(); break;
            case CAT: obj = std::make_unique<Cat>(); break;
            case CHEESE: obj = std::make_unique<Cheese>(); break;
            case MOUSE: obj = std::make_unique<Mouse>(); break;
            case DOOR: obj = std::make_unique<Door>(); break;
            case KEY: obj = std::make_unique<Key>(); break;
            case GIFT: obj = std::make_unique<RemoveCat>(); break;
            default: continue;
            }
            obj->setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
            row.push_back(std::move(obj));
        }
        map.push_back(std::move(row));
        ++y;
    }
}

std::vector<Objects*> Level::getRawObjectPointers() const {
    std::vector<Objects*> rawPointers;
    for (const auto& row : map) {
        for (const auto& objPtr : row) {
            if (objPtr) {
                rawPointers.push_back(objPtr.get());
            }
        }
    }
    return rawPointers;
}

void Level::render() {
    for (const auto& row : map) {
        for (const auto& obj : row) {
            if (obj) {
                obj->render(window);
            }
        }
    }
}