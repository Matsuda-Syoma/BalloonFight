#pragma once
#include "common.h"
#include "LoadImages.h"
// 左の座標、上の座標、右の座標、下の座標
float LoadMap[MAP][MAP_COUNT][MAP_SIZE] =
{
	//設置しているBoxは左側から順番に作っています
	
	// １ステージ
	{{0, 420, 160, 480},	// 0左下
	{180, 285, 460, 300},	// 真ん中
	{480, 420, 640, 480},	// 右下
	},
	// ２ステージ
	{{0, 420, 160, 480},	// 0左下
	{100, 165, 220, 182},	// 1左上
	{180, 285, 460, 300},	// 2真ん中
	{460, 150, 580, 172},	// 3右上
	{480, 420, 640, 480},	// 4右下
	},
	// 3ステージ
	{{0, 420, 160, 480},	// 0左下
	{158, 268, 220, 284},	// 1左真ん中
	{181, 284, 200, 335},	// 2左　＜鍾乳石＞19 51
	{200, 98, 240, 114},	// 3左上
	{280, 368, 360, 390},	// 4真ん中下
	{320, 184, 380, 200},	// 5右真ん中
	{340, 200, 359, 251},	// 6右真ん中＜鍾乳石＞
	{500, 100, 560, 117},	// 7右上
	{520, 117, 539, 168},	// 8右上
	{480, 420, 640, 480},	// 9右下
	},
	// 4ステージ
	{{0, 420, 160, 480},	// 0左下
	{120, 268, 180, 285},	// 1左
	{240, 300, 300, 320},	// 2真ん中
	{320, 182, 380, 200},	// 3上 真ん中
	{360, 368, 420, 387},	// 4右
	{480, 420, 640, 480},	// 5右下
	{460, 285, 520, 300},	// 6右上
	},
	//5ステージ
	{{0, 420, 160, 480},	// 0左下
	{100, 200, 120, 247},	// 1左＜鍾乳石＞
	{200, 335, 260, 353},	// 2左 真ん中 
	{258, 166, 282, 217},	// 3真ん中＜鍾乳石＞
	{220, 80, 280, 100},	// 4左上
	{380, 335, 440, 353},	// 5右 真ん中
	{498, 149, 522, 217},	// 6右＜鍾乳石＞
	{480, 420, 640, 480},	// 7右下
	},
	// 640,480
};

int LoadMapImage[MAP][MAP_COUNT] =
{
	{0,5,2,0,0,0,0,0,0,0},
	{0,6,5,6,2,0,0,0,0,0},
	{0,8,-1,9,7,8,-1,8,-1,2},
	{0,10,10,10,10,2,10,0,0,0},
	{0,11,10,11,10,10,12,2,0,0}
};