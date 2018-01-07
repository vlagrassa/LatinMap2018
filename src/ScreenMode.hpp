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
    std::vector<LinkedButton> buttons;
    sf::Window& window;
    
    ScreenMode(sf::Window& window) : window(window) {};
    ScreenMode(const ScreenMode& orig) : window(orig.window) {};
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
        buttons.push_back(LinkedButton(s, window));
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (LinkedButton b : buttons) {
            target.draw(b);
        }
    }
    
private:
    
};

#endif /* SCREENMODE_H */
