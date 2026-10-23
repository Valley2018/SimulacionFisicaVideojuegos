#include "ParticleGen.h"
#include <random>
#include <iostream>
ParticleGen::ParticleGen(Vector3D _pos, Vector3D _vel, Vector3D _ac, float _damp, float _mass, float _lifeTime, float _size, Vector4 _color, Particle::Shape _shape, physx::PxQuat _rot, Vector3D pIncr, Vector3D vDes, Vector3D aIncr, float dIncr, float mIncr, float lIncr, float sIncr, Vector4 cIncr) {
	modelo.pos = _pos;
	modelo.vel = _vel;
	modelo.ac = _ac;
	modelo.damp = _damp;
	modelo.mass = _mass;
	modelo.lifeTime = _lifeTime;
	modelo.size = _size;
	modelo.color = _color;
	modelo.shape = _shape;
	modelo.rot = _rot;

	incr.posIncr = pIncr;
	incr.velDes = vDes;
	incr.acIncr = aIncr;
	incr.dampIncr = dIncr;
	incr.massIncr = mIncr;
	incr.lifeTimeIncr = lIncr;
	incr.sizeIncr = sIncr;
	incr.colorIncr = cIncr;
}

ParticleGen::~ParticleGen() {

}

std::mt19937 _mt;

float ParticleGen::UniformDistr(float min, float max) {
	std::uniform_real_distribution<float> uni(min, max);
	return uni(_mt);
}

double ParticleGen::NormalDistr(double media, double d) {
	if (d <= 0) 
	{
		return media;
	}
	std::normal_distribution<double> nor(media, d);
	return nor(_mt);
}

Particle* ParticleGen::generate(double dt) {
	//Calculo de los datos con distribuciones.
	Vector3D pos (UniformDistr(modelo.pos.x - incr.posIncr.x, modelo.pos.x + incr.posIncr.x),
								UniformDistr(modelo.pos.y - incr.posIncr.y, modelo.pos.y + incr.posIncr.y),
								UniformDistr(modelo.pos.z - incr.posIncr.z, modelo.pos.z + incr.posIncr.z));

	Vector3D vel (NormalDistr(modelo.vel.x, incr.velDes.x),
							   NormalDistr(modelo.vel.y, incr.velDes.y),
							   NormalDistr(modelo.vel.z, incr.velDes.z));

	Vector3D ac (UniformDistr(modelo.ac.x - incr.acIncr.x, modelo.ac.x + incr.acIncr.x),
		UniformDistr(modelo.ac.y - incr.acIncr.y, modelo.ac.y + incr.acIncr.y),
							  UniformDistr(modelo.ac.z - incr.acIncr.z, modelo.ac.z + incr.acIncr.z));

	float damp = UniformDistr(modelo.damp - incr.dampIncr, modelo.damp + incr.dampIncr);
	float mass = UniformDistr(modelo.mass - incr.massIncr, modelo.mass + incr.massIncr);
	float life = UniformDistr(modelo.lifeTime - incr.lifeTimeIncr, modelo.lifeTime + incr.lifeTimeIncr);
	float size = UniformDistr(modelo.size - incr.sizeIncr, modelo.size + incr.sizeIncr);

	Vector4 col(UniformDistr(modelo.color.x - incr.colorIncr.x, modelo.color.x + incr.colorIncr.x),
		UniformDistr(modelo.color.y - incr.colorIncr.y, modelo.color.y + incr.colorIncr.y),
		UniformDistr(modelo.color.z - incr.colorIncr.z, modelo.color.z + incr.colorIncr.z),
		UniformDistr(modelo.color.w - incr.colorIncr.w, modelo.color.w + incr.colorIncr.w));

	Particle* p = new Particle(pos, vel, ac, damp, mass, life + dt, size, col, modelo.shape, modelo.rot);

	return p;
}