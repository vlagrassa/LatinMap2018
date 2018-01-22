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

void buildMapPoints(std::string filename, LinkedList<MapPoint&> destination);

const unsigned int WINDOW_X = 1300; //1366;
const unsigned int WINDOW_Y = 650;  //768;

sf::Font DEFAULT_FONT;
sf::RenderWindow DEFAULT_WINDOW(sf::VideoMode(WINDOW_X, WINDOW_Y), "Latin Map Project");

int main() {
    std::cout << "Salve, munde!" << "\n";
    
    DEFAULT_WINDOW.setFramerateLimit(0);
    DEFAULT_WINDOW.setVerticalSyncEnabled(true);
    
    DEFAULT_FONT.loadFromFile("res/Cochin.ttc");
    
    MapPoint cithaeron1("Mons Cithaeron", sf::Vector2f(20, 20), mons);
    MapPoint cithaeron2("Mount Kithairon", sf::Vector2f(1200, 600), mons);
    
    sf::Texture backTexture;
    backTexture.loadFromFile("res/Blank_Roman_Empire.png");
    
    Stack<ScreenMode&> listOfScreens;
    
    MapScreen testMapScreen(&backTexture);
    testMapScreen.addButton(cithaeron1);
    testMapScreen.addButton(cithaeron2);
    
    testMapScreen.addButton(*new MapPoint("Mons Parnassus", sf::Vector2f(100, 150), mons));
    
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

void buildMapPoints(std::string filename, LinkedList<MapPoint&> destination) {
    std::fstream                file(filename);
    std::string                 line;
    
    while (std::getline(file, line)) {
        if (line.size() > 0) {
            if (line.at(0) == '*') {
                std::string tempName = line.substr(2, line.find(":")-1);
                std::getline(file, line);
                float tempx = std::stoi(line);
                std::getline(file, line);
                float tempy = std::stoi(line);
                std::cout << "Adding " << tempName << " at " << tempx << ", " << tempy << "\n";
                destination.add(*new MapPoint(tempName, sf::Vector2f(tempx, tempy), mons));
                std::cout << destination << "\n";
            }
        }
        
    }
    std::cout << "At the end\n" << destination << "\n";
}
