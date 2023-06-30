#pragma once
#include"common.h"
#include"AbstractScene.h"

class UI{
public:
	UI();							// コンストラクタ
	~UI();							// デストラクタ
	void Update();	// 描画以外の更新を実行
	void Draw() const;			// 描画に関することを実装
};

