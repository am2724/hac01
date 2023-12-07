#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegametitle.h"
#include "scenegamemain.h"
#include "sceneexplanation.h"
#include "gamepad.h"

struct MULTIPAD
{
	int keyold;
	int key;
	int trg;
	int rel;
};

struct ENEMY
{
	int		use;			//1なら表示
	int     type;			//敵のタイプ
	int		x, y;			//座標
	int		hp;				//特殊ボスのみ体力3(使わなくする)
	int		anicnt;
	int		anispd;
	int		button[PAD_BUTTON_MAX];		// 押さなきゃいけないボタンのインデックスを1、全部0になったら死亡
};

struct PLAYER
{
	int hp;					//体力
	int LivesEnemy;			//敵残機
	int Combo;				//コンボ数
	int EnemyCount;			//10超えると特殊ボス出現
	int hit;				//1なら殴る演出
	int anicnt;
	int damagecnt;
	int damage;
};

//struct PICTUREENEMY
//{
//	int use;
//	int posx;
//	int posy;
//
//};

int gPadUse[PAD_BUTTON_MAX];

int gEnemyPad[PAD_BUTTON_MAX] =
{
	PAD_INPUT_1,
	PAD_INPUT_2,
	PAD_INPUT_3,
	PAD_INPUT_4
};

int gEnemyButton[ENEMY_TYPE_MAX][PAD_BUTTON_MAX] =
{
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{0,0,0,1},
	{1,1,1,0},
	{1,1,0,1},
	{1,0,1,1},
	{0,1,1,1}
};

struct ENEMY en[PLAYER_MAX][ENEMY_MAX];
struct PLAYER player[PLAYER_MAX];
struct MULTIPAD mpad[PLAYER_MAX];
//struct PICTUREENEMY pien;

int		cgMonster[8][5];
int		cgLife;
int		cgLifeLoss;
int		cgLifePlate;
int		cgCombo[10];
int		cgCombospell;
int		cgHit[5];
int		cgWinhand;
int		cgLosehand;
int		gFinish;
int		cgLives;
int		cgLivesCount[10];
int		cgTime;
int		cgTimer[10];
int		cgStandready;
int		cgHiteffect[17];
int		cgDamage[30];
int		cgHand[5];
int		cgDmonster[8];
//開発用
int		kouti;
int		cgkoutihand[5];
int		cgkoutistandhand;
int		cgkoutiwin;
int		cgkoutilose;



void SetEnemy(int pl, int index, int type)
{
	int xPosTable[PLAYER_MAX][ENEMY_MAX] = {
		{440, 400, 420, 440},
		{1070,1160,1090,1150}
	};
	en[pl][index].use = 1;
	en[pl][index].type = type;
	en[pl][index].x = xPosTable[pl][index];
	en[pl][index].y = 100 * index + 200;
	en[pl][index].anicnt = 0;


	for (int i = 0; i < PAD_BUTTON_MAX; i++)
	{
		en[pl][index].button[i] = gEnemyButton[type][i];
	}
}

void InitEnemy()
{

	for (int p = 0; p < PLAYER_MAX; p++)
	{
		for (int e = 0; e < ENEMY_MAX; e++)
		{
			SetEnemy(p, e, e);
		}
	}
}

void InitPlayer()
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		player[i].hp = 5;
		player[i].LivesEnemy = 60;
		player[i].Combo = 0;
		player[i].EnemyCount = 0;
		player[i].hit = 0;
		player[i].anicnt = 0;
		player[i].damagecnt = 0;
	}



}

//void InitPicEnemy()
//{
//	pien.use = 0;
//	pien.posx = 500;
//	pien.posy = 400;
//}



