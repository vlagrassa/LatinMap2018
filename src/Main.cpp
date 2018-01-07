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
    
    MapPoint test1(10, 10, "Test 1", "This is a test", 5, 5);
    MapPoint test2(27, 42, "Test 2", "This is a test", 5, 5);
    
    Stack<ScreenMode&> listOfScreens;
    ScreenMode testScreen(window);
    
    testScreen.createButton(new ScreenMode(window));
    listOfScreens.push(testScreen);
    
    //sf::Texture defaultPoint;
    //defaultPoint.loadFromFile("res/x.jpg"); //Image from https://www.freepik.com/free-icon/x-circle_692346.htm
    
    //test1.setTexture(defaultPoint);
    //test2.setTexture(defaultPoint);
    
    //test1.setScale(0.05, 0.05);
    //test2.setScale(0.05, 0.05);
    
    int countdown = 10;
    
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        if (countdown <= 0) {
            window.close();
        }
        
        ScreenMode* nextScreen = listOfScreens.top->data.run();
        
        if (nextScreen == 0) {
            listOfScreens.pop();
        } else if (nextScreen != &listOfScreens.top->data) {
            listOfScreens.push(*nextScreen);
        }
        
        window.clear(sf::Color::White);
        
        window.draw(test1);
        window.draw(test2);
        for (LinkedButton b : listOfScreens.top->data.buttons) {
            window.draw(b);
        }
        
        window.display();
    }
}