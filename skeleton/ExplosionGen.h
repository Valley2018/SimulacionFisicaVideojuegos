
#pragma once
#include "ForceGenerator.h"
#include <cmath>

//Generador de explosiones con onda expansiva 
class ExplosionGen : public ForceGenerator
{
public:
    ExplosionGen(Vector3D _center = Vector3D (0.0f, 0.0f, 0.0f),  float _K = 1000.0f,  float _ve = 340.0f, float _tau = 1.0f,
        Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : center(_center), K(_K), ve(_ve),  tau(_tau), actionSpace(_actionSpace),  time(0.0f),  active(false),  fuerza(0, 0, 0)
    {
    }

    void startExplosion()
    {
        time = 0.0f;
        active = true;
    }

    void setForce(Particle* p) override
    {
        fuerza = Vector3D(0, 0, 0);

        if (!active || tau <= 0.0f)
            return;

        Vector3D diff( p->getPos().x - center.x, p->getPos().y - center.y, p->getPos().z - center.z);

        float distance = diff.magnitude();
        float R = ve * time;

        if (distance < R && distance > 0.001f)
        {
            float intensidad = (K / (distance * distance)) * exp(-time / tau);

            fuerza = diff * intensidad;
        }
    }

    Vector3D getForce() override
    {
        return fuerza;
    }

    Vector3D getActionSpace() override
    {
        return actionSpace;
    }

    void update(double dt) override
    {
        if (active)
        {
            time += dt;

            if (time >= 4.0f * tau)
            {
                active = false;
            }
        }
    }

private:
    Vector3D center;
    Vector3D actionSpace;

    float K;
    float ve;
    float tau;
    float time;

    bool active;

    Vector3D fuerza;
};
