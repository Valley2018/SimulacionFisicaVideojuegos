#pragma once
#include "Vector3D.h"
#include "Projectile.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <vector>
#include <stdexcept>

//Clase weapon para disparar projectiles
class Weapon
{
public:
	Weapon();
	~Weapon();

	//tipos de proyectil. Bala (trayectoria casi rectilínea) y Roca (arco parabólico)
	enum projectilTypes { BULLET, ROCK };

	void shoot(const physx::PxTransform& camera, projectilTypes type);
	void update(double dt);
	void keyPress(unsigned char key, const physx::PxTransform& camera);

	float getMass() { 
		if (balas.empty()) throw std::domain_error ("No hay balas");
		return balas.back()->getMass(); 
	}
	float getGravity() {
		if (balas.empty()) throw std::domain_error("No hay balas");
		return balas.back()->getGravity(); 
	}

private:
	//vector de balas
	std::vector<Projectile*> balas;
};

