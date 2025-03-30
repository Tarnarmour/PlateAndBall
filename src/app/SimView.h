#pragma once
#include <SFML/Graphics.hpp>

class SimView {
public:
    SimView();

    void update();
    void render(sf::RenderWindow& window);
};
