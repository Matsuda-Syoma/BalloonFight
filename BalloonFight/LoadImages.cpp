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
	Image[4] = LoadGraph("Resources/images/Stage/Stage_Sea01.png");
	Image[5] = LoadGraph("Resources/images/Stage/Stage_Footing01.png");
	Image[6] = LoadGraph("Resources/images/Stage/Stage_Footing02.png");
	Image[7] = LoadGraph("Resources/images/Stage/Stage_Footing03.png");
	Image[8] = LoadGraph("Resources/images/Stage/Stage_Footing04.png");
	Image[9] = LoadGraph("Resources/images/Stage/Stage_Footing05.png");
	Image[10] = LoadGraph("Resources/images/Stage/Stage_Footing06.png");
	Image[11] = LoadGraph("Resources/images/Stage/Stage_Footing07.png");
	Image[12] = LoadGraph("Resources/images/Stage/Stage_Footing08.png");
}
