#include "BoxCollider.h"
#include <math.h>
#include "DxLib.h"
#include <vector>
BoxCollider::BoxCollider() {

}

// Box�̑傫����Get
void BoxCollider::GetSize(float& _top, float& _bottom, float& _left, float& _right) {
	_top = box.top;
	_bottom = box.bottom;
	_left = box.left;
	_right = box.right;
}

// Box���m���������Ă����False���A��
int BoxCollider::HitBox(BoxCollider boxCollider) const {
	Box other;	// ����̔���
	boxCollider.GetSize(other.top, other.bottom, other.left, other.right);
	float epsilon = other.bottom - other.top;
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
	if (fabsf(box.bottom-other.top)< epsilon) {
		return 1;
	}
	if (fabsf(box.top - other.bottom) < epsilon) {
		return 2;
	}
	//if (other.bottom > box.top) {
	//	return 2;
	//}
	///////////// �����l��2�����o�͂���Ȃ��̂ł���̏C��


	//if (box.bottom < other.top) {
	//	return 1;						// ��
	//}
	//if (other.bottom < box.top) {
	//	return 2;						// ��
	//}
	//if (box.right < other.left) {
	//	return 3;
	//}
	//if (other.right < box.left) {
	//	return 4;
	//}

	return 0;
}

//// ��`A�̉E�[����`B�̍��[�������ɂ���ꍇ
//if (rectangleA.x + rectangleA.width < rectangleB.x) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̍��[����`B�̉E�[�����E�ɂ���ꍇ
//if (rectangleA.x > rectangleB.x + rectangleB.width) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̉��[����`B�̏�[������ɂ���ꍇ
//if (rectangleA.y + rectangleA.height < rectangleB.y) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// ��`A�̏�[����`B�̉��[�������ɂ���ꍇ
//if (rectangleA.y > rectangleB.y + rectangleB.height) {
//	return CollisionDirection::None; // �������Ă��Ȃ�
//}
//
//// �d�Ȃ��Ă���ꍇ�A�ǂ̕����ɏd�Ȃ��Ă��邩�𔻒肷��
//if (rectangleA.x + rectangleA.width == rectangleB.x) {
//	return CollisionDirection::Right;		�E
//}
//
//if (rectangleA.x == rectangleB.x + rectangleB.width) {
//	return CollisionDirection::Left;		��
//}
//
//if (rectangleA.y + rectangleA.height == rectangleB.y) {
//	return CollisionDirection::Bottom;		��
//}
//
//if (rectangleA.y == rectangleB.y + rectangleB.height) {
//	return CollisionDirection::Top;			��
//}
//
//return CollisionDirection::None;
//}


// Sphere��Box���������Ă����False���A��
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