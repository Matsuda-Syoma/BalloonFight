#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include "PAD_INPUT.h"
#include <math.h>
class Player : public BoxCollider
{
private:
	bool flg;					// プレイヤーが動かせるか
	bool landingflg;			// プレイヤーが地面に立っているか
	bool groundflg;				// プレイヤーが着地したか
	bool missflg;				// ミスしたときのフラグ
	bool animflg;				// ミスしたときのフラグ
	int life;					// プレイヤーの残機
	int balloon;					// プレイヤーの風船の数
	int HitStage;				// プレイヤーがどこに当たったか
	float x, y;					// プレイヤーの座標
	float w, h;					// プレイヤーの大きさ
	int speedX;					// プレイヤーの速度
	float startX;				// プレイヤーの初速
	float FlyspeedMax;			// プレイヤーの空中最大速度
	float GroundspeedMax;		// プレイヤーの地上最大速度
	float inertiaX, inertiaY;	// プレイヤーの慣性
	float imageX, imageY;		// プレイヤーの画像の座標
	int AnimImg;
	int AnimWork;
	int AnimSelect;
	int AnimUpdateTime;
	int AnimFlg = 0b0000;
	bool imageReverse;
	int images[40];
	int LifeImg;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;
	
public:
	int jumpdelay;
	Player();							// コンストラクタ
	~Player();							// デストラクタ
	void Init(int _life);				// 数値の初期化
	void Update();						// 更新処理
	void Draw()const;					// 描画処理
	void LoadImages();					// 画像読み込み
	void DeleteImages();				// 画像削除
	void Miss(int i);					// ミスの関数
	void BallonBreak(int i);			// 風船を減らして0以下だったらFlgを切る
	void AnimUpdate();

	bool IsFly(Stage box);				// 飛んでいるかどうか
	bool IsFlg();						// プレイヤーが生きているか

	float GetBoxSide(Stage box, int i);	// 引数で数値を返す(1:上、2:下、3:左、4:右)
	float inputX();						// スティックの入力値を返す

	int GetLife();				// 残機を返す
	
};

