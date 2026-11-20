#include "Goblin.h"
#include <iostream>
Goblin::Goblin(Vector3D pos, Vector4 _color, float _lifeTime, float _size, float _strength)
	: Particle(pos, { 0, 0, 0 }, { 0, 0, 0 }, 1.0f, 1.0f, _lifeTime, _size, _color) {
	newPos = recalculateNewPos();
	strength = _strength;
}

void Goblin::update(double dt) {

    //Vector3D direction = newPos - getPos();
    //float distance = direction.magnitude();

    //// Si llega al destino, elegir otro
    //if (distance < 3.0f) {
    //    newPos = recalculateNewPos();
    //    direction = newPos - getPos();
    //}

    //// Aplicar fuerza hacia el destino
    //direction.normalize();
    //applyForce(direction * strength);

    //integrateSemi(dt);
}


Vector3D Goblin::recalculateNewPos() {
	float x = UniformDistr(-60.0f, 60.0f);
	float z = UniformDistr(-60.0f, 60.0f);
	return Vector3D(x, -10.0f, z);
}
