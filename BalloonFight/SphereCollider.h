#pragma once

struct Location
{
	float x; //中心座標(x)
	float y; //中心座標(y)

};

class SphereCollider
{
protected:
	int radius; // 半径
	Location location;// 当たり判定
public:
	SphereCollider(); // コンストラクタ
	int GetRadius() const; // 半径の取得
	bool HitSphere(SphereCollider* spherecollider)const; // 当たり判定
	bool HitBox(class BoxCollider boxCollider) const;

	Location GetLocation(); // 中心座標を取得


};