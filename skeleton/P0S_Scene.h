#pragma once

#include "Scene.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <vector>

class P0S_Scene : public Scene {
public:
    explicit P0S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        Vector3D u (3.0f, 1.0f, 0.0f);
        Vector3D v (0.0f, 4.0f, 0.0f);
        Vector3D w = u.cross(v);

        u = u.normalize();
        u = u * 5.0f;

        v = v.normalize();
        v = v * 5.0f;

        w = w.normalize();
        w = w * 5.0f;

       m_transformX = physx::PxTransform(u);
       m_renderItemX = new RenderItem(shape, &m_transformX, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

       m_transformY = physx::PxTransform(v);
       m_renderItemY = new RenderItem(shape, &m_transformY, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

       m_transformZ = physx::PxTransform(w);
       m_renderItemZ = new RenderItem(shape, &m_transformZ, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
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
        if (m_renderItemX) {
            m_renderItemX->release(); // Deregistra y destruye el item
            m_renderItemX = nullptr;
        }
        if (m_renderItemY) {
            m_renderItemY->release(); // Deregistra y destruye el item
            m_renderItemY = nullptr;
        }
        if (m_renderItemZ) {
            m_renderItemZ->release(); // Deregistra y destruye el item
            m_renderItemZ = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transformX;
    physx::PxTransform m_transformY;
    physx::PxTransform m_transformZ;

    RenderItem* m_renderItem{ nullptr };
    RenderItem* m_renderItemX{ nullptr };
    RenderItem* m_renderItemY{ nullptr };
    RenderItem* m_renderItemZ{ nullptr };
};