#pragma once

#include "Scene.h"
#include "../Particle/ParticleSys.h"
#include "../Force/GravityGen.h"
#include "../Force/WindGen.h"
#include "../Force/WhirlwindGen.h"
#include "../Force/ExplosionGen.h"
#include <vector>
#include <stdexcept>

//Escena 7 (Práctica 3): Se carga con la tecla 7
class P3S_Scene : public Scene {
public:
    explicit P3S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        display_text = "Presiona 'e' para provocar una explosión";

        //Sistema 1: Lluvia. Tiene un generador de gravedad que hace que caigan las gotas y uno de viento que las desplaza en el eje x.
        ParticleSys* sysLluvia = new ParticleSys(Vector3D(0.0f, 20.0f, 0.0f), Vector3D(0.0f, -20.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 0.01f, 500.0f, 0.5f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 0.0f, 0.6f, 1.0f), Particle::CAPSULE, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)),
            Vector3(50.0f, 0.0f, 50.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.4f, 0.0f));
        sistemas.push_back(sysLluvia);

        GravityGen* g = new GravityGen();
        sysLluvia->addForce(g);
        fuerzas.push_back(g);
        WindGen* w = new WindGen(Vector3D(20.0f, 0.0f, 0.0f), 1.0f, 0.0);
        sysLluvia->addForce(w);
        fuerzas.push_back(w);

        //Sistema 2: Polvo. Tiene un generador de gravedad y uno de tornado.
        ParticleSys* sysPolvo = new ParticleSys(Vector3D(100.0f, 5.0f, 100.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, 1.0f, 0.5f, Vector3D(500.0f, 500.0f, 500.0f), Vector4(0.6f, 0.6f, 0.6f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(20.0f, 5.0f, 20.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysPolvo);

        WhirlwindGen* ww = new WhirlwindGen(Vector3D(100.0f, 5.0f, 100.0f), 100.0f);
        sysPolvo->addForce(ww);
        sysPolvo->addForce(g);
        fuerzas.push_back(ww);

        //Sistema 3: Partículas para la explosión. Tiene un generador de explosión que se activa con la tecla 'e'.
        ParticleSys* sysExplosion = new ParticleSys(Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, -0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 0.5f, 60.0f, 0.5f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.6f, 0.3f, 0.1f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)),
            Vector3(50.0f, 1.0f, 50.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysExplosion);

        explosion = new ExplosionGen();
        sysExplosion->addForce(explosion);
        fuerzas.push_back(explosion);

        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(100, 1, 100));
        floorTransform = physx::PxTransform(Vector3D(0, -20, 0));
        renderItem = new RenderItem(floor, &floorTransform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    //Actualizar la partícula
    void update(double dt) override {
        for (auto s : sistemas) s->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'e' && explosion != nullptr) explosion->startExplosion();
        for (auto f : fuerzas) f->keyPressed(key);
    }

    //Liberar la partícula
    void cleanup() override {
        for (auto s : sistemas) delete s;
        sistemas.clear();
        for (auto f : fuerzas) delete f;
        fuerzas.clear();

        if (renderItem) {
            renderItem->release();
            renderItem = nullptr;
        }
    }

private:
    std::vector<ParticleSys*> sistemas;
    std::vector<ForceGenerator*> fuerzas;

    ExplosionGen* explosion;
    physx::PxTransform floorTransform;
    RenderItem* renderItem;
};