#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "MapPoint.hpp"
#include "Utils.hpp"

int main() {
    std::cout << "Salve, munde!" << "\n";
    MapPoint test1(10, 10, "Test 1", "This is a test", 5, 5);
    
    sf::Vector2f testVector(27, 42);
    MapPoint test2(testVector, "Test 1", "This is a test", 5, 5);
    
    std::cout << "Test 1: (" << test1.getPosition().x << ", " << test1.getPosition().y << ")\n";
    std::cout << "Test 2: (" << test2.getPosition().x << ", " << test2.getPosition().y << ")\n";
    
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Latin Map Project");
    
    //sf::Texture defaultPoint;
    //defaultPoint.loadFromFile("res/x.jpg"); //Image from https://www.freepik.com/free-icon/x-circle_692346.htm
    
    //test1.setTexture(defaultPoint);
    //test2.setTexture(defaultPoint);
    
    test1.setScale(0.05, 0.05);
    test2.setScale(0.05, 0.05);
    
    Node<MapPoint> testNode1(test1);
    Node<MapPoint> testNode2(test2);
    testNode1.next = &testNode2;
    Stack<MapPoint> testStack(testNode1);
    testStack.push(testNode2);
    
    
//    while (window.isOpen()) {
//
//        sf::Event event;
//        
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//        }
//        
//        window.clear(sf::Color::White);
//        
//        window.draw(test1);
//        window.draw(test2);
//        
//        window.display();
//    }
}