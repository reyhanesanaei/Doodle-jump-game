#include "SFML/Graphics.hpp"
#include <iostream>
#include "Platform.h"
using namespace std;

Platform::Platform (const sf::Vector2f& position) : sprite(normalPlatform) {
    if (!normalPlatform.loadFromFile("assets/normal_platform.png")) {
        cerr << "Failed to load normal platform.\n";
    }

    sprite = sf::Sprite(normalPlatform);
    sprite.setPosition(position);
    
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Platform::getBounds() const {
    return sprite.getGlobalBounds();
}
