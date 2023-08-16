#include "GameMain.h"
#include "Map.h"
#include <string>
GameMain::GameMain(int _score, int _stage, int _life)				// ここで初期化
{
	Hitthunder = false;
	Hitthunder2 = false;

	StageSwitch = false;
	StageSwitchTime = 0;
	Sounds::LoadSounds();
	StageImages::LoadImages();
	SetSoundCurrentTime(0.0f, Sounds::BGM_Trip);
	player = new Player;
	
	player->SetLife(100);
	ui = new UI;
	//enemy.emplace_back(300, 270);
	fish = new Fish(0,0,0);
	SpawnDelay = 0;
	StageNum = _stage;
	if (StageNum > 4) {
		StageNum = 0;
	}
	thunder = new Thunder(StageNum);
	Score = _score;
	for (int i = 0; i < MAP_COUNT; i++) {
		int imagework;
		imagework = StageImages::Image[LoadMapImage[StageNum][i]];
		float work[MAP_SIZE];
		for (int j = 0; j < MAP_SIZE; j++) {
			work[j] = LoadMap[StageNum][i][j];
		}
		// 読み込んだ座標が上下、左右足してどちらとも0より大きいなら足場に情報を渡す
		if (work[0] + work[2] > 0 && work[1] + work[3] > 0) {
			stage.emplace_back(work[0], work[1], work[2], work[3],imagework);
		}
	}
	for (int i = 0; i < ENEMY_COUNT; i++) {
		float work[2];
		for (int j = 0; j < 2; j++) {
			work[j] = LoadEnemy[StageNum][i][j];
		}
		if (work[0] != 0 && work[1] != 0) {
			enemy.emplace_back(work[0], work[1]);
			enemy.at(i).name = '0' + i;
		}
	}

	HighScore = 10000;

	Pause = false;
	LifeImg = LoadGraph("Resources/images/UI/UI_Stock.png");
	th_Bcnt = 0;

	for (int t = 0; t <= 9; t++) {
		thunderball[t] = nullptr;
		thunderball2[t] = nullptr;
	}
}

GameMain::~GameMain()				// ここでdeleteなどをする
{
	StopSoundMem(Sounds::BGM_Trip);
}

AbstractScene* GameMain::Update()	// ここでゲームメインの更新をする
{
	if (ui->Title_flg == true) {
		return new Title();
	}
	

	if(PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_START)) {
		Pause = !Pause;
		Sounds::AllStop();
	}
	if (!Pause) {
		Game();
	}
	if (StageSwitch) {
		Pause = true;
		Sounds::AllStop();
		PlaySoundMem(Sounds::SE_StageClear, DX_PLAYTYPE_BACK, false);
		if (++StageSwitchTime > 120) {
			return new GameMain(Score, ++StageNum,player->GetLife());
		}
	}
	return this;
}

void GameMain::Draw() const			// ここでゲームメインの描画
{
	int PlayerLife = player->GetLife();
	thunder->Draw();

	for (int i = 0; i <= 9; i++) {
		if (thunderball[i] != nullptr) {
			thunderball[i]->Draw();
			thunderball2[i]->Draw();

		}
	}

	if (PlayerLife > 0) {
		for (int i = 0; i < PlayerLife - 1; i++) {
			/*DrawBox(60 + (15 * i), 30, 70 + (15 * i)
				, 40, 0xFF0000, TRUE);*/

			DrawGraph(150 - (15 * i), 30, LifeImg, TRUE);
		}
	}

	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}

	player->Draw();

	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Draw();
	}

	fish->Draw();

	for (size_t i = 0; i < bubble.size(); i++) {
		bubble.at(i).Draw();
	}


	for (size_t i = 0; i < scoreUP.size(); i++) {
		scoreUP.at(i).Draw();
	}

	DrawGraph(-80, 455, StageImages::Image[4], true);
	DrawGraph(400, 455, StageImages::Image[4], true);

	DrawGraph(160,450,StageImages::Image[4],true);

	for (size_t i = 0; i < splash.size(); i++) {
		splash.at(i).Draw();
	}

	ui->Draw();
	
}

