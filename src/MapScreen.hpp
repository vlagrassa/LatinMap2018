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
        background.setTextureRect(sf::IntRect(screenCoords.x, screenCoords.y, static_cast<signed>(window.getSize().x), static_cast<signed>(window.getSize().y)));
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
                moveY(-20);
                break;
            case (sf::Keyboard::Down):
                moveY(20);
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
        int temp = dist;
        if (screenCoords.x + temp <= 0)
            temp = 0 - screenCoords.x;
        if (screenCoords.x + temp > static_cast<signed>(background.getTexture()->getSize().x - window.getSize().x))
            temp = static_cast<signed>(background.getTexture()->getSize().x - window.getSize().x) - screenCoords.x;
        
        screenCoords.x += temp;
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            n->data.move(-temp, 0);
        }
    }
    
    void moveY(int dist) {
        int temp = dist;
        if (screenCoords.y + temp < 0)
            temp = 0 - screenCoords.y;
        if (screenCoords.y + temp > static_cast<signed>(background.getTexture()->getSize().y - window.getSize().y))
            temp = static_cast<signed>(background.getTexture()->getSize().y - window.getSize().y) - screenCoords.y;
        
        screenCoords.y += temp;
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            n->data.move(0, -temp);
        }
    }

};

#endif /* MAPSCREEN_H */
