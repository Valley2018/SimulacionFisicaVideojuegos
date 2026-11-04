#pragma once
#include "WindGen.h"

//Generador de tornados (hereda del generador de viento).  Se desactiva/activa con 'W' (mayúscula).
class WhirlwindGen : public WindGen
{
public:

    WhirlwindGen(Vector3D _center, float _K, Vector3D _actionSpace = Vector3D(500.0f, 500.0f, 500.0f)) : WindGen(Vector3D(0, 0, 0), _K, 0, _actionSpace), center(_center), activated(true)
    {
    }

    void setForce(Particle* p) override
    {
        Vector3D diff(p->getPos().x - center.x, 0.0f,  p->getPos().z - center.z );

        float distance = diff.magnitude();

        if (distance > 50.0f || distance < 0.001f)
        {
            fuerza = Vector3D(0, 0, 0);
        }
        else
        {
            Vector3D tangent(-diff.z / distance, 0.0f, diff.x / distance);

            fuerza = tangent * k1;
        }
    }

    Vector3D getForce() override
    {
        return fuerza;
    }

    void keyPressed(unsigned char key) override{
        if (key == 'V') activated = !activated;
    }
    virtual bool isActivated() override { return activated; }


private:
    Vector3D center;
    Vector3D fuerza;
    bool activated;
};
