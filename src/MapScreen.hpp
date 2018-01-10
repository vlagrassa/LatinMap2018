#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>

#include "Utils.hpp"
#include "ScreenMode.hpp"

class MapScreen : public ScreenMode {
    MapScreen(sf::Window& window) : ScreenMode(window) {};
    MapScreen(const MapScreen& orig) : ScreenMode(orig) {};
    virtual ~MapScreen() {};
};

#endif /* MAPSCREEN_H */
