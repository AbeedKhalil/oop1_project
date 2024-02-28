#include "Level.h"

Level::Level(sf::RenderWindow& window) : m_window(window), m_tileSize(TILE_SIZE), m_level(1), m_cheeseCount(0) {}

void Level::loadFromFile()
{
    m_map.clear();
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
        std::vector<std::shared_ptr<Objects>> row;
        std::vector<std::shared_ptr<Objects>> rowMovingObjects;
        for (int x = 0; x < static_cast<int>(line.length()); ++x) {
            char ch = line[x];
            std::shared_ptr<Objects> obj = nullptr;
            switch (ch) {
            case WALL: obj = std::make_shared<Wall>(); break;
            case CAT: obj = std::make_shared<Cat>(); break;
            case CHEESE:
            {
                obj = std::make_shared<Cheese>();
                m_cheeseCount++;
                break;
            }
            case MOUSE: obj = std::make_shared<Mouse>(); break;
            case HEART: obj = std::make_shared<Heart>(); break;
            case DOOR: obj = std::make_shared<Door>(); break;
            case KEY: obj = std::make_shared<Key>(); break;
            case PUSECATS: obj = std::make_shared<PuseCats>(); break;
            case ADDTIME: obj = std::make_shared<AddTime>(); break;
            case GIFT: obj = std::make_shared<RemoveCat>(); break;
            default: continue;
            }
            if (std::dynamic_pointer_cast<Mouse>(obj) != nullptr || std::dynamic_pointer_cast<Cat>(obj) != nullptr)
            {
                obj->setPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
                rowMovingObjects.push_back(std::move(obj));
            }
            else
            {
                obj->setPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
                row.push_back(std::move(obj));
            }
        }
        m_map.push_back(std::move(row));
        m_movingObjects.push_back(std::move(rowMovingObjects));
        ++y;
    }
}

void Level::updateLevel(GameState& gameState)
{
    if (m_level >= MAX_LEVELS) {
        gameState = GameState::Win;
    }
    else {
        m_level++;
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

std::vector<std::shared_ptr<Objects>> Level::getSharedObjectPointers() const {
    std::vector<std::shared_ptr<Objects>> allObjects;
    for (const auto& row : m_map) {
        for (const auto& obj : row) {
            if (obj) {
                allObjects.push_back(obj);
            }
        }
    }
    return allObjects;
}

std::vector<std::shared_ptr<Objects>> Level::getMovingSharedObjectPointers() const
{
    std::vector<std::shared_ptr<Objects>> movingObjects;
    for (const auto& row : m_movingObjects) {
        for (const auto& obj : row) {
            if (obj) {
                movingObjects.push_back(obj);
            }
        }
    }
    return movingObjects;
}

void Level::render() {
    for (const auto& row : m_map) {
        for (const auto& obj : row) {
            if (obj && obj->isVisible()) {
                obj->render(m_window);
            }
        }
    }

    for (const auto& row : m_movingObjects) {
        for (const auto& obj : row) {
            if (obj && obj->isVisible()) {
                obj->render(m_window);
            }
        }
    }
}