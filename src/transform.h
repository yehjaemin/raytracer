#pragma once

#include <cstring>
#include "untitled.h"

struct Matrix4 {
    Matrix4() {
        // identity matrix
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = 
            m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
    }
    Matrix4(float matrix[4][4]) {
        std::memcpy(m, matrix, 16 * sizeof(float));
    }
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    Matrix4 operator*(const Matrix4 &that) const {
        float p[4][4];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                p[i][j] = m[i][0] * that.m[0][j] + 
                          m[i][1] * that.m[1][j] + 
                          m[i][2] * that.m[2][j] + 
                          m[i][3] * that.m[3][j];
            }
        }
        return Matrix4(p);
    }

    bool operator==(const Matrix4 &that) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (m[i][j] != that.m[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix4 &that) const {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (m[i][j] != that.m[i][j])
                    return true;
        return false;
    }

    Matrix4 transpose() const {
        float t[4][4];
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                t[i][j] = m[j][i];
        return Matrix4(t);
    }

    Matrix4 inverse() const {
        // TODO Gauss-Jordan elimination
        float inv[4][4];
        return Matrix4(inv);
    }

    float m[4][4];
};

class Transform {
public:
    Transform() {}
    Transform(const Matrix4 &m) : m(m) {}
    Transform(const Matrix4 &m, const Matrix4 &mInv) : m(m), mInv(mInv) {}

private:
    Matrix4 m, mInv;
};
