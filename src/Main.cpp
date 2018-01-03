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
    MapPoint test2(testVector, "Test 2", "This is a test", 5, 5);
    
    //std::cout << test1.getName() << ": " << test1.getDescription() << "; at (" << test1.getPosition().x << ", " << test1.getPosition().y << ")\n";
    //std::cout << test2.getName() << ": " << test2.getDescription() << "; at (" << test2.getPosition().x << ", " << test2.getPosition().y << ")\n";
    
    //std::cout << test1 << "\n";
    //std::cout << test1.operator std::string() << "\n";
    
    //Stack<MapPoint> testStack;
    //testStack.push(test1);
    //testStack.push(test2);
    
    //std::cout << "\nTop:\n" << *testStack.top << "\n";
    //std::cout << "\nStack:\n" << testStack << "\n\n";
    
    //Node<MapPoint> topTemp = *testStack.top;
    //std::cout << topTemp << "\n";
    
    Stack<int> intStack;
    
    intStack.push(*(new Node<int>(0)));
    std::cout << intStack.pop() << "\n";
    
    intStack.push(*(new Node<int>(3)));
    std::cout << intStack << "\n";
    intStack.push(*(new Node<int>(2)));
    std::cout << intStack << "\n";
    intStack.push(*(new Node<int>(1)));
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    intStack.pop();
    std::cout << intStack << "\n";
    
    intStack.push(3);
    intStack.push(2);
    intStack.push(1);
    std::cout << intStack << "\n";
    //std::cout << intStack.popData() << "\n";
    //std::cout << intStack.popData() << "\n";
    //std::cout << intStack.popData() << "\n";
    
    
    
    Queue<int> intQueue(intStack);
    std::cout << intQueue << "\n";
    
    intQueue.enqueue(*(new Node<int>(4)));
    std::cout << intQueue << "\n";
    intQueue.enqueue(*(new Node<int>(5)));
    std::cout << intQueue << "\n";
    intQueue.enqueue(*(new Node<int>(6)));
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    intQueue.dequeue();
    std::cout << intQueue << "\n";
    
    intQueue.enqueue(4);
    intQueue.enqueue(5);
    intQueue.enqueue(6);
    std::cout << intQueue.dequeue() << "\n";
    std::cout << intQueue.dequeue() << "\n";
    std::cout << intQueue.dequeue() << "\n";
    
    std::cout << intStack << "\n";
    
    ActiveVector<int> testActiveVector;
    testActiveVector.setActiveIndex(3);
    
    //sf::RenderWindow window(sf::VideoMode(1366, 768), "Latin Map Project");
    
    //sf::Texture defaultPoint;
    //defaultPoint.loadFromFile("res/x.jpg"); //Image from https://www.freepik.com/free-icon/x-circle_692346.htm
    
    //test1.setTexture(defaultPoint);
    //test2.setTexture(defaultPoint);
    
    //test1.setScale(0.05, 0.05);
    //test2.setScale(0.05, 0.05);
    
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