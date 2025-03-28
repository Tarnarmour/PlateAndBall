#pragma once
#include <SFML/Graphics.hpp>
#include "app/GuiLayer.h"
#include "app/SimView.h"

class App {
public:
    App();
    void run();

private:
    // Members
    sf::RenderWindow window;
    GuiLayer gui;
    SimView view;

    // Methods
    void handleEvents(sf::Event event);
};
