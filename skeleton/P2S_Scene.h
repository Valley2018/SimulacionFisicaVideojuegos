#pragma once

#include "Scene.h"
#include "ParticleSys.h"
#include <vector>
#include <stdexcept>

//Escena 6 (Práctica 2): Se carga con la tecla 6
class P2S_Scene : public Scene {
public:
    explicit P2S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        display_text = " " ;

        //Sistema 1: Lluvia. Las partículas tienen forma de cápsula, caen hacia abajo hasta salir de su espacio de acción.
        ParticleSys* sysLluvia = new ParticleSys(Vector3D(0.0f, 20.0f, 0.0f), Vector3D(0.0f, -20.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.5f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 0.0f, 0.6f, 1.0f), Particle::CAPSULE, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1)),
            Vector3(100.0f, 0.0f, 100.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.4f, 0.0f));
        sistemas.push_back(sysLluvia);

 /*       ParticleSys*  sysHumo = new ParticleSys(Vector3D(60.0f, -19.0f, 10.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 7.0f, 0.5f, Vector3D(100.0f, 100.0f, 100.0f), Vector4(0.4f, 0.4f, 0.4f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(10.0f, 0.0f, 10.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 3.0f, 0.3f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysHumo);*/

     /*   ParticleSys*  sysManguera = new ParticleSys(Vector3D(-20.0f, -5.0f, -20.0f), Vector3D(20.0f, 20.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.5f, 0.65f, 1.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.05f, 0.05f, 0.0f, 0.0f));
        sistemas.push_back(sysManguera);*/

        addRainbow();
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


    void addRainbow() {

        //Sistema 2: Arcoíris. Cada color sale con una velocidad inicial en x y en y. Les afecta la fuerza de la gravedad, por lo que acaban cayendo creando la forma del arco.
        //Tienen el mismo efecto que la manguera (comentada en el método init). Se borran al salir de su espacio de acción.
        ParticleSys* sysRojo = new ParticleSys(/*Posición modelo*/Vector3D(-20.0f, -13.0f, 20.0f), /*Velocidad modelo*/Vector3D(20.0f, 25.0f, 0.0f), /*Aceñeración modelo*/Vector3D(0.0f, -10.0f, 0.0f), 
            /*Damp modelo*/1.0f, /*Masa modelo*/0.0f, /*Tiempo de vida modelo*/500.0f, /*Tamaño modelo*/0.4f, /*Espacio de acción del sistema*/Vector3D(100.0f, 20.0f, 100.0f), /*Color modelo*/Vector4(1.0f, 0.0f, 0.0f, 1.0f), /*Forma de las partículas*/Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            /*Variación Posición*/Vector3(0.5f, 0.5f, 0.0f), /*Variación velocidad*/Vector3D(0.0f, 0.0f, 0.0f),  /*Variación aceleración*/Vector3D(0.0f, 0.0f, 0.0f), 
            /*Variación damp*/0.0f,  /*Variación masa*/0.0f,  /*Variación tiempo de vida*/0.0f,  /*Variación tamaño*/0.0f,  /*Variación color*/Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysRojo);

        ParticleSys* sysNaranja = new ParticleSys(Vector3D(-20.0f, -14.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(1.0f, 0.6f, 0.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysNaranja);

        ParticleSys* sysAmarillo = new ParticleSys(Vector3D(-20.0f, -15.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysAmarillo);

        ParticleSys* sysVerde = new ParticleSys(Vector3D(-20.0f, -16.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysVerde);

        ParticleSys* sysAzul = new ParticleSys(Vector3D(-20.0f, -17.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 0.65f, 1.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysAzul);

        ParticleSys* sysIndigo = new ParticleSys(Vector3D(-20.0f, -18.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysIndigo);

        ParticleSys* sysVioleta = new ParticleSys(Vector3D(-20.0f, -19.0f, 20.0f), Vector3D(20.0f, 25.0f, 0.0f), Vector3D(0.0f, -10.0f, 0.0f), 1.0f, 0.0f, 500.0f, 0.4f, Vector3D(100.0f, 20.0f, 100.0f), Vector4(1.0f, 0.0f, 1.0f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(0.5f, 0.5f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysVioleta);


        //Sistema 3: Nubes. Las partículas tienen tamaños y tiempos de vida variables, para dar la sensación de ser un objeto etéreo. Tienen el mismo efecto que el humo
        //(comentado en el método init). Las partículas se borran cuando se acaba su tiempo de vida.
        ParticleSys* sysNube1 = new ParticleSys(Vector3D(-20.0f, -19.0f, 20.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 8.0f, 0.8f, Vector3D(100.0f, 100.0f, 100.0f), Vector4(0.8f, 0.8f, 0.8f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(10.0f, 0.0f, 10.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 3.0f, 0.3f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysNube1);

        ParticleSys* sysNube2 = new ParticleSys(Vector3D(80.0f, -19.0f, 20.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, 0.0f, 8.0f, 0.8f, Vector3D(100.0f, 100.0f, 100.0f), Vector4(0.8f, 0.8f, 0.8f, 1.0f), Particle::SPHERE, physx::PxQuat(physx::PxIdentity),
            Vector3(10.0f, 0.0f, 10.0f), Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, 0.0f, 3.0f, 0.3f, Vector4(0.0f, 0.0f, 0.0f, 0.0f));
        sistemas.push_back(sysNube2);


    }
    
};