#pragma once

#include "util/util.h"

class System {
public:
    struct Parameters {
        float sideLength = 0.1f;
        float plateMass = 1.0f;
        float ballRadius = 0.01f;
        float ballMass = 0.01f;
        float gravity = -9.81f;
    };

    struct State {
        float x = 0.0f;
        float y = 0.0f;
        float vx = 0.0f;
        float vy = 0.0f;

        State operator+(const State& other) const {
            return {
                x + other.x, y + other.y, vx + other.vx, vy + other.vy
            };
        }

        State operator*(float scalar) const {
            return {
                x * scalar, y * scalar, vx * scalar, vy * scalar
            };
        }

        State& operator+=(const State& other) {
            x += other.x; y += other.y; vx += other.vx; vy += other.vy;
            return *this;
        }

        State operator/(float scalar) const {
            return {
                x / scalar, y / scalar, vx / scalar, vy / scalar
            };
        }
    };

    struct Input {
        float a = 0.0f;
        float b = 0.0f;

        Input operator+(const Input& other) const {
            return { a + other.a, b + other.b };
        }

        Input& operator+=(const Input& other) {
            a += other.a;
            b += other.b;
            return *this;
        }

        Input operator*(float scalar) const {
            return { a * scalar, b * scalar };
        }

        Input operator/(float scalar) const {
            return { a / scalar, b / scalar };
        }
    };

    System() = default;
    System(State _state) : state(_state), initialState(_state) {};
    System(Parameters _params, State _state) : parameters(_params), state(_state), initialState(_state) {};

    void step(float dt, Input u);

    // Getters / Setters
    void reset();
    State getState() const;
    Parameters getParameters() const;
    void setState(State);
    void setParameters(Parameters);

private:
    State calculateDerivatives(const State, const Input) const;
    R3 calculatePlateNormalVector(System::Input u) const;

    Parameters parameters;
    State state;
    State initialState;
};

inline System::State operator*(float scalar, const System::State& s) {
    return s * scalar;
}

inline System::Input operator*(float scalar, const System::Input& input) {
    return input * scalar;
}