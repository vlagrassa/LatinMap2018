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

void buildMapPoints(std::string filename, MapPointType filetype, LinkedList<MapPoint&>& destination);

const unsigned int WINDOW_X = 1300; //1366;
const unsigned int WINDOW_Y = 650;  //768;

sf::Font DEFAULT_FONT;
sf::RenderWindow DEFAULT_WINDOW(sf::VideoMode(WINDOW_X, WINDOW_Y), "Latin Map Project");

int main() {
    std::cout << "Salve, munde!" << "\n";
    
    DEFAULT_WINDOW.setFramerateLimit(0);
    DEFAULT_WINDOW.setVerticalSyncEnabled(true);
    
    DEFAULT_FONT.loadFromFile("res/Cochin.ttc");
    
    sf::Texture backTexture;
    backTexture.loadFromFile("res/Blank_Roman_Empire.png");
    
    Stack<ScreenMode&> listOfScreens;
    
    MapScreen testMapScreen(&backTexture);
    
    LinkedList<MapPoint&> testList;
    buildMapPoints("res/map_points/Montes", mons, testList);
    
    for (Node<MapPoint&>* n = testList.first; n != NULL; n = n->next) {
        testMapScreen.addButton(n->data);
    }
    
    testMapScreen.move(200, 250);
    listOfScreens.push(testMapScreen);
    std::cout << "Pushing Map Screen...\n" << listOfScreens << "\n";
    
    sf::Text mouseCoords;
    mouseCoords.setFont(DEFAULT_FONT);
    mouseCoords.setFillColor(sf::Color::Black);
    
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
            if (!listOfScreens.isEmpty()) {
                listOfScreens.top->data.update(event);
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
        mouseCoords.setString(
            std::to_string(sf::Mouse::getPosition(DEFAULT_WINDOW).x + testMapScreen.screenCoords.x)
          + std::string(", ")
          + std::to_string(sf::Mouse::getPosition(DEFAULT_WINDOW).y + testMapScreen.screenCoords.y)
        );
        DEFAULT_WINDOW.draw(mouseCoords);
        
        DEFAULT_WINDOW.display();
    }
    
    std::cout << "\n\n" << listOfScreens << "\n";
}

void buildMapPoints(std::string filename, MapPointType filetype, LinkedList<MapPoint&>& destination) {
    std::fstream                file(filename);
    std::string                 line;
    std::string tempName;
    sf::Vector2f tempCoords;
    MapPoint* tempPoint;
    
    while (std::getline(file, line)) {
        if (line.size() > 0) {
            switch (line.at(0)) {
                case ('*'):
                    tempName = line.substr(2, line.find(":")-1);
                    std::getline(file, line);
                    tempCoords.x = std::stoi(line)-10;
                    std::getline(file, line);
                    tempCoords.y = std::stoi(line)-10;
                    std::cout << "Adding " << tempName << " at " << tempCoords.x << ", " << tempCoords.y << "\n";
                    tempPoint = new MapPoint(tempName, tempCoords, filetype);
                    break;
                case ('E'):
                    tempPoint->names.english = line.substr(3, std::string::npos);
                    break;
                case ('A'):
                    tempPoint->names.alternate = line.substr(3, std::string::npos);
                    break;
                case ('C'):
                    tempPoint->coords = line.substr(4, std::string::npos);
                    break;
                case ('D'):
                    tempPoint->description = line.substr(3, std::string::npos);
                    break;
                case ('-'):
                    tempPoint->events.push_back(line.substr(1, std::string::npos));
                    break;
                case ('#'):
                    tempPoint->setText();
                    destination.add(*tempPoint);
                    break;
                default:
                    break;
            }
        }
    }
    std::cout << "At the end\n" << destination << "\n";
}
