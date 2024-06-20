//
// Created by nbollom on 12/02/24.
//

#include "colour.hpp"
using namespace ndg::common;

Colour::Colour(float red, float green, float blue, float alpha) {
    _data[0] = red;
    _data[1] = green;
    _data[2] = blue;
    _data[3] = alpha;
}

float Colour::Red() const {
    return _data[0];
}

float Colour::Green() const {
    return _data[1];
}

float Colour::Blue() const {
    return _data[2];
}

float Colour::Alpha() const {
    return _data[3];
}

float* Colour::GetDataRef() {
    return _data;
}

void Colour::Red(float value) {
    _data[0] = value;
}

void Colour::Blue(float value) {
    _data[1] = value;
}

void Colour::Green(float value) {
    _data[2] = value;
}

void Colour::Alpha(float value) {
    _data[3] = value;
}

