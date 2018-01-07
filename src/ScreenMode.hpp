#ifndef SCREENMODE_H
#define SCREENMODE_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class ScreenMode {
public:
    ScreenMode() {};
    ScreenMode(const ScreenMode& orig) {
        for (ScreenMode* s : orig.references) {
            references.push_back(s);
        }
    };
    virtual ~ScreenMode() {};
    
    ScreenMode* run() {
        if (references.size() > 0) {
            return references.at(0);
        } else {
            return 0;
        }
    };
    
    void addReference(ScreenMode* s) {
        references.push_back(s);
    }
    std::vector<ScreenMode*> references;
private:
    
};

class LinkedButton : public sf::Sprite {
public:
    ScreenMode* link;
    
    LinkedButton() {};
    LinkedButton(const LinkedButton& orig) : link(orig.link) {};
    virtual ~LinkedButton() {};
    
    bool touchingMouse() {
        return getGlobalBounds().contains(sf::Mouse().getPosition().x, sf::Mouse().getPosition().y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
    }
};

#endif /* SCREENMODE_H */
