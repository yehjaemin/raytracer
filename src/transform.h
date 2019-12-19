#pragma once

#include <cstring>
#include "geometry.h"
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
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                p[i][j] = m[i][0] * that.m[0][j] + 
                          m[i][1] * that.m[1][j] + 
                          m[i][2] * that.m[2][j] + 
                          m[i][3] * that.m[3][j];
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

    float m[4][4];
};

Matrix4 transpose(const Matrix4 &m) {
    float t[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            t[i][j] = m.m[j][i];
    return Matrix4(t);
}

Matrix4 inverse(const Matrix4 &m) {
    // Gauss-Jordan elimination
    // instead of having an aux identity matrix,
    // we treat the pivot's col as an identity col
    // choose largest possible abs value pivot
    // this improves numerical stability with floating point

    int indxr[4], indxc[4]; // record pivots' original row and col
    int ipiv[4] = {0, 0, 0, 0}; // keep track of rows that got pivoted
    float mInv[4][4];
    std::memcpy(mInv, m, 16 * sizeof(float));
    for (int i = 0; i < 4; ++i) { // traverse for pivots
        int irow = 0, icol = 0;
        float big = 0.f;

        // choose pivot
        for (int j = 0; j < 4; ++j) { // traverse rows
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; ++k) { // traverse cols
                    assert(ipiv[k] < 1); // otherwise singular matrix
                    if (ipiv[k] == 0) {
                        float num = std::abs(mInv[j][k]);
                        if (num >= big) { // >= for rightmost bottommost
                            big = num;
                            irow = j;
                            icol = k;
                        }
                    }
                }
            }
        }
        // mark col after choosing pivot
        ++ipiv[icol];

        // record row and col of pivot
        indxr[i] = irow;
        indxc[i] = icol;

        // swap rows so that pivot is on the diagonal
        // pivot will move to mInv[icol][icol]
        if (irow != icol)
            for (int k = 0; k < 4; ++k)
                std::swap(mInv[irow][k], mInv[icol][k]);

        // normalize pivot's row
        assert(big != 0.f); // otherwise singular matrix
        float pivinv = 1.f / mInv[icol][icol]; // account for negative
        mInv[icol][icol] = 1.f; // pivot's col gets divided twice
        for (int k = 0; k < 4; ++k)
            mInv[icol][k] *= pivinv;

        // zero out pivot's col by subtracting pivot's row
        for (int j = 0; j < 4; ++j) { // traverse rows
            if (j != icol) { // skip pivot's row
                float save = mInv[j][icol];
                mInv[j][icol] = 0; // pivot's col gets subtracted twice
                for (int k = 0; k < 4; ++k) { // traverse cols
                    mInv[j][k] -= mInv[icol][k] * save;
                }
            }
        }
    }

    // swap cols to reflect pivot
    for (int j = 3; j >= 0; --j) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; ++k)
                std::swap(mInv[k][indxr[j]], mInv[k][indxc[j]]);
        }
    }
    return Matrix4(mInv);
}

class Transform {
public:
    Transform() {}
    Transform(const Matrix4 &m) : m(m) {}
    Transform(const Matrix4 &m, const Matrix4 &mInv) : m(m), mInv(mInv) {}

    bool operator==(const Transform& t) const {
        return m == t.m && mInv == t.mInv;
    }

    bool operator!=(const Transform& t) const {
        return m != t.m || mInv == t.mInv;
    }

    Matrix4 getMatrix() const {
        return m;
    }

    Matrix4 getInverseMatrix() const {
        return mInv;
    }

    template <typename T> Vector3<T> operator()(const Vector3<T> &v) const;
    template <typename T> Point3<T> operator()(const Point3<T> &p) const;
    template <typename T> Normal3<T> operator()(const Normal3<T> &n) const;
    template <typename T> Ray3<T> operator()(const Ray3<T> &r) const;
    template <typename T> Bounds3<T> operator()(const Bounds3<T> &b) const;
    Transform operator()(const Transform &t) const;

private:
    Matrix4 m, mInv;
};

Transform transpose(const Transform &m) {
    return Transform(transpose(m.getMatrix()), transpose(m.getInverseMatrix()));
}

Transform inverse(const Transform &m) {
    return Transform(m.getInverseMatrix(), m.getMatrix());
}
