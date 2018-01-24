#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Utils.hpp"
#include "Defaults.hpp"
#include "ScreenMode.hpp"

struct MapPointNames;
class PointScreen;
class MapPoint;

struct MapPointNames {
    std::string latin;
    std::string english;
    std::string alternate;
};

enum MapPointType {
    flumen      =   1,
    insula      =   2,
    mare        =   4,
    mons        =   8,
    provincia   =  16,
    regio       =  32,
    urbs        =  64,
    via         = 128
};

class PointScreen : public ScreenMode {
public:
    sf::RectangleShape popup;
    sf::RectangleShape inmap;
    
    PointScreen() : ScreenMode() {
        initPopup();
        showPrevious = true;
    };
    
    PointScreen(const PointScreen& orig) : ScreenMode(orig) {
        initPopup();
        showPrevious = true;
    };
    
    virtual ~PointScreen() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    void initPopup();

};

class MapPoint : public LinkedButton {
public:
    MapPoint(std::string name, sf::Vector2f pos, MapPointType type) : LinkedButton(pos, *new PointScreen()), type(type) {
        names.latin = name;
        link.addText(name, sf::Vector2f(315, 200), 60);
        setAppearance();
    };
    
    MapPoint(const MapPoint& orig) : MapPoint(orig.names.english, orig.outline.getPosition(), orig.type) {
        description = orig.description;
        coords = orig.coords;
        names.latin = orig.names.latin;
        names.alternate = orig.names.alternate;
    };
    
    virtual ~MapPoint() {};
    
    operator std::string() const {
        std::string temp;
        temp += names.latin;
        temp += ": ";
        temp += description;
        return temp;
    };
    
    void setText();
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
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
    
    const MapPointType type;
    
private:
    void setAppearance();
    
    friend std::ostream& operator<<(std::ostream &strm, const MapPoint& p) {
        return strm << p.operator std::string();
    };
};

class MapPointLegend : public sf::Drawable, public LinkedList<MapPoint> {
public:
    char filter = 255;
    sf::RectangleShape outline;
    std::vector<sf::Text> names;
    
    MapPointLegend(const sf::Vector2f size) : outline(size) {
        outline.setOutlineColor(sf::Color::Black);
        outline.setOutlineThickness(5);
        outline.setFillColor(sf::Color::White);
    };
    MapPointLegend(const MapPointLegend& orig) {};
    virtual ~MapPointLegend() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    void updateFilter();
    
    void toggleFilter(MapPointType t);
};

#endif /* MAPPOINT_H */
