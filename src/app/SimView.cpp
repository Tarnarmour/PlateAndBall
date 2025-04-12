// SimView.cpp
#include "app/SimView.h"
#include <glad/glad.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

const char* vertexShaderSource = "#version 330\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

float plateVertices[] {
    -0.1f, -0.1f, -0.01f,
    0.1f, -0.1f, -0.1f,
    -0.1f, 0.1f, -0.01f,
    0.1f, 0.1f, -0.1f
};

unsigned int plateIndices []{
    0, 1, 2,
    1, 2, 3,
};
 
SimView::SimView()  {
}

SimView::~SimView() {
    if (initialized) {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
        glDeleteProgram(plateShaderProgram);
    }
}

bool SimView::initialize(sf::RenderWindow& window, float size) {
    gladLoadGL();

    // Load and compile the plate vertex shader
    unsigned int plateVertexShader;
    plateVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(plateVertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(plateVertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(plateVertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(plateVertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Likewise with the fragment shader
    unsigned int plateFragmentShader;
    plateFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(plateFragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(plateFragmentShader);
    glGetShaderiv(plateFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(plateFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Link the pipeline of the vertex and fragment shader together into a program,
    // which could be used by calling `glUseProgram(plateShaderProgram);`
    plateShaderProgram = glCreateProgram();
    glAttachShader(plateShaderProgram, plateVertexShader);
    glAttachShader(plateShaderProgram, plateFragmentShader);
    glLinkProgram(plateShaderProgram);
    glGetProgramiv(plateShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(plateShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return false;
    }

    // Clean up the individual shaders (now that they are linked in the program).
    glDeleteShader(plateVertexShader);
    glDeleteShader(plateFragmentShader);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plateVertices), plateVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plateIndices), plateIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    std::cout << "Successfully initialized OpenGL!" << std::endl;
    initialized = true;
    return true;
}

void SimView::render(sf::RenderWindow& window, float t) {
    if (!initialized) return;

    // Set the view port to take up a portion of the left side of the screen.
    glViewport(0, 0, window.getSize().x * 0.5f, window.getSize().y);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(plateShaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Check for errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error during rendering: " << err << std::endl;
    }
}