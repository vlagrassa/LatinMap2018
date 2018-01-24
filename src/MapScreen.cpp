#include "MapScreen.hpp"



void MapScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(background, states);
    for (sf::Text t : displayText) {
        target.draw(t);
    }
    for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
        try {
            MapPoint& temp = static_cast<MapPoint&>(n->data);
            if (temp.type & legend.filter) {
                target.draw(temp);
            } else {

            }
        } catch (...) {
            target.draw(n->data);
        }
    }
    target.draw(legend);
}

void MapScreen::update(sf::Event event) {
    moveArrows(event);
    legend.updateFilter();
}

ScreenMode* MapScreen::run(sf::Event event) {
    moveScroll(event);
    background.setTextureRect(sf::IntRect(screenCoords.x, screenCoords.y, static_cast<signed>(DEFAULT_WINDOW.getSize().x), static_cast<signed>(DEFAULT_WINDOW.getSize().y)));
    return checkButtons();
};

ScreenMode* MapScreen::checkButtons() {
    for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
        try {
            MapPoint& temp = static_cast<MapPoint&>(n->data);
            if (temp.clicked() && (temp.type & legend.filter)) {
                return &n->data.link;
            }
        } catch (...) {
            //throw std::generic_error("MapScreen should only have MapPoint buttons");
        }
    }
    return this;
};

void MapScreen::addButton(LinkedButton& b) {
    try {
        PointScreen& temp = static_cast<PointScreen&>(b.link);
        temp.setMinimapTexture(background.getTexture());
        temp.minimap.setTextureRect(sf::IntRect(b.outline.getPosition().x-100, b.outline.getPosition().y-100, 200, 200));
    } catch (...) {

    }
    ScreenMode::addButton(b);
}

void MapScreen::moveArrows(sf::Event event) {
    switch (event.key.code) {
        case (sf::Keyboard::Left):
            moveX(-10);
            break;
        case (sf::Keyboard::Right):
            moveX(10);
            break;
        case (sf::Keyboard::Up):
            moveY(-20);
            break;
        case (sf::Keyboard::Down):
            moveY(20);
            break;
        default:
            break;
    }
}

void MapScreen::moveScroll(sf::Event event) {
    moveX(-2 * ((event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) ? event.mouseWheelScroll.delta : 0));
    moveY(-2 * ((event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)   ? event.mouseWheelScroll.delta : 0));
}

void MapScreen::move(int x, int y) {
    moveX(x);
    moveY(y);
}

void MapScreen::moveX(int dist) {
    int temp = dist;
    if (screenCoords.x + temp <= 0)
        temp = 0 - screenCoords.x;
    if (screenCoords.x + temp > static_cast<signed>(background.getTexture()->getSize().x - DEFAULT_WINDOW.getSize().x))
        temp = static_cast<signed>(background.getTexture()->getSize().x - DEFAULT_WINDOW.getSize().x) - screenCoords.x;

    screenCoords.x += temp;
    for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
        n->data.outline.move(-temp, 0);
    }
}

void MapScreen::moveY(int dist) {
    int temp = dist;
    if (screenCoords.y + temp < 0)
        temp = 0 - screenCoords.y;
    if (screenCoords.y + temp > static_cast<signed>(background.getTexture()->getSize().y - DEFAULT_WINDOW.getSize().y))
        temp = static_cast<signed>(background.getTexture()->getSize().y - DEFAULT_WINDOW.getSize().y) - screenCoords.y;

    screenCoords.y += temp;
    for (Node<LinkedButton&>* n = buttons.first; n != 0; n = n->next) {
        n->data.outline.move(0, -temp);
    }
}

void MapScreen::initLegend() {
    legend.outline.setPosition((DEFAULT_WINDOW.getSize().x-800)/2, DEFAULT_WINDOW.getSize().y-50);
    int yOffset = 5;
    addToLegend("Flumina", 1, yOffset, flumen);
    addToLegend("Insulae", 2, yOffset, insula);
    addToLegend("Maria", 3, yOffset, mare);
    addToLegend("Montes", 4, yOffset, mons);
    addToLegend("Provinciae", 5, yOffset, provincia);
    addToLegend("Regiones", 6, yOffset, regio);
    addToLegend("Urbes", 7, yOffset, urbs);
    addToLegend("Viae", 8, yOffset, via);
}

void MapScreen::addToLegend(std::string name, int xOffset, int yOffset, MapPointType type) {
    legend.add(*new MapPoint(name, sf::Vector2f(
        legend.outline.getPosition().x + (legend.outline.getSize().x/9)*xOffset - 5 - (
            (type == insula || type == urbs) ? 10 :
            ((type == flumen || type == via) ? 40 :
        0)),
        legend.outline.getPosition().y + yOffset + (
            (type == flumen || type == via) ? 17 :
            ((type == insula || type == urbs) ? -10 :
            ((type == mons) ? 3 :
        0)))
    ), type));
    sf::Text* temp = new sf::Text(name, DEFAULT_FONT, 20);
    temp->setFillColor(sf::Color::Black);
    temp->setPosition(
        legend.outline.getPosition().x + (legend.outline.getSize().x/9)*xOffset - temp->getGlobalBounds().width/2 + 5,
        legend.outline.getPosition().y + yOffset + 17
    );
    legend.names.push_back(*temp);
}