SceneGameMain::SceneGameMain() {
	// 画像の読み出し
	_cgBg  = LoadGraph("res/game_scene.png"); // 背景画像
	_cgBg1 = LoadGraph("res/time_plate.png"); // 時間プレート
	_cgBg2 = LoadGraph("res/P1_plate.png");	  //1Pプレート
	_cgBg3 = LoadGraph("res/P2_plate.png");	  //2Pプレート 
	_cgBg4 = LoadGraph("res/front_FINISH.png");  // FINISH
	_cgBg5 = LoadGraph("res/front_WIN.png");  // WIN
	_cgBg6 = LoadGraph("res/front_LOSE.png"); // LOSE
	_cgBg7 = LoadGraph("res/front_draw.png"); // DRAW

	//モンスター
	cgMonster[0][0] = LoadGraph("res/monster_X_1.png");
	cgMonster[0][1] = LoadGraph("res/monster_X_2.png");
	cgMonster[0][2] = LoadGraph("res/monster_X_3.png");
	cgMonster[0][3] = LoadGraph("res/monster_X_4.png");
	cgMonster[0][4] = LoadGraph("res/monster_X_5.png");

	cgMonster[1][0]= LoadGraph("res/monster_Y_1.png");
	cgMonster[1][1]= LoadGraph("res/monster_Y_2.png");
	cgMonster[1][2]= LoadGraph("res/monster_Y_3.png");
	cgMonster[1][3]= LoadGraph("res/monster_Y_4.png");
	cgMonster[1][4]= LoadGraph("res/monster_Y_5.png");

	cgMonster[2][0]= LoadGraph("res/monster_A_1.png");
	cgMonster[2][1]= LoadGraph("res/monster_A_2.png");
	cgMonster[2][2]= LoadGraph("res/monster_A_3.png");
	cgMonster[2][3]= LoadGraph("res/monster_A_4.png");
	cgMonster[2][4]= LoadGraph("res/monster_A_5.png");

	cgMonster[3][0]= LoadGraph("res/monster_B_1.png");
	cgMonster[3][1]= LoadGraph("res/monster_B_2.png");
	cgMonster[3][2]= LoadGraph("res/monster_B_3.png");
	cgMonster[3][3]= LoadGraph("res/monster_B_4.png");
	cgMonster[3][4]= LoadGraph("res/monster_B_5.png");

	cgMonster[4][0]= LoadGraph("res/S_monster_XYA_1.png");
	cgMonster[4][1]= LoadGraph("res/S_monster_XYA_2.png");
	cgMonster[4][2]= LoadGraph("res/S_monster_XYA_3.png");
	cgMonster[4][3]= LoadGraph("res/S_monster_XYA_4.png");
	cgMonster[4][4]= LoadGraph("res/S_monster_XYA_5.png");

	cgMonster[5][0]= LoadGraph("res/S_monster_BXY_1.png");
	cgMonster[5][1]= LoadGraph("res/S_monster_BXY_2.png");
	cgMonster[5][2]= LoadGraph("res/S_monster_BXY_3.png");
	cgMonster[5][3]= LoadGraph("res/S_monster_BXY_4.png");
	cgMonster[5][4]= LoadGraph("res/S_monster_BXY_5.png");

	cgMonster[6][0] = LoadGraph("res/S_monster_ABX_1.png");
	cgMonster[6][1] = LoadGraph("res/S_monster_ABX_2.png");
	cgMonster[6][2] = LoadGraph("res/S_monster_ABX_3.png");
	cgMonster[6][3] = LoadGraph("res/S_monster_ABX_4.png");
	cgMonster[6][4] = LoadGraph("res/S_monster_ABX_5.png");
	
	cgMonster[7][0] = LoadGraph("res/S_monster_YAB_1.png");
	cgMonster[7][1] = LoadGraph("res/S_monster_YAB_2.png");
	cgMonster[7][2] = LoadGraph("res/S_monster_YAB_3.png");
	cgMonster[7][3] = LoadGraph("res/S_monster_YAB_4.png");
	cgMonster[7][4] = LoadGraph("res/S_monster_YAB_5.png");

	//敵(負傷)
	cgDmonster[0] = LoadGraph("res/D_monster_X.png");
	cgDmonster[0] = LoadGraph("res/D_monster_Y.png");
	cgDmonster[0] = LoadGraph("res/D_monster_A.png"); 
	cgDmonster[0] = LoadGraph("res/D_monster_B.png");
	cgDmonster[0] = LoadGraph("res/D_S_monster_XYA.png");
	cgDmonster[0] = LoadGraph("res/D_S_monster_BXY.png");
	cgDmonster[0] = LoadGraph("res/D_S_monster_ABX.png");
	cgDmonster[0] = LoadGraph("res/D_S_monster_YAB.png");


	//コンボ
	cgCombo[0] = LoadGraph("res/combo0.png");
	cgCombo[1] = LoadGraph("res/combo1.png");
	cgCombo[2] = LoadGraph("res/combo2.png");
	cgCombo[3] = LoadGraph("res/combo3.png");
	cgCombo[4] = LoadGraph("res/combo4.png");
	cgCombo[5] = LoadGraph("res/combo5.png");
	cgCombo[6] = LoadGraph("res/combo6.png");
	cgCombo[7] = LoadGraph("res/combo7.png");
	cgCombo[8] = LoadGraph("res/combo8.png");
	cgCombo[9] = LoadGraph("res/combo9.png");
	cgCombospell = LoadGraph("res/front_combo.png");
	//ライフ
	cgLife = LoadGraph("res/HP_full.png");
	cgLifeLoss = LoadGraph("res/HP_loss.png");
	cgLifePlate = LoadGraph("res/monster_plate.png");


	cgWinhand = LoadGraph("res/WIN_hand.png");
	cgLosehand = LoadGraph("res/LOSE_hand.png");

	cgLives = LoadGraph("res/nokori.png");
	cgLivesCount[0] = LoadGraph("res/nokori0.png");
	cgLivesCount[1] = LoadGraph("res/nokori1.png");
	cgLivesCount[2] = LoadGraph("res/nokori2.png");
	cgLivesCount[3] = LoadGraph("res/nokori3.png");
	cgLivesCount[4] = LoadGraph("res/nokori4.png");
	cgLivesCount[5] = LoadGraph("res/nokori5.png");
	cgLivesCount[6] = LoadGraph("res/nokori6.png");
	cgLivesCount[7] = LoadGraph("res/nokori7.png");
	cgLivesCount[8] = LoadGraph("res/nokori8.png");
	cgLivesCount[9] = LoadGraph("res/nokori9.png");

	cgTime = LoadGraph("res/time_colon.png");
	cgTimer[0] = LoadGraph("res/time_0.png");
	cgTimer[1] = LoadGraph("res/time_1.png");
	cgTimer[2] = LoadGraph("res/time_2.png");
	cgTimer[3] = LoadGraph("res/time_3.png");
	cgTimer[4] = LoadGraph("res/time_4.png");
	cgTimer[5] = LoadGraph("res/time_5.png");
	cgTimer[6] = LoadGraph("res/time_6.png");
	cgTimer[7] = LoadGraph("res/time_7.png");
	cgTimer[8] = LoadGraph("res/time_8.png");
	cgTimer[9] = LoadGraph("res/time_9.png");
	
	cgStandready= LoadGraph("res/stand ready.png");
	cgHand[0] = LoadGraph("res/hit_right_1.png");
	cgHand[1] = LoadGraph("res/hit_right_2.png");
	cgHand[2] = LoadGraph("res/hit_right_3.png");
	cgHand[3] = LoadGraph("res/hit_right_4.png");
	cgHand[4] = LoadGraph("res/hit_right_5.png");



	cgHiteffect[0] = LoadGraph("res/hit_effect_01.png");
	cgHiteffect[1] = LoadGraph("res/hit_effect_02.png");
	cgHiteffect[2] = LoadGraph("res/hit_effect_03.png");
	cgHiteffect[3] = LoadGraph("res/hit_effect_04.png");
	cgHiteffect[4] = LoadGraph("res/hit_effect_05.png");
	cgHiteffect[5] = LoadGraph("res/hit_effect_06.png");
	cgHiteffect[6] = LoadGraph("res/hit_effect_07.png");
	cgHiteffect[7] = LoadGraph("res/hit_effect_08.png");
	cgHiteffect[8] = LoadGraph("res/hit_effect_09.png");
	cgHiteffect[9] = LoadGraph("res/hit_effect_10.png");
	cgHiteffect[10] = LoadGraph("res/hit_effect_11.png");
	cgHiteffect[11] = LoadGraph("res/hit_effect_12.png");
	cgHiteffect[12] = LoadGraph("res/hit_effect_13.png");
	cgHiteffect[13] = LoadGraph("res/hit_effect_14.png");
	cgHiteffect[14] = LoadGraph("res/hit_effect_15.png");
	cgHiteffect[15] = LoadGraph("res/hit_effect_16.png");
	cgHiteffect[16] = LoadGraph("res/hit_effect_17.png");

	cgDamage[0] = LoadGraph("res/damage_effect_01.png");
	cgDamage[1] = LoadGraph("res/damage_effect_02.png");
	cgDamage[2] = LoadGraph("res/damage_effect_03.png");
	cgDamage[3] = LoadGraph("res/damage_effect_04.png");
	cgDamage[4] = LoadGraph("res/damage_effect_05.png");
	cgDamage[5] = LoadGraph("res/damage_effect_06.png");
	cgDamage[6] = LoadGraph("res/damage_effect_07.png");
	cgDamage[7] = LoadGraph("res/damage_effect_08.png");
	cgDamage[8] = LoadGraph("res/damage_effect_09.png");
	cgDamage[9] = LoadGraph("res/damage_effect_10.png");
	cgDamage[10] = LoadGraph("res/damage_effect_11.png");
	cgDamage[11] = LoadGraph("res/damage_effect_12.png");
	cgDamage[12] = LoadGraph("res/damage_effect_13.png");
	cgDamage[13] = LoadGraph("res/damage_effect_14.png");
	cgDamage[14] = LoadGraph("res/damage_effect_15.png");
	cgDamage[15] = LoadGraph("res/damage_effect_16.png");
	cgDamage[16] = LoadGraph("res/damage_effect_17.png");
	cgDamage[17] = LoadGraph("res/damage_effect_18.png");
	cgDamage[18] = LoadGraph("res/damage_effect_19.png");
	cgDamage[19] = LoadGraph("res/damage_effect_20.png");
	cgDamage[20] = LoadGraph("res/damage_effect_21.png");
	cgDamage[21] = LoadGraph("res/damage_effect_22.png");
	cgDamage[22] = LoadGraph("res/damage_effect_23.png");
	cgDamage[23] = LoadGraph("res/damage_effect_24.png");
	cgDamage[24] = LoadGraph("res/damage_effect_25.png");
	cgDamage[25] = LoadGraph("res/damage_effect_26.png");
	cgDamage[26] = LoadGraph("res/damage_effect_27.png");
	cgDamage[27] = LoadGraph("res/damage_effect_28.png");
	cgDamage[28] = LoadGraph("res/damage_effect_29.png");
	cgDamage[29] = LoadGraph("res/damage_effect_30.png");
	
	//開発用（モードkouti）
	cgkoutistandhand = LoadGraph("res/K_ready.png");
	cgkoutihand[0] = LoadGraph("res/L_KOUTI_hand_01.png");
	cgkoutihand[1] = LoadGraph("res/L_KOUTI_hand_02.png");
	cgkoutihand[2] = LoadGraph("res/L_KOUTI_hand_03.png");
	cgkoutihand[3] = LoadGraph("res/L_KOUTI_hand_04.png");
	cgkoutihand[4] = LoadGraph("res/L_KOUTI_hand_05.png");
	cgkoutiwin= LoadGraph("res/K_win.png");
	cgkoutilose = LoadGraph("res/K_lose.png");
	

	


	// 効果音の読み込み
	_se[SE_HIT] = LoadSoundMem("res/Hit_se.mp3");
	_se[SE_DAMAGE] = LoadSoundMem("res/damage.mp3");
	_se[SE_FINISH] = LoadSoundMem("res/Finish_se.mp3");
	_se[SE_RESULT] = LoadSoundMem("res/result_se.mp3");

	// BGMの読み込み
	_bgm = LoadSoundMem("res/sento_BGM.mp3");
	ChangeNextPlayVolumeSoundMem(200, _bgm);
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);

	Time = 4860;
	Second = 0;
	Minute = 0;

	startTime = 240;




	InitEnemy();

	InitPlayer();

	//InitPicEnemy();

	for (int i = 0; i < PAD_BUTTON_MAX; i++)
	{
		gPadUse[i] = 0;
	}
}

