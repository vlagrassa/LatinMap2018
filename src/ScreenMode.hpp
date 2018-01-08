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
    bool pressed;
    
    LinkedButton(ScreenMode& link, sf::Window& window) : link(link), window(window), pressed(0) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Red);
        setOutlineThickness(5);
        setPosition(10, 20);
    };
    
    LinkedButton(ScreenMode* link, sf::Window& window) : link(*link), window(window), pressed(0) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Cyan);
        setOutlineThickness(5);
        setPosition(350, 20);
    }
    
    LinkedButton(const LinkedButton& orig) : link(orig.link), window(orig.window), pressed(0) {
        setSize(sf::Vector2f(100, 50));
        setOutlineColor(sf::Color::Green);
        setOutlineThickness(5);
        setPosition(10, 20);
    };
    
    virtual ~LinkedButton() {};
    
    bool touchingMouse() {
//        std::cout << "\nWindow is:" << &window << "\n";
//        std::cout << "Relative mouse x is " << sf::Mouse::getPosition().x << "\n";
//        std::cout << "Made it here...\n";
        return getGlobalBounds().contains(sf::Mouse().getPosition(window).x, sf::Mouse().getPosition(window).y);
    }
    
    bool clicked() {
        return touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left);
//        if (touchingMouse() && sf::Mouse().isButtonPressed(sf::Mouse().Left)) {
//            if (!pressed) {
//                pressed = true;
//                return true;
//            }
//        } else {
//            pressed = false;
//        }
//        return false;
    }
};

class ScreenMode : public sf::Drawable {
public:
    Queue<LinkedButton&> buttons;
    sf::Window& window;
    
    ScreenMode(sf::Window& window) : window(window) {};
    ScreenMode(const ScreenMode& orig) : window(orig.window) {};
    virtual ~ScreenMode() {};
    
    ScreenMode* run() {
        if (!buttons.isEmpty()) {
            for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
                n->data;
//                std::cout << "Trying Button " << &n->data;
//                std::cout << " @ node " << &n << "\n";
//                std::cout << "Link is " << &n->data.link;
//                std::cout << "\nClicked is " << n->data.clicked();
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
    
    void createButton(ScreenMode& s) {
        LinkedButton temp(s, window);
        buttons.enqueue(temp);
    }
    
    void createNullButton() {
        LinkedButton temp(0, window);
        buttons.enqueue(temp);
    }
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (Node<LinkedButton&>* n = buttons.head; n != 0; n = n->next) {
            target.draw(n->data);
        }
    }
    
private:
    
};

#endif /* SCREENMODE_H */
