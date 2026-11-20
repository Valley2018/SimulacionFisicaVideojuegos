#include "GoblinSpell.h"

GoblinSpell::GoblinSpell() : limit(5){}

GoblinSpell::~GoblinSpell() {
	for (auto g : goblins) delete g;
	goblins.clear();
}

void GoblinSpell::createGoblin(const physx::PxTransform& camera) {
	if (goblins.size() == limit) return;
	physx::PxVec3 dir = camera.q.rotate(
		physx::PxVec3(0, 0, -1)
	);

	Vector3D cameraDir(dir.x, dir.y, dir.z);

	Vector3D spawnPos = camera.p + cameraDir * 8.0f;

	spawnPos.y = -10.0f;

	auto g = new Goblin(spawnPos);
	goblins.push_back(g);
}

void GoblinSpell::update(double dt) {
	for (auto g : goblins) g->update(dt);
}

void GoblinSpell::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'c') createGoblin(camera);
}