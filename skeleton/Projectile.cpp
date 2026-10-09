#include "Projectile.h"
#include <iostream>

Projectile::Projectile(float _realMass, float _realSpeed, float _simulatedSpeed, Vector3D _pos, Vector3D _dir) : 
	Particle(_pos, { _simulatedSpeed, 0, 0 }, { 0, -9.8, 0 }, 1.0f){

	realGravity = -9.81;
	simulatedSpeed = _simulatedSpeed;
	realSpeed = _realSpeed;
	realMass = _realMass;
	increase = 10;
	dir = _dir;
	recalculate();
}


void Projectile::update(double t) {
	/*std::cout << "Masa: " << realMass << std::endl;
	std::cout << "MasaSim: " << simulatedMass << std::endl;
	std::cout << "Velocidad: " << realSpeed << std::endl;
	std::cout << "VelocidadSim: " << simulatedSpeed << std::endl;*/
	//std::cout << "Pos: (" << transform.p.x << ", " << transform.p.y << ", " << transform.p.z << ")" << std::endl;
	//std::cout << "Vel: (" << vel.x << ", " << vel.y << ", " << vel.z << ")" << std::endl;
	//std::cout << "Ac: (" << ac.x << ", " << ac.y << ", " << ac.z << ")" << std::endl;

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
