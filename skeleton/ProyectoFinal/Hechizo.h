#pragma once
#include "PxPhysicsAPI.h"

class Hechizo
{
public:
	virtual ~Hechizo() {}
	virtual void update(double dt) {}
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera){}
};

