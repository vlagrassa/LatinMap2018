#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class LinkedButton;
class ScreenMode;

class LinkedButton : public sf::RectangleShape {
public:
    ScreenMode* link;
    sf::Window& window;
    
    LinkedButton(ScreenMode* link, sf::Window& window) : link(link), window(window) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Red);
        setOutlineThickness(5);
        setPosition(10, 20);
    };
    LinkedButton(const LinkedButton& orig) : link(orig.link), window(orig.window) {};
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
    std::vector<LinkedButton> buttons;
    
    ScreenMode() {};
    ScreenMode(const ScreenMode& orig) {};
    virtual ~ScreenMode() {};
    
    ScreenMode* run() {
        if (buttons.size() > 0) {
            for (LinkedButton b : buttons) {
                if (b.clicked()) {
                    return b.link;
                }
            }
        }
        return this;
    };
    
    void createButton(ScreenMode* s) {
        buttons.push_back(LinkedButton(s));
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (LinkedButton b : buttons) {
            target.draw(b);
        }
    }
    
private:
    
};

#endif /* SCREENMODE_H */
