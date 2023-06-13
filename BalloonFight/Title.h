#pragma once
#include "AbstractScene.h"
class Title : public AbstractScene {
public:
	Title();							// コンストラクタ
	~Title();							// デストラクタ
	AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;			// 描画に関することを実装
};