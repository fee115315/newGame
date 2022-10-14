#pragma once

#include "Vec2.h"

class SceneMain;

class EnemyBase
{
public:
	// 敵グラフィックサイズ
	static constexpr int kEnemyGraphicSizeX = 64;
	static constexpr int kEnemyGraphicSizeY = 80;
public:
	EnemyBase();
	virtual ~EnemyBase();

	void setHandle(int handle) { m_handle = handle; }

	//初期化
	virtual void init();
	// 更新
	virtual void update();
	// 表示
	virtual void draw();
	//存在するか
	bool isExist() const { return m_isExist; }
	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// 情報の取得
	Vec2 getPos() const { return m_pos; }

protected:
	// グラフィックハンドル
	int m_handle;
	//何秒で画面に入ってくるか
	int m_inCount;
	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;
	//SceneMainのポインタ
	SceneMain* m_pMain;
	//存在するか
	bool    m_isExist;
	//次弾の間隔
	int m_shotInterval;
	int m_waitFrame;
};

