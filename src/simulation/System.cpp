#include "System.h"
#include "util/util.h"

void System::reset() {
    state = initialState;
}

void System::setState(System::State _state) {
    state = _state;
}

void System::setParameters(System::Parameters _params) {
    parameters = _params;
}

System::State System::getState() const {
    return state;
}

System::Parameters System::getParameters() const {
    return parameters;
}

void System::step(float dt, System::Input u) {
    System::State f1 = System::calculateDerivatives(state, u);
    System::State f2 = System::calculateDerivatives(state + f1 * dt / 2.0, u);
    System::State f3 = System::calculateDerivatives(state + f2 * dt / 2.0, u);
    System::State f4 = System::calculateDerivatives(state + f3 * dt, u);

    state += dt / 6.0 * (f1 + 2 * f2 + 2 * f3 + f4);
}

System::State System::calculateDerivatives(const System::State _state, const System::Input u) const {

    // Use the input to find the orientation of the plate (n_hat);
    R3 plateRotationMatrix = System::calculatePlateNormalVector(u);
    Vector3 nhat = plateRotationMatrix.k();

    // Calculate the perpendicular component of the gravity vector;
    Vector3 F_g = { 0.f, 0.f, parameters.gravity };
    Vector3 F_g_perp = F_g - nhat * (F_g.dot(nhat) * nhat.z);

    // Acceleration is equal to: a = F_g_perp / (m_ball + I_ball / r_ball^2)
    // NOTE: When the plate is properly modeled, I'll need to add the centrifugal / other forces from the angular velocity of the plate to this!
    Vector3 acceleration = F_g_perp / (parameters.ballMass * 7. / 5.);

    // Finally, project acceleration onto the coordinates of the plate;
    float ax = plateRotationMatrix.i().dot(acceleration);
    float ay = plateRotationMatrix.j().dot(acceleration);

    return System::State(_state.vx, _state.vy, ax, ay);
}

R3 System::calculatePlateNormalVector(System::Input u) const {
    /*
    We're going to assume the plate has a pin joint in the center, so the middle of the plate is constrained,
    and a pin on the middle of the +X and +Y sides which is attached to some actuator such that the Input, u,
    controls exactly the Z height of the +X and +Y pins (while the X / Y coordinate is free).
    */

    float d;
    float L = parameters.sideLength / 2.f;

    // Get direction vector to X side attachment point;
    d = std::sqrt(L * L - u.a * u.a);
    Vector3 va{ d, 0.f, u.a };
    va.normalize();

    // Get direction vector to Y side attachment point;
    d = std::sqrt(L * L - u.b * u.b);
    Vector3 vb{ 0.f, d, u.b };
    vb.normalize();

    // Get the rotation matrix using cross products;
    Vector3 vc = va.cross(vb);
    return R3(va, vb, vc);
}