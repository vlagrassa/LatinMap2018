#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"
#include "Defaults.hpp"
#include "ScreenMode.hpp"
#include "MapPoint.hpp"

class MapScreen : public ScreenMode {
public:
    sf::Sprite background;
    sf::Vector2i screenCoords;
    MapPointLegend legend;
    
    MapScreen(const sf::Texture* texture) : ScreenMode(), legend(sf::Vector2f(800, 50)) {
        background.setTexture(*texture);
        screenCoords.x = 0;
        screenCoords.y = 0;
        initLegend();
    };
    
    MapScreen(const MapScreen& orig) : MapScreen(orig.background.getTexture()) {};
    
    virtual ~MapScreen() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    virtual void update(sf::Event event);
    
    virtual ScreenMode* run(sf::Event event);
    
    void moveArrows(sf::Event event);
    
    void moveScroll(sf::Event event);
        
    void move(int x, int y);
    
    void moveX(int dist);
    
    void moveY(int dist);
    
private:
    void initLegend();
    void addToLegend(std::string name, int xOffset, int yOffset, MapPointType type);
};

#endif /* MAPSCREEN_H */
