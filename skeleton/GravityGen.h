#pragma once
#include "ForceGenerator.h"
#include "Vector3D.h"

//Generador de gravedad
class GravityGen : public ForceGenerator
{
public: 
	GravityGen(Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : GRAVITY_AC(Vector3D(0.0f, -9.81f, 0.0f)), actionSpace(_actionSpace){
		
	}


	void setForce(Particle* p) override { fuerza = GRAVITY_AC * p->getMass(); }
	Vector3D getForce() override { return fuerza; }
	Vector3D getActionSpace() override{ return actionSpace; }

private:
	const Vector3D GRAVITY_AC;
	Vector3D fuerza;
	Vector3D actionSpace;
};

