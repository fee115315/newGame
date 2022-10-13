#pragma once

#include "Vec2.h"

class Back
{
public:
	Back();
	virtual ~Back();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }
	// �}�b�v�̏�����
	void init();
	// ����
	void update();
	// �`��
	void draw();

private:
	//�摜�̃n���h��
	int m_handle;
	//�摜�̃T�C�Y
	Vec2 m_backSize;
	// �\���ʒu
	Vec2 m_pos;
};