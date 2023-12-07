#pragma once
#include "source/SceneBase.h"
class SceneGameend : public SceneBase
{
public:
	SceneGameend();			// コンストラクタ
	virtual ~SceneGameend();	// デストラクタ

	void	Input()override;	// 入力
	void	Process()override;	// 計算
	void	Draw()override;		// 描画

protected:

	int		_cgBg;		// 背景画像
	int		_cgBg1;		// 時間プレート
	int		_cgBg2;		// 1プレイヤープレート
	int		_cgBg3;		// 2プレイヤープレート
	int		_cgBg4;		// FINISH
	int		_cgBg5;		// WIN
	int		_cgBg6;		// LOSE
	int		_cgBg7;		// DRAW

	int		_bgm;		//　ゲームプレイ中に流れるBGM
};
