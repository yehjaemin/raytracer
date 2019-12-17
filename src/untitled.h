#pragma once

namespace untitled {
inline float lerp(float t, float a, float b) {
    return (1 - t) * a + t * b;
}
} // namespace untitled
