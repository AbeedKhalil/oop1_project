#include "Map.h"
namespace fs = std::filesystem;

Map::Map() : m_level(1) {
    // Preload textures to improve performance and handle missing files
    preloadTextures();

    // Load the first level
    loadLevel();
}

Map::~Map() {}

void Map::preloadTextures() {
    if (!wallTexture.loadFromFile("Wall.png")) {
        std::cerr << "Failed to load wall texture\n";
    }

    if (!mouseTexture.loadFromFile("Mouse.png")) {
        std::cerr << "Failed to load mouse texture\n";
    }

    if (!tileTexture.loadFromFile("TileSheet.png")) {
        std::cerr << "Failed to load tile texture\n";
    }
}

void Map::loadLevel() {
    // Clear previous level data
    tiles.clear();
    m_map.clear();

    // Construct file path using std::filesystem to handle paths correctly
    std::string filename = "Level" + std::to_string(m_level) + ".txt";
    if (!fs::exists(filename)) {
        std::cerr << "Error: File does not exist - " << filename << std::endl;
        return;
    }

    // Read level from file
    if (!readLevelFromFile(m_level)) {
        std::cerr << "Failed to load level " << m_level << "\n";
        return;
    }

    // Initialize tiles based on the loaded level
    initTiles();
}

void Map::initTiles() {
    tiles.resize(m_map.size(), std::vector<sf::Sprite>(m_map[0].size()));

    for (int i = 0; i < m_map.size(); i++) {
        for (int j = 0; j < m_map[i].size(); j++) {
            sf::Sprite sprite;

            switch (m_map[i][j]) {
            case WALL:
                sprite.setTexture(wallTexture);
                break;
            case MOUSE:
                sprite.setTexture(mouseTexture);
                break;
            default:
                continue; // Skip if it's not a recognized character
            }

            sprite.setPosition(j * 60, i * 60);
            tiles[i][j] = sprite;
        }
    }
}

void Map::render(sf::RenderTarget& target) {
    for (const auto& row : tiles) {
        for (const auto& tile : row) {
            target.draw(tile);
        }
    }
}

void Map::updateLevel() {
    m_level++;
    loadLevel(); // Reload the level with updated level number
}

bool Map::readLevelFromFile(const int level) {
    std::string filename = "Level" + std::to_string(level) + ".txt";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    int height, width;
    file >> height >> width;
    m_map.resize(height, std::vector<char>(width, ' '));
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < height; ++i) {
        std::string line;
        if (std::getline(file, line)) {
            for (int j = 0; j < width && j < line.size(); ++j) {
                m_map[i][j] = line[j];
            }
        }
        else {
            std::cerr << "Error reading map file: " << filename << std::endl;
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}
