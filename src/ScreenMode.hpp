#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"

class LinkedButton;
class ScreenMode;

class LinkedButton : public sf::RectangleShape {
public:
    ScreenMode& link;
    sf::Window& window;
    
    LinkedButton(ScreenMode& link, sf::Window& window) : link(link), window(window) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Red);
        setOutlineThickness(5);
        setPosition(10, 20);
    };
    
    LinkedButton(ScreenMode* link, sf::Window& window) : link(*link), window(window) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Cyan);
        setOutlineThickness(5);
        setPosition(350, 20);
    }
    
    LinkedButton(const LinkedButton& orig) : link(orig.link), window(orig.window) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(5);
        setPosition(10, 20);
    };
    
    virtual ~LinkedButton() {};
    
    bool touchingMouse() {
        return getGlobalBounds().contains(sf::Mouse().getPosition(window).x, sf::Mouse().getPosition(window).y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
    }
};

class ScreenMode : public sf::Drawable {
public:
    Queue<LinkedButton&> buttons;
    sf::Window& window;
    
    ScreenMode(sf::Window& window) : window(window) {};
    ScreenMode(const ScreenMode& orig) : window(orig.window) {};
    virtual ~ScreenMode() {};
    
    virtual ScreenMode* run(sf::Event event) {
        return checkButtons();
    };
    
    virtual void update(sf::Event) {};
    
    ScreenMode* checkButtons() {
        if (!buttons.isEmpty()) {
            for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
                if (n->data.clicked()) {
                    return &n->data.link;
                }
            }
        }
        return this;
    };
    
    void addButton(LinkedButton& b) {
        buttons.enqueue(b);
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            target.draw(n->data);
        }
    }
};

#endif /* SCREENMODE_H */