SceneGameMain::~SceneGameMain() {
	DeleteGraph(_cgBg);
	DeleteGraph(_cgBg1);
	DeleteGraph(_cgBg2);
	DeleteGraph(_cgBg3);
	DeleteGraph(_cgBg4);
	DeleteGraph(_cgBg5);
	DeleteGraph(_cgBg6);
	DeleteGraph(_cgBg7);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			DeleteGraph(cgMonster[i][j]);
		}
	}
		
		
	/*DeleteGraph(cgMonster[0]);
	DeleteGraph(cgMonster[1]);
	DeleteGraph(cgMonster[2]);
	DeleteGraph(cgMonster[3]);
	DeleteGraph(cgMonster[4]);
	DeleteGraph(cgMonster[5]);
	DeleteGraph(cgMonster[6]);
	DeleteGraph(cgMonster[7]);*/

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(cgCombo[i]);
	}

	/*DeleteGraph(cgCombo[1]);
	DeleteGraph(cgCombo[2]);
	DeleteGraph(cgCombo[3]);
	DeleteGraph(cgCombo[4]);
	DeleteGraph(cgCombo[5]);
	DeleteGraph(cgCombo[6]);
	DeleteGraph(cgCombo[7]);
	DeleteGraph(cgCombo[8]);
	DeleteGraph(cgCombo[9]);*/
	
	DeleteGraph(cgCombospell);

	DeleteGraph(cgLife);
	DeleteGraph(cgLifeLoss);
	DeleteGraph(cgLifePlate);

	DeleteGraph(_bgm);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(cgTimer[i]);
	}
	
	/*DeleteGraph(cgTimer[1]);
	DeleteGraph(cgTimer[2]);
	DeleteGraph(cgTimer[3]);
	DeleteGraph(cgTimer[4]);
	DeleteGraph(cgTimer[5]);
	DeleteGraph(cgTimer[6]);
	DeleteGraph(cgTimer[7]);
	DeleteGraph(cgTimer[8]);
	DeleteGraph(cgTimer[9]);*/
	
	DeleteGraph(cgTime);
	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(cgLivesCount[i]);
	}
	
	/*DeleteGraph(cgLivesCount[1]);
	DeleteGraph(cgLivesCount[2]);
	DeleteGraph(cgLivesCount[3]);
	DeleteGraph(cgLivesCount[4]);
	DeleteGraph(cgLivesCount[5]);
	DeleteGraph(cgLivesCount[6]);
	DeleteGraph(cgLivesCount[7]);
	DeleteGraph(cgLivesCount[8]);
	DeleteGraph(cgLivesCount[9]);*/
	
	DeleteGraph(cgLives);

	DeleteGraph(cgWinhand);
	DeleteGraph(cgLosehand);

	for (int i = 0; i < 17; i++)
	{
		DeleteGraph(cgHiteffect[i]);
	}
	
	for (int i = 0; i < 30; i++)
	{
		DeleteGraph(cgDamage[i]);
	}

	DeleteGraph(cgkoutistandhand);
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(cgkoutihand[i]);
	}
	DeleteGraph(cgkoutiwin);
	DeleteGraph(cgkoutilose);



}

