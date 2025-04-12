#pragma once
#include <SFML/Graphics.hpp>

class SimView {
public:
    SimView();
    ~SimView();
    bool initialize(sf::RenderWindow& window, float size);
    void render(sf::RenderWindow& window, float t);
private:
    unsigned int plateShaderProgram = 0;
    unsigned int VAO, VBO, EBO = 0;
    bool initialized = false;
};
