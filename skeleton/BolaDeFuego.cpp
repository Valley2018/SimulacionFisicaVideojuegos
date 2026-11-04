#include "BolaDeFuego.h"
#include "Weapon.h"

BolaDeFuego::BolaDeFuego() {
}
//Destructora
BolaDeFuego::~BolaDeFuego() {
    for (auto p : balas) delete p;
    balas.clear();
}

//Disparar el proyectil desde la cámara con parámetros según su tipo
void BolaDeFuego::shoot(const physx::PxTransform& camera) {
    Vector3D eye(camera.p.x, camera.p.y, camera.p.z);
    physx::PxVec3 dir = camera.q.rotate(physx::PxVec3(0, 0, -1));
    Vector3D direction(dir.x, dir.y, dir.z);
    float vel, mass;
        vel = 300;
        mass = 0.02;
    Projectile* p = new Projectile(mass, vel, 10, eye, dir, Vector4(1.0f, .0f, 0.0f, 1.0f));
    balas.push_back(p);
}


void BolaDeFuego::update(double dt) {
    for (auto p : balas) p->update(dt);
}

void BolaDeFuego::keyPress(unsigned char key, const physx::PxTransform& camera) {
    if (key == 'f') {
        shoot(camera);
    }
    for (auto p : balas) p->keyPress(key, camera);
}