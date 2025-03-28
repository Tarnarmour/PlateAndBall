#include "app/GuiLayer.h"
#include <imgui.h>
#include <implot.h>

void GuiLayer::update() {
    ImGui::Begin("Control Panel");
    ImGui::Text("Simulation Parameters:");
    // sliders, buttons, etc.
    ImGui::End();

    ImGui::Begin("State Plot");
    if (ImPlot::BeginPlot("Ball Position")) {
        // plot values here
        ImPlot::EndPlot();
    }
    ImGui::End();
}
