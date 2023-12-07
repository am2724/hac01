#pragma once	// .hの先頭に記述。#includeでこのファイルを何度読み込みしても、1度しか読み込まない
#include "SceneBase.h"


class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();			// コンストラクタ
	virtual ~SceneGameTitle();	// デストラクタ

	void	Input() override;	// 入力
	void	Process() override;	// 計算
	void	Draw() override;	// 描画

protected:
	int		_cgBg;		// 背景画像
	int		_cgBg1;		// Bボタンで説明へ
	int		_cgBg2;		// Aボタンでタイトルへ
	int		_bgm;
};

