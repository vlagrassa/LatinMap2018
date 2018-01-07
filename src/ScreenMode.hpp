#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class LinkedButton;
class ScreenMode;

class LinkedButton : public sf::Sprite {
public:
    ScreenMode* link;
    
    LinkedButton() {};
    LinkedButton(ScreenMode* link) : link(link) {};
    LinkedButton(const LinkedButton& orig) : link(orig.link) {};
    virtual ~LinkedButton() {};
    
    bool touchingMouse() {
        return getGlobalBounds().contains(sf::Mouse().getPosition().x, sf::Mouse().getPosition().y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
    }
};

class ScreenMode {
public:
    std::vector<LinkedButton> buttons;
    
    ScreenMode() {};
    ScreenMode(const ScreenMode& orig) {};
    virtual ~ScreenMode() {};
    
    ScreenMode* run() {
        return 0;
    };
    
    void createButton(ScreenMode* s) {
        buttons.push_back(LinkedButton(s));
    }
    
private:
    
};

#endif /* SCREENMODE_H */
