#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "MapPoint.hpp"

int main() {
    std::cout << "Salve, munde!" << "\n";
    MapPoint test1(10, 10);
    
    sf::Vector2f testVector(27, 42);
    MapPoint test2(testVector);
    
    std::cout << "Test 1: (" << test1.getPosition().x << ", " << test1.getPosition().y << ")\n";
    std::cout << "Test 2: (" << test2.getPosition().x << ", " << test2.getPosition().y << ")\n";
    
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Latin Map Project");
    
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::White);
        
        window.draw(test1);
        window.draw(test2);
        
        window.display();
    }
}