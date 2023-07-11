#include "LoadImages.h"
#include "DxLib.h"

//int StageImages::StageLeft_01;
//int StageImages::StageLeft_02;
//int StageImages::StageRight_01;
//int StageImages::StageRight_02;

int StageImages::Image[13];

void StageImages::LoadImages()
{
	//StageLeft_01 = LoadGraph("Resources/images/Stage/Stage_Land_Left01.png");
	//StageLeft_02= LoadGraph("Resources/images/Stage/Stage_Land_Left02.png");
	//StageRight_01 = LoadGraph("Resources/images/Stage/Stage_Land_Right01.png");
	//StageRight_02 = LoadGraph("Resources/images/Stage/Stage_Land_Right02.png");

	Image[0] = LoadGraph("Resources/images/Stage/Stage_Land_Left01.png");
	Image[1] = LoadGraph("Resources/images/Stage/Stage_Land_Left02.png");
	Image[2] = LoadGraph("Resources/images/Stage/Stage_Land_Right01.png");
	Image[3] = LoadGraph("Resources/images/Stage/Stage_Land_Right02.png");
}
