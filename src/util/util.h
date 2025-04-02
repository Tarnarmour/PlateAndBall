#pragma once

#include <cmath>

struct Vector2 {
    float x;
    float y;

    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    };

    Vector2 operator-(const Vector2& other) const {
        return { x - other.x, y - other.y };
    };

    Vector2 operator*(const float scalar) const {
        return { x * scalar, y * scalar };
    };

    Vector2 operator/(const float scalar) const {
        return { x / scalar, y / scalar };
    };

    float dot(const Vector2& other) const {
        return (x * other.x + y * other.y);
    };

    float length() const {
        return std::sqrt(this->dot(*this));
    };

    void normalize() {
        float length = this->length();
        if (length > 0.f) {
            x /= length;
            y /= length;
        }
    };
};

inline Vector2 operator*(float a, const Vector2 v) {
    return v * a;
}

struct Vector3 {
    float x;
    float y;
    float z;

    Vector3 operator+(const Vector3& other) const {
        return { x + other.x, y + other.y, z + other.z };
    };

    Vector3 operator-(const Vector3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    };

    Vector3 operator*(const float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    };

    Vector3 operator/(const float scalar) const {
        return { x / scalar, y / scalar, z / scalar };
    };

    float dot(const Vector3& other) const {
        return (x * other.x + y * other.y + z * other.z);
    };

    float length() const {
        return std::sqrt(this->dot(*this));
    };

    void normalize() {
        float length = this->length();
        if (length > 0.f) {
            x /= length;
            y /= length;
            z /= length;
        }
    };

    Vector3 cross(const Vector3& other) const {
        return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
    };
};

inline Vector3 operator*(float a, const Vector3 v) {
    return v * a;
}

struct R2 {

    /*
    | ix jx |
    | iy jy |
    */

    float ix, iy, jx, jy;

    R2() = default;

    R2(float _ix, float _iy, float _jx, float _jy) :
        ix(_ix), iy(_iy), jx(_jx), jy(_jy) {
    };

    R2(float theta) {
        ix = std::cos(theta); iy = std::sin(theta);
        jx = -std::sin(theta); jy = std::cos(theta);
    }

    R2(Vector2 i, Vector2 j) {
        ix = i.x; iy = i.y;
        jx = j.x; jy = j.y;
    }

    // Column accessors
    Vector2 i() const {
        return { ix, iy };
    }

    Vector2 j() const {
        return { jx, jy };
    }

    // Row accessors
    Vector2 x() const {
        return { ix, jx };
    }

    Vector2 y() const {
        return { iy, jy };
    }

    // Transpose
    R2 T() const {
        return {
            { ix, jx },
            { iy, jy }
        };
    }

    // Matrix-matrix multiply
    R2 operator*(const R2& other) const {
        return {
            {
                ix * other.ix + jx * other.iy,  // new ix
                iy * other.ix + jy * other.iy   // new iy
            },
            {
                ix * other.jx + jx * other.jy,  // new jx
                iy * other.jx + jy * other.jy   // new jy
            }
        };
    }

    // Matrix-vector multiply
    Vector2 operator*(const Vector2& v) const {
        return {
            ix * v.x + jx * v.y,
            iy * v.x + jy * v.y
        };
    }
};


struct R3 {

    /*
    | ix jx kx |
    | iy jy ky |
    | iz jz kz |
    */

    float ix, jx, kx, iy, jy, ky, iz, jz, kz;

    R3() = default;

    R3(float _ix, float _iy, float _iz,
        float _jx, float _jy, float _jz,
        float _kx, float _ky, float _kz)
        : ix(_ix), iy(_iy), iz(_iz),
        jx(_jx), jy(_jy), jz(_jz),
        kx(_kx), ky(_ky), kz(_kz) {
    }

    R3(Vector3 i, Vector3 j, Vector3 k) {
        ix = i.x; iy = i.y; iz = i.z;
        jx = j.x; jy = j.y; jz = j.z;
        kx = k.x; ky = k.y; kz = k.z;
    }

    Vector3 i() const {
        return { ix, iy, iz };
    }

    Vector3 j() const {
        return { jx, jy, jz };
    }

    Vector3 k() const {
        return { kx, ky, kz };
    }

    Vector3 x() const {
        return { ix, jx, kx };
    }

    Vector3 y() const {
        return { iy, jy, ky };
    }

    Vector3 z() const {
        return { iz, jz, kz };
    }

    R3 T() const {
        return { ix, iy, iz, jx, jy, jz, kx, ky, kz };
    }

    R3 operator*(const R3& other) const {
        Vector3 ci = *this * other.i();
        Vector3 cj = *this * other.j();
        Vector3 ck = *this * other.k();
        return R3(ci, cj, ck);
    }

    Vector3 operator*(const Vector3& v) const {
        return {
            ix * v.x + jx * v.y + kx * v.z,
            iy * v.x + jy * v.y + ky * v.z,
            iz * v.x + jz * v.y + kz * v.z
        };
    }
};