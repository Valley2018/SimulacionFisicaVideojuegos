#pragma once
#include "ForceGenerator.h"
#include "../Vector3D.h"
#include <iostream>

//Generador de gravedad. Se desactiva/activa con 'g'.
class GravityGen : public ForceGenerator
{
public: 
	GravityGen(Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : GRAVITY_AC(Vector3D(0.0f, -9.81f, 0.0f)), actionSpace(_actionSpace), activated(true){
		
	}


	void setForce(Particle* p) override { fuerza = GRAVITY_AC * p->getMass(); }
	Vector3D getForce() override
	{
		return fuerza;
	}
	Vector3D getActionSpace() override{ return actionSpace; }

	void keyPressed(unsigned char key) {
		if (key == 'G') activated = !activated;
		std::cout << activated << std::endl;
	}
	virtual bool isActivated() override { return activated; }

private:
	const Vector3D GRAVITY_AC;
	Vector3D fuerza;
	Vector3D actionSpace;

	bool activated;
};

