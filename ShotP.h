#pragma once

#include "ShotBase.h"

class ShotP : public ShotBase
{
public:
	ShotP()
	{
	}
	virtual ~ShotP()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
};