void SceneGameMain::Input() 
{
	mpad[0].keyold = mpad[0].key;
	mpad[1].keyold = mpad[1].key;
	mpad[0].key = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得
	mpad[1].key = GetJoypadInputState(DX_INPUT_PAD2);
	mpad[0].trg = (mpad[0].key ^ mpad[0].keyold) & mpad[0].key;
	mpad[1].trg = (mpad[1].key ^ mpad[1].keyold) & mpad[1].key;
	mpad[0].rel = (mpad[0].key ^ mpad[0].keyold) & ~mpad[0].key;
	mpad[1].rel = (mpad[1].key ^ mpad[1].keyold) & ~mpad[1].key;
}



void DeleteEnemy(int pl)
{


	for (int i = ENEMY_MAX - 1; i > 0; --i)
	{
		SetEnemy(pl, i, en[pl][i - 1].type);
	}
	if (player[pl].EnemyCount == 10)
	{
		SetEnemy(pl, 0, 4 + rand() % 4);
		player[pl].EnemyCount = 0;
	}
	else {
		SetEnemy(pl, 0, rand() % 4);
	}

}

void EnemyProcess()
{
	// 一番下の敵に対応したボタンが押されたか判定
	// 対応したボタンが押された場合は構造体メンバのbutton[]を0にする
	int i;
	int f = 0;
	//1P	
	if (mpad[0].trg != 0)
	{
		for (i = 0; i < PAD_BUTTON_MAX; i++)
		{
			if (mpad[0].trg & gEnemyPad[i])
			{
				// 対応していないボタンが押されていたら f = 1 にする
				if (en[0][ENEMY_MAX - 1].button[i] == 0)
				{
					f = 1;
				}
				en[0][ENEMY_MAX - 1].button[i] = 0;
			}
		}

		if (f == 1)
		{
			player[0].damage = 1;
			player[0].hp--;
			player[0].Combo = 0;
			player[0].EnemyCount = 0;
			player[0].damagecnt = 0;
		}
		if (player[0].hp < 0)
		{
			player[0].hp = 0;
		}
	}

	// 一番下の敵のbutton[]が全て0なら死んだことにする
	for (i = 0; i < PAD_BUTTON_MAX; i++)
	{
		if (en[0][ENEMY_MAX - 1].button[i] != 0)
		{
			break;
		}


	}

	// ループ最後まで0だったら i はPAD_BUTTON_MAX になっているはず
	if (i == PAD_BUTTON_MAX)
	{
		if (en[0][ENEMY_MAX - 1].type >= 4)
		{
			player[1].LivesEnemy += 10;
		}
		player[0].hit = 1;
		DeleteEnemy(0);
		player[0].Combo++;
		player[0].EnemyCount++;
		player[0].LivesEnemy--;
		player[0].anicnt = 0;

	}



	//2P
	if (mpad[1].trg != 0)
	{
		for (i = 0; i < PAD_BUTTON_MAX; i++)
		{
			if (mpad[1].trg & gEnemyPad[i])
			{
				// 対応していないボタンが押されていたら f = 1 にする
				if (en[1][ENEMY_MAX - 1].button[i] == 0)
				{
					f = 1;
				}
				en[1][ENEMY_MAX - 1].button[i] = 0;
			}
		}

		if (f == 1)
		{
			player[1].damage = 1;
			player[1].hp--;
			player[1].Combo = 0;
			player[1].EnemyCount = 0;
			player[1].damagecnt = 0;
		}

		if (player[1].hp == 0)
		{
			player[1].hp = 0;
		}
	}

	// 一番下の敵のbutton[]が全て0なら死んだことにする
	for (i = 0; i < PAD_BUTTON_MAX; i++)
	{
		if (en[1][ENEMY_MAX - 1].button[i] != 0)
		{
			break;
		}


	}

	// ループ最後まで0だったら i はPAD_BUTTON_MAX になっているはず
	if (i == PAD_BUTTON_MAX)
	{
		if (en[1][ENEMY_MAX - 1].type >= 4)
		{
			player[0].LivesEnemy += 10;
		}
		player[1].hit = 1;
		DeleteEnemy(1);
		player[1].Combo++;
		player[1].EnemyCount++;
		player[1].LivesEnemy--;
		player[1].anicnt = 0;
		
		



	}


	// モンスターアニメカウント
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < ENEMY_MAX; j++)
		{
			en[i][j].anicnt++;
		}
	}


	
	
}






void SceneGameMain::Process() 
{
	if(gPad._trg & PAD_INPUT_11)
	{		// BARKボタンでタイトル画面へ
		SceneBase* scene = new SceneGameTitle();
		ChangeScene(scene);
	}
	
	if (gFinish == 0)
	{
		

		

		startTime--;
		if (startTime <= 0)
		{
			startTime = 0;
		}

		if (startTime <= 0)
		{
			Time--;
			if (Time <= 0)
			{
				Time = 0;
			}
			EnemyProcess();
		}


		Second = Time / 60;
		Minute = Second / 60;
		Second = Second % 60;

		if (player[1].hp == 0 || player[0].LivesEnemy == 0)
		{
			gFinish = 1;
		}
		if (player[0].hp == 0 || player[1].LivesEnemy == 0)
		{
			gFinish = 2;
		}
		if (Time == 0)
		{
			if (player[0].hp == player[1].hp)
			{
				if(player[0].LivesEnemy > player[1].LivesEnemy)
				{
					gFinish = 2;

				}
				else
				{
					gFinish = 1;
				}
				
				if(player[0].LivesEnemy == player[1].LivesEnemy)
				{
					gFinish = 3;
				}
				

			}
			if (player[0].hp > player[1].hp)
			{
				gFinish = 1;
			}
			if (player[0].hp < player[1].hp)
			{
				gFinish = 2;
			}


		}
	}

	
	if(player[0].hit == 1)
	{
		if(player[0].anicnt == 3)
		{
			PlaySoundMem(_se[SE_HIT], DX_PLAYTYPE_BACK, TRUE);
		}
		if(player[0].anicnt >= 12)
		{
			player[0].hit = 0;
		}
	}

	if(player[1].hit == 1)
	{
		if(player[1].anicnt == 3)
		{
			PlaySoundMem(_se[SE_HIT], DX_PLAYTYPE_BACK, TRUE);
		}
		if(player[1].anicnt >= 12)
		{
			player[1].hit = 0;
		}
	}
	

	
	if(player[0].damage == 1)
	{
		if(player[0].damagecnt == 10)
		{
				PlaySoundMem(_se[SE_DAMAGE], DX_PLAYTYPE_BACK, TRUE);
		}
		if(player[0].damagecnt >= 30)
		{
				player[0].damage = 0;
		}
	}
	
	if(player[1].damage == 1)
	{
		if(player[1].damagecnt == 10)
		{
			PlaySoundMem(_se[SE_DAMAGE], DX_PLAYTYPE_BACK, TRUE);
		}
		if(player[1].damagecnt >= 30)
		{
			player[1].damage = 0;
		}
	}


	

	/*if(player[1].hit == 1)
	{
		if(player[1].anicnt == 3)
		{
			
			PlaySoundMem(_se[SE_HIT], DX_PLAYTYPE_BACK, TRUE);
		}
		if(player[1].anicnt >= 12)
		{
			player[1].hit = 0;
		}
	}*/

	

	
	player[0].anicnt++;
	player[1].anicnt++;
	player[0].damagecnt++;
	player[1].damagecnt++;
	
	//HitEnemy();
	/*if(player[0].hit == 1)
	{
		pien.use = 1;
		pien.posx -= 40;
		pien.posy -= 40;
		if(pien.posx <= 0 || pien.posy <= 0)
		{
			pien.use = 0;
		}
	}*/
	
	
	
}

//void HitEnemy()
//{
//	
//	
//
//}

void DrawEnemy() {
	int i;

	int drawOrder[ENEMY_MAX];
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		drawOrder[i] = i;	// 0から順に入れる
	}

	// todo:ここでdrawOrder[]の中を、キャラのy座標順に並び替える
	// 「バブルソート」や「クイックソート」などで調べてみよう

	// 「バブルソート」アルゴリズムで、drawOrder[]を、キャラのy座標順に並び替える
	for (i = 0; i < ENEMY_MAX; i++) {
		for (int z = i + 1; z < ENEMY_MAX; z++) {
			if (en[0][drawOrder[i]].y > en[0][drawOrder[z]].y) {
				// drawOrder[i] と drawOrder[z]を交換する
				int temp = drawOrder[i];
				drawOrder[i] = drawOrder[z];
				drawOrder[z] = temp;
			}
			if (en[1][drawOrder[i]].y > en[1][drawOrder[z]].y) {
				// drawOrder[i] と drawOrder[z]を交換する
				int temp = drawOrder[i];
				drawOrder[i] = drawOrder[z];
				drawOrder[z] = temp;
			}
		}
	}

	for (int z = 0; z < ENEMY_MAX; z++)
	{
		int i = drawOrder[z];	// [i]はdrawOrder[]順

		int anim1 = (en[0][i].anicnt / 10) % 5;
		int anim2 = (en[1][i].anicnt / 10) % 5;

		// この敵は使用中か？
		if (en[0][i].use == 1)
		{
			DrawGraph(en[0][i].x, en[0][i].y, cgMonster[en[0][i].type][anim1], TRUE);
		}
		if (en[1][i].use == 1)
		{
			DrawGraph(en[1][i].x, en[1][i].y, cgMonster[en[1][i].type][anim2], TRUE);
		}
	}


}

void DrawPlayer1()
{
	int i;
	DrawGraph(230, 20, cgLifePlate, TRUE);
	for (i = 0; i < 5; i++)
	{
		DrawGraph(75 * i + 280, 60, cgLifeLoss, TRUE);
	}
	for (i = 0; i < player[0].hp; i++)
	{
		DrawGraph(75 * i + 280, 60, cgLife, TRUE);
	}
	if (player[0].hit == 1)
	{
		for (i = 0; i < 5; i++)
		{
			DrawGraph(490, 480, cgHit[i], TRUE);
			DrawGraph(500, 600, cgHiteffect[player[1].anicnt / 3 % 17], TRUE);
		}
		
	}

	
	DrawGraph(105, 500, cgCombo[player[0].Combo % 10], TRUE);
	DrawGraph(35, 500, cgCombo[player[0].Combo / 10], TRUE);
	DrawGraph(10, 450, cgCombospell, TRUE);
	SetFontSize(32);
	//DrawFormatString(0, 200, GetColor(255, 255, 255), "  残り　: %d ", player[0].LivesEnemy);
	DrawGraph(10, 200, cgLives, TRUE);
	DrawGraph(150, 200, cgLivesCount[player[0].LivesEnemy % 10], TRUE);
	DrawGraph(110, 200, cgLivesCount[player[0].LivesEnemy / 10], TRUE);

	
	

	if (gFinish == 0)
	{
		if(kouti != 0)
		{
			if(player[0].hit == 1)
			{
				DrawGraph(100, 760, cgkoutihand[player[0].anicnt / 3 % 5], TRUE);
			}
			else
			{
				DrawGraph(100, 760, cgkoutistandhand, TRUE);
			}

			if(player[0].damage == 1)
			{
				DrawGraph(100, 760, cgDamage[player[0].damagecnt % 30], TRUE);
			}
		}

		else
		{
			if(player[0].hit == 1)
			{
				DrawGraph(100, 760, cgHand[player[0].anicnt / 3 % 5], TRUE);
				/*if(pien.use == 1)
				{
					DrawGraph(pien.posx, pien.posy, cgDmonster[en[0][i].type], TRUE);
				}*/
				
			}
			else
			{
				DrawGraph(100, 760, cgStandready, TRUE);
			}

			if(player[0].damage == 1)
			{
				DrawGraph(100, 760, cgDamage[player[0].damagecnt % 30], TRUE);
			}
		}
		

		

	}

	
	
}

void DrawPlayer2()
{
	int i;
	DrawGraph(1100, 20, cgLifePlate, TRUE);
	for (i = 0; i < 5; i++)
	{
		DrawGraph(75 * i + 1150, 60, cgLifeLoss, TRUE);
	}
	for (i = 0; i < player[1].hp; i++)
	{
		DrawGraph(75 * i + 1150, 60, cgLife, TRUE);
	}
	DrawGraph(1815, 500, cgCombo[player[1].Combo % 10], TRUE);
	DrawGraph(1745, 500, cgCombo[player[1].Combo / 10], TRUE);
	DrawGraph(1725, 450, cgCombospell, TRUE);
	SetFontSize(32);
	//DrawFormatString(1670, 200, GetColor(255, 255, 255), "  残り　: %d ", player[1].LivesEnemy);
	DrawGraph(1720, 200, cgLives, TRUE);
	DrawGraph(1860, 200, cgLivesCount[player[1].LivesEnemy % 10], TRUE);
	DrawGraph(1820, 200, cgLivesCount[player[1].LivesEnemy / 10], TRUE);
	/*if (gFinish == 0)
	{
		DrawGraph(920, 760, cgStandready, TRUE);
	}
	*/
	if(gFinish == 0)
	{
		if(kouti == 0)
		{
			if(player[1].hit == 1)
			{
				DrawGraph(900, 760, cgHand[player[1].anicnt / 3 % 5], TRUE);
				DrawGraph(1200, 600, cgHiteffect[player[1].anicnt / 3 % 17], TRUE);
			}
			else
			{
				DrawGraph(920, 760, cgStandready, TRUE);
			}

			if(player[1].damage == 1)
			{
				DrawGraph(920, 760, cgDamage[player[1].damagecnt % 30], TRUE);
			}
		}
		
		else
		{
			if(player[1].hit == 1)
			{
				DrawGraph(900, 760, cgkoutihand[player[1].anicnt / 3 % 5], TRUE);
				DrawGraph(1200, 600, cgHiteffect[player[1].anicnt / 3 % 17], TRUE);
			}
			else
			{
				DrawGraph(920, 760, cgkoutistandhand, TRUE);
			}

			if(player[1].damage == 1)
			{
				DrawGraph(920, 760, cgDamage[player[1].damagecnt % 30], TRUE);
			}
		}
	}
}



