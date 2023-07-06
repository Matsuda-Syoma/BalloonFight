#include "ScoreUP.h"

ScoreUP::ScoreUP(int _score, int px,int py)
{
	Score = _score;
	x = px;
	y = py;
	WaitTime = 0;
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
	DrawFormatString(x, y, 0xff0000, "%d", Score);
}
