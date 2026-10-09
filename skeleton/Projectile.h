#pragma once
#include "Particle.h"

//Clase proyectil que hereda de partícula.
class Projectile : public Particle
{
public:
	Projectile(float realMass, float realSpeed, float simulatedSpeed = 10, Vector3D _pos = Vector3D(0, 0, 0), Vector3D dir = Vector3D(1, 0, 0));
	void keyPress(unsigned char key, const physx::PxTransform& camera);
	void update(double t);
	void setDir(Vector3D dir);
	float getMass() { return simulatedMass; }
	float getGravity() { return simulatedGravity; }
private:
	void recalculate();
	float realMass;
	float realSpeed;

	float simulatedMass;
	float simulatedSpeed;

	float realGravity;
	float simulatedGravity;

	float increase;

	Vector3D dir;
};

