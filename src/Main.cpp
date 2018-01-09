#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "MapPoint.hpp"
#include "Utils.hpp"
#include "ScreenMode.hpp"

std::vector<MapPoint> buildMapPoints(std::string filename);

int main() {
    std::cout << "Salve, munde!" << "\n";
    
    std::cout << "Coords of the thing should be " << buildMapPoints("res/map_points/Montes").at(0).coords << "\n";
    
    std::vector<std::string> tempStringVector;
    MapPoint cithaeron(sf::Vector2f(20, 20), "Cithaeron", tempStringVector, "This is a mountain in Greece", tempStringVector, "38°11′03″N 23°14′57″E" );
    
    sf::Texture defaultPoint;
    defaultPoint.loadFromFile("res/x.jpg"); //Image from https://www.freepik.com/free-icon/x-circle_692346.htm
    cithaeron.setTexture(defaultPoint);
    cithaeron.scale(0.05, 0.05);
    
    std::cout << "Init test Loop\n";
    Loop<int> testLoop;
    std::cout << "Add to test Loop\n";
    testLoop.append(1);
    testLoop.append(2);
    testLoop.append(3);
    std::cout << "Printing test Loop\n";
    std::cout << testLoop << "\n";
    
    std::cout << testLoop.shift() << "\n";
    std::cout << testLoop.shift() << "\n";
    std::cout << testLoop.shift() << "\n";
    std::cout << testLoop.shift() << "\n";
    std::cout << testLoop.shift() << "\n";
    std::cout << "Active: " << testLoop.active->data << "\n";
    std::cout << "Bottom: " << testLoop.bottom->data << "\n";
    
    sf::RenderWindow window(sf::VideoMode(1366, 768), "Latin Map Project");
    
    sf::Texture backTexture;
    backTexture.loadFromFile("res/Blank_Roman_Empire.png");
    sf::Sprite background;
    background.setTexture(backTexture);
    background.setTextureRect(sf::IntRect(0, 0, 1300, 700));
    
    sf::Vector2i screenCoords(300, 50);
    
    std::cout << "Window is " << &window << "\n";
    
    Stack<ScreenMode&> listOfScreens;
    
    ScreenMode testScreen1(window);
    ScreenMode testScreen2(window);
    
    LinkedButton testButton1(testScreen2, window);
    testButton1.setSize(sf::Vector2f(100, 50));
    testButton1.setOutlineColor(sf::Color::Cyan);
    testButton1.setOutlineThickness(5);
    testButton1.setPosition(250, 250);
    
    LinkedButton testButton2(0, window);
    
    testScreen1.addButton(testButton1);
    testScreen2.addButton(testButton2);
    
    listOfScreens.push(testScreen1);
    std::cout << "Pushing screen 1:\n" << listOfScreens << "\n";
    listOfScreens.push(testScreen2);
    std::cout << "Pushing screen 2:\n" << listOfScreens << "\n";
    
    while (window.isOpen()) {

        sf::Event event;
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    screenCoords.x -= 10;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    screenCoords.x += 10;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    screenCoords.y -= 10;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    screenCoords.y += 10;
                }
            }
        }
        
        screenCoords.x -= 2 * ((event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) ? event.mouseWheelScroll.delta : 0);
        screenCoords.y -= 2 * ((event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)   ? event.mouseWheelScroll.delta : 0);
        
        window.clear(sf::Color::White);
        
        //screenCoords.x = sf::Mouse::getPosition(window).x;
        //screenCoords.y = sf::Mouse::getPosition(window).y;
        background.setTextureRect(sf::IntRect(screenCoords.x, screenCoords.y, 1366, 768));
        window.draw(background);
        
        if (!listOfScreens.isEmpty()) {
            ScreenMode* nextScreen = listOfScreens.top->data.run();
            if (nextScreen == 0) {
                listOfScreens.pop();
                std::cout << "Removed screen:\n" << listOfScreens << "\n";
            } else if (nextScreen != &listOfScreens.top->data) {
                listOfScreens.push(*nextScreen);
                std::cout << "Added screen:\n" << listOfScreens << "\n";
            }
            
            for (Node<LinkedButton&>* n = listOfScreens.top->data.buttons.head; n != 0; n = n->next) {
                window.draw(n->data);
            }
        }
        
        window.draw(cithaeron);
        
        window.display();
    }
    
    std::cout << "\n\n" << listOfScreens << "\n";
}

std::vector<MapPoint> buildMapPoints(std::string filename) {
    std::fstream                file(filename);
    std::string                 line;
    std::vector<MapPoint>       listOfPoints;
    
    std::string                 tempName;
    std::vector<std::string>    tempAltNames;
    sf::Vector2f                tempPos;
    std::string                 tempCoords;
    std::string                 tempDescription;
    std::vector<std::string>    tempEvents;
    
    while (std::getline(file, line)) {
        if (line.size() > 0) {
            if (line.at(0) == '*') {
                //std::cout << line.substr(2, std::string::npos) << "\n";
                tempName = line.substr(2, std::string::npos);
            } else if (line.compare(0, std::string("Coords: ").size(), "Coords: ")) {
                tempCoords = line.substr(line.find(":")+1, std::string::npos);
            }
        }
        
    }
    listOfPoints.push_back(MapPoint(tempPos, tempName, tempAltNames, tempDescription, tempEvents, tempCoords));
    std::cout << tempCoords << ", are ";
    
    return listOfPoints;
}
