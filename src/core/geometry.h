#pragma once

#include <algorithm>
#include <assert.h>
#include <cmath>
#include <limits>

namespace untitled {
inline float lerp(float t, float a, float b) {
    return (1 - t) * a + t * b;
}
} // namespace untitled

template <typename T> class Vector2 {
public:
    Vector2() : x(0), y(0) {}
    Vector2(T i, T j) : x(i), y(j) {}

    inline Vector2<T> operator+(const Vector2<T> &v) const {
        return Vector2(x + v.x, y + v.y);
    }

    inline const Vector2<T> &operator+=(const Vector2<T> &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vector2<T> operator-(const Vector2<T> &v) const {
        return Vector2(x - v.x, y - v.y);
    }

    inline const Vector2<T> &operator-=(const Vector2<T> &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <typename U>
    inline Vector2<T> operator*(U u) const {
        return Vector2(u * x, u * y);
    }

    template <typename U>
    inline const Vector2<T> &operator*=(U u) {
        x *= u;
        y *= u;
        return *this;
    }

    template <typename U>
    inline Vector2<T> operator/(U u) const {
        return Vector2(x / u, y / u);
    }

    template <typename U>
    inline const Vector2<T> operator/=(U u) {
        U uInv = 1 / u;
        x *= uInv;
        y *= uInv;
        return *this;
    }

    inline Vector2<T> operator-() const {
        return Vector2f(-x, -y);
    }

    inline T operator[](int i) const {
        assert(0 <= i && i <= 1);
        if (i == 0)
            return x;
        return y;
    }

    inline bool operator==(const Vector2<T> &v) const {
        return x == v.x && y == v.y;
    }

    inline bool operator!=(const Vector2<T> &v) const {
        return x != v.x || y != v.y;
    }

    inline float length() const {
        return std::sqrt(x * x + y * y);
    }

    T x, y;
};

template <typename T> class Vector3 {
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T i, T j, T k) : x(i), y(j), z(k) {}

    inline Vector3<T> operator+(const Vector3<T> &v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    inline const Vector3<T> &operator+=(const Vector3<T> &v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    inline Vector3<T> operator-(const Vector3<T> &v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    inline const Vector3<T> operator-=(const Vector3<T> &v) {
        v -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename U>
    inline Vector3<T> operator*(U u) const {
        return Vector3(u * x, u * y, u * z);
    }

    template <typename U>
    inline const Vector3<T> &operator*=(U u) {
        x *= u;
        y *= u;
        z *= u;
        return *this;
    }

    template <typename U>
    inline Vector3<T> operator/(U u) const {
        U uInv = 1 / u;
        return Vector3(uInv * x, uInv * y, uInv * z);
    }

    template <typename U>
    inline const Vector3<T> &operator/=(U u) {
        U uInv = 1 / u;
        x *= uInv;
        y *= uInv;
        z *= uInv;
        return *this;
    }

    inline Vector3<T> operator-() const {
        return Vector3(-x, -y, -z);
    }

    inline T operator[](int i) const {
        assert(0 <= i && i <= 2);
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        return z;
    }

    inline bool operator==(const Vector3<T> &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    inline bool operator!=(const Vector3<T> &v) const {
        return x != v.x || y != v.y || z != v.z;
    }

    inline float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    T x, y, z;
};

template <typename T>
inline T dot(const Vector3<T> &u, const Vector3<T> &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T>
inline Vector3<T> cross(const Vector3<T> &u, const Vector3<T> &v) {
    return Vector3<T>(u.y * v.z - u.z * v.y,
                      u.z * v.x - u.x * v.z,
                      u.x * v.y - u.y * v.x);
}

template <typename T>
inline Vector2<T> normalize(const Vector2<T> &v) {
    return v / v.length();
}

template <typename T>
inline Vector3<T> normalize(const Vector3<T> &v) {
    return v / v.length();
}

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;

template <typename T> class Point2 {
public:
    Point2() : x(0), y(0) {}
    Point2(T i, T j) : x(i), y(j) {}

    inline Point2<T> operator+(const Vector2<T> &v) const {
        return Point2(x + v.x, y + v.y);
    }

    inline const Point2<T> &operator+=(const Vector2<T> &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    inline Vector2<T> operator-(const Point2<T> &p) const {
        return Vector2<T>(x - p.x, y - p.y);
    }

    inline Point2<T> operator-(const Vector2<T> &v) const {
        return Point2<T>(x - v.x, y - v.y);
    }

    inline const Point2<T> &operator-=(const Vector2<T> &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    T x, y;
};

template <typename T> class Point3 {
public:
    Point3() : x(0), y(0), z(0) {}
    Point3(T i, T j, T k) : x(i), y(j), z(k) {}

    inline Point3<T> operator+(const Vector3<T> &v) const {
        return Point3(x + v.x, y + v.y, z + v.z);
    }

    inline const Point3<T> &operator+=(const Vector3<T> &v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    inline Vector3<T> operator-(const Point3<T> &p) const {
        return Vector3<T>(x - p.x, y - p.y, z - p.z);
    }

    inline Point3<T> operator-(const Vector3<T> &v) const {
        return Point3<T>(x - v.x, y - v.y, z - v.z);
    }

    inline const Point3<T> operator-=(const Vector3<T> &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    T x, y, z;
};

template <typename T>
inline float distance(const Point2<T> &p, const Point2<T> &q) {
    return (p - q).length();
}

template <typename T>
inline float distance(const Point3<T> &p, const Point3<T> &q) {
    return (p - q).length();
}

typedef Point2<float> Point2f;
typedef Point3<float> Point3f;

template <typename T> class Normal3 {
public:
    Normal3() : x(0), y(0), z(0) {}
    Normal3(T i, T j, T k) : x(i), y(j), z(k) {}

    explicit Normal3<T>(const Vector3<T> &v) : x(v.x), y(v.y), z(v.z) {}

    inline Normal3<T> operator+(const Normal3<T> &n) const {
        return Normal3<T>(x + n.x, y + n.y, z + n.z);
    }

    inline const Normal3<T> &operator+=(const Normal3<T> &n) {
        x += n.x;
        y += n.y;
        z += n.z;
        return *this;
    }

    inline Normal3<T> operator-(const Normal3<T> &n) const {
        return Normal3<T>(x - n.x, y - n.y, z - n.z);
    }

    inline const Normal3<T> operator-=(const Normal3<T> &n) {
        x -= n.x;
        y -= n.y;
        z -= n.z;
        return *this;
    }

    template <typename U>
    inline Normal3<T> operator*(U u) const {
        return Normal3<T>(u * x, u * y, u * z);
    }

    template <typename U>
    inline const Normal3<T> &operator*=(U u) {
        x *= u;
        y *= u;
        z *= u;
        return *this;
    }

    template <typename U>
    inline Normal3<T> operator/(U u) const {
        U uInv = 1 / u;
        return Normal3<T>(uInv * x, uInv * y, uInv * z);
    }

    template <typename U>
    inline const Normal3<T> &operator/=(U u) {
        U uInv = 1 / u;
        x *= uInv;
        y *= uInv;
        z *= uInv;
        return *this;
    }

    inline Normal3<T> operator-() const {
        return Normal3<T>(-x, -y, -z);
    }

    inline T operator[](int i) const {
        assert(0 <= i && i <= 2);
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        return z;
    }

    inline bool operator==(const Normal3<T> &n) const {
        return x == n.x && y == n.y && z == n.z;
    }

    inline bool operator!=(const Normal3<T> &n) const {
        return x != n.x || y != n.y || z != n.z;
    }

    inline float length() const {
        return std::sqrt(x * x + y * y + z* z);
    }

    T x, y, z;
};

template <typename T>
inline Normal3<T> normalize(const Normal3<T> &n) {
    return n / n.length();
}

template <typename T>
inline Normal3<T> reorient(const Normal3<T> &n, const Vector3<T> &v) {
    if (dot(n, v) < 0)
        return -n;
    return n;;;
}

template <typename T>
inline T dot(const Normal3<T> &n1, const Normal3<T> &n2) {
    return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline T dot(const Normal3<T> &n, const Vector3<T> &v) {
    return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline T dot(const Vector3<T> &v, const Normal3<T> &n) {
    return v.x * n.x + v.y * n.y + v.z * n.z;
}

template <typename T>
inline T cross(const Normal3<T> &n, const Vector3<T> &v) {
    return Vector3<T>(n.y * v.z - n.z * v.y,
                      n.z * v.x - n.x * v.z,
                      n.x * v.y - n.y * v.x);
}

template <typename T>
inline T cross(const Vector3<T> &v, const Normal3<T> &n) {
    return Vector3<T>(v.y * n.z - v.z * n.y,
                      v.z * n.x - v.x * n.z,
                      v.x * n.y - v.y * n.x);
}

typedef Normal3<float> Normal3f;

template <typename T> class Ray3 {
public:
    Ray3() {}
    Ray3(const Point3<T> &o, const Vector3<T> &d) : o(o), d(d) {}
    Point3<T> operator ()(T t) const {
        return o + d * t;
    }

    Point3<T> o; // origin
    Vector3<T> d; // direction
};

typedef Ray3<float> Ray3f;

template <typename T> class Bounds2 {
public:
    Bounds2() {
        T nMin = std::numeric_limits<T>::lowest();
        T nMax = std::numeric_limits<T>::max();
        pMin = Point2<T>(nMax, nMax);
        pMax = Point2<T>(nMin, nMin);
    }
    Bounds2(const Point2<T> &p) : pMin(p), pMax(p) {}
    Bounds2(const Point2<T> &p, const Point2<T> &q) {
        pMin = Point2<T>(std::min(p.x, q.x), std::min(p.y, q.y));
        pMax = Point2<T>(std::max(p.x, q.x), std::max(p.y, q.y));
    }

    inline Vector2<T> diagonal() const {
        return pMax - pMin;
    }

    inline T area() const {
        return (pMax.x - pMin.x) * (pMax.y - pMin.y);
    }

    inline int maxAxis() const {
        Vector2<T> diag = pMax - pMin;
        if (diag.x > diag.y)
            return 0;
        return 1;
    }

    inline bool operator==(const Bounds2<T> &b) const {
        return pMin == b.pMin && pMax == b.pMax;
    }

    inline bool operator!=(const Bounds2<T> &b) const {
        return pMin != b.pMin || pMax != b.pMax;
    }

    inline Point2<T> lerp(const Point2f &t) const {
        return Point2<T>(untitled::lerp(t.x, pMin.x, pMax.x), untitled::lerp(t.y, pMin.y, pMax.y));
    }

    inline Point2<T> offset(const Point2<T> &p) const {
        Point2<T> q = p - pMin;
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        if (x > 0)
            q /= x;
        if (y > 0)
            q /= y;
        return q;
    }

    Point2<T> pMin, pMax;
};

template <typename T> class Bounds3 {
public:
    Bounds3() {
        T nMin = std::numeric_limits<T>::lowest();
        T nMax = std::numeric_limits<T>::max();
        pMin = Point3<T>(nMax, nMax, nMax);
        pMax = Point3<T>(nMin, nMin, nMin);
    }
    Bounds3(const Point3<T> &p) : pMin(p), pMax(p) {}
    Bounds3(const Point3<T> &p, const Point3<T> &q) {
        pMin = Point3<T>(std::min(p.x, q.x), std::min(p.y, q.y), std::min(p.z, q.z));
        pMax = Point3<T>(std::max(p.x, q.x), std::max(p.y, q.y), std::max(p.z, q.z));
    }

    inline Vector3<T> diagonal() const {
        return pMax - pMin;
    }

    inline T surfaceArea() const {
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        T z = pMax.z - pMin.z;
        return 2 * x * y + 2 * y * z + 2 * x * z;
    }

    inline T volume() const {
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        T z = pMax.z - pMin.z;
        return x * y * z;
    }

    inline int maxAxis() const {
        Vector3<T> diag = pMax - pMin;
        T aMax = std::max(diag.x, diag.y, diag.z);
        if (diag.x == aMax)
            return 0;
        if (diag.y == aMax)
            return 1;
        return 2;
    }

    inline bool operator==(const Bounds3<T> &b) const {
        return pMin == b.pMin && pMax == b.pMax;
    }

    inline bool operator!=(const Bounds3<T> &b) const {
        return pMin != b.pMin && pMax == b.pMax;
    }

    inline Point3<T> lerp(const Point3f &t) const {
        return Point3<T>(untitled::lerp(t.x, pMin.x, pMax.x), untitled::lerp(t.y, pMin.y, pMax.y), untitled::lerp(t.z, pMin.z, pMax.z));
    }

    inline Point3<T> offset(const Point3<T> &p) const {
        Point3<T> q = p - pMin;
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        T z = pMax.z - pMin.z;
        if (x > 0)
            q /= x;
        if (y > 0)
            q /= y;
        if (z > 0)
            q /= z;
        return q;
    }

    Point3<T> pMin, pMax;
};


template <typename T>
inline Bounds3<T> getUnion(const Bounds3<T> &b, const Point3<T> &p) {
    Point3<T> pMin = Point3<T>(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y), std::min(b.pMin.z, p.z));
    Point3<T> pMax = Point3<T>(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y), std::max(b.pMax.z, p.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T>
inline Bounds3<T> getUnion(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    Point3<T> pMin = Point3<T>(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y), std::min(b1.pMin.z, b2.pMin.z));
    Point3<T> pMax = Point3<T>(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y), std::max(b1.pMax.z, b2.pMax.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T>
inline Bounds3<T> getIsect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    Point3<T> pMin = Point3<T>(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y), std::max(b1.pMin.z, b2.pMin.z));
    Point3<T> pMax = Point3<T>(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y), std::min(b1.pMax.z, b2.pMax.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T>
inline bool isInside(const Point3<T> &p, const Bounds3<T> &b) {
    return b.pMin.x <= p.x && p.x <= b.pMax.x && b.pMin.y <= p.y && p.y <= b.pMax.y && b.pMin.z <= p.z <= b.pMax.z;
}

template <typename T>
inline Bounds3<T> expand(const Bounds3<T> &b, T pad) {
    Point3<T> pMin = Point3<T>(b.pMin.x - pad, b.pMin.y - pad, b.pMin.z - pad);
    Point3<T> pMax = Point3<T>(b.pMax.x + pad, b.pMax.y + pad, b.pMax.z + pad);
    return Bounds3<T>(pMin, pMax);
}

typedef Bounds2<float> Bounds2f;
typedef Bounds3<float> Bounds3f;
