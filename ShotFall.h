#pragma once

#include "ShotBase.h"

class ShotFall : public ShotBase
{
public:
	ShotFall()
	{
	}
	virtual ~ShotFall()
	{
	}

	//�V���b�g�J�n
	virtual void start(Vec2 pos,int vect);
	// �X�V
	virtual void update();
};