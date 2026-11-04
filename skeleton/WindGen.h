#pragma once
#include "ForceGenerator.h"

//Generador de viento
class WindGen : public ForceGenerator
{
	public:
		WindGen( Vector3D _windSpeed, float _k1, float _k2 = 0, Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : actionSpace(_actionSpace), windSpeed(_windSpeed), k1(_k1), k2(_k2){

		}


		void setForce(Particle* p) override { 
			Vector3D diff = Vector3D(windSpeed.x - p->getSpeed().x, 0.0f, windSpeed.z - p->getSpeed().z);
	
			fuerza = diff * k1 	+ diff * k2 * diff.magnitude();
		}
		Vector3D getForce() override { return fuerza; }
		Vector3D getActionSpace() override { return actionSpace; }

	protected:
		Vector3D fuerza;
		Vector3D actionSpace;
		Vector3D windSpeed;
		float k1;
		float k2;
};

