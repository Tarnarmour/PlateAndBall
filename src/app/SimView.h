#pragma once
#include <SFML/Graphics.hpp>

class SimView {
public:
    SimView();
    ~SimView();
    void initialize(sf::RenderWindow& window, float size);
    void render(sf::RenderWindow& window, float t);
private:
    unsigned int shaderProgram;
    unsigned int VAO, VBO, EBO;
    bool initialized;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;
};
