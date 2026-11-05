#pragma once
#include "ForceGenerator.h"

class FireForceGenerator : public ForceGenerator {
public:
    FireForceGenerator(float r, float s) : radius(r), strength(s), activated(true), position(Vector3D(0.0f, 0.0f, 0.0f)), actionSpace(Vector3D(500.0f, 500.0f, 500.0f)) {}

    void setPosition(Vector3D pos) { position = pos; }

    void setForce(Particle* p) override {

        // MUY IMPORTANTE: reiniciar la fuerza para cada partícula
        force = Vector3D(0, 0, 0);

        if (!activated || p == nullptr)
            return;

        // Vector desde la bola hasta la partícula
        Vector3D direction = p->getPos() - position;

        float distance = direction.magnitude();

        // Solo afecta a las partículas cercanas
        if (distance < radius && distance > 0.001f) {

            direction.normalize();

            // La fuerza disminuye al alejarse de la bola
            float intensity = strength * (1.0f - distance / radius);

            force = direction * intensity;
        }
    }


    virtual Vector3D getForce() { return force; }

    void keyPressed(unsigned char key) override {
        if (key == 'b') activated = !activated;
    }

    Vector3D getActionSpace() { return actionSpace; }
    bool isActivated() override { return activated; }

private:
    Vector3D position;
    Vector3D force;
    Vector3D actionSpace;

    float radius;
    float strength;
    bool activated;
};