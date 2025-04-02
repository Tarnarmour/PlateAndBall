#include "app/App.h"
#include "app/GuiLayer.h"
#include "simulation/System.h"
#include <imgui-SFML.h>
#include <implot.h>

#include <iostream>
#include <math.h>

App::App() : window(sf::VideoMode::getDesktopMode(),
                    "Ball on Plate",
                    sf::Style::Default,
                    sf::State::Windowed,
                    sf::ContextSettings(24, 8, 4, 3, 3)) // Set OpenGL context settings: depth-buffer = 24 bits, stencil buffer = 8 bits, anti-aliasing = 4, OpenGL version 3.3, OpenGL CORE settings

{
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        std::cout << "Error initializing SFML window!" << std::endl;
    ImPlot::CreateContext();

    // Set the proportion of the screen that the GUI will fill.
    gui.setSize(1.0);

    // Initialize the OpenGL view port, with view port size.
    //view.initialize(window, 0.3);
}

void App::run() {
    System plant(System::State(0.75f, 0.f, 0.f, 0.3f));

    sf::Clock deltaClock;
    sf::Clock simClock;

    float currentTime = simClock.getElapsedTime().asSeconds();
    float dt;

    while (window.isOpen()) {
        dt = simClock.getElapsedTime().asSeconds() - currentTime;
        currentTime = simClock.getElapsedTime().asSeconds();

        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event.has_value()) {
                this->handleEvents(event.value());
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        window.clear();


        System::State state = plant.getState();
        System::Input u = {state.x * 0.001 + state.vx * 0.002, state.y * 0.001 + state.vy * 0.0005 };
        plant.step(dt, u);
        state = plant.getState();

        gui.updateData(currentTime, state, u);
        gui.renderPlot(window);

        ImGui::SFML::Render(window);
        window.display();
    }
    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();
}

void App::handleEvents(sf::Event event) {
    return;
}