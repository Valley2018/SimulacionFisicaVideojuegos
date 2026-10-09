#pragma once

#include "Scene.h"
#include "Weapon.h"
#include <vector>
#include <iostream>
#include <stdexcept>

//Escena 5 (Práctica 1.2): Se carga con la tecla 5
class P1S_Scene2 : public Scene {
public:
    explicit P1S_Scene2(std::string name) : Scene(std::move(name)) {}

    void init() override {
        w = new Weapon();
      
        std::cout << "Presiona 'm' para reducir la masa de los proyectiles y 'M' para aumentarla." << std::endl;
        std::cout << "Presiona 'v' para reducir la velocidad de los proyectiles y 'V' para aumentarla." << std::endl;
        std::cout << "Presiona 'b' para disparar una bala." << std::endl;
        std::cout << "Presiona 'r' para lanzar una roca." << std::endl;

        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100, 1, 100));
        floorTransform = physx::PxTransform(Vector3D(0, -1, 0));
        renderItem = new RenderItem(floor, &floorTransform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    //Actualizar la partícula
    void update(double dt) override {
        w->update(dt);
        try {
            display_text = "Masa: " + std::to_string(w->getMass()) + " Gravedad: " + std::to_string(w->getGravity());
        }
        catch (std::domain_error e) {
            display_text = "Dispara una roca con 'r' o una bala con 'b'." ;
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        w->keyPress(key, camera);
    }

    //Liberar la partícula
    void cleanup() override {
        delete w;

        if (renderItem) {
            renderItem->release();
            renderItem = nullptr;
        }
    }

private:

    Weapon* w;

    physx::PxTransform floorTransform;
    RenderItem* renderItem;
};