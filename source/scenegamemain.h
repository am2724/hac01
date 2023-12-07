#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "scenebase.h"
#include "framedata.h"
#include "motiondata.h"


// アニメーションパターン用定義
// 配列の番号は間を空けて余裕を持って設定しています
//#define	PT_PLAYER_STAND		0		//  0～ 20枚
//#define	PT_PLAYER_RUN		20		//  20～ 6枚
//#define	PT_PLAYER_ATTACK	30		//  30～ 7枚
//#define	PT_PLAYER_DAMAGE	40		//  40～ 1枚
//#define	PT_PLAYER_JUMP_UP	50		//  50～ 2枚
//#define	PT_PLAYER_JUMP_DOWN	60		//  60～ 2枚
//#define	_PT_CHARA_ALLNUM_	100		// 全パターン枚数
// ※キャラクタ関連の画像はすべて _cgChara[] に読み込むようにするので、このIDを重複しないように設定すること

// 効果音用定義
// 配列の番号は0～
#define	SE_HIT		0		// 殴る
#define	SE_FINISH	1		// ゲーム終了
#define	SE_RESULT	2		// リザルト画面
#define SE_DAMAGE   3
#define	_SE_ALL_	4		// 全SE数

#define ENEMY_MAX (4)
#define ENEMY_TYPE_MAX (8)
#define PLAYER_MAX (2)
#define PAD_BUTTON_MAX (4)
    





class SceneGameMain : public SceneBase {
public:
	SceneGameMain();			// コンストラクタ
	virtual ~SceneGameMain();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	//void	CharaChangeMotion(int charaIndex, int motion);
	//int		SearchFrame(int frameId);

protected:
	int		_cgBg;		// 背景画像
	int		_cgBg1;		// 時間プレート
	int		_cgBg2;		// 1プレイヤープレート
	int		_cgBg3;		// 2プレイヤープレート
	int		_cgBg4;		// FINISH
	int		_cgBg5;		// WIN
	int		_cgBg6;		// LOSE
	int		_cgBg7;		// DRAW

	

	int		_se[_SE_ALL_];	// 効果音セット
	int		_bgm;		//　ゲームプレイ中に流れるBGM

	int Time;
	int Second;
	int Minute;

	int startTime;

	
	
	
};

extern int kouti;