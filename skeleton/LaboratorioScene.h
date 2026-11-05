#pragma once

#include "Scene.h"
#include "ParticleSys.h"
#include "Hechizo.h"
#include "Gravityparticles.h"
#include "BolaDeFuego.h"
#include <vector>
#include <stdexcept>

//Escena 7 (Práctica 3): Se carga con la tecla 7
class LaboratorioScene : public Scene {
public:
    explicit LaboratorioScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        display_text = " ";

        
        auto gravityParticles = new GravityParticles();
        auto bolaDeFuego = new BolaDeFuego();

        bolaDeFuego->setGravityParticles(gravityParticles);
        hechizos.push_back(gravityParticles);
        hechizos.push_back(bolaDeFuego);

        createRoom();
    }

    void update(double dt) override {
        for (auto h : hechizos) h->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        for (auto h : hechizos) h->keyPress(key, camera);

    }

    void cleanup() override {
        for (auto h : hechizos) delete h;
        hechizos.clear();

        clearRoom();
    }

private:
    physx::PxTransform floorTransform;
    RenderItem* renderItemFloor;

    physx::PxTransform roofTransform;
    RenderItem* renderItemRoof;

    physx::PxTransform wall1Transform;
    RenderItem* renderItemWall1;

    physx::PxTransform wall2Transform;
    RenderItem* renderItemWall2;

    physx::PxTransform wall3Transform;
    RenderItem* renderItemWall3;

    physx::PxTransform wall4Transform;
    RenderItem* renderItemWall4;

    std::vector<Hechizo*> hechizos;

    void createRoom() {

        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100, 1, 100));
        floorTransform = physx::PxTransform(Vector3D(0, -26, 0));
        renderItemFloor = new RenderItem(floor, &floorTransform, Vector4(1, 1, 1, 1));

        physx::PxShape* roof = CreateShape(physx::PxBoxGeometry(100, 1, 100));
        roofTransform = physx::PxTransform(Vector3D(0, 26, 0));
        renderItemRoof = new RenderItem(roof, &roofTransform, Vector4(1, 1, 1, 1));

        physx::PxShape* wall1 = CreateShape(physx::PxBoxGeometry(100, 25, 1));
        wall1Transform = physx::PxTransform(Vector3D(0, 0, 99));
        renderItemWall1 = new RenderItem(wall1, &wall1Transform, Vector4(1, 1, 1, 1));

        physx::PxShape* wall2 = CreateShape(physx::PxBoxGeometry(100, 25, 1));
        wall2Transform = physx::PxTransform(Vector3D(0, 0, -99));
        renderItemWall2 = new RenderItem(wall2, &wall2Transform, Vector4(1, 1, 1, 1));

        physx::PxShape* wall3 = CreateShape(physx::PxBoxGeometry(1, 25, 100));
        wall3Transform = physx::PxTransform(Vector3D(99, 0, 0));
        renderItemWall3 = new RenderItem(wall3, &wall3Transform, Vector4(1, 1, 1, 1));

        physx::PxShape* wall4 = CreateShape(physx::PxBoxGeometry(1, 25, 100));
        wall4Transform = physx::PxTransform(Vector3D(-99, 0, 0));
        renderItemWall4 = new RenderItem(wall4, &wall4Transform, Vector4(1, 1, 1, 1));
    }

    void clearRoom() {
        if (renderItemFloor) {
            renderItemFloor->release();
            renderItemFloor = nullptr;
        }

        if (renderItemRoof) {
            renderItemRoof->release();
            renderItemRoof = nullptr;
        }

        if (renderItemWall1) {
            renderItemWall1->release();
            renderItemWall1 = nullptr;
        }

        if (renderItemWall2) {
            renderItemWall2->release();
            renderItemWall2 = nullptr;
        }

        if (renderItemWall3) {
            renderItemWall3->release();
            renderItemWall3 = nullptr;
        }

        if (renderItemWall4) {
            renderItemWall4->release();
            renderItemWall4 = nullptr;
        }
    }
};