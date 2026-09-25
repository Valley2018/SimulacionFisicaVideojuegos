#pragma once

#include "Scene.h"
#include "Particle.h"
#include <vector>

//Escena 4 (Práctica 1, apartado 1a): Se carga con la tecla 4
class P1S_Scene : public Scene {
public:
    explicit P1S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        //Origen
        p = new Particle(Vector3D(0, 0, 0), Vector3D(8, 0, 0), Vector3D(3,0,0), 0.1f);
    }

    void update(double dt) override {
        p->integrate(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete p;
    }

private:
    Particle* p;
};