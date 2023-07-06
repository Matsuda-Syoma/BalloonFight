#include "UI.h"
#include "DxLib.h"
//コンストラクタ
UI::UI()
{
	NowScore = 0;
	HighScore = 10000;

	Stage = 1;
	PhaseCount = 0;
}

//デストラクタ
UI::~UI()
{

}

//更新
void UI::Update()
{
	if (PhaseCount < 240) {
		PhaseCount++;
		if (PhaseCount % 20 < 10) {
			PhaseFlg = true;
		}
		else {
			PhaseFlg = false;
		}
	}

	//ハイスコアを更新
	if (NowScore > HighScore) {
		HighScore = NowScore;
	}
}

//描画
void UI::Draw() const
{
	//スコア
	DrawString(20, 10, "I-", 0xff0000);
	DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);

	DrawString(270, 10, "TOP-", 0xffa500);
	DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);

	if (PlayerLife == 0) {
		DrawString(280, 230, "GameOver", 0xffffff);
	}


	if (!PhaseFlg) {
		DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
	}
}

//画像読込
void UI::LoadImages()
{

}

//画像削除
void UI::DeleteImages()
{

}