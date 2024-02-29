#include "Level.h"

Level::Level(sf::RenderWindow& window) : m_window(window), m_tileSize(TILE_SIZE), m_level(1), m_cheeseCount(0) {}

void Level::loadFromFile(int level)
{
    m_level = level;
    m_timerOn = false;
    m_catNum = 0;
    m_static.clear();
    m_moving.clear();
    initialMovingPositions.clear();
    std::string filename = "Level" + std::to_string(m_level) + ".txt";
    std::ifstream file(filename);
    if (!file) {
        return;
    }
    std::string line;
    int y = 0;
    m_cheeseCount = 0;
    while (std::getline(file, line)) {
        std::vector<std::shared_ptr<Objects>> rowStatic, rowMoving;
        for (int x = 0; x < static_cast<int>(line.length()); ++x) {
            char ch = line[x];
            std::shared_ptr<Objects> obj = nullptr;
            switch (ch) {
            case WALL: obj = std::make_shared<Wall>(); break;
            case CAT:
            {
                obj = std::make_shared<Cat>();
                m_catNum++;
                break;
            }
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
            case ADDTIME:
            {
                obj = std::make_shared<AddTime>();
                m_timerOn = true;
                break;
            }
            case GIFT: obj = std::make_shared<RemoveCat>(); break;
            default: continue;
            }
            if (std::dynamic_pointer_cast<Mouse>(obj) != nullptr || std::dynamic_pointer_cast<Cat>(obj) != nullptr)
            {
                obj->setPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
                initialMovingPositions.push_back(obj->getPosition());
                rowMoving.push_back(std::move(obj));
            }
            else
            {
                obj->setPosition(static_cast<float>(x * m_tileSize), static_cast<float>(y * m_tileSize));
                rowStatic.push_back(std::move(obj));
            }
        }
        m_static.push_back(std::move(rowStatic));
        m_moving.push_back(std::move(rowMoving));
        ++y;
    }
}

void Level::resetMoving() {
    size_t index = 0;
    for (auto& row : m_moving) {
        for (auto& obj : row) {
            if (index < initialMovingPositions.size()) {
                obj->setPosition(initialMovingPositions[index].x, initialMovingPositions[index].y);
                index++;
            }
        }
    }
}

void Level::updateLevel(GameState& gameState)
{
    if (m_level >= MAX_LEVELS) {
        gameState = GameState::Win;
    }
    else {
        m_level++;
        loadFromFile(m_level); // Attempt to load the new level
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

std::vector<std::shared_ptr<Objects>> Level::getStaticObjectPointers(bool& timer) const {
    timer = m_timerOn;
    std::vector<std::shared_ptr<Objects>> staticObjects;
    for (const auto& row : m_static) {
        for (const auto& obj : row) {
            if (obj) {
                staticObjects.push_back(obj);
            }
        }
    }
    return staticObjects;
}

std::vector<std::shared_ptr<Objects>> Level::getMovingObjectPointers() const {
    std::vector<std::shared_ptr<Objects>> movingObjects;
    for (const auto& row : m_moving) {
        for (const auto& obj : row) {
            if (obj) {
                movingObjects.push_back(obj);
            }
        }
    }
    return movingObjects;
}

void Level::render() {
    for (const auto& row : m_static) {
        for (const auto& obj : row) {
            if (obj && obj->isVisible()) {
                obj->render(m_window);
            }
        }
    }

    for (const auto& row : m_moving) {
        for (const auto& object : row) {
            if (object && object->isVisible()) {
                object->render(m_window);
            }
        }
    }
}