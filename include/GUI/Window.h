#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Window {
public:
    Window(int width, int height);

    void eventLoop();

private:
    sf::RenderWindow m_window;

    void handleEvents();
    void render();

    static const sf::Time FRAME_INTERVAL;
};
