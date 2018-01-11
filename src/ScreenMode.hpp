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
    
    LinkedButton(sf::Vector2f location, ScreenMode& link, sf::Window& window) : link(link), window(window) {
        setPosition(location);
    };
    
    LinkedButton(sf::RectangleShape& orig, ScreenMode& link, sf::Window& window) : sf::RectangleShape(orig), link(link), window(window) {};
    
    LinkedButton(sf::Vector2f location, ScreenMode* link, sf::Window& window) : link(*link), window(window) {
        setPosition(location);
    };
    
    LinkedButton(sf::RectangleShape& orig, ScreenMode* link, sf::Window& window) : sf::RectangleShape(orig), link(*link), window(window) {};
    
    LinkedButton(const LinkedButton& orig) : link(orig.link), window(orig.window) {
        setPosition(orig.getPosition());
    };
    
    virtual ~LinkedButton() {};
    
    void setDefaultLook() {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(5);
    }
    
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
    bool showPrevious;
    
    ScreenMode(sf::Window& window) : window(window), showPrevious(false) {};
    ScreenMode(const ScreenMode& orig) : window(orig.window), showPrevious(false) {};
    virtual ~ScreenMode() {};
    
    virtual ScreenMode* run(sf::Event event) {
        return checkButtons();
    };
    
    virtual void update(sf::Event) {};
    
    ScreenMode* checkButtons() {
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            if (n->data.clicked()) {
                return &n->data.link;
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
