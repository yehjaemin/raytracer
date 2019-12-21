#include "film.h"

void Film::writeFrame(const std::vector<Vector3f> &frame) {
    *ofs << "P6" << std::endl;
    *ofs << width << " " << height << std::endl;
    *ofs << "255" << std:: endl;
    for (int i = 0; i < width * height; ++i)
        for (int j = 0; j < 3; ++j)
            *ofs << char(255 * frame[i][j]);
}
