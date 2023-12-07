#include "DxLib.h"
#include "source/scenebase.h"
#include "source/sceneexplanation.h"
#include "source/scenegamemain.h"
#include "source/scenegametitle.h"
#include "source/gamepad.h"
#include "source/gamemain.h"

//
// 定数・構造体定義
//



//
// グローバル変数宣言
//

// ゲーム情報

GamePad	gPad;			// ゲームパッドの情報








// 敵の種類とボタンの対応表












// Sceneポインタ
SceneBase* gScene;					// ポインタなのでnewするまで実体は無い

// Sceneの切り替え用
SceneBase* gNewScene;				// NULL以外がセットされていたら、シーンを切り替える

// Sceneを変更する
void ChangeScene(SceneBase* scene) 
{
	gNewScene = scene;		// 次のシーンをセット
}

// 敵一体を設定







// アプリの初期化
// 起動時に1回だけ実行される
void AppInit()
{
	

	

	gNewScene = NULL;		// 次のシーンを初期化する
	gScene = new SceneGameTitle();		// Sceneの実体を作る
}



// アプリの解放
// 終了時に1回だけ実行される
void AppRelease()
{
	delete gScene;				// Sceneを削除する
}











//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void FrameInput()
{
	gPad.Input();

	

	// Sceneの入力呼び出し
	gScene->Input();
}



// フレーム処理：計算
void FrameProcess()
{

	// Sceneの計算呼び出し
	gScene->Process();

}











// フレーム処理：描画
void FrameDraw() {

	ClearDrawScreen();	// 画面を初期化する

	// Sceneの描画呼び出し
	gScene->Draw();
	
	
	
	ScreenFlip();							// 裏画面の内容を表画面に反映させる
}

//
void GameMain()
{
	AppInit();	// 初期化

	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{

		// シーンを切り替えるか？
		if (gNewScene != NULL) {
			delete gScene;		// 今のシーンを削除する
			gScene = gNewScene;	// 受け取ったシーンをポインタセット
			gNewScene = NULL;	// 次のシーンを初期化する
		}

		FrameInput();	// 入力
		FrameProcess();	// 計算
		FrameDraw();	// 描画
		
	}

	AppRelease();	// 解放
}
