//
// Created by nbollom on 12/02/24.
//

#include "common.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "common.hpp"

bool glfw_initialised = false;

void ndg::common::initialise_glfw() {
    if (glfw_initialised){
        return;
    }

    if (!glfwInit()) {
        std::cout << "ERROR: Failed to load GLFW\n";
        const char *error;
        glfwGetError(&error);
        std::cout << &error << "\n";
        exit(EXIT_FAILURE);
    }

    glfw_initialised = true;
}

bool glew_initialised = false;

void ndg::common::initialise_glew() {
    if (glew_initialised) {
        return;
    }

    GLenum err = glewInit();

    if (err != GLEW_OK) {
        std::cout << "ERROR: Failed to initialised GLEW\n";
        std::cout << glewGetErrorString(err) << "\n";
        exit(EXIT_FAILURE);
    }

    glew_initialised = true;
}
