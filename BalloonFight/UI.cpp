#include "UI.h"
#include "DxLib.h"
//コンストラクタ
UI::UI()
{
	
	HighScore = 10000;
	Stage = 1;
	PhaseCount = 0;
	GameOverFlg = false;

	PosX = 89;

	LoadImages();
}

//デストラクタ
UI::~UI()
{

}

//更新
void UI::Update(int _score)
{
	NowScore = _score;
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
	//サンプル
	//DrawGraph(0, 0, SampleImg, FALSE);
	//スコア
	DrawGraph(60, 14, ScoreImg, true);
	//DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);
	for (int i = 0; i < 6; i++) {
		DrawRotaGraph(PosX + (20 * i), 22, 1.0, 0.0, NumImg[NowScore],TRUE);
	}


	DrawGraph(240, 15, HighScoreImg, true);
	//DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);
	//DrawGraph(310, 10, NumImg[HighScore], true);

	if (GameOverFlg) {
		//DrawString(280, 230, "GameOver", 0xffffff);
		DrawGraph(220, 220, GameOImg, TRUE);
	}


	if (!PhaseFlg) {
		//DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
		DrawGraph(240, 32, PhaseImg, TRUE);
		DrawRotaGraph(369, 40, 1.0, 0.0, NumImg[0], TRUE);
		DrawRotaGraph(390,40, 1.0, 0.0, NumImg[Stage], TRUE);
	}

}

//画像読込
void UI::LoadImages()
{
	SampleImg = LoadGraph("Resources/images_alp/StageSample/Stage_1.png");
	ScoreImg = LoadGraph("Resources/images/UI/UI_Score.png");
	HighScoreImg = LoadGraph("Resources/images/UI/UI_HiScore.png");
	GameOImg = LoadGraph("Resources/images/UI/UI_GameOver.png");
	PhaseImg = LoadGraph("Resources/images/UI/UI_Phase.png");
	LoadDivGraph("Resources/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, NumImg);


}

//画像削除
void UI::DeleteImages()
{

}

void UI::GameOver()
{
	GameOverFlg = true;
}