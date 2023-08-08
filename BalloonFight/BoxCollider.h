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
	Box box; // 当たり判定

public:

	char name;

	BoxCollider();
	void GetSize(float& top, float& bottom, float& left, float& right);
	int HitBox(BoxCollider boxCollider) const;								// 上、下、右、左
	bool HitSphere(SphereCollider sphereCollider) const;
	void DrawCollider() const;
	// 1:上2:下3:左4:右
	float GetSide(int i);
	float GetCenterY();
};

