#pragma once

#include "Scene.h"
#include "Vector3D.h"
#include "RenderUtils.hpp"
#include <vector>

class P0S_Scene3 : public Scene {
public:
    explicit P0S_Scene3(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(0.5f));
        physx::PxShape* shape1 = CreateShape(physx::PxSphereGeometry(1.0f));

        //Enemigo
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

        Vector3D A(-8.0, 1.0, -8.0),
            B(8.0, 8.0, 8.0);

        m_transformA = physx::PxTransform(A);
        m_renderItemA = new RenderItem(shape1, &m_transformA, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

        m_transformB = physx::PxTransform(B);
        m_renderItemB = new RenderItem(shape1, &m_transformB, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        float t = 0.0f;
        float incr = 1.0f / 10.0f;

        m_ballTransforms.reserve(10);
        m_ballRenderItems.reserve(10);

        for (int i = 1; i <= 10; ++i) {
            float t = static_cast<float>(i) / 11.0f;

            Vector3D pos = A + (B - A) * t;

            m_ballTransforms.emplace_back(
                physx::PxTransform(pos)
            );

            m_ballRenderItems.push_back(
                new RenderItem(
                    shape,
                    &m_ballTransforms.back(),
                    Vector4(0.5f, 0.5f, 0.5f, 1.0f)
                )
            );
        
           t += incr;
        }
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
        if (m_renderItemA) {
            m_renderItemA->release(); // Deregistra y destruye el item
            m_renderItemA = nullptr;
        }
        if (m_renderItemB) {
            m_renderItemB->release(); // Deregistra y destruye el item
            m_renderItemB = nullptr;
        }
        for (RenderItem* item : m_ballRenderItems) {
            if (item) {
                item->release();
            }
        }

        m_ballRenderItems.clear();
        m_ballTransforms.clear();
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transformA;
    physx::PxTransform m_transformB;

    RenderItem* m_renderItem{ nullptr };
    RenderItem* m_renderItemA{ nullptr };
    RenderItem* m_renderItemB{ nullptr };

    std::vector<physx::PxTransform> m_ballTransforms;
    std::vector<RenderItem*> m_ballRenderItems;
};