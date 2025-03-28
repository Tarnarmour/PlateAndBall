#include "app/App.h"
#include <imgui-SFML.h>

App::App() : window(sf::VideoMode::getDesktopMode(), "Ball on Plate") {
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
}

void App::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            //this->handleEvents(event);
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //gui.update();       // ImGui widgets + plots
        //view.update();      // Simulation view rendering

        window.clear();
        view.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}

void App::handleEvents(sf::Event event) {
    return;
}