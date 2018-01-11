#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"
#include "ScreenMode.hpp"

class MapScreen : public ScreenMode {
public:
    sf::Sprite background;
    sf::Vector2i screenCoords;
    
    MapScreen(sf::Window& window, const sf::Texture* texture) : ScreenMode(window) {
        background.setTexture(*texture);
        screenCoords.x = 0;
        screenCoords.y = 0;
    };
    
    MapScreen(const MapScreen& orig) : MapScreen(orig.window, orig.background.getTexture()) {};
    
    virtual ~MapScreen() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(background);
        ScreenMode::draw(target, states);
    }
    
    virtual ScreenMode* run(sf::Event event) {
        moveScroll(event);
        background.setTextureRect(sf::IntRect(screenCoords.x, screenCoords.y, window.getSize().x, window.getSize().y));
        return checkButtons();
    };
    
    virtual void update(sf::Event event) {
        if (event.type == sf::Event::KeyPressed) moveArrows(event);
    }
    
    void moveArrows(sf::Event event) {
        switch (event.key.code) {
            case (sf::Keyboard::Left):
                moveX(-10);
                break;
            case (sf::Keyboard::Right):
                moveX(10);
                break;
            case (sf::Keyboard::Up):
                moveY(-10);
                break;
            case (sf::Keyboard::Down):
                moveY(10);
                break;
            default:
                break;
        }
    }
    
    void moveScroll(sf::Event event) {
        moveX(-2 * ((event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) ? event.mouseWheelScroll.delta : 0));
        moveY(-2 * ((event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)   ? event.mouseWheelScroll.delta : 0));
    }
    
    void move(int x, int y) {
        moveX(x);
        moveY(y);
    }
    
    void moveX(int dist) {
        screenCoords.x += dist;
        if (screenCoords.x < 0) screenCoords.x = 0;
        if (screenCoords.x > background.getTexture()->getSize().x - window.getSize().x) screenCoords.x = background.getTexture()->getSize().x - window.getSize().x;
    }
    
    void moveY(int dist) {
        screenCoords.y += dist;
        if (screenCoords.y < 0) screenCoords.y = 0;
        if (screenCoords.x > background.getTexture()->getSize().x - window.getSize().x) screenCoords.x = background.getTexture()->getSize().x - window.getSize().x;
    }

};

#endif /* MAPSCREEN_H */
