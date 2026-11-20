#include "Weapon.h"

Weapon::Weapon() {
}
//Destructora
Weapon::~Weapon() {
    for (auto p : balas) delete p;
    balas.clear();
}

//Disparar el proyectil desde la cámara con parámetros según su tipo
void Weapon::shoot (const physx::PxTransform& camera, projectilTypes type){
    Vector3D eye(camera.p.x, camera.p.y, camera.p.z);
    physx::PxVec3 dir = camera.q.rotate( physx::PxVec3(0, 0, -1));
    Vector3D direction(dir.x, dir.y,  dir.z);
    float vel,  mass;
    switch (type) 
    {
        case BULLET :{
            vel = 300;
            mass = 0.02;
            break;
        }
        case ROCK: {
            vel = 25;
            mass = 3;
            break;
        }
    }
    Projectile* p = new Projectile(mass, vel, 10, eye, dir);
   balas.push_back(p);
}


void Weapon::update(double dt) {
    for (auto p : balas) p->update(dt);
}

void Weapon::keyPress(unsigned char key, const physx::PxTransform& camera) {
	if (key == 'b') {
		shoot(camera, BULLET);
	}else if (key == 'r') {
        shoot(camera, ROCK);
    }
    for (auto p : balas) p->keyPress(key, camera);
}