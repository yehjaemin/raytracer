#pragma once

#include <cstring>
#include <stack>
#include "geometry.h"

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

Matrix4 transpose(const Matrix4 &m);

Matrix4 inverse(const Matrix4 &m);

class Transform {
public:
    Transform() {}
    Transform(const Matrix4 &m) : m(m) {}
    Transform(const Matrix4 &m, const Matrix4 &mInv) : m(m), mInv(mInv) {}

    inline bool operator==(const Transform& t) const {
        return m == t.m && mInv == t.mInv;
    }

    inline bool operator!=(const Transform& t) const {
        return m != t.m || mInv == t.mInv;
    }

    inline Matrix4 getMatrix() const {
        return m;
    }

    inline Matrix4 getInverseMatrix() const {
        return mInv;
    }

    template <typename T>
    inline Vector3<T> operator()(const Vector3<T> &v) const {
        // weight doesn't apply to vectors
        T x = v.x, y = v.y, z = v.z;
        return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                          m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                          m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
    }

    template <typename T>
    inline Point3<T> operator()(const Point3<T> &p) const {
        // weight applies to points
        T x = p.x, y = p.y, z = p.z;
        T tx = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
        T ty = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
        T tz = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
        T tw = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
        if (tw == 1)
            return Point3<T>(tx, ty, tz);
        T div = 1 / tw;
        return Point3<T>(tx * div, ty * div, tz * div);
    }

    template <typename T>
    inline Normal3<T> operator()(const Normal3<T> &n) const {
        // m = transform(tangent)
        // m' = transform(normal)
        // m' = tranpose(mInv)
        T x = n.x, y = n.y, z = n.z;
        return Normal3<T>(mInv.m[0][0] * x + mInv.m[1][0] * y + mInv.m[2][0] * z,
                          mInv.m[0][1] * x + mInv.m[1][1] * y + mInv.m[2][1] * z,
                          mInv.m[0][2] * x + mInv.m[1][2] * y + mInv.m[2][2] * z);
    }

    template <typename T>
    inline Ray3<T> operator()(const Ray3<T> &r) const {
        // transform ray origin and direction
        Point3<T> to = (*this)(r.o);
        Vector3<T> td = (*this)(r.d);

        // TODO offset ray origin to edge of error bounds and compute tMax
        return Ray(to, td, r.tMax, r.time);
    }

    template <typename T>
    inline Bounds3<T> operator()(const Bounds3<T> &b) const {
        // transform all corner points and recompute bounds to encompass those points
        Bounds3<T> tb((*this)(Point3<T>(b.pMin.x, b.pMin.y, b.pMin.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMax.x, b.pMin.y, b.pMin.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMin.x, b.pMax.y, b.pMin.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMin.x, b.pMin.y, b.pMax.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMin.x, b.pMax.y, b.pMax.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMax.x, b.pMin.y, b.pMax.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMax.x, b.pMax.y, b.pMin.z)));
        tb = getUnion(tb, (*this)(Point3<T>(b.pMax.x, b.pMax.y, b.pMax.z)));

        // TODO implement a technique to do this computation more efficiently
        return tb;
    }

    inline Transform operator()(const Transform &t) const {
        // T(p) = A(B(C(p)))
        // T = A * B * C
        // inverse(A * B) = inverse(B) * inverse(A)
        return Transform(m * t.m, t.mInv * mInv);
    }

    bool swapsHandedness() const;

private:
    Matrix4 m, mInv;
};

inline Transform transpose(const Transform &m) {
    return Transform(transpose(m.getMatrix()), transpose(m.getInverseMatrix()));
}

inline Transform inverse(const Transform &m) {
    return Transform(m.getInverseMatrix(), m.getMatrix());
}

Transform translate(const Vector3f &delta);
Transform scale(const Vector3f &mag);
Transform rotateX(float theta);
Transform rotateY(float theta);
Transform rotateZ(float theta);
Transform rotate(float theta, const Vector3f &axis);
Transform lookAt(const Point3f &pos, const Point3f &look, const Vector3f &up);
