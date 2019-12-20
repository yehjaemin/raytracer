#pragma once

namespace untitled {
inline float lerp(float t, float a, float b) {
    return (1 - t) * a + t * b;
}
} // namespace untitled

// --------------------
// tiny ray tracer ver.
// --------------------

#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "geometry.h"

void render();
int main();
