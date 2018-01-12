#ifndef MAPPOINT_H
#define MAPPOINT_H

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Utils.hpp"
#include "ScreenMode.hpp"
#include "MapScreen.hpp"

class PointScreen;
class MapPoint;

class PointScreen : public ScreenMode {
public:
    PointScreen(sf::Window& window) : ScreenMode(window) {
        showPrevious = true;
    };
    
    PointScreen(const PointScreen& orig) : ScreenMode(orig) {
        showPrevious = true;
    };
    
    virtual ~PointScreen() {};
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        ScreenMode::draw(target, states);
    };

};

class MapPoint : public LinkedButton {
public:
    MapPoint(sf::Window&                window,
            sf::Font&                   font,
            int                         x,
            int                         y,
            std::string                 names,
            std::string                 desc,
            std::vector<std::string>    events,
            std::string                 coords
    ) : MapPoint(window, font, sf::Vector2f(x, y), names, desc, events, coords) {};
    
    MapPoint(sf::Window&                window,
            sf::Font&                   font,
            sf::Vector2f                pos,
            std::string                 names,
            std::string                 desc,
            std::vector<std::string>    events,
            std::string                 coords
    ) : LinkedButton(pos, *new PointScreen(window), window),
        name(names.substr(0, names.find('|'))),
        altNames(names.substr(names.find('|')+1, std::string::npos)),
        description(desc), events(events), coords(coords)
    {
        this->link.addText(name, font, sf::Vector2f(100, 200), sf::Color::Blue);
    };
    
    MapPoint(const MapPoint& orig) : LinkedButton(orig.getPosition(), *new PointScreen(orig.window), orig.window),
    name(orig.name), description(orig.description), coords(orig.coords) {};
    
//    MapPoint(sf::Window& window, sf::Vector2f pos, std::vector<std::string> strings, sf::Font font) :
//    LinkedButton(pos, *new PointScreen(window), window),
//    name(strings.at(0)), description(strings.at(1)), coords(strings.at(2))
//    {};
    
    virtual ~MapPoint() {};
    
    //virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    operator std::string() const {
        std::string temp;
        temp += name;
        temp += ": ";
        temp += description;
        return temp;
    };
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The name of the location.
     */
    const std::string name;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * Alternate names for the location.
     */
    const std::string altNames;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The main text description to display.
     */
    const std::string description;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * List of notable events involving the
     * location.
     */
    const std::vector<std::string> events;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * The real-world longitude and latitude
     * coordinates.
     */
    const std::string coords;
    
    /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
     * Whether to render based on filters.
     */
    bool display;
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const MapPoint& p) {
        return strm << p.operator std::string();
    };
};

#endif /* MAPPOINT_H */