void GameMain::Game()				// ここでゲームの判定などの処理をする
{

	if (CheckSoundMem(Sounds::BGM_Trip) == 0) {
		PlaySoundMem(Sounds::BGM_Trip, DX_PLAYTYPE_BACK, true);
	}
	
	player->Update();
	if (player->GetFlg()) {
		for (size_t i = 0; i < stage.size(); i++) {
			if (player->IsFly(stage.at(i))) {
				break;
			}
		}
	}
	else {
		player->Miss(0);
	}
	if (player->GetSpawnFlg()) {
		player->Init(player->GetLife() - 1);
		PlaySoundMem(Sounds::SE_Restart, DX_PLAYTYPE_BACK, true);
	}

	// 画面下に行った場合ミス
	if (player->GetY() > SCREEN_HEIGHT && !player->GetSpawnFlg()) {
		StopSoundMem(Sounds::SE_Falling);
		if (player->state != Player::STATE::FISH && SpawnDelay == 1) {
			splash.emplace_back(player->GetX());
		}
		if (++SpawnDelay > 90) {
			SpawnDelay = 0;
			player->SetSpawnFlg(true);
		}
	}
	if (player->GetLife() <= 0) {
		ui->GameOver();
	}
	// 魚の処理
	if (fish != nullptr) {
		fish->flg1 = false;
		//fish->flg2 = false;
		fish->Update();
		if (!fish->flg2) {
			for (size_t i = 0; i < enemy.size() + 1; i++) {
				if (i == 0) {
					if (fish->GetTarget(*player)) {
						break;
					}
				}
				if (i >= 1) {
					if (fish->GetTarget(enemy.at(i - 1))) {
						break;
					}
				}
			}
		}
		else {
			for (size_t i = 0; i < enemy.size() + 1; i++) {
				if (i == 0) {
					if (fish->GetEatTarget().name == player->name) {
						fish->GetTarget(*player);
					}
				}
				if (i >= 1) {
					if (fish->GetEatTarget().name == enemy.at(i - 1).name) {
						fish->GetTarget(enemy.at(i - 1));
					}
				}
			}
		}

		// 魚のメイン処理
		for (size_t i = 0; i < enemy.size() + 1; i++) {
			if (i == 0) {
				// 名前がプレイヤーなら
				if (fish->GetEatTarget().name == player->name) {
					// 状態が魚以外の時
					if (player->state != Player::STATE::FISH) {
						// 判定内なら食べる
						if (fish->Eat(*player)) {
							if (player->state != Player::STATE::MISS) {
								player->Miss(1);
								if (CheckSoundMem(Sounds::SE_Eatable) == 0) {
									PlaySoundMem(Sounds::SE_Eatable, DX_PLAYTYPE_BACK, true);
									break;
								}
							}
							StopSoundMem(Sounds::SE_Falling);
						}
					}
				}
			}
			if (i >= 1) {
				// 名前が敵(n)の時
				if (fish->GetEatTarget().name == enemy.at(i - 1).name) {
					// 状態が魚以外の時
					if (enemy.at(i - 1).state != Enemy::STATE::FISH) {
						// 判定内なら食べる
						if (fish->Eat(enemy.at(i - 1))) {
							enemy.at(i - 1).Death(1);
							if (CheckSoundMem(Sounds::SE_Eatable) == 0) {
								PlaySoundMem(Sounds::SE_Eatable, DX_PLAYTYPE_BACK, true);
							}

						}
					}
				}
			}

		}
	}
	// 敵の処理
	for (size_t i = 0; i < enemy.size(); i++) {
		enemy.at(i).Update();
		if (!enemy.at(i).GetDeathFlg()) {
			// 敵とステージの当たり判定
			for (size_t j = 0; j < stage.size(); j++) {
				if (enemy.at(i).IsFly(stage.at(j))) {
					break;
				}
			}
			// 敵同士跳ね返るようにする
			for (size_t j = 0; j < enemy.size(); j++) {
				if (!enemy.at(j).GetDeathFlg()) {
					enemy.at(i).ChangeInertia(enemy.at(j), enemy.at(j).HitEnemy(enemy.at(i)));
				}

			}
			// プレイヤーのフラグが立っているなら当たり判定がある
			if (player->GetFlg()) {
				int Hit = player->HitEnemy(enemy.at(i),enemy.at(i).GetState());
				if (Hit != 0) {
					if (Hit != 5) {
						if (enemy.at(i).GetBalloon() != 0) {
							enemy.at(i).ChangeInertia(*player, Hit);
						}
						
						if (player->DamageCheck(enemy.at(i), enemy.at(i).GetBalloon(), enemy.at(i).GetState())) {
							if (enemy.at(i).GetBalloon() != 0) {
								Score += 500;
								scoreUP.emplace_back(500, enemy.at(i).GetX(), enemy.at(i).GetY() - 24);
							}
							else {
								Score += 1000;
								scoreUP.emplace_back(1000, enemy.at(i).GetX(), enemy.at(i).GetY() - 24);
							}
							enemy.at(i).BallonBreak(1);
						}
					}
					// 地面に立っているときは跳ね返らずに倒れる
					else {
						Score += 750;
						scoreUP.emplace_back(750, enemy.at(i).GetX(), enemy.at(i).GetY() - 24);
						enemy.at(i).BallonBreak(1);
					}
				}
			}
		}

		if (enemy.at(i).GetBalloon() != 0) {
			parachuteflg = false;
		}
		else {
			parachuteflg = true;
		}
		// 画面外に行ったらしぶきと泡がでる
		if (enemy.at(i).GetY() > SCREEN_HEIGHT - 24) {
			if (enemy.at(i).state != Enemy::STATE::FISH) {
				splash.emplace_back(enemy.at(i).GetX());
				bubble.emplace_back(enemy.at(i).GetX());
			}
			enemy.at(i).SetFlg(false);
		}
		// フラグがたってないなら削除
		if (!enemy.at(i).GetFlg()) {
			enemy.erase(enemy.begin() + i);
			continue;
		}
	}
	// パラシュート状態
	//if (parachuteflg) {
	//	if (CheckSoundMem(Sounds::SE_parachute) == 0) {
	//		PlaySoundMem(Sounds::SE_parachute, DX_PLAYTYPE_BACK, true);
	//	}
	//}
	//else {
	//	StopSoundMem(Sounds::SE_parachute);
	//}

	for (int it = 0; it <= 9; it++) {
		if (thunderball[it] != nullptr) {
			thunderball[it]->Update();// コンストラクタ読み込みされていたらUpdate処理
			if (thunderball[it]->HitPlayer(*player) != 0) {
				player->Miss(2);
				thunderball[it]->SetY();
			}
			/*if (thunderball[it]->playerhit==true) {
				
			}*/
			for (size_t i = 0; i < stage.size(); i++) {
				if (thunderball[it]->Hit(stage.at(i))) {

				}
			}
		}

	}

	for (int j = 0; j <= 9; j++) {
		if (thunderball2[j] != nullptr) {
			thunderball2[j]->Update();// コンストラクタ読み込みされていたらUpdate処理
			if (thunderball2[j]->HitPlayer(*player) != 0) {
				player->Miss(2);
		
				thunderball2[j]->SetY();
			}

			for (size_t i = 0; i < stage.size(); i++) {
				if (thunderball2[j]->Hit(stage.at(i))) {
				}
			}
		}

	}
		thunder->Update();
			if (thunder->ThunderSpawn()) {
				thunder->RandSpawn();
				if (thunderball[th_Bcnt] == nullptr) {
					thunderball[th_Bcnt] = new ThunderBall(thunder->GetRandSpawn(), player->GetFlg(), thunder->CloudX_Set, thunder->CloudY_Set);		// カウントが達成されたらコンストラクタ読み込み
					th_Bcnt = th_Bcnt + 1;
					
				}
				if (thunder->WCloud_flg == true) {
					if (thunderball2[th_Bcnt2] == nullptr) {
						thunderball2[th_Bcnt2] = new ThunderBall(thunder->GetRandSpawn(), player->GetFlg(), thunder->CloudX_Set2, thunder->CloudY_Set2);		// カウントが達成されたらコンストラクタ読み込み
						th_Bcnt2 = th_Bcnt2 + 1;
					}
				}
			}
			//// 無限リスポーン処理
			//if (th_Bcnt > 4) {// 5-9
			//	for (int i = 0; i <= 4; i++) {
			//		thunderball[i] = nullptr;// 0から4番目までnull
			//	}
			//}
			//else// 1-4
			//{
			//	for (int i = 5; i <= 9; i++) {
			//		thunderball[i] = nullptr;// 5から9番目までnull
			//	}
			//}
			//if (th_Bcnt < 9) {
			//	th_Bcnt = 0;
			//}
	

		

	for (size_t i = 0; i < bubble.size(); i++) {
		if (player->HitBox(bubble.at(i)) && !bubble.at(i).GetHitFlg()) {
			Score += 500;
			scoreUP.emplace_back(500, player->GetX(), player->GetY());
			PlaySoundMem(Sounds::SE_Bubble, DX_PLAYTYPE_BACK, true);
			bubble.at(i).SetHitFlg(true);
		}
		if (bubble.at(i).GetHitFlg()) {
			if (bubble.at(i).PlayAnim()) {
				bubble.erase(bubble.begin() + i);
				continue;
			}
		}
	}

	for (size_t i = 0; i < bubble.size(); i++) {
		bubble.at(i).Update();
		if (!bubble.at(i).GetFlg()) {
			bubble.erase(bubble.begin() + i);
			continue;
		}
	}

	for (size_t i = 0; i < scoreUP.size(); i++) {
		if (scoreUP.at(i).Update()) {
			scoreUP.erase(scoreUP.begin() + i);
			continue;
		}
	}
	ui->Update(Score, StageNum + 1);

	for (size_t i = 0; i < splash.size(); i++) {
		if (splash.at(i).Update()) {
			splash.erase(splash.begin() + i);
			continue;
		}
	}

	StageSwitch = true;
	for (size_t i = 0; i < enemy.size(); i++) {
		if (!enemy.at(i).GetDeathFlg() && enemy.size() != 0) {
			StageSwitch = false;
		}
	}
	
}