void SceneGameMain::Draw() 
{

	
	DrawGraph(0, 0, _cgBg, FALSE);							// 背景画像
	DrawGraph((SCREEN_W - 350) / 2, 15, _cgBg1, TRUE);		// 時間プレート
	DrawGraph(10, 10, _cgBg2, TRUE);						// 1Pプレート
	DrawGraph(SCREEN_W - 100 - 10, 10, _cgBg3, TRUE);		// 2Pプレート


	


	// 制限時間の表示
	SetFontThickness(8);
	SetFontSize(48);
	DrawFormatString(SCREEN_W / 2 - 190, 70, GetColor(0, 0, 0), " 　%02d : %02d", 0, 0);
	/*Second = Time / 60;
	Minute = Second / 60;
	Second = Second % 60;*/


	// ゲームスタート時のカウントダウンの表示
	SetFontThickness(9);
	SetFontSize(120);
	DrawFormatString(SCREEN_W / 2 - 30, SCREEN_H / 2, GetColor(255, 255, 255), "%d", startTime / 60);
	//DrawFormatString(SCREEN_W / 2 - 600, SCREEN_H / 300, GetColor(255, 255, 255), "%d",kouti);
	
		if (startTime == 0)
		{
			DrawGraph(0, 0, _cgBg, FALSE);							// 背景画像
			DrawGraph((SCREEN_W - 350) / 2, 15, _cgBg1, TRUE);		// 時間プレート
			DrawGraph(10, 10, _cgBg2, TRUE);						// 1Pプレート
			DrawGraph(SCREEN_W - 100 - 10, 10, _cgBg3, TRUE);		// 2Pプレート

			DrawEnemy();
			DrawPlayer1();
			DrawPlayer2();


			// 制限時間の表示
			SetFontThickness(8);
			SetFontSize(48);
			DrawFormatString(SCREEN_W / 2 - 190, 70, GetColor(0, 0, 0), " 　%02d : %02d", Minute, Second);
			
		}

	

	//if (Time == 0)
	//{
	//	
	//	 FINISH表示
	//	DrawGraph(SCREEN_W / 4 + 18, SCREEN_H / 2 - 200, _cgBg4, TRUE);
	//	
	//}

	if (kouti == 0)
	{
		if (gFinish == 1)
		{
			DrawGraph(300, 450, _cgBg5, TRUE);		// WIN表示
			DrawGraph(1100, 450, _cgBg6, TRUE);		// LOSE表示
			DrawGraph(100, 760, cgWinhand, TRUE);
			DrawGraph(900, 800, cgLosehand, TRUE);


		}

		if (gFinish == 2)
		{
			DrawGraph(300, 450, _cgBg6, TRUE);
			DrawGraph(1100, 450, _cgBg5, TRUE);
			DrawGraph(100, 800, cgLosehand, TRUE);
			DrawGraph(900, 760, cgWinhand, TRUE);
		}

		if (gFinish == 3)
		{
			DrawGraph(SCREEN_W / 4 + 40, SCREEN_H / 2 - 100, _cgBg7, TRUE);

		}
	}

	else
	{
		if (gFinish == 1)
		{
			DrawGraph(300, 450, _cgBg5, TRUE);		// WIN表示
			DrawGraph(1100, 450, _cgBg6, TRUE);		// LOSE表示
			DrawGraph(100, 760, cgkoutiwin, TRUE);
			DrawGraph(900, 800, cgkoutilose, TRUE);


		}

		if (gFinish == 2)
		{
			DrawGraph(300, 450, _cgBg6, TRUE);
			DrawGraph(1100, 450, _cgBg5, TRUE);
			DrawGraph(100, 800, cgkoutilose , TRUE);
			DrawGraph(900, 760, cgkoutiwin, TRUE);
		}

		if (gFinish == 3)
		{
			DrawGraph(SCREEN_W / 4 + 40, SCREEN_H / 2 - 100, _cgBg7, TRUE);

		}
	}
	

	//DrawGraph(0, 0, _cgBg5, TRUE);		// WIN表示
	//DrawGraph(0, 0, _cgBg6, TRUE);		// LOSE表示
	//DrawGraph(0, 0, _cgBg7, TRUE);		// DRAW表示

	

}
