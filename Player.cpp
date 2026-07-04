#include "Player.h"
using namespace std;

Player::Player() : sprite(leftTexture) {

    sprite.setPosition({300.f, 500.f}); // Start position

    sprite.setScale({0.2f , 0.2f});

    speed = 300.f;

    if (!leftTexture.loadFromFile("assets/left_doodle.png")) {
        cerr << "Failed to load texture!" << endl;
    }
   
    if (!rightTexture.loadFromFile("assets/right_doodle.png")) {
        cerr << "Failed to load texture!" << endl;
    }

    sprite = sf::Sprite(leftTexture);
    sprite.setPosition({300.f, 500.f});
    

}

void Player::update(float dt){
    // Update player position based on speed and delta time and gravity    

    velocity.x = 0.f; // Reset horizontal velocity each frame

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        sprite.setTexture(leftTexture);

        velocity.x = -speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        sprite.setTexture(rightTexture);
        
        velocity.x = speed;
    }
    
    velocity.y += gravity * dt; // Apply gravity to vertical velocity

    sprite.move(velocity * dt);
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::jump() {
    velocity.y = -800.f; // Set vertical velocity to jump
}

bool Player::isFalling() const {
    return velocity.y > 0.f; // Check if the player is falling
}