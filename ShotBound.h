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
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

private:
};