#pragma once
#include <PxPhysicsAPI.h>
#include <cmath>

class Vector3D {
public:
	float x, y, z;
	Vector3D(float _x = 0, float _y = 0, float _z = 0) : x(_x), y(_y), z(_z){}
	Vector3D(physx::PxVec3 vector) : x(vector.x), y(vector.y), z(vector.z){}
	
	float magnitude () const {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
	
	Vector3D normalize() const {
		float mag = magnitude();
		return{ x / mag, y / mag, z / mag };
	}

	float dot(const Vector3D& v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

	Vector3D cross(const Vector3D& v) const {
		return{ y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x };
	}

	bool operator ==(Vector3D& v) {
		return(x == v.x && y == v.y && z == v.z);
	}

	Vector3D& operator =(Vector3D& v) {
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector3D operator +(Vector3D& v) const{
		Vector3D vector;
		vector.x = x + v.x;
		vector.y = y + v.y;
		vector.z = z + v.z;
		return vector;
	}

	Vector3D operator -(Vector3D& v) const{
		Vector3D vector;
		vector.x = x - v.x;
		vector.y = y - v.y;
		vector.z = z - v.z;
		return vector;
	}

	Vector3D operator *(float v) const{
		Vector3D vector;
		vector.x = x * v;
		vector.y = y * v;
		vector.z = z * v;
		return vector;
	}

	Vector3D operator +=(Vector3D& v) {
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	operator physx::PxVec3() const {
		return physx::PxVec3(x, y, z);
	}

};