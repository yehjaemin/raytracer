#include "untitled.h"

struct Matrix4 {
    Matrix4() {
        // identity matrix
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.f;
        m[0][1] = m[0][2] = m[0][3] = m[1][0] = m[1][2] = m[1][3] = 
            m[2][0] = m[2][1] = m[2][3] = m[3][0] = m[3][1] = m[3][2] = 0.f;
    }
    Matrix4(float matrix[4][4]) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                m[i][j] = matrix[i][j];
    }

    bool operator==(const Matrix4 &that) const {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                if(m[i][j] != that.m[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix4 &that) const {
        for(int i = 0; i < 4; ++i)
            for(int j = 0; j < 4; ++j)
                if(m[i][j] != that.m[i][j])
                    return true;
        return false;
    }

    Matrix4 transpose() const {
        float t[4][4];
        for (int i = 0; i < 4; ++i)
            for (int j
        return Matrix4(
    }

    float m[4][4];
};

class Transform {
public:
    Transform() {}
    Transform(const Matrix4 &m) : m(m) {}
    Transform(const Matrix4 &m, const Matrix4 &mInv) : m(m), mInv(mInv) {}

    Matrix4 m, mInv;
};
