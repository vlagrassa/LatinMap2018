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
#include "MapScreen.hpp"

std::vector<MapPoint> buildMapPoints(std::string filename, sf::Window& window);

const unsigned int WINDOW_X = 1300; //1366;
const unsigned int WINDOW_Y = 650;  //768;

sf::Font DEFAULT_FONT;
sf::RenderWindow DEFAULT_WINDOW(sf::VideoMode(WINDOW_X, WINDOW_Y), "Latin Map Project");

int main() {
    std::cout << "Salve, munde!" << "\n";
    
    DEFAULT_WINDOW.setFramerateLimit(0);
    DEFAULT_WINDOW.setVerticalSyncEnabled(true);
    
    DEFAULT_FONT.loadFromFile("res/Cochin.ttc");
    
    //std::cout << "Coords of the thing should be " << buildMapPoints("res/map_points/Montes", window).at(0).coords << "\n";
    
    MapPoint cithaeron1("Mons Cithaeron", sf::Vector2f(20, 20), mons);
    MapPoint cithaeron2("Mount Kithairon", sf::Vector2f(1200, 600), mons);
    
    cithaeron1.setDefaultLook();
    cithaeron2.setDefaultLook();
    
    sf::Texture backTexture;
    backTexture.loadFromFile("res/Blank_Roman_Empire.png");
    
    Stack<ScreenMode&> listOfScreens;
    
    MapScreen testMapScreen(&backTexture);
    testMapScreen.addButton(cithaeron1);
    testMapScreen.addButton(cithaeron2);
    
    listOfScreens.push(testMapScreen);
    std::cout << "Pushing Map Screen...\n" << listOfScreens << "\n";
    
    while (DEFAULT_WINDOW.isOpen()) {

        sf::Event event;
        
        while (DEFAULT_WINDOW.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed):
                    DEFAULT_WINDOW.close();
                    break;
                case (sf::Event::KeyPressed):
                    if (event.key.code == sf::Keyboard::Q) {
                        if (listOfScreens.top->hasNext()) listOfScreens.pop();
                    }
                    break;
                default:
                    break;
            }
        }
        
        DEFAULT_WINDOW.clear(sf::Color::White);
        
        if (!listOfScreens.isEmpty()) {
            ScreenMode* nextScreen = listOfScreens.top->data.run(event);
            if (nextScreen == 0) {
                listOfScreens.pop();
                std::cout << "Removed screen:\n" << listOfScreens << "\n";
            } else if (nextScreen != &listOfScreens.top->data) {
                listOfScreens.push(*nextScreen);
                std::cout << "Added screen:\n" << listOfScreens << "\n";
            }
            
            /*
            Stack<ScreenMode&> drawStack(listOfScreens.top);
            for (Node<ScreenMode&>* tempNode = listOfScreens.top; tempNode != 0 && tempNode->data.showPrevious; tempNode = tempNode->next) {
                drawStack.push(*new Node<ScreenMode&>(*tempNode));
                std::cout << drawStack << "\n";
                break;
                
            }
            while (!drawStack.isEmpty()) {
                DEFAULT_WINDOW.draw(drawStack.pop());
            }
            */
            if (nextScreen->showPrevious) {DEFAULT_WINDOW.draw(listOfScreens.top->next->data);}
            DEFAULT_WINDOW.draw(*nextScreen);
        }
        
        //window.draw(testText);
        
        DEFAULT_WINDOW.display();
    }
    
    std::cout << "\n\n" << listOfScreens << "\n";
}

std::vector<MapPoint> buildMapPoints(std::string filename, sf::Window& window) {
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
    //listOfPoints.push_back(MapPoint(window, tempPos, tempName, tempAltNames, tempDescription, tempEvents, tempCoords));
    std::cout << tempCoords << ", are ";
    
    return listOfPoints;
}
