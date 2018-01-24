#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"
#include "Defaults.hpp"

class LinkedButton;
class ScreenMode;

class LinkedButton : public sf::Drawable {
public:
    ScreenMode& link;
    sf::Shape& outline;
    
    LinkedButton(sf::Vector2f location, ScreenMode& link) : outline(*new sf::RectangleShape(location)), link(link) {
        outline.setPosition(location);
    };
    
    LinkedButton(sf::Shape& orig, ScreenMode& link) : outline(orig), link(link) {};
    
    LinkedButton(sf::Vector2f location, ScreenMode* link) : outline(*new sf::RectangleShape(location)), link(*link) {
        outline.setPosition(location);
    };
    
    LinkedButton(sf::Shape& orig, ScreenMode* link) : outline(orig), link(*link) {};
    
    LinkedButton(const LinkedButton& orig) : outline(orig.outline), link(orig.link) {
        outline.setPosition(orig.outline.getPosition());
    };
    
    virtual ~LinkedButton() {};
    
    bool touchingMouse() {
        return outline.getGlobalBounds().contains(sf::Mouse().getPosition(DEFAULT_WINDOW).x, sf::Mouse().getPosition(DEFAULT_WINDOW).y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
    }
};

class ScreenMode : public sf::Drawable {
public:
    LinkedList<LinkedButton&> buttons;
    std::vector<sf::Text> displayText;
    bool showPrevious;
    
    ScreenMode() : showPrevious(false) {};
    ScreenMode(const ScreenMode& orig) : showPrevious(false) {};
    virtual ~ScreenMode() {};
    
    virtual void update(sf::Event event) {};
    
    virtual ScreenMode* run(sf::Event event) {
        return checkButtons();
    };
    
    ScreenMode* checkButtons() {
        for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
            if (n->data.clicked()) {
                return &n->data.link;
            }
        }
        return this;
    };
    
    void addButton(LinkedButton& b) {
        buttons.add(b);
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
        for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
            target.draw(n->data);
        }
    }
};

#endif /* SCREENMODE_H */
