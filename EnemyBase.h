#pragma once

#include "Vec2.h"

class EnemyBase
{
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

	
protected:
	// グラフィックハンドル
	int m_handle;
	//何秒で画面に入ってくるか
	int m_inCount;
	// 表示位置
	Vec2	m_pos;
	// 移動
	Vec2	m_vec;
	//存在するか
	bool    m_isExist;
};

