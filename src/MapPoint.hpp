#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

class MapPoint : public sf::Sprite {
public:
    MapPoint(int x, int y);
    MapPoint(sf::Vector2f pos);
    MapPoint(const MapPoint& orig);
    virtual ~MapPoint();
    
    //std::string getDescription();
    
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    std::string description;
};

#endif /* MAPPOINT_H */
