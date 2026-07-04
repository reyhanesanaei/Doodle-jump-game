#include "Player.h"
#include "Platform.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode({600, 1000}), "Simple Doodle Jump");
    
    Player player;

    vector<Platform> platforms;
    //just testing
    platforms.emplace_back(sf::Vector2f{250.f, 900.f});
    platforms.emplace_back(sf::Vector2f{120.f, 750.f});
    platforms.emplace_back(sf::Vector2f{350.f, 600.f});
    platforms.emplace_back(sf::Vector2f{180.f, 450.f});
    platforms.emplace_back(sf::Vector2f{280.f, 300.f});

    sf::Clock clock;
    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        const float dt = clock.restart().asSeconds();
        player.update(dt);
        
        window.clear();
        
        //check every platform
        for (Platform& platform : platforms) {
            platform.draw(window);
            //jump if only there is a platform to jump on
            if (player.isFalling() && 
                player.getBounds().findIntersection(platform.getBounds())) {
                player.jump();
            }        
        }

        player.draw(window); 

        window.display();
    }

    return 0;
}