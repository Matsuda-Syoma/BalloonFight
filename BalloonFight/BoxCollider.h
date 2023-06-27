#pragma once

#include "SphereCollider.h"

typedef struct Box {
	float top;
	float bottom;
	float left;
	float right;
} Box;

class BoxCollider
{
private:

protected:
	Box box; // “–‚½‚è”»’è

public:
	BoxCollider();
	void GetSize(float& top, float& bottom, float& left, float& right);
	int HitBox(BoxCollider boxCollider) const;
	bool HitSphere(SphereCollider sphereCollider) const;
	void DrawCollider() const;
};

