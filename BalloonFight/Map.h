#pragma once
#include "common.h"

// 左の座標、上の座標、右の座標、下の座標
float LoadMap[MAP][MAP_COUNT][MAP_SIZE] =
{
	//設置しているBoxは左側から順番に作っています
	
	// １ステージ
	{{0, 420, 160, 455},	// 左下
	{180, 285, 460, 300},	// 真ん中
	{480, 420, 640, 455},	// 右下
	{0, 455, 640, 480}		// 海
	},		

	// ２ステージ
	{{0, 420, 160, 455},	// 左下
	{100, 165, 230, 182},	// 左上
	{180, 285, 460, 300},	// 真ん中
	{450, 140, 600, 170},	// 右上
	{480, 420, 640, 455},	// 右下
	{0, 455, 640, 480}		// 海
	},

	{{0, 440, 160, 465},	// 左下
	{450, 440, 640, 465},	// 右下
	{290, 370, 350, 400},	// 真ん中下
	{0, 465, 640, 480}		// 海
	},

	// 640,480

};
