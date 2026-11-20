#include "BolaDeFuego.h"

BolaDeFuego::BolaDeFuego() {
    bala = nullptr;
    ffg = nullptr;
    shooting = false;
}

BolaDeFuego::~BolaDeFuego() {

    delete bala;
    bala = nullptr;

    if (ffg != nullptr && gravityParticles != nullptr) {
        gravityParticles->removeForceGenerator(ffg);
    }

    delete ffg;
    ffg = nullptr;
}

void BolaDeFuego::shoot(const physx::PxTransform& camera) {

    if (shooting) return;

    shooting = true;

    Vector3D eye(camera.p.x, camera.p.y, camera.p.z);

    physx::PxVec3 dir = camera.q.rotate(physx::PxVec3(0, 0, -1));

    bala = new Projectile(0.02f, 300, 10, eye, dir, Vector4(1.0f, 0.5f, 0.0f, 1.0f), 7.0f, 2.0f);

    ffg = new FireForceGenerator(50.0f, 5.0f);
    ffg->setPosition(eye);

    if (gravityParticles != nullptr) {
        gravityParticles->addForceGenerator(ffg);
    }
}

void BolaDeFuego::update(double dt) {

    if (!shooting || bala == nullptr) return;

    bala->update(dt);

    if (!bala->isAlive()) {
        delete bala;
        bala = nullptr;

        if (gravityParticles != nullptr) {
            gravityParticles->removeForceGenerator(ffg);
        }
        delete ffg;
        ffg = nullptr;

        shooting = false;
    }
    else {
        ffg->setPosition(bala->getPos());
    }
}

void BolaDeFuego::keyPress(unsigned char key,
    const physx::PxTransform& camera) {

    if (key == 'f' && !shooting) {
        shoot(camera);
    }

    if (bala != nullptr) {
        bala->keyPress(key, camera);
    }
}