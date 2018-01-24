#include "MapPoint.hpp"


void PointScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(popup);
    target.draw(minimap);
    ScreenMode::draw(target, states);
};

void PointScreen::setMinimapTexture(const sf::Texture* t) {
    minimap.setTexture(t);
}

void PointScreen::initPopup() {
    popup.setPosition(305, 205);
    popup.setSize(sf::Vector2f(DEFAULT_WINDOW.getSize().x - 610, DEFAULT_WINDOW.getSize().y - 410));
    popup.setOutlineColor(sf::Color::Black);
    popup.setOutlineThickness(5);
    minimap.setPosition(DEFAULT_WINDOW.getSize().x - 305 - (DEFAULT_WINDOW.getSize().y - 410) + 10, 205 + 10);
    minimap.setSize(sf::Vector2f(DEFAULT_WINDOW.getSize().y - 410 - 20, DEFAULT_WINDOW.getSize().y - 410 - 20));
    minimap.setOutlineColor(sf::Color::Black);
    minimap.setOutlineThickness(3);
};


void MapPoint::setText() {
    if (names.alternate.size() > 0) link.addText(std::string("AKA ") + names.alternate, sf::Vector2f(315, 325));
    link.addText(names.english, sf::Vector2f(315, 275));
    link.addText(coords, sf::Vector2f(315, 415), 25);
    //link.addText(description, sf::Vector2f(250, 265));
}

void MapPoint::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(outline);
}

void MapPoint::setAppearance() {
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
            tempCircle.move(20, 0);
            tempCircle.setPointCount(3);
            tempCircle.setOutlineThickness(3);
            tempCircle.setOutlineColor(sf::Color(102, 0, 0));
            tempCircle.setFillColor(sf::Color(204, 0, 102));
            outline = tempCircle;
            break;
    }
}


void MapPointLegend::updateFilter() {
    for (Node<MapPoint>* n = this->first; n != NULL; n = n->next) {
        if (n->data.clicked())
            toggleFilter(n->data.type);
    }
}

void MapPointLegend::toggleFilter(MapPointType t) {
    filter ^= t;
}

void MapPointLegend::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(outline, states);
    for (Node<MapPoint>* n = this->first; n != NULL; n = n->next) {
        if (n->data.type & filter)
            target.draw(n->data, states);
    }
    for (sf::Text t : names) {
        target.draw(t);
    }
}
