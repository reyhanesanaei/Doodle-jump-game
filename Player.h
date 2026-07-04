#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Player {
private:
    float speed;
    sf::Texture leftTexture;
    sf::Texture rightTexture;
    sf::Sprite sprite;
    sf::Vector2f velocity = {0.f, 0.f};

public:

    Player();
    const float gravity = 1500.f;
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void jump();
    sf::FloatRect getBounds() const;
    bool isFalling() const;

};