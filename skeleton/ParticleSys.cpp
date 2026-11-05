#include "ParticleSys.h"
#include <algorithm>

ParticleSys::ParticleSys(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp, float _mass, float _lifeTime, float _size, Vector3D dist, Vector4 _color, Particle::Shape _shape, physx::PxQuat rot,
    Vector3D pIncr, Vector3D vDes, Vector3D aIncr, float dIncr, float mIncr, float lIncr, float sIncr, Vector4 cIncr, float _spawnInterval, bool gen) {
	auto g = new ParticleGen(_pos, _vel, _ac, _damp, _mass, _lifeTime, _size, _color, _shape, rot, pIncr, vDes, aIncr, dIncr, mIncr, lIncr, sIncr, cIncr, _spawnInterval, gen);
    genVector.push_back(g);
    actionSpace = dist;
    force = Vector3D(0, 0, 0);
    spawnTimer = 0.0f;
    spawnInterval = _spawnInterval;
}

ParticleSys::~ParticleSys() {
	for (auto p : particles) delete p;
	particles.clear();

    forceVector.clear();

    for (auto g : genVector) delete g;
    genVector.clear();
}

void ParticleSys::addForce(ForceGenerator* f) {
    forceVector.push_back(f);
}


void ParticleSys::removeForce(ForceGenerator* f) {
    auto it = std::find(forceVector.begin(), forceVector.end(), f);

    if (it != forceVector.end()) {
        forceVector.erase(it);
    }
}

void ParticleSys::addGen(ParticleGen* g) {
    genVector.push_back(g);
}

void ParticleSys::update(double dt) {
   for (auto fuerza : forceVector) fuerza->update(dt);

    for (auto p : particles) {
        if(forceVector.size() > 0)
        {
            Vector3D f(0, 0, 0);
            for (auto fuerza : forceVector) {
                if (fuerza->isActivated() && fuerza->getActionSpace() > p->getPos())
                {
                    fuerza->setForce(p);
                    Vector3D fuerzaActual = fuerza->getForce();
                    f += fuerza->getForce();
                }
            }
            p->applyForce(f);
        }

        p->integrate(dt);
    }

    for (auto g : genVector)
    {
        if (spawnInterval < 0.0f) {
            particles.push_back(g->generate(dt));
        }
        else if (spawnInterval == 0.0f) {
            particles.push_back(g->generate(dt));
        }
        else {
            spawnTimer += dt;

            while (spawnTimer >= spawnInterval) {
                particles.push_back(g->generate(dt));
                spawnTimer -= spawnInterval;
            }
        }
    }

    auto it = particles.begin();

    while (it != particles.end()) {
        Particle* p = *it;

        float life = p->setLifeTime(dt);

        if (life <= 0.0f || p->getPos() > actionSpace) {
            delete p;
            it = particles.erase(it);
        }
        else {
            ++it;
        }
    }
}
