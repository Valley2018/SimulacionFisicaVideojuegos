#pragma once
#include "ForceGenerator.h"

//Generador de viento.  Se desactiva/activa con 'w'.
class WindGen : public ForceGenerator
{
	public:
		WindGen( Vector3D _windSpeed, float _k1, float _k2 = 0, Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : actionSpace(_actionSpace), windSpeed(_windSpeed), k1(_k1), k2(_k2), activated(true){

		}


		void setForce(Particle* p) override { 
			Vector3D diff = Vector3D(windSpeed.x - p->getSpeed().x, 0.0f, windSpeed.z - p->getSpeed().z);
	
			fuerza = diff * k1 	+ diff * k2 * diff.magnitude();
		}
		Vector3D getForce() override
		{
			return fuerza;
		}
		Vector3D getActionSpace() override { return actionSpace; }
		

		void keyPressed(unsigned char key) override {
			if (key == 'v') activated = !activated;
		}
		virtual bool isActivated() override { return activated; }

	protected:
		Vector3D fuerza;
		Vector3D actionSpace;
		Vector3D windSpeed;
		float k1;
		float k2;

		bool activated;
};

