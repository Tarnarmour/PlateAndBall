#pragma once
#include <SFML/Graphics.hpp>

class SimView {
public:
    void update();
    void render(sf::RenderWindow& window);
};
