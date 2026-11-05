#pragma once
#include "Vector3D.h"
#include "Hechizo.h"
#include "GravityParticles.h"
#include "MagneticForceGenerator.h"
#include "Projectile.h"
#include "RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <vector>
#include <stdexcept>

class MagneticSpell : public Hechizo
{
public:
	MagneticSpell();
	~MagneticSpell();

	void shoot(const physx::PxTransform& camera);
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;

	void setGravityParticles(GravityParticles* gp) {
		gravityParticles = gp;
	}
private:
	Projectile* bala;
	MagneticForceGenerator* mfg;
	GravityParticles* gravityParticles = nullptr;

	bool shooting;
};

