#include "Projectile.h"

Projectile::Projectile(float _realMass, float _realSpeed, float _simulatedSpeed, Vector3D _pos, Vector3D _dir, Vector4 color) :
	Particle(_pos, { _simulatedSpeed, 0, 0 }, { 0, -9.8, 0 }, 1.0f, 0.1f, -1.0f, 0.5f, color){

	realGravity = -9.81;
	simulatedSpeed = _simulatedSpeed;
	realSpeed = _realSpeed;
	realMass = _realMass;
	increase = 10;
	dir = _dir;
	recalculate();
}


void Projectile::update(double t) {
	integrate(t);
}

void Projectile::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'm') {
		realMass -= increase;
		if (realMass < 0) realMass = 0;
		recalculate();
	}else if (key == 'M') {
		realMass += increase;
		recalculate();
	}else if (key == 'v') {
		realSpeed -= increase;
		recalculate();
	}
	else if (key == 'V') {
		realSpeed += increase;
		recalculate();
	}
}

//Calculo de la masa y la gravedad simuladas.
void Projectile::recalculate() {
	simulatedMass = realMass * pow(realSpeed, 2) / pow(simulatedSpeed, 2);
	if(realSpeed!=0)
	simulatedGravity = (pow((simulatedSpeed / realSpeed), 2)* realGravity);

	mass = simulatedMass;
	ac = Vector3D(0, simulatedGravity, 0);
	setDir(dir);
}

//Dirección
void Projectile::setDir(Vector3D dir) {
	vel = dir * simulatedSpeed;
}
