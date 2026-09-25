#include "Particle.h"
Particle::Particle(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp) {
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
    transform = physx::PxTransform(_pos);
    renderItem = new RenderItem(shape, &transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    vel = _vel;
    ac = _ac;
    damp = _damp;
}

Particle::~Particle() {
    if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}

void Particle::integrate(double t) {
    transform = physx::PxTransform(transform.p + vel*t);
    vel = vel + ac * t;
    vel = vel * pow(damp, t);
}