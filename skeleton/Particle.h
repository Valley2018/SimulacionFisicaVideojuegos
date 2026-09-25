#pragma once
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"

class Particle
{
public:
	Particle(Vector3D _pos = Vector3D(0,0,0), Vector3D _vel = Vector3D(0, 0, 0), Vector3D _ac = Vector3D(0, 0, 0), float _damp = 0.0f);
	~Particle();

	void integrate(double t);
private:
	Vector3D vel;
	Vector3D ac;
	float damp;

	physx::PxTransform transform;
	RenderItem* renderItem;
};

