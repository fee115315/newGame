#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "Back.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void init();
	// 終了処理
	void end();

	// 毎フレームの処理
	void update();
	// 毎フレームの描画
	void draw();

	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	int m_hbackGraphic;
	//背景
	Back m_back;
	// プレイヤー
	Player m_player;
	// ショット
	std::vector<ShotBase*> m_pShotVt;

	int m_hTestSound;
};