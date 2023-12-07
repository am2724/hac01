#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない


// キャラクタ動作テーブル
struct CHARA_MOTION_ITEM {
	int		frameId;	// 表示したいフレームID
	int		frameCnt;	// 何フレーム表示するか
	int		mx, my;		// 表示中、1フレームあたり移動する値
};

// １モーションあたり、モーションアイテムをいくつまで書けるか
#define	CHARA_MOTION_ITEM_MAX	64

// モーションアイテム用コマンド。frameId に指定して使う。frameIdと重複してはいけない
// コマンドはフレーム終了時に処理されるため、最初のフレームには指定できない仕様
#define	CHARA_MOTION_COMMAND_LOOP		1	// モーションをループする(frameCntにモーションindex指定)
#define	CHARA_MOTION_COMMAND_MOTION		2	// 別のモーションへ(frameCntにモーション番号指定)
#define	CHARA_MOTION_COMMAND_PLAYSE		3	// 効果音再生(frameCntにSE_xxxx)



struct CHARA_MOTION {		//使わないから後でコメントアウトしておく
	//int		mirror_lr;	// 左右反転するなら1, しないなら0
	CHARA_MOTION_ITEM	item[CHARA_MOTION_ITEM_MAX];
};

// モーション番号。0番からの通し番号であること
//#define	MOTION_R_STAND		0
//#define	MOTION_L_STAND		1
//#define	MOTION_R_RUN		2
//#define	MOTION_L_RUN		3
//#define	MOTION_R_ATTACK		4
//#define	MOTION_L_ATTACK		5
//#define	MOTION_R_DAMAGE		6
//#define	MOTION_L_DAMAGE		7
//#define	MOTION_R_JUMP_UP	8
//#define	MOTION_L_JUMP_UP	9
//#define	MOTION_R_JUMP_DOWN	10
//#define	MOTION_L_JUMP_DOWN	11


// モーション番号。0番からの通し番号であること
/*#define	MOTION_STAND		0
  #define	MOTION_ATTACK		1*/


extern struct CHARA_MOTION tblMotion[];
