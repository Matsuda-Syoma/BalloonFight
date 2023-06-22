#pragma once

#include "SphereCollider.h"

typedef struct Box {
	float top;
	float bottom;
	float left;
	float right;
} Box;

const float epsilon = 1.0f;

class BoxCollider
{
protected:
	Box box; // �����蔻��

public:
	BoxCollider();
	void GetSize(float& top, float& bottom, float& left, float& right);
	int HitBox(BoxCollider boxCollider) const;
	bool HitSphere(SphereCollider sphereCollider) const;
	void DrawCollider() const;
};

