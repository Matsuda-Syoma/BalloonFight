#include "LoadSounds.h"
#include "DxLib.h"
int Sounds::BGM_Trip;
int Sounds::SE_Bubble;
int Sounds::SE_crack;
int Sounds::SE_DefeatTheEnemy;
int Sounds::SE_Eatable;
int Sounds::SE_EnemyMove;
int Sounds::SE_Falling;
int Sounds::SE_GameOver;
int Sounds::SE_parachute;
int Sounds::SE_Perfect;
int Sounds::SE_PlayerJump;
int Sounds::SE_PlayerWalk;
int Sounds::SE_Restart;
int Sounds::SE_Splash;
int Sounds::SE_StageClear;
int Sounds::SE_Start;

void Sounds::LoadSounds() {
	BGM_Trip = LoadSoundMem("Resources/sounds/BGM_Trip.wav");
	SE_Bubble = LoadSoundMem("Resources/sounds/SE_Bubble.wav");
	SE_crack = LoadSoundMem("Resources/sounds/SE_crack.wav");
	SE_DefeatTheEnemy = LoadSoundMem("Resources/sounds/SE_DefeatTheEnemy.wav");
	SE_Eatable = LoadSoundMem("Resources/sounds/SE_Eatable.wav");
	SE_EnemyMove = LoadSoundMem("Resources/sounds/SE_EnemyMove.wav");
	SE_Falling = LoadSoundMem("Resources/sounds/SE_Falling.wav");
	SE_GameOver = LoadSoundMem("Resources/sounds/SE_GameOver.wav");
	SE_parachute = LoadSoundMem("Resources/sounds/SE_parachute.wav");
	SE_Perfect = LoadSoundMem("Resources/sounds/SE_Perfect.wav");
	SE_PlayerJump = LoadSoundMem("Resources/sounds/SE_PlayerJump.wav");
	SE_PlayerWalk = LoadSoundMem("Resources/sounds/SE_PlayerWalk.wav");
	SE_Restart = LoadSoundMem("Resources/sounds/SE_Restart.wav");
	SE_Splash = LoadSoundMem("Resources/sounds/SE_Splash.wav");
	SE_StageClear = LoadSoundMem("Resources/sounds/SE_StageClear.wav");
	SE_Start = LoadSoundMem("Resources/sounds/SE_Start.wav");

	ChangeVolumeSoundMem(127, SE_PlayerJump);
}