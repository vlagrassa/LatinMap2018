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
        popup.setPosition(305, 205);
        popup.setSize(sf::Vector2f(DEFAULT_WINDOW.getSize().x - 610, DEFAULT_WINDOW.getSize().y - 410));
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
        link.addText(name, sf::Vector2f(315, 200), 60);
        setAppearance();
    };
    
    MapPoint(const MapPoint& orig) : LinkedButton(orig.outline.getPosition(), *new PointScreen()),
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
    
    void setText() {
        if (names.alternate.size() > 0) link.addText(std::string("AKA ") + names.alternate, sf::Vector2f(315, 325));
        link.addText(names.english, sf::Vector2f(315, 275));
        link.addText(coords, sf::Vector2f(315, 415), 25);
        //link.addText(description, sf::Vector2f(250, 265));
    }
    
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
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(outline);
    }
    
private:
    friend std::ostream& operator<<(std::ostream &strm, const MapPoint& p) {
        return strm << p.operator std::string();
    };
    
    void setAppearance() {
        sf::CircleShape tempCircle(10);
        tempCircle.setPosition(outline.getPosition());
        switch (type) {
            case (flumen):
                tempCircle.setRotation(180);
                tempCircle.move(20, 0);
                tempCircle.setPointCount(3);
                tempCircle.setOutlineThickness(3);
                tempCircle.setOutlineColor(sf::Color(0, 0, 51));
                tempCircle.setFillColor(sf::Color(51, 153, 255));
                outline = tempCircle;
                break;
            case (insula):
                tempCircle.setPointCount(4);
                tempCircle.setRadius(5);
                tempCircle.move(5, 5);
                tempCircle.setOutlineThickness(2);
                tempCircle.setOutlineColor(sf::Color(25, 51, 0));
                tempCircle.setFillColor(sf::Color(0, 153, 76));
                outline = tempCircle;
                break;
            case (mare):
                tempCircle.setPointCount(20);
                tempCircle.setOutlineThickness(2);
                outline = tempCircle;
                outline.setOutlineColor(sf::Color(0, 0, 51));
                outline.setFillColor(sf::Color(51, 153, 255));
                break;
            case (mons):
                tempCircle.setPointCount(3);
                tempCircle.setOutlineThickness(3);
                tempCircle.setOutlineColor(sf::Color(51, 25, 0));
                tempCircle.setFillColor(sf::Color(153, 76, 0));
                outline = tempCircle;
                break;
            case (provincia):
                tempCircle.setPointCount(5);
                tempCircle.setOutlineThickness(3);
                tempCircle.setOutlineColor(sf::Color(0, 0, 51));
                tempCircle.setFillColor(sf::Color(102, 0, 204));
                outline = tempCircle;
                break;
            case (regio):
                tempCircle.setPointCount(20);
                tempCircle.setOutlineThickness(2);
                tempCircle.setOutlineColor(sf::Color(25, 51, 0));
                tempCircle.setFillColor(sf::Color(0, 153, 76));
                outline = tempCircle;
                break;
            case (urbs):
                tempCircle.setPointCount(4);
                 tempCircle.setRadius(5);
                tempCircle.move(5, 5);
                tempCircle.setOutlineThickness(2);
                tempCircle.setOutlineColor(sf::Color(102, 0, 0));
                tempCircle.setFillColor(sf::Color(204, 0, 102));
                outline = tempCircle;
                break;
            case (via):
                tempCircle.setRotation(180);
                tempCircle.setPointCount(3);
                tempCircle.setOutlineThickness(3);
                tempCircle.setOutlineColor(sf::Color(102, 0, 0));
                tempCircle.setFillColor(sf::Color(204, 0, 102));
                outline = tempCircle;
                break;
        }
    }
};

#endif /* MAPPOINT_H */
