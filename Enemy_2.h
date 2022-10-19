#pragma once

#include "EnemyBase.h"

class Enemy_2 : public EnemyBase
{
public:
	Enemy_2()
	{

	}
	virtual ~Enemy_2()
	{

	}
	//初期化
	virtual void init();
	//更新
	virtual void update();
	//敵の弾のハンドルの設定
	void setShotHandle(int handle) { m_shotHandle = handle; }
	void draw();

private:
	//弾のハンドル
	int m_shotHandle;
	Vec2 m_basePos;
	float m_sinRate;
	Vec2 m_Graphsize;
};