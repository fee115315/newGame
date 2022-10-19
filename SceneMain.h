#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "EnemyBase.h"
#include "Enemy.h"
#include "Enemy_2.h"
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
	bool createShotNormal(Vec2 pos,int vect);
	bool createShotFall(Vec2 pos, int vect);
	bool createShotBound(Vec2 pos, int vect);
	bool createShotP(Vec2 pos);
	// 当たり判定
	virtual bool Col_Shot();
	virtual bool Col_Enemy();
	virtual bool Col_Enemy2();

private:

	//グラフィックハンドル
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	int m_hbackGraphic;
	//背景
	Back m_back;
	// プレイヤー
	Player m_player;
	// ショット
	std::vector<ShotBase*> m_pShotVt;
	//敵のハンドル
	int m_hEnemyGraphic;
	//敵のハンドル2
	int m_hEnemyGraphic2;
	//敵の弾
	int m_hShotEnemyGraphic;
	//敵の弾2
	int m_hShotEnemyGraphic2;
	//playerのライフ
	int m_life;
	//無敵判定
	int m_hitInvi;   
	//敵
	Enemy m_enemy;
	//敵2
	Enemy_2 m_enemy2;

	int m_hTestSound;

	bool m_isEnd;
};