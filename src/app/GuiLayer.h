#pragma once
#include <SFML/Graphics.hpp>

class GuiLayer {
public:
    GuiLayer(float size) : size(size) {};
    void update(sf::RenderWindow& window);  // Draw GUI

private:
    float size;
};
