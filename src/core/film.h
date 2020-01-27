#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "geometry.h"

class Film {
public:
    Film() : height(720), width(1280) {}
    Film(int height, int width) : height(height), width(width) {}
    ~Film() {
    }

    void writeFrame(const std::vector<Vector3f> &frame);

    int height, width;
};
