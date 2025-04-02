#pragma once
#include <SFML/Graphics.hpp>
#include "simulation/System.h"

class GuiLayer {
public:
    void setSize(float size);
    void updateData(float t, System::State state, System::Input u);
    void renderPlot(sf::RenderWindow& window);

private:
    float size;
    std::vector<float> time{};
    std::vector<float> x{};
    std::vector<float> y{};
    std::vector<float> vx{};
    std::vector<float> vy{};
    std::vector<float> ua{};
    std::vector<float> ub{};
};
