#pragma once

#include "Scene.h"
#include "Particle.h"
#include <vector>

//Escena 4 (Práctica 1.1): Se carga con la tecla 4
class P1S_Scene : public Scene {
public:
    explicit P1S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        display_text = "";

        //Origen
        p = new Particle(Vector3D(0, 0, 0), Vector3D(8, 0, 0), Vector3D(3,0,0), 0.1f);
    }

    //Actualizar la partícula
    void update(double dt) override {

        p->verlet(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    //Liberar la partícula
    void cleanup() override {
        delete p;
    }

private:
    Particle* p;
};