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

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
};