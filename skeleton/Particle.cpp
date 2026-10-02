#include "Particle.h"
//Inicializar valores de la partícula
Particle::Particle(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp) {
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
    transform = physx::PxTransform(_pos);
    previousPos = _pos;
    renderItem = new RenderItem(shape, &transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    vel = _vel;
    ac = _ac;
    damp = _damp;
}
//Destructora
Particle::~Particle() {
    if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}

//Método de Euler
void Particle::integrate(double t) {
    transform = physx::PxTransform(transform.p + vel * t);
    vel = vel + ac * t;
    vel = vel * pow(damp, t);
}

//Método de Euler Semi-implícito
void Particle::integrateSemi(double t) {
    vel = vel + ac * t;
   transform = physx::PxTransform(transform.p + vel * t);

}

//Método de Verlet
void Particle::verlet(double t) {
    Vector3D currentPos = transform.p;

    transform = physx::PxTransform(
        currentPos* 2.0f - previousPos + ac * t * t
    );

    previousPos = currentPos;
}