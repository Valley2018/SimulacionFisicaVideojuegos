#pragma once
#include "../Force/ForceGenerator.h"

class FireForceGenerator : public ForceGenerator {
public:
    FireForceGenerator(float r, float s) : radius(r), strength(s), activated(true), position(Vector3D(0.0f, 0.0f, 0.0f)), actionSpace(Vector3D(500.0f, 500.0f, 500.0f)) {}

    void setPosition(Vector3D pos) { position = pos; }

    void setForce(Particle* p) override {

        force = Vector3D(0, 0, 0);

        if (!activated || p == nullptr)
            return;

        Vector3D direction = p->getPos() - position;

        float distance = direction.magnitude();

        if (distance < radius && distance > 0.001f) {

            direction.normalize();

            float intensity = strength * (1.0f - distance / radius);

            force = direction * intensity;
        }
    }


    virtual Vector3D getForce() { return force; }

    void keyPressed(unsigned char key) override {
        if (key == 'F') activated = !activated;
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