#pragma once

#include "ShotBase.h"

class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos,int vect);
	// �X�V
	virtual void update();
};