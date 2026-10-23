#pragma once
#include "Particle.h"

struct ParticleModel {
	Vector3D pos;
	Vector3D vel;
	Vector3D ac;
	float damp;
	float mass;
	float lifeTime;
	float size;
	Vector4 color;
	Particle::Shape shape;
	physx::PxQuat rot;
};

struct Increments {
	Vector3D posIncr;
	Vector3D velDes;
	Vector3D acIncr;
	float dampIncr;
	float massIncr;
	float lifeTimeIncr;
	float sizeIncr;
	Vector4 colorIncr;
};

//Generador de Partículas. Contiene una partícula modelo y un struct que guarda los datos
// necesarios para llevar a cabo las distribuciones. El método para generar partículas utiliza 
// todos esos datos y las distribuciones para crear las partículas del sistema. Todos los datos 
// están parametrizados.
class ParticleGen
{
public: 
	ParticleGen(Vector3D _pos = Vector3D(0, 0, 0), Vector3D _vel = Vector3D(0, 0, 0), Vector3D ac = Vector3D(0, -10, 0), float _damp = 1.0f, float mass = 0.0f, float _lifeTime = -1, float size = 0.5f, Vector4 _color = Vector4(1.0, 1.0, 1.0, 1.0), Particle::Shape _shape = Particle::SPHERE, physx::PxQuat rot = physx::PxQuat(physx::PxIdentity),
		Vector3D pIncr = Vector3D(0.0f, 0.0f, 0.0f), Vector3D vDes = Vector3D(0.2f, 0.2f, 0.2f), Vector3D aIncr = Vector3D(0.0f, 0.0f, 0.0f), float dIncr = 0.0f, float mIncr = 0.0f, float lIncr = 0.5f, float sIncr = 0.0f, Vector4 cIncr = Vector4(0.5f, 0.5f, 0.5f, 0.0f));

	~ParticleGen();

	float UniformDistr(float min, float max);
	double NormalDistr(double media, double d);

	Particle* generate(double dt);
private:
	ParticleModel modelo;
	Increments incr;
};

