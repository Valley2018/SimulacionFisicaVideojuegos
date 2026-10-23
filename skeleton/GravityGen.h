#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"

class GravityGen : public ForceGenerator
{
public: 
	GravityGen(float mass) : GRAVITY_AC(Vector3D(0.0f, -9.81f, 0.0f)) {
		fuerza = GRAVITY_AC * mass;
	}

	Vector3D getForce() { return fuerza; }

private:
	const Vector3D GRAVITY_AC;
	Vector3D fuerza;
};

