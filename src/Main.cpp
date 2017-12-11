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
}