#pragma once
#include <SFML/Graphics.hpp>
#include "app/GuiLayer.h"
#include "app/SimView.h"
#include "simulation/System.h"

class App {
public:
    App();
    void run();
    bool initialize();

private:
    // Members
    sf::RenderWindow window;
    GuiLayer gui;
    SimView view;
    System system;

    // Methods
    void handleEvents(sf::Event event);
};
