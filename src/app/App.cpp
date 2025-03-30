#include "app/App.h"
#include "app/GuiLayer.h"
#include <imgui-SFML.h>
#include <implot.h>

App::App() : window(sf::VideoMode::getDesktopMode(), "Ball on Plate"),
             gui(0.3),
             view()
{
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    ImPlot::CreateContext();

    // Set the proportion of the screen that the GUI will fill.
    gui = GuiLayer(0.3);
}

void App::run() {
    sf::Clock deltaClock;
    while (window.isOpen()) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event.has_value()) {
                this->handleEvents(event.value());
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        gui.update(this->window);
        //view.update();      // Simulation view rendering

        window.clear();
        view.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImPlot::DestroyContext();
    ImGui::SFML::Shutdown();
}

void App::handleEvents(sf::Event event) {
    return;
}