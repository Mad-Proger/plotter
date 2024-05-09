#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class InteractiveDrawable: public sf::Drawable {
public:
    virtual void processEvent(sf::Event event) = 0;
};