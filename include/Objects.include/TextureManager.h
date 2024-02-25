#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class TextureManager {
public:
    static TextureManager& getInstance() {
        static TextureManager instance; // Guaranteed to be destroyed and instantiated on first use
        return instance;
    }

    sf::Texture& getTexture(const std::string& filename) {
        // Check if texture is already loaded
        auto it = textures.find(filename);
        if (it != textures.end()) {
            return it->second;
        }

        // Load texture and add it to the map
        sf::Texture texture;
        if (texture.loadFromFile(filename)) {
            textures[filename] = texture;
        }

        return textures[filename];
    }

private:
    std::map<std::string, sf::Texture> textures; // Map to store textures

    // Private Constructor & Destructor
    TextureManager() {}
    ~TextureManager() {}

    // Delete copy constructor and assignment operation
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;
};
