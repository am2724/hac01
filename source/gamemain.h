#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "scenebase.h"
#include "GamePad.h"


// 他のcppでも使いたいグローバル変数は、ヘッダファイルでextern宣言する

// ゲーム情報

void ChangeScene(SceneBase* scene);	// Sceneを変更する

void GameMain();	// gamemain.cpp に実体を記述


extern int gTime;
extern int gSecond;
extern int gMinute;

extern int gStartTime;

extern GamePad	gPad;			// ゲームパッドの情報
