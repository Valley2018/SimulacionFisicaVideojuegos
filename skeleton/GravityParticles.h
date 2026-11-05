#pragma once
#include "Hechizo.h"
#include "ParticleSys.h"

class GravityParticles : public Hechizo
{
public: 
	GravityParticles(Vector3D _pos = Vector3D(0, 0, 0), Vector3D _vel = (0, 0, 0), Vector3D ac = (0, 0, 0), float _damp = 1.0f, float mass = 0.01f, float _lifeTime = 120.0f, float _size = 0.8f, Vector3D maxDis = Vector3D(100.0f, 25.0f, 100.0f), Vector4 _color = Vector4(0.0, 0.0, 0.6, 1.0), Particle::Shape _shape = Particle::SPHERE, physx::PxQuat rot = physx::PxQuat(physx::PxIdentity),
		Vector3D pIncr = Vector3D(98.0f, 23.0f, 98.0f), Vector3D vDes = Vector3D(0.4f, 0.4f, 0.4f), Vector3D aIncr = Vector3D(0.0f, 0.0f, 0.0f), float dIncr = 0.0f, float mIncr = 0.0f, float lIncr = 60.0f, float sIncr = 0.2f, Vector4 cIncr = Vector4(0.0f, 0.0f, 0.4f, 0.0f), float spawnTime = 0.5f, bool gen = true);
	~GravityParticles() override;

	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;
	void addForceGenerator(ForceGenerator* f);
	void removeForceGenerator(ForceGenerator* f);
private:
	ParticleSys* sistema = nullptr; 
};

