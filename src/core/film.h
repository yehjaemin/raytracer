#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

class Film {
public:
    Film() : height(720), width(1280) {
        ofs->open("./out.ppm");
    }
    Film(int height, int width) : height(height), width(width) {
        ofs->open("./out.ppm");
    }
    ~Film() {
        ofs->close();
    }

    void writeFrame(const std::vector<Vector3f> &frame);

    int height, width;

private:
    std::ofstream *ofs;
};
