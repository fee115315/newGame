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
	//������
	virtual void init();
	//�X�V
	virtual void update();
	//�G�̒e�̃n���h���̐ݒ�
	void setShotHandle(int handle) { m_shotHandle = handle; }

private:
	//�e�̃n���h��
	int m_shotHandle;
};