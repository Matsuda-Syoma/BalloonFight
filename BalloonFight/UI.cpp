#include "UI.h"
#include "DxLib.h"
//コンストラクタ
UI::UI()
{
	Stage = 1;
	PhaseCount = 0;
	GameOverFlg = false;
	LoadImages();
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
	DrawGraph(20, 10, ScoreImg, true);
	DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);

	DrawGraph(260, 10, HighScoreImg, true);
	//DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);
	DrawGraph(310, 10, NumImg[5], true);

	if (GameOverFlg) {
		//DrawString(280, 230, "GameOver", 0xffffff);
		DrawGraph(220, 220, GameOImg, TRUE);
	}


	if (!PhaseFlg) {
		//DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
		DrawGraph(260, 30, PhaseImg, TRUE);
	}

}

//画像読込
void UI::LoadImages()
{
	ScoreImg = LoadGraph("Resources/images/UI/UI_Score.png");
	HighScoreImg = LoadGraph("Resources/images/UI/UI_HiScore.png");
	GameOImg = LoadGraph("Resources/images/UI/UI_GameOver.png");
	PhaseImg = LoadGraph("Resources/images/UI/UI_Phase.png");
	LoadDivGraph("Resources/images/Player/UI_NumAnimation.png", 10, 10, 1, 64, 64, NumImg);


}

//画像削除
void UI::DeleteImages()
{

}

void UI::GameOver()
{
	GameOverFlg = true;
}