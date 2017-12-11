#include "MapPoint.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>

MapPoint::MapPoint(int x, int y) {
    setPosition(x, y);
}

MapPoint::MapPoint(sf::Vector2f pos) {
    setPosition(pos);
}

MapPoint::MapPoint(const MapPoint& orig) {
    MapPoint(orig.getPosition());
}

MapPoint::~MapPoint() {
    
}
