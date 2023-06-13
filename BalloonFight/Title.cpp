#include "Title.h"

Title::Title()
{
}

Title::~Title()
{
}

AbstractScene* Title::Update()
{
	return this;
}

void Title::Draw() const
{
	DrawString(100, 100, "test title", 0xff0000);
}
