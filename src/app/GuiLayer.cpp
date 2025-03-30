#include "app/GuiLayer.h"
#include <imgui.h>
#include <implot.h>
#include <SFML/Graphics.hpp>

void GuiLayer::update(sf::RenderWindow& window) {

    sf::Vector2u windowSize = window.getSize();

    // GUI Window
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * (1 - this->size), 0));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * this->size, windowSize.y * 0.5));

    ImGui::Begin("Control Panel");
    ImGui::Text("Simulation Parameters:");
    ImGui::End();

    // State Plot
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * (1 - this->size), windowSize.y * 0.5));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * this->size, windowSize.y * 0.5));

    ImGui::Begin("State Plot");
    if (ImPlot::BeginPlot("Ball Position")) {
        // plot values here
        ImPlot::EndPlot();
    }
    else {
        ImGui::Text("Error creating plot!");
    }
    ImGui::End();
}
