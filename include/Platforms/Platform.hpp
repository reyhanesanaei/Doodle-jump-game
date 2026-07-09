#pragma once

#include "Entities/Player.hpp"
#include "Platforms/Spring.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

class Platform
{
public:
    Platform(const sf::Texture& texture, sf::Vector2f position);
    virtual ~Platform() = default;

    virtual void update(float dt);
    virtual void draw(sf::RenderWindow& window) const;
    virtual void onPlayerLanded(Player& player) = 0;
    virtual bool isSolid() const;
    virtual bool shouldRemove(float windowHeight) const;

    void move(float dy);
    float getY() const;
    sf::FloatRect getBounds() const;

    void attachSpring(std::unique_ptr<Spring> spring);
    Spring* getSpring();
    const Spring* getSpring() const;

protected:
    sf::Sprite m_sprite;
    std::unique_ptr<Spring> m_spring;
};
