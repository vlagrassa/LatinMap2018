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
    
    std::string getName() const;
    std::string getDescription() const;
    
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The name of the location.
     */
    const std::string name;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The main text decription to display.
     */
    const std::string description;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The real-world longitude coordinate.
     */
    const float coordLon;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The real-world latitude coordinate.
     */
    const float coordLat;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * Whether to render based on filters.
     */
    bool display;
};

#endif /* MAPPOINT_H */
