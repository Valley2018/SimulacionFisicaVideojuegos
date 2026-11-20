#pragma once
#include "../Particle/Particle.h"
#include <random>

//Clase proyectil que hereda de partícula.
class Goblin : public Particle
{
public:
	Goblin(Vector3D pos = Vector3D(0, 0, 0), Vector4 _color = Vector4(0.55f, 0.75f, 0.40f, 1.0f), float _lifeTime = -1.0f, float _size = 5.0f, float strength = 0.1f);
	void update(double dt);
private:
	Vector3D recalculateNewPos();
	Vector3D newPos;
	float strength; 

	std::mt19937 _mt{ std::random_device{}() };
	float UniformDistr(float min, float max) {
		std::uniform_real_distribution<float> uni(min, max);
		return uni(_mt);
	}
};

