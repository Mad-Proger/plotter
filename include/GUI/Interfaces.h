#pragma once

#include <SFML/Graphics.hpp>

class InteractiveDrawable: public sf::Drawable {
public:
    virtual void processEvent(sf::Event event) = 0;
};