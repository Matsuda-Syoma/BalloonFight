#include "BoxCollider.h"
#include <math.h>
#include "DxLib.h"
#include <vector>
BoxCollider::BoxCollider() {

}

// Boxの大きさをGet
void BoxCollider::GetSize(float& _top, float& _bottom, float& _left, float& _right) {
	_top = box.top;
	_bottom = box.bottom;
	_left = box.left;
	_right = box.right;
}

// Box同士が当たっているとFalseが帰る
int BoxCollider::HitBox(BoxCollider boxCollider) const {
	Box other;			// 相手の判定
	boxCollider.GetSize(other.top, other.bottom, other.left, other.right);
	float epsilon = 10.0f;		// 誤差
	if (other.bottom < box.top) {
		return 0;
	}
	if (other.top > box.bottom) {
		return 0;
	}
	if (other.right < box.left) {
		return 0;
	}
	if (other.left > box.right) {
		return 0;
	}
	if (fabsf(box.bottom - other.top) < epsilon / 2) {	// 上に当たったとき1を返す
		return 1;
	}
	if (fabsf(box.right - other.left) < epsilon) {	// 左に当たったとき3を返す
		return 3;
	}
	if (fabsf(box.left - other.right) < epsilon) {	// 右に当たったとき4を返す
		return 4;
	}
	if (fabsf(box.top - other.bottom) < epsilon) {	// 下に当たったとき2を返す
		return 2;
	}



	//if (box.bottom < other.top) {
	//	return 1;						// 上
	//}
	//if (other.bottom < box.top) {
	//	return 2;						// 下
	//}
	//if (box.right < other.left) {
	//	return 3;
	//}
	//if (other.right < box.left) {
	//	return 4;
	//}

	return 0;
}

//// 矩形Aの右端が矩形Bの左端よりも左にある場合
//if (rectangleA.x + rectangleA.width < rectangleB.x) {
//	return CollisionDirection::None; // 当たっていない
//}
//
//// 矩形Aの左端が矩形Bの右端よりも右にある場合
//if (rectangleA.x > rectangleB.x + rectangleB.width) {
//	return CollisionDirection::None; // 当たっていない
//}
//
//// 矩形Aの下端が矩形Bの上端よりも上にある場合
//if (rectangleA.y + rectangleA.height < rectangleB.y) {
//	return CollisionDirection::None; // 当たっていない
//}
//
//// 矩形Aの上端が矩形Bの下端よりも下にある場合
//if (rectangleA.y > rectangleB.y + rectangleB.height) {
//	return CollisionDirection::None; // 当たっていない
//}
//
//// 重なっている場合、どの方向に重なっているかを判定する
//if (rectangleA.x + rectangleA.width == rectangleB.x) {
//	return CollisionDirection::Right;		右
//}
//
//if (rectangleA.x == rectangleB.x + rectangleB.width) {
//	return CollisionDirection::Left;		左
//}
//
//if (rectangleA.y + rectangleA.height == rectangleB.y) {
//	return CollisionDirection::Bottom;		下
//}
//
//if (rectangleA.y == rectangleB.y + rectangleB.height) {
//	return CollisionDirection::Top;			上
//}
//
//return CollisionDirection::None;
//}


// SphereとBoxが当たっているとFalseが帰る
bool BoxCollider::HitSphere(SphereCollider sphereCollider) const {
	float width = box.right - box.left;
	float height = box.bottom - box.top;
	float centerX = box.right - width / 2.f;
	float centerY = box.bottom - height / 2.f;

	float distance = sqrtf(powf(sphereCollider.GetLocation().x - centerX, 2) + powf(sphereCollider.GetLocation().y - centerY, 2));
	float distanceX = sqrtf(powf(sphereCollider.GetLocation().x - centerX, 2));
	float distanceY = sqrtf(powf(sphereCollider.GetLocation().y - centerY, 2));

	if (distanceX < width / 2 + sphereCollider.GetRadius() && distanceY < height / 2 + sphereCollider.GetRadius()) {
		return true;
	}

	return false;
}

void BoxCollider::DrawCollider() const {
	DrawBox(box.left, box.top, box.right, box.bottom, 0xFF, TRUE);
}

float BoxCollider::GetSide(int i) // 1:上2:下3:左4:右
{
	switch (i)
	{
	case 1:
		return box.top;
		break;

	case 2:
		return box.bottom;
		break;

	case 3:
		return box.left;
		break;

	case 4:
		return box.right;
		break;

	default:
		return 0;
	}

}

float BoxCollider::GetCenterY() {
	return box.top - (box.bottom - box.top) / 2;
}