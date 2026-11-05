#pragma once
#include "Vector3D.h"
#include "Hechizo.h"
#include "GravityParticles.h"
#include "FireForceGenerator.h"
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

	void shoot(const physx::PxTransform& camera);
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;

	float getMass() {
		if (!bala) throw std::domain_error("No hay balas");
		return bala->getMass();
	}
	float getGravity() {
		if (!bala) throw std::domain_error("No hay balas");
		return bala->getGravity();
	}

	void setGravityParticles(GravityParticles* gp) {
		gravityParticles = gp;
	}
private:
	Projectile* bala;
	FireForceGenerator* ffg;
	GravityParticles* gravityParticles = nullptr;

	bool shooting;
};

