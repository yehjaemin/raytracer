#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "geometry.h"

class Film {
public:
    Film() : height(720), width(1280) {
        ofs = std::shared_ptr<std::ofstream>(new std::ofstream);
        ofs->open("./out.ppm");
    }
    Film(int height, int width) : height(height), width(width) {
        ofs->open("./out.ppm");
    }
    ~Film() {
    }

    void writeFrame(const std::vector<Vector3f> &frame);

    int height, width;

private:
    std::shared_ptr<std::ofstream> ofs;
};
