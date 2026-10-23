#pragma once

#include "Scene.h"
#include "ParticleSys.h"
#include <vector>
#include <stdexcept>

//Escena 7 (Práctica 3): Se carga con la tecla 7
class P3S_Scene : public Scene {
public:
    explicit P3S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        display_text = " ";

        //Sistema 1: Lluvia. Las partículas tienen forma de cápsula, caen hacia abajo hasta salir de su espacio de acción.
        ParticleSys* sysLluvia = new ParticleSys(Vector3D(0.0f, 20.0f, 0.0f), Vector3D(0.0f, -20.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.5f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 0.0f, 0.6f, 1.0f), Particle::CAPSULE, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)),
            Vector3(100.0f, 0.0f, 100.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.4f, 0.0f));
        sistemas.push_back(sysLluvia);

        
        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100, 1, 100));
        floorTransform = physx::PxTransform(Vector3D(0, -20, 0));
        renderItem = new RenderItem(floor, &floorTransform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    //Actualizar la partícula
    void update(double dt) override {
        for (auto s : sistemas) s->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    //Liberar la partícula
    void cleanup() override {
        for (auto s : sistemas) delete s;
        sistemas.clear();

        if (renderItem) {
            renderItem->release();
            renderItem = nullptr;
        }
    }

private:
    std::vector<ParticleSys*> sistemas;

    physx::PxTransform floorTransform;
    RenderItem* renderItem;
};