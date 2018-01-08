#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "MapPoint.hpp"
#include "Utils.hpp"
#include "ScreenMode.hpp"

int main() {
    std::cout << "Salve, munde!" << "\n";
    
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Latin Map Project");
    
    std::cout << "Window is " << &window << "\n";
    
    MapPoint test1(10, 10, "Test 1", "This is a test", 5, 5);
    MapPoint test2(27, 42, "Test 2", "This is a test", 5, 5);
    
    
    ScreenMode testScreen(window);
    LinkedButton testButton(testScreen, window);
    testScreen.addButton(testButton);
    std::cout << "Test Button from main:   " << &testButton << "\n";
    std::cout << "Test Button from screen: " << &testScreen.buttons.head->data << "\n";
    std::cout << "Test Button from main window:   " << &testButton.window << "\n";
    std::cout << "Test Button from screen window: " << &testScreen.buttons.head->data.window << "\n";
    
    Node<LinkedButton&> testButtonNode(testButton);
    Queue<LinkedButton&> testQueue(testButtonNode);
    testQueue.enqueue(*new LinkedButton(testScreen, window));
    
    for (Node<LinkedButton&>* thing = testQueue.head; thing != 0; thing = thing->next) {
        std::cout << "Clicked: " << testQueue.head->data.clicked() << "\n";
    }
    
    std::cout << "Relative Mouse position: " << sf::Mouse().getPosition(window).x << "\n";
    
    
    Stack<ScreenMode&> listOfScreens;
    ScreenMode testScreen1(window);
    ScreenMode testScreen2(window);
    
    LinkedButton testButton1(testScreen2, window);
    testButton1.setSize(sf::Vector2f(100, 50));
    testButton1.setOutlineColor(sf::Color::Cyan);
    testButton1.setOutlineThickness(5);
    testButton1.setPosition(250, 250);
    
    testScreen1.addButton(testButton1);
    testScreen2.createNullButton();
    
    std::cout << "Test Screen 1: " << &testScreen1 << "\n";
    std::cout << "Test Screen 2: " << &testScreen2 << "\n\n";
    std::cout << "Test Button 1: " << &testScreen1.buttons.head->data.link << "\n";
    std::cout << "Test Button 2: " << &testScreen2.buttons.head->data.link << "\n";
    
    listOfScreens.push(testScreen1);
    std::cout << "Pushing screen 1:\n" << listOfScreens << "\n";
    listOfScreens.push(listOfScreens.top->data.buttons.head->data.link);
    std::cout << "Pushing screen 2:\n" << listOfScreens << "\n";
    
    
    //sf::Texture defaultPoint;
    //defaultPoint.loadFromFile("res/x.jpg"); //Image from https://www.freepik.com/free-icon/x-circle_692346.htm
    
    //test1.setTexture(defaultPoint);
    //test2.setTexture(defaultPoint);
    
    //test1.setScale(0.05, 0.05);
    //test2.setScale(0.05, 0.05);
    
//    int countdown = 10;
    
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        window.clear(sf::Color::White);
        
        if (!listOfScreens.isEmpty()) {
            std::cout << "Hi\n";
            ScreenMode* nextScreen = listOfScreens.top->data.run();
            std::cout << "Hi\n";
            
            if (nextScreen == 0) {
                listOfScreens.pop();
            } else if (nextScreen != &listOfScreens.top->data) {
                listOfScreens.push(*nextScreen);
            }
            
            for (Node<LinkedButton&>* n = listOfScreens.top->data.buttons.head; n != 0; n = n->next) {
                window.draw(n->data);
            }
        }
        
        window.draw(test1);
        window.draw(test2);
        
        //window.draw(testButton1);
        
        window.display();
    }
    
    std::cout << "\n\n" << listOfScreens << "\n";
}
