#include "ParticleSys.h"
ParticleSys::ParticleSys(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp, float _mass, float _lifeTime, float _size, Vector3D dist, Vector4 _color, Particle::Shape _shape, physx::PxQuat rot,
    Vector3D pIncr, Vector3D vDes, Vector3D aIncr, float dIncr, float mIncr, float lIncr, float sIncr, Vector4 cIncr) {
	g = new ParticleGen(_pos, _vel, _ac, _damp, _mass, _lifeTime, _size, _color, _shape, rot, pIncr, vDes, aIncr, dIncr, mIncr, lIncr, sIncr, cIncr);
    actionSpace = dist;
}

ParticleSys::~ParticleSys() {
	for (auto p : particles) delete p;
	particles.clear();
    delete g;
}

void ParticleSys::update(double dt) {
    for (auto p : particles) {
        p->integrate(dt);
    }

    particles.push_back(g->generate(dt));

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
