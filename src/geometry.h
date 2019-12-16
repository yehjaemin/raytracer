#include <algorithm>
#include <assert.h>
#include <limits>
#include <math.h>
#include "untitled.h"

template <typename T> class Vector2 {
public:
    Vector2() : x(0), y(0) {}
    Vector2(T i, T j) : x(i), y(j) {}

    Vector2<T> operator+(const Vector2<T> &v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2<T> &operator+=(const Vector2<T> &v) const {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2<T> operator-(const Vector2<T> &v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2<T> &operator-=(const Vector2<T> &v) const {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    template <typename U> Vector2<T> operator*(U u) const {
        return Vector2(u * x, u * y);
    }

    template <typename U> Vector2<T> &operator*=(U u) const {
        x *= u;
        y *= u;
        return *this;
    }

    template <typename U> Vector2<T> operator/(U u) const {
        return Vector2(x / u, y / u);
    }

    template <typename U> Vector2<T> operator/=(U u) const {
        x /= u;
        y /= u;
        return *this;
    }

    Vector2<T> operator-() const {
        return Vector2f(-x, -y);
    }

    T operator[](int i) {
        assert(0 <= i && i <= 1);
        if (i == 0)
            return x;
        return y;
    }

    bool operator==(const Vector2<T> &v) const {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector2<T> &v) const {
        return x != v.x || y != v.y;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }

    T x, y;
};

template <typename T> class Vector3 {
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(T i, T j, T k) : x(i), y(j), z(k) {}

    Vector3<T> operator+(const Vector3<T> &v) const {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }

    Vector3<T> &operator+=(const Vector3<T> &v) const {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector3<T> operator-(const Vector3<T> &v) const {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3<T> operator-=(const Vector3<T> &v) const {
        v -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    template <typename U> Vector3<T> operator*(U u) const {
        return Vector3(u * x, u * y, u * z);
    }

    template <typename U> const Vector3<T> &operator*=(U u) const {
        x *= u;
        y *= u;
        z *= u;
        return *this;
    }

    template <typename U> Vector3<T> operator/(U u) const {
        return Vector3(x / u, y / u, z / u);
    }

    template <typename U> const Vector3<T> &operator/=(U u) const {
        x /= u;
        y /= u;
        z /= u;
        return *this;
    }

    Vector3<T> operator-() const {
        return Vector3(-x, -y, -z);
    }

    T operator[](int i) {
        assert(0 <= i && i <= 2);
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        return z;
    }

    bool operator==(const Vector3<T> &v) const {
        return x == v.x && y == v.y && z == v.z;
    }

    bool operator!=(const Vector3<T> &v) const {
        return x != v.x && y != v.y && z != v.z;
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    T x, y, z;
};

template <typename T> inline T
dot(const Vector3<T> &u, const Vector3<T> &v) {
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

template <typename T> inline Vector3<T>
cross(const Vector3<T> &u, const Vector3<T> &v) {
    return Vector3<T>(u.y * v.z - u.z * v.y,
                      u.z * v.x - u.x * v.z,
                      u.x * v.y - u.y * v.x);
}

template <typename T> inline Vector2<T>
normalize(const Vector2<T> &v) {
    return v / v.length();
}

template <typename T> inline Vector3<T>
normalize(const Vector3<T> &v) {
    return v / v.length();
}

typedef Vector2<float> Vector2f;
typedef Vector3<float> Vector3f;

template <typename T> class Point2 {
public:
    Point2() : x(0), y(0) {}
    Point2(T i, T j) : x(i), y(j) {}

    Point2<T> operator+(const Vector2<T> &v) const {
        return Point2(x + v.x, y + v.y);
    }

    const Point2<T> operator+=(const Vector2<T> &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2<T> operator-(const Point2<T> &p) const {
        return Vector2<T>(x - p.x, y - p.y);
    }

    Point2<T> operator-(const Vector2<T> &v) const {
        return Point2<T>(x - v.x, y - v.y);
    }

    const Point2<T> &operator-=(const Vector2<T> &v) {
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

    Point3<T> operator+(const Vector3<T> &v) const {
        return Point3(x + v.x, y + v.y, z + v.z);
    }

    const Point3<T> &operator+=(const Vector3<T> &v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    Vector3<T> operator-(const Point3<T> &p) const {
        return Vector3<T>(x - p.x, y - p.y, z - p.z);
    }

    Point3<T> operator-(const Vector3<T> &v) const {
        return Point3<T>(x - v.x, y - v.y, z - v.z);
    }

    const Point3<T> operator-=(const Vector3<T> &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    T x, y, z;
};

template <typename T> inline float getDistance(const Point2<T> &p, const Point2<T> &q) {
    return (p - q).length();
}

template <typename T> inline float getDistance(const Point3<T> &p, const Point3<T> &q) {
    return (p - q).length();
}

typedef Point2<float> Point2f;
typedef Point3<float> Point3f;

class Ray {
public:
    Ray() : tMax(std::numeric_limits<float>::infinity()), time(0.f) {}
    Ray(const Point3f &o, const Vector3f &d, float tMax = std::numeric_limits<float>::infinity(), float time = 0.f) : o(o), d(d), tMax(tMax), time(time) {}
    Point3f operator ()(float t) const {
        return o + d * t;
    }

    Point3f o; // origin
    Vector3f d; // direction
    float tMax; // r(t) = o + dt
    float time;
};

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

    Vector2<T> diagonal() const {
        return pMax - pMin;
    }

    T area() const {
        return (pMax.x - pMin.x) * (pMax.y - pMin.y);
    }

    int maxAxis() const {
        Vector2<T> diag = pMax - pMin;
        if (diag.x > diag.y)
            return 0;
        return 1;
    }

    bool operator==(const Bounds2<T> &b) const {
        return pMin == b.pMin && pMax == b.pMax;
    }

    bool operator!=(const Bounds2<T> &b) const {
        return pMin != b.pMin || pMax != b.pMax;
    }

//    Point2<T> lerp(const Point2f &t) const {
//        return Point2<T>(untitled::lerp(t.x, pMin.x, pMax.x), untitled::lerp(t.y, pMin.y, pMax.y));
//    }

    Point2<T> offset(const Point2<T> &p) const {
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

    Vector3<T> diagonal() const {
        return pMax - pMin;
    }

    T surfaceArea() const {
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        T z = pMax.z - pMin.z;
        return 2 * x * y + 2 * y * z + 2 * x * z;
    }

    T volume() const {
        T x = pMax.x - pMin.x;
        T y = pMax.y - pMin.y;
        T z = pMax.z - pMin.z;
        return x * y * z;
    }

    int maxAxis() const {
        Vector3<T> diag = pMax - pMin;
        T aMax = std::max(diag.x, diag.y, diag.z);
        if (diag.x == aMax)
            return 0;
        if (diag.y == aMax)
            return 1;
        return 2;
    }

    bool operator==(const Bounds3<T> &b) const {
        return pMin == b.pMin && pMax == b.pMax;
    }

    bool operator!=(const Bounds3<T> &b) const {
        return pMin != b.pMin && pMax == b.pMax;
    }

//    Point3<T> lerp(const Point3f &t) const {
//        return Point3<T>(untitled::lerp(t.x, pMin.x, pMax.x), untitled::lerp(t.y, pMin.y, pMax.y), untitled::lerp(t.z, pMin.z, pMax.z));
//    }

    Point3<T> offset(const Point3<T> &p) const {
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


template <typename T> Bounds3<T> getUnion(const Bounds3<T> &b, const Point3<T> &p) {
    Point3<T> pMin = Point3<T>(std::min(b.pMin.x, p.x), std::min(b.pMin.y, p.y), std::min(b.pMin.z, p.z));
    Point3<T> pMax = Point3<T>(std::max(b.pMax.x, p.x), std::max(b.pMax.y, p.y), std::max(b.pMax.z, p.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T> Bounds3<T> getUnion(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    Point3<T> pMin = Point3<T>(std::min(b1.pMin.x, b2.pMin.x), std::min(b1.pMin.y, b2.pMin.y), std::min(b1.pMin.z, b2.pMin.z));
    Point3<T> pMax = Point3<T>(std::max(b1.pMax.x, b2.pMax.x), std::max(b1.pMax.y, b2.pMax.y), std::max(b1.pMax.z, b2.pMax.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T> Bounds3<T> getIsect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
    Point3<T> pMin = Point3<T>(std::max(b1.pMin.x, b2.pMin.x), std::max(b1.pMin.y, b2.pMin.y), std::max(b1.pMin.z, b2.pMin.z));
    Point3<T> pMax = Point3<T>(std::min(b1.pMax.x, b2.pMax.x), std::min(b1.pMax.y, b2.pMax.y), std::min(b1.pMax.z, b2.pMax.z));
    return Bounds3<T>(pMin, pMax);
}

template <typename T> bool isInside(const Point3<T> &p, const Bounds3<T> &b) {
    return b.pMin.x <= p.x && p.x <= b.pMax.x && b.pMin.y <= p.y && p.y <= b.pMax.y && b.pMin.z <= p.z <= b.pMax.z;
}

template <typename T> Bounds3<T> expand(const Bounds3<T> &b, T pad) {
    Point3<T> pMin = Point3<T>(b.pMin.x - pad, b.pMin.y - pad, b.pMin.z - pad);
    Point3<T> pMax = Point3<T>(b.pMax.x + pad, b.pMax.y + pad, b.pMax.z + pad);
    return Bounds3<T>(pMin, pMax);
}

typedef Bounds2<float> Bounds2f;
typedef Bounds3<float> Bounds3f;
