#include "transform.h"

Matrix4 transpose(const Matrix4 &m) {
    float t[4][4];
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            t[i][j] = m.m[j][i];
    return Matrix4(t);
}

Matrix4 inverse(const Matrix4 &m) {
    // Gauss-Jordan elimination
    // instead of having an augmented matrix,
        // calculate inverse across piv col
        // keep track of piv rows and cols
    // max abs val pivs for numerical stability

    std::stack<int> pivrow, pivcol;
    int locked[4] = {0, 0, 0, 0};
    float minv[4][4];
    std::memcpy(minv, m.m, 16 * sizeof(float));

    for (int p = 0; p < 4; ++p) {
        int row = 0, col = 0;
        float big = 0.f;

        // choose pivot
        for (int i = 0; i < 4; ++i) {
            if (locked[i] != 1) {
                for (int j = 0; j < 4; ++j) {
                    assert(locked[j] <= 1); // otherwise singular matrix
                    if (locked[j] == 0) {
                        // 1) not in locked
                        // 2) max abs val
                        // 3) rightmost bottommost
                        float num = std::abs(minv[i][j]);
                        if (num >= big) {
                            big = num;
                            row = i;
                            col = j;
                        }
                    }
                }
            }
        }
        // record piv row and col
        pivrow.push(row);
        pivcol.push(col);

        // swap rows so that piv is on the diagonal
        // pivot will move to minv[icol][icol]
        if (row != col)
            for (int j = 0; j < 4; ++j)
                std::swap(minv[row][j], minv[col][j]);

        // mark piv row in locked
        ++locked[col];

        // normalize piv row
        assert(big != 0.f); // otherwise singular matrix
        float div = 1.f / minv[col][col]; // account for negative
        minv[col][col] = 1.f; // piv stores inverse value
        for (int j = 0; j < 4; ++j)
            minv[col][j] *= div;

        // zero out piv col with row operations
        for (int i = 0; i < 4; ++i) {
            if (i != col) { // skip piv row
                float coeff = minv[i][col];
                minv[i][col] = 0; // piv col stores inverse values
                for (int j = 0; j < 4; ++j)
                    minv[i][j] -= coeff * minv[col][j];
            }
        }
    }

    // for each row swapped,
    // swap col in reverse order
    // assert(pivrow.size() == 4);
    // assert(pivcol.size() == 4);
    while (!pivrow.empty()) {
        int row = pivrow.top(), col = pivcol.top();
        pivrow.pop(); pivcol.pop();
        if (row != col)
            for (int i = 0; i < 4; ++i)
                std::swap(minv[i][row], minv[i][col]);
    }
    return Matrix4(minv);
}

template <typename T>
Vector3<T> Transform::operator()(const Vector3<T> &v) const {
    // weight doesn't apply to vectors
    T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z,
                      m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z,
                      m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z);
}

template <typename T>
Point3<T> Transform::operator()(const Point3<T> &p) const {
    // weight applies to points
    T x = p.x, y = p.y, z = p.z;
    T tx = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3];
    T ty = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3];
    T tz = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3];
    T tw = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3];
    if (tw == 1)
        return Point3<T>(tx, ty, tz);
    return Point3<T>(tx, ty, tz) / tw;
}

template <typename T>
Normal3<T> Transform::operator()(const Normal3<T> &n) const {
    // m = transform(tangent)
    // m' = transform(normal)
    // m' = tranpose(mInv)
    T x = n.x, y = n.y, z = n.z;
    return Normal3<T>(mInv.m[0][0] * x + mInv.m[1][0] * y + mInv.m[2][0] * z,
                      mInv.m[0][1] * x + mInv.m[1][1] * y + mInv.m[2][1] * z,
                      mInv.m[0][2] * x + mInv.m[1][2] * y + mInv.m[2][2] * z);
}

template <typename T>
Ray3<T> Transform::operator()(const Ray3<T> &r) const {
    // transform ray origin and direction
    Point3<T> to = (*this)(r.o);
    Vector3<T> td = (*this)(r.d);

    // TODO offset ray origin to edge of error bounds and compute tMax
    return Ray(to, td, r.tMax, r.time);
}

template <typename T>
Bounds3<T> Transform::operator()(const Bounds3<T> &b) const {
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

Transform Transform::operator()(const Transform &t) const {
    // T(p) = A(B(C(p)))
    // T = A * B * C
    // inverse(A * B) = inverse(B) * inverse(A)
    return Transform(m * t.m, t.mInv * mInv);
}

bool Transform::swapsHandedness() const {
    // swaps if det of upper left 3x3 submatrix if negative
    float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) - 
                m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) + 
                m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
    return det < 0;
}
