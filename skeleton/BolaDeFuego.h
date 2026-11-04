#pragma once
#include "Vector3D.h"
#include "Hechizo.h"
#include "Projectile.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <vector>
#include <stdexcept>

//Clase weapon para disparar projectiles
class BolaDeFuego : public Hechizo
{
public:
	BolaDeFuego();
	~BolaDeFuego();

	//tipos de proyectil. Bala (trayectoria casi rectilínea) y Roca (arco parabólico)

	void shoot(const physx::PxTransform& camera);
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;

	float getMass() {
		if (balas.empty()) throw std::domain_error("No hay balas");
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

