#include "Level.h"

Level::Level(sf::RenderWindow& window) : m_window(window), m_tileSize(TILE_SIZE), m_level(0), m_cheeseCount(0) {}

void Level::loadFromFile()
{
    m_map.clear();
    m_level++;
    std::string filename = "Level" + std::to_string(m_level) + ".txt";
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file " << filename << ". Loading default level instead." << std::endl;
        // Consider loading a default level or taking other error recovery actions
        return;
    }
    std::string line;
    int y = 0;
    m_cheeseCount = 0;
    while (std::getline(file, line)) {
        std::vector<std::unique_ptr<Objects>> row;
        for (int x = 0; x < static_cast<int>(line.length()); ++x) {
            char ch = line[x];
            std::unique_ptr<Objects> obj = nullptr;
            switch (ch) {
            case WALL: obj = std::make_unique<Wall>(); break;
            case CAT: obj = std::make_unique<Cat>(); break;
            case CHEESE:
            {
                obj = std::make_unique<Cheese>();
                m_cheeseCount++;
                break;
            }
            case MOUSE: obj = std::make_unique<Mouse>(); break;
            case DOOR: obj = std::make_unique<Door>(); break;
            case KEY: obj = std::make_unique<Key>(); break;
            case GIFT: obj = std::make_unique<RemoveCat>(); break;
            default: continue;
            }
            obj->setPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
            row.push_back(std::move(obj));
        }
        m_map.push_back(std::move(row));
        ++y;
    }
}

void Level::updateLevel()
{
    if (m_level >= MAX_LEVELS) {
        std::cout << "Congratulations! You've completed all levels." << std::endl;
    }
    else {
        loadFromFile(); // Attempt to load the new level
    }
}


void Level::updateCheeseNum()
{
    m_cheeseCount--;
}

bool Level::therIsNoCheese() const
{
    if (m_cheeseCount <= 0) {
        return true;
    }

    else {
        return false;
    }
}

std::vector<Objects*> Level::getRawObjectPointers() const {
    std::vector<Objects*> rawPointers;
    for (const auto& row : m_map) {
        for (const auto& objPtr : row) {
            if (objPtr) {
                rawPointers.push_back(objPtr.get());
            }
        }
    }
    return rawPointers;
}

void Level::render() {
    for (const auto& row : m_map) {
        for (const auto& obj : row) {
            if (obj && obj->isVisible()) {
                obj->render(m_window);
            }
        }
    }
}