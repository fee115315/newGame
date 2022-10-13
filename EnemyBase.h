#pragma once

#include "Vec2.h"

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	void setHandle(int handle) { m_handle = handle; }

	//������
	virtual void init();
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();
	//���݂��邩
	bool isExist() const { return m_isExist; }

	
protected:
	// �O���t�B�b�N�n���h��
	int m_handle;
	//���b�ŉ�ʂɓ����Ă��邩
	int m_inCount;
	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
	//���݂��邩
	bool    m_isExist;
};

