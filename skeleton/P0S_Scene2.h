#pragma once

#include "Scene.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <vector>

//Escena 2 (Práctica 0, reto B): Se carga con la tecla 2
class P0S_Scene2 : public Scene {
public:
    explicit P0S_Scene2(std::string name) : Scene(std::move(name)) {}

    void init() override {
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));

        //Enemigo
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        //Dirección de visión
        Vector3D dVision(0.0f, 0.0f, 1.0f);

        //Objetivos
        Vector3D P_1(2.0, 0.0, 3.0), 
            P_2(-4.0, 0.0, 1.0), 
            P_3(0.0, 0.0, - 5.0) ,
            P_4(3.0, 0.0, 0.0);
        
        m_transform1 = physx::PxTransform(P_1);
        m_renderItem1 = new RenderItem(shape, &m_transform1, setColor(P_1, dVision));

        m_transform2 = physx::PxTransform(P_2);
        m_renderItem2 = new RenderItem(shape, &m_transform2, setColor(P_2, dVision));

        m_transform3 = physx::PxTransform(P_3);
        m_renderItem3 = new RenderItem(shape, &m_transform3, setColor(P_3, dVision));

        m_transform4 = physx::PxTransform(P_4);
        m_renderItem4 = new RenderItem(shape, &m_transform4, setColor(P_4, dVision));
    }

    //Método setColor para cambiar el color del objetivo en función
    //de su posición en relación con el enemigo usando el producto escalar.
    Vector4 setColor(Vector3D obj, Vector3D vis) {
        Vector4 color;
        if (obj.dot(vis) > 0.0f) color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
        else if (obj.dot(vis) < 0.0f) color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        else color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);

        return color;
    }

    void update(double dt) override {
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (m_renderItem) {
            m_renderItem->release(); // Deregistra y destruye el item
            m_renderItem = nullptr;
        }
        if (m_renderItem1) {
            m_renderItem1->release(); // Deregistra y destruye el item
            m_renderItem1 = nullptr;
        }
        if (m_renderItem2) {
            m_renderItem2->release(); // Deregistra y destruye el item
            m_renderItem2 = nullptr;
        }
        if (m_renderItem3) {
            m_renderItem3->release(); // Deregistra y destruye el item
            m_renderItem3 = nullptr;
        }
        if (m_renderItem4) {
            m_renderItem4->release(); // Deregistra y destruye el item
            m_renderItem4 = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transform1;
    physx::PxTransform m_transform2;
    physx::PxTransform m_transform3;
    physx::PxTransform m_transform4;

    RenderItem* m_renderItem{ nullptr };
    RenderItem* m_renderItem1{ nullptr };
    RenderItem* m_renderItem2{ nullptr };
    RenderItem* m_renderItem3{ nullptr };
    RenderItem* m_renderItem4{ nullptr };
};