#include "Window.h"

const sf::Time Window::FRAME_INTERVAL = sf::milliseconds(20);

Window::Window(int width, int height, std::unique_ptr<InteractiveDrawable> plot)
        : m_window(sf::VideoMode(width, height), "Plotter")
        , m_plot(std::move(plot)) {}

void Window::eventLoop() {
    sf::Clock clock;
    while (true) {
        clock.restart();

        handleEvents();
        if (!m_window.isOpen()) break;
        render();

        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed < FRAME_INTERVAL) {
            sf::sleep(FRAME_INTERVAL - elapsed);
        }
    }
}

void Window::handleEvents() {
    sf::Event event{};
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
            break;
        }
        if (m_plot != nullptr) m_plot->processEvent(event);
    }
}

void Window::render() {
    m_window.clear();
    if (m_plot != nullptr) m_window.draw(*m_plot);
    m_window.display();
}
