#include "GravityParticles.h"

GravityParticles::GravityParticles(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp, float _mass, float _lifeTime, float _size, Vector3D _maxDis, Vector4 _color, Particle::Shape _shape, physx::PxQuat _rot,
	Vector3D _pIncr, Vector3D _vDes, Vector3D _aIncr, float _dIncr, float _mIncr, float _lIncr, float _sIncr, Vector4 _cIncr, float spawnTime, bool gen) {

	sistema = new ParticleSys( _pos,  _vel,  _ac,  _damp,  _mass,  _lifeTime,  _size,  _maxDis,  _color,  _shape, _rot,
		 _pIncr,  _vDes,  _aIncr,  _dIncr,  _mIncr,  _lIncr,  _sIncr,  _cIncr, spawnTime, gen);
}


GravityParticles::~GravityParticles() {
	delete sistema;
}

void GravityParticles::update(double t) {
	sistema->update(t);
}

void GravityParticles::addForceGenerator(ForceGenerator* f) {
	sistema->addForce(f);
}

void GravityParticles::removeForceGenerator(ForceGenerator* f) {
	sistema->removeForce(f);
}

void GravityParticles::keyPress(unsigned char key, const physx::PxTransform& camera) {

	if (key == 'g') { sistema->setGen(); }
}