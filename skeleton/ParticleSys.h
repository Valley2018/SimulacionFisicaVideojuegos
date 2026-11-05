#pragma once
#include "Particle.h"
#include "ParticleGen.h"
#include "ForceGenerator.h"
#include <vector>

//Sistema de partículas. Contiene un vector con todas sus partículas. Las actualiza
//y las elimina si termina su tiempo de vida o si salen del espacio de acción del sistema.
class ParticleSys
{
public:
	ParticleSys(Vector3D _pos = Vector3D(0, 0, 0), Vector3D _vel = (0, 0, 0), Vector3D ac = (0, -10, 0), float _damp = 1.0f, float mass = 0.0f, float _lifeTime = 2.0f, float _size = 0.5f, Vector3D maxDis = Vector3D(500.0f, 500.0f, 500.0f), Vector4 _color = Vector4(1.0, 1.0, 1.0, 1.0), Particle::Shape _shape = Particle::SPHERE, physx::PxQuat rot = physx::PxQuat(physx::PxIdentity),
		Vector3D pIncr = Vector3D(0.0f, 0.0f, 0.0f), Vector3D vDes = Vector3D(0.2f, 0.2f, 0.2f), Vector3D aIncr = Vector3D(0.0f, 0.0f, 0.0f), float dIncr = 0.0f, float mIncr = 0.0f, float lIncr = 0.5f, float sIncr = 0.0f, Vector4 cIncr = Vector4(0.5f, 0.5f, 0.5f, 0.0f), float spawnInterval = -1.0f, bool gen = true);
	~ParticleSys();

	void update(double dt);
	void addForce(ForceGenerator* f);
	void removeForce(ForceGenerator* f);
	void addGen(ParticleGen* g);
private:
	std::vector<Particle*> particles;
	std::vector<ForceGenerator*> forceVector;
	std::vector<ParticleGen*> genVector;
	Vector3D actionSpace;
	Vector3D force;

	float spawnInterval; 
	float spawnTimer;
	bool generate;
};

