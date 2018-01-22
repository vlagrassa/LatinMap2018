#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"
#include "Defaults.hpp"

class LinkedButton;
class ScreenMode;

class LinkedButton : public sf::RectangleShape {
public:
    ScreenMode& link;
    
    LinkedButton(sf::Vector2f location, ScreenMode& link) : link(link) {
        setPosition(location);
    };
    
    LinkedButton(sf::RectangleShape& orig, ScreenMode& link) : sf::RectangleShape(orig), link(link) {};
    
    LinkedButton(sf::Vector2f location, ScreenMode* link) : link(*link) {
        setPosition(location);
    };
    
    LinkedButton(sf::RectangleShape& orig, ScreenMode* link) : sf::RectangleShape(orig), link(*link) {};
    
    LinkedButton(const LinkedButton& orig) : link(orig.link) {
        setPosition(orig.getPosition());
    };
    
    virtual ~LinkedButton() {};
    
    void setDefaultLook() {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(5);
    }
    
    bool touchingMouse() {
        return getGlobalBounds().contains(sf::Mouse().getPosition(DEFAULT_WINDOW).x, sf::Mouse().getPosition(DEFAULT_WINDOW).y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
    }
};

class ScreenMode : public sf::Drawable {
public:
    Queue<LinkedButton&> buttons;
    std::vector<sf::Text> displayText;
    bool showPrevious;
    
    ScreenMode() : showPrevious(false) {};
    ScreenMode(const ScreenMode& orig) : showPrevious(false) {};
    virtual ~ScreenMode() {};
    
    virtual ScreenMode* run(sf::Event event) {
        return checkButtons();
    };
    
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
    
    void addText(std::string text, sf::Vector2f pos, unsigned int size = 35, sf::Color color = sf::Color::Black) {
        sf::Text temp(text, DEFAULT_FONT);
        temp.setCharacterSize(size);
        temp.setPosition(pos);
        temp.setFillColor(color);
        displayText.push_back(temp);
        
    }
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (sf::Text t : displayText) {
            target.draw(t);
        }
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            target.draw(n->data);
        }
    }
};

#endif /* SCREENMODE_H */
