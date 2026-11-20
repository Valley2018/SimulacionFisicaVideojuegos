#pragma once
#pragma once
#include "../Force/ForceGenerator.h"

class MagneticForceGenerator : public ForceGenerator {
public:
    MagneticForceGenerator(float r, float s, float stop = 1.0f, float brake = 5.0f) : radius(r), strength(s), stopDistance(stop), brakeStrength(brake), activated(true), position(Vector3D(0.0f, 0.0f, 0.0f)), actionSpace(Vector3D(500.0f, 500.0f, 500.0f)) {}

    void setPosition(Vector3D pos) { position = pos; }

    void setForce(Particle* p) override {

        force = Vector3D(0, 0, 0);

        if (!activated || p == nullptr || p->getMass() <= 0.001f)
            return;

        Vector3D direction = p->getPos() - position;
        float distance = direction.magnitude();

        if (distance < radius && distance > stopDistance) {

            direction.normalize();

            float intensity = strength *
                (distance - stopDistance) / (radius - stopDistance);

            Vector3D attraction = direction * (-intensity * p->getMass());

            Vector3D braking = p->getSpeed() *
                (-brakeStrength * p->getMass());

            force = attraction + braking;
        }
        else if (distance <= stopDistance) {

            force = p->getSpeed() *
                (-brakeStrength * p->getMass());
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
    float stopDistance;
    float brakeStrength;
};