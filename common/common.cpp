//
// Created by nbollom on 12/02/24.
//

#include "common.hpp"

#include <GL/gl3w.h>
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

bool gl3w_initialised = false;

void ndg::common::initialise_gl3w() {
    if (gl3w_initialised) {
        return;
    }

    if (gl3wInit() || !gl3wIsSupported(3, 2)) {
        std::cout << "ERROR: Failed to initialised GLEW\n";
        exit(EXIT_FAILURE);
    }

    gl3w_initialised = true;
}
