#pragma once

#include "EnemyBase.h"

class Enemy : public EnemyBase
{
public:
	Enemy()
	{

	}
	virtual ~Enemy()
	{

	}
	//初期化
	virtual void init();
	//更新
	virtual void update();
	//敵の弾のハンドルの設定
	void setShotHandle(int handle) { m_shotHandle = handle; }

private:
	//弾のハンドル
	int m_shotHandle;
};