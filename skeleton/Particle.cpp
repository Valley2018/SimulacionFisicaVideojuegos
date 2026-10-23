#include "Particle.h"

//Inicializar valores de la partícula
Particle::Particle(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp, float _mass, float _lifeTime,  float size, Vector4 _color, Shape _s, physx::PxQuat _rot) {
    s = _s;

    physx::PxShape* shape = nullptr;
    switch (s) {
    case SPHERE:
        shape = CreateShape(physx::PxSphereGeometry(size));
        break;

    case BOX:
        shape = CreateShape(physx::PxBoxGeometry(size, size, size));
        break;

    case CAPSULE:
        shape = CreateShape(physx::PxCapsuleGeometry(size / 2.0f, size) );
        break;
    }

    transform = physx::PxTransform(_pos, _rot);
    rot = _rot;
    previousPos = _pos;
    renderItem = new RenderItem(shape, &transform, _color);
    vel = _vel;
    ac = _ac;
    damp = _damp;
    mass = _mass;
    lifeTime = _lifeTime;
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
    transform = physx::PxTransform(transform.p + vel * t, rot);
    vel = vel + ac * t;
    vel = vel * pow(damp, t);
}

//Método de Euler Semi-implícito
void Particle::integrateSemi(double t) {
    vel = vel + ac * t;
    vel = vel * pow(damp, t);
   transform = physx::PxTransform(transform.p + vel * t, rot);

}

//Método de Verlet
void Particle::verlet(double t) {
    Vector3D currentPos = transform.p;

    transform = physx::PxTransform(
        currentPos* 2.0f - previousPos + ac * t * t, rot
    );

    previousPos = currentPos;
}