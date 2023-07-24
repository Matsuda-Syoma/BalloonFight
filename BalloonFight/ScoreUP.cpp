#include "ScoreUP.h"

ScoreUP::ScoreUP(int _score, int px,int py)
{
	Score = _score;
	x = px;
	y = py;
	WaitTime = 0;
	switch (Score)
	{
	case 500:
		DrawScore = LoadGraph("Resources/images/Score/GetScore_500.png");
		break;
	case 750:
		DrawScore = LoadGraph("Resources/images/Score/GetScore_750.png");
		break;
	case 1000:
		DrawScore = LoadGraph("Resources/images/Score/GetScore_1000.png");
		break;
	case 1500:
		DrawScore = LoadGraph("Resources/images/Score/GetScore_1500.png");
		break;
	case 2000:
		DrawScore = LoadGraph("Resources/images/Score/GetScore_2000.png");
		break;
	default:
		break;
	}
}

ScoreUP::~ScoreUP()
{
}

bool ScoreUP::Update()
{
	if (++WaitTime > 100) {
		return true;
	}
	return false;
}

void ScoreUP::Draw() const
{
	//DrawFormatString(x, y, 0xff0000, "%d", Score);
	DrawGraph(x, y, DrawScore, true);
}

void ScoreUP::LoadImages() {
}
