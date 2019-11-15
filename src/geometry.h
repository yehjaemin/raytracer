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

    template <typename U> &Vector2<T> operator*=(U u) const {
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
        assert 0 <= i && i <= 1;
        if (i == 0) {
            return x;
        }
        return y;
    }

    bool operator==(const Vector2<T> &v) const {
        return x == v.x && y == v.y;
    }

    bool operator!=(const Vector2<T> &v) const {
        return x != v.x || y != v.y;
    }

    T x, y;
};

template <typename T> class Vector3 {
public:
    Vector3() : x(0), y(0), z(0);
    Vector3(T i, T j, T k) : x(i), y(j), z(k);

    

    T x, y, z;
};
