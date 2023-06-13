#include "SphereCollider.h"
#include<math.h>
#include "BoxCollider.h"


SphereCollider::SphereCollider()
{
	//radius = 5;
}

// Sphere同士が当たるとFalseが帰る
bool SphereCollider::HitSphere(SphereCollider* spherecollider)const
{
	bool ret = false;//返り値
	float distance;	//中心座標の距離

	//中心座標の距離の計算
	distance = sqrtf(powf(spherecollider->GetLocation().x - location.x, 2) + powf(spherecollider->GetLocation().y - location.y, 2));

	if (distance < radius + spherecollider->GetRadius()) //当たり判定
	{
		ret = true;
	}

	return ret;
}

// SphereとBoxが当たっているとFalseが帰る
bool SphereCollider::HitBox(BoxCollider boxCollider) const {
	Box box;
	boxCollider.GetSize(box.top, box.bottom, box.left, box.right);
	float width = box.right - box.left;
	float height = box.bottom - box.top;
	float centerX = box.right - width / 2.f;
	float centerY = box.bottom - height / 2.f;

	float distance = sqrtf(powf(location.x - centerX, 2) + powf(location.y - centerY, 2));
	float distanceX = sqrtf(powf(location.x - centerX, 2));
	float distanceY = sqrtf(powf(location.y - centerY, 2));

	if (distanceX < width / 2 + radius && distanceY < height / 2 + radius) {
		return true;
	}

	return false;
}

// 半径を取得
int SphereCollider::GetRadius()const
{
	return radius;
}

// 中心座標を取得
Location SphereCollider::GetLocation()
{
	return location;
}

