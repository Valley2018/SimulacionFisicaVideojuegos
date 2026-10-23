#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"

class Particle
{
public:
	enum Shape { BOX, SPHERE, CAPSULE };

	Particle(Vector3D _pos = Vector3D(0,0,0), Vector3D _vel = Vector3D(0, 0, 0), Vector3D _ac = Vector3D(0, 0, 0), float _damp = 1.0f, float mass = 0.0f, float _lifeTime = -1, float size = 0.5f, Vector4 _color = Vector4(1.0, 1.0, 1.0, 1.0), Shape s = SPHERE, physx::PxQuat rot = physx::PxQuat(physx::PxIdentity));
	~Particle();

	void integrate(double t);
	void integrateSemi(double t);
	void verlet(double t);

	void setMass(float m) { mass = m; }
	void setVel(Vector3D v) { vel = v; }
	void setAc(Vector3D a) { ac = a; }
	float setLifeTime(double dt) { return lifeTime -= dt; }
	Vector3D getPos() {  return transform.p; }

private:
	//Rozamiento
	float damp;
	float lifeTime;
	Vector3D previousPos;
	RenderItem* renderItem;

protected:
	physx::PxTransform transform;
	Vector3D vel;
	Vector3D ac;
	float mass;
	Shape s;
	physx::PxQuat rot;
};

