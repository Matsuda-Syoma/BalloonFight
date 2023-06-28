#include "UI.h"
#include "DxLib.h"
//コンストラクタ
UI::UI()
{

}

//デストラクタ
UI::~UI()
{

}

//更新
void UI::Update()
{
	
}

//描画
void UI::Draw() const
{
	DrawString(100, 100, "test title", 0xff0000);
}