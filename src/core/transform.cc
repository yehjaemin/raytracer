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

bool Transform::swapsHandedness() const {
    // swaps if det of upper left 3x3 submatrix if negative
    float det = m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]) - 
                m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]) + 
                m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
    return det < 0;
}

Transform translate(const Vector3f &delta) {
    Matrix4 m(1, 0, 0, delta.x,
              0, 1, 0, delta.y,
              0, 0, 1, delta.z,
              0, 0, 0,       1);
    Matrix4 mInv(1, 0, 0, -delta.x,
                 0, 1, 0, -delta.y,
                 0, 0, 1, -delta.z,
                 0, 0, 0,        1);
    return Transform(m, mInv);
}

Transform scale(const Vector3f &mag) {
    Matrix4 m(mag.x,     0,     0, 0,
                  0, mag.y,     0, 0,
                  0,     0, mag.z, 0,
                  0,     0,     0, 1);
    Matrix4 mInv(1 / mag.x,         0,         0, 0,
                         0, 1 / mag.y,         0, 0,
                         0,         0, 1 / mag.z, 0,
                         0,         0,         0, 1);
    return Transform(m, mInv);
}

Transform rotateX(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Matrix4 m(1, 0,  0, 0,
              0, c, -s, 0,
              0, s,  c, 0,
              0, 0,  0, 1);
    return Transform(m, transpose(m));
}

Transform rotateY(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Matrix4 m( c, 0, s, 0,
               0, 1, 0, 0,
              -s, 0, c, 0,
               0, 0, 0, 1);
    return Transform(m, transpose(m));
}

Transform rotateZ(float theta) {
    float c = std::cos(theta);
    float s = std::sin(theta);
    Matrix4 m(c, -s, 0, 0,
              s,  c, 0, 0,
              0,  0, 1, 0,
              0,  0, 0, 1);
    return Transform(m, transpose(m));
}

Transform rotate(float theta, const Vector3f &axis) {
    Vector3f a = normalize(axis);
    float c = std::cos(theta);
    float s = std::sin(theta);
    Matrix4 m;

    // rotate first basis vector
    m.m[0][0] = a.x * a.x + (1 - a.x * a.x) * c; 
    m.m[0][1] = a.x * a.y * (1 - c) - a.z * s;
    m.m[0][2] = a.x * a.z * (1 - c) + a.y * s;
    m.m[0][3] = 0;

    // rotate second basis vector
    m.m[1][0] = a.x * a.y * (1 - c) + a.z * s;
    m.m[1][1] = a.y * a.y + (1 - a.y * a.y) * c;
    m.m[1][2] = a.y * a.z * (1 - c) - a.x * s;
    m.m[1][3] = 0;

    // rotate third basis vector
    m.m[2][0] = a.x * a.z * (1 - c) - a.y * s;
    m.m[2][1] = a.y * a.z * (1 - c) + a.x * s;
    m.m[2][2] = a.z * a.z + (1 - a.z * a.z) * c;
    m.m[2][3] = 0;
    return Transform(m, transpose(m));
}

Transform lookAt(const Point3f &pos, const Point3f &look, const Vector3f &up) {
    Matrix4 cameraToWorld;

    // fourth col gives the point that the camera space origin maps to in world space
    // this is the camera position, supplied by pos
    cameraToWorld.m[0][3] = pos.x;
    cameraToWorld.m[1][3] = pos.y;
    cameraToWorld.m[2][3] = pos.z;
    cameraToWorld.m[3][3] = 1;
    
    // third col gives the world space direction that the +z axis in camera space maps to
    // this is the direction from the camera to the look-at point
    Vector3f dir = normalize(look - pos);
    cameraToWorld.m[0][2] = dir.x;
    cameraToWorld.m[1][2] = dir.y;
    cameraToWorld.m[2][2] = dir.z;
    cameraToWorld.m[3][2] = 0;

    // first col gives the world space direction that the +x axis in camera space maps to
    // this is the cross product of the up and dir vectors
    Vector3f right = normalize(cross(up, dir));
    cameraToWorld.m[0][0] = right.x;
    cameraToWorld.m[1][0] = right.y;
    cameraToWorld.m[2][0] = right.z;
    cameraToWorld.m[3][0] = 0;

    // second col gives the world space direction that the +y axis in camera space maps to
    // this is the cross product of the dir and right vectors
    // (recomputed to ensure that y and z are perpendicular)
    Vector3f newUp = normalize(cross(dir, right));
    cameraToWorld.m[0][1] = newUp.x;
    cameraToWorld.m[1][1] = newUp.y;
    cameraToWorld.m[2][1] = newUp.z;
    cameraToWorld.m[3][1] = 0;
    return Transform(inverse(cameraToWorld), cameraToWorld);
}
