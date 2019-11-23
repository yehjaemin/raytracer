#include <algorithm>
#include <assert.h>
#include <limits>
#include <math.h>

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
&normalize(const Vector2<T> &v) {
    return v / v.length();
}

template <typename T> inline Vector3<T>
&normalize(const Vector3<T> &v) {
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

template <typename T> inline float distance(const Point2<T> &p, const Point2<T> &q) {
    return (p - q).length();
}

template <typename T> inline float distance(const Point3<T> &p, const Point3<T> &q) {
    return (p - q).length();
}

typedef Point2<float> Point2f;
typedef Point3<float> Point3f;

class Ray {
public:
    Ray() : tMax(std::numeric_limits<float>::infinity()), time(0.f) {}
    Ray(const Point3f &o, const Vector3f &d, float tMax = std::numeric_limits<float>::infinity(), float time = 0.f) : o(o), d(d), tMax(tMax), time(time) {}

    Point3f o; // origin
    Vector3f d; // direction
    float tMax; // r(t) = o + dt
    float time;
};
