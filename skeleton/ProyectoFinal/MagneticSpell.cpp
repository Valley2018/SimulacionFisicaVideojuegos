#include "MagneticSpell.h"
#include <iostream>

MagneticSpell::MagneticSpell() {
    bala = nullptr;
    mfg = nullptr;
    shooting = false;
}

MagneticSpell::~MagneticSpell() {
    if(bala)
    delete bala;
    bala = nullptr;

    if (mfg != nullptr && gravityParticles != nullptr) {
        gravityParticles->removeForceGenerator(mfg);
    }

    if (mfg)
    delete mfg;
    mfg = nullptr;
}

void MagneticSpell::shoot(const physx::PxTransform& camera) {

    if (shooting) return;

    shooting = true;

    Vector3D eye(camera.p.x, camera.p.y, camera.p.z);

    physx::PxVec3 dir = camera.q.rotate(physx::PxVec3(0, 0, -1));

    bala = new Projectile(0.02f, 300, 10, eye, dir, Vector4(0.55f, 0.58f, 0.62f, 1.0f), 7.0f, 1.0f);

    mfg = new MagneticForceGenerator(20.0f, 5.0f, 0.5f, 3.0f);
    mfg->setPosition(eye);

    if (gravityParticles != nullptr) {
        gravityParticles->addForceGenerator(mfg);
    }
}

void MagneticSpell::update(double dt) {

    if (!shooting || bala == nullptr || mfg == nullptr) return;

    bala->update(dt);

    if (!bala->isAlive()) {
        delete bala;
        bala = nullptr;

        if (gravityParticles != nullptr) {
            gravityParticles->removeForceGenerator(mfg);
        }
        delete mfg;
        mfg = nullptr;

        shooting = false;
    }
    else {
        mfg->setPosition(bala->getPos());
    }
}

void MagneticSpell::keyPress(unsigned char key,
    const physx::PxTransform& camera) {

    if (key == 'i' && !shooting) {
        shoot(camera);
    }

    if (bala != nullptr) {
        bala->keyPress(key, camera);
    }
}