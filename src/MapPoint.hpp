#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Utils.hpp"
#include "Defaults.hpp"
#include "ScreenMode.hpp"
#include "MapScreen.hpp"

struct MapPointNames;
class PointScreen;
class MapPoint;

struct MapPointNames {
    std::string latin;
    std::string english;
    std::string alternate;
};

enum MapPointType {
    flumen,
    insula,
    mare,
    mons,
    provincia,
    regio,
    urbs,
    via
};

class PointScreen : public ScreenMode {
public:
    sf::RectangleShape popup;
    
    PointScreen() : ScreenMode() {
        initPopup();
        showPrevious = true;
    };
    
    PointScreen(const PointScreen& orig) : ScreenMode(orig) {
        initPopup();
        showPrevious = true;
    };
    
    virtual ~PointScreen() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(popup);
        ScreenMode::draw(target, states);
    };
    
private:
    void initPopup() {
        popup.setPosition(205, 105);
        popup.setSize(sf::Vector2f(DEFAULT_WINDOW.getSize().x - 410, DEFAULT_WINDOW.getSize().y - 210));
        popup.setOutlineColor(sf::Color::Black);
        popup.setOutlineThickness(5);
    }

};

class MapPoint : public LinkedButton {
public:
    MapPoint(std::string  name,
            sf::Vector2f  pos,
            MapPointType  type
            
    ) : LinkedButton(pos, *new PointScreen()), type(type) {
        names.latin = name;
        link.addText(name, sf::Vector2f(215, 100), 60);
    };
    
    MapPoint(const MapPoint& orig) : LinkedButton(orig.getPosition(), *new PointScreen()),
    description(orig.description), coords(orig.coords), type(orig.type) {};
    
    virtual ~MapPoint() {};
    
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    operator std::string() const {
        std::string temp;
        temp += names.latin;
        temp += ": ";
        temp += description;
        return temp;
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * Struct to hold names of the location.
     */
    MapPointNames names;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The main text description to display.
     */
    std::string description;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * List of notable events involving the
     * location.
     */
    std::vector<std::string> events;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The real-world longitude and latitude
     * coordinates.
     */
    std::string coords;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * Whether to render based on filters.
     */
    bool display;
    
    const MapPointType type;
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const MapPoint& p) {
        return strm << p.operator std::string();
    };
};

#endif /* MAPPOINT_H */
