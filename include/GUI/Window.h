#pragma once

#include "Interfaces.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>

class Window {
public:
    Window(int width, int height, std::unique_ptr<InteractiveDrawable> plot);

    void eventLoop();

private:
    sf::RenderWindow m_window;
    std::unique_ptr<InteractiveDrawable> m_plot;

    void handleEvents();
    void render();

    static const sf::Time FRAME_INTERVAL;
};
