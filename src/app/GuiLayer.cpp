#include "app/GuiLayer.h"
#include "simulation/System.h"
#include <imgui.h>
#include <implot.h>
#include <SFML/Graphics.hpp>

void GuiLayer::setSize(float size) {
    this->size = size;
}

void GuiLayer::updateData(float t, System::State state, System::Input u) {
    this->time.push_back(t);
    this->x.push_back(state.x);
    this->y.push_back(state.y);
    this->vx.push_back(state.vx);
    this->vy.push_back(state.vy);
    this->ua.push_back(u.a);
    this->ub.push_back(u.b);
}

void GuiLayer::renderPlot(sf::RenderWindow& window) {

    sf::Vector2u windowSize = window.getSize();

    // State Plots
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * (1 - this->size), windowSize.y * 0.1));
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * this->size, windowSize.y * 0.8));

    ImGui::Begin("State Plots");
    if (ImPlot::BeginPlot("Ball Position")) {
        ImPlot::SetupAxes("Time (sec)", "Position (m)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
        if (!this->time.empty()) {
            ImPlot::PlotLine("x vs time", this->time.data(), this->x.data(), static_cast<int>(this->time.size()));
            ImPlot::PlotLine("y vs time", this->time.data(), this->y.data(), static_cast<int>(this->time.size()));
        }
        ImPlot::EndPlot();
    }
    else {
        ImGui::Text("Error creating plot!");
    }

    if (ImPlot::BeginPlot("Ball Velocity")) {
        ImPlot::SetupAxes("Time (sec)", "Velocity (m/sec)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
        if (!this->time.empty()) {
            ImPlot::PlotLine("Vx vs time", this->time.data(), this->vx.data(), static_cast<int>(this->time.size()));
            ImPlot::PlotLine("Vy vs time", this->time.data(), this->vy.data(), static_cast<int>(this->time.size()));
        }
        ImPlot::EndPlot();
    }
    else {
        ImGui::Text("Error creating plot!");
    }

    if (ImPlot::BeginPlot("Inputs")) {
        ImPlot::SetupAxes("Time (sec)", "Height (m)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);
        if (!this->time.empty()) {
            ImPlot::PlotLine("Ua vs time", this->time.data(), this->ua.data(), static_cast<int>(this->time.size()));
            ImPlot::PlotLine("Ub vs time", this->time.data(), this->ub.data(), static_cast<int>(this->time.size()));
        }
        ImPlot::EndPlot();
    }
    else {
        ImGui::Text("Error creating plot!");
    }

    ImGui::End();
}
