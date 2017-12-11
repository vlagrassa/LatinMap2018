#include "MapPoint.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>
#include <ctime>

MapPoint::MapPoint(int x, int y, std::string n, std::string d, float lon, float lat) : name(n), description(d), coordLon(lon), coordLat(lat) {
    setPosition(x, y);
}

MapPoint::MapPoint(sf::Vector2f pos, std::string n, std::string d, float lon, float lat) : name(n), description(d), coordLon(lon), coordLat(lat) {
    setPosition(pos);
}

MapPoint::MapPoint(const MapPoint& orig) : name(orig.getName()), description(orig.getDescription()), coordLon(5), coordLat(5) {
    setPosition(orig.getPosition().x, orig.getPosition().y);
}

MapPoint::~MapPoint() {
    
}

std::string MapPoint::getName() const {
    return name;
}

std::string MapPoint::getDescription() const {
    return description;
}
