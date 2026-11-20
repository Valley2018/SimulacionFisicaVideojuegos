#pragma once
#include "../Vector3D.h"
#include "Hechizo.h"
#include "Goblin.h"
#include "../Proyectil/Projectile.h"
#include "../RenderUtils.hpp"
#include "PxPhysicsAPI.h"
#include <vector>
#include <stdexcept>

//Clase weapon para disparar projectiles
class GoblinSpell : public Hechizo
{
public:
	GoblinSpell();
	~GoblinSpell();

	void createGoblin(const physx::PxTransform& camera);
	void update(double dt) override;
	void keyPress(unsigned char key, const physx::PxTransform& camera) override;

private:
	std::vector<Goblin*> goblins;
	int limit;
};

