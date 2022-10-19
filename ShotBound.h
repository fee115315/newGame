#pragma once

#include "ShotBase.h"

class ShotBound : public ShotBase
{
public:
	ShotBound()
	{
		
	}
	virtual ~ShotBound()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos, int vect);
	// 更新
	virtual void update();

private:
	////跳ね返った回数
	//int m_boundCount;
};