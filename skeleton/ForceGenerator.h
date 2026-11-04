#pragma once
#include "Particle.h"

//Clase abstracta ForceGenerator, base de los generadores de fuerza.
class ForceGenerator
{
public: 
	virtual ~ForceGenerator(){}
	virtual void setForce(Particle* p) = 0;
	virtual void update(double dt) {}
	virtual Vector3D getForce() { return(0, 0, 0); }
	virtual Vector3D getActionSpace() { return(0, 0, 0); }
	virtual void keyPressed(unsigned char key) = 0;
	virtual bool isActivated() = 0;
};

