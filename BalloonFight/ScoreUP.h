#pragma once
#include "Player.h"
class ScoreUP
{
private:
	int x, y;
	int Score;
	int WaitTime;

public:
	ScoreUP(int _score, int px, int py);
	~ScoreUP();
	bool Update();
	void Draw()const;
};

