// SimView.cpp
#include "app/SimView.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

SimView::SimView() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void SimView::update() {
    // step physics, maybe later
}

void SimView::render(sf::RenderWindow& window) {
    // draw 2D representation of ball and plate
}
