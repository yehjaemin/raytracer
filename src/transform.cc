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
