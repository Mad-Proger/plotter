#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow wnd(sf::VideoMode(1280, 720), "Test");

    while (true) {
        sf::Event event{};
        while (wnd.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                wnd.close();
                break;
            }
        }
        if (!wnd.isOpen()) break;

        wnd.clear();
        wnd.display();
        sf::sleep(sf::milliseconds(20));
    }

    return 0;
}
