#pragma once

#include "Vec2.h"

class SceneMain;

class EnemyBase
{
public:
	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = 64;
	static constexpr int kEnemyGraphicSizeY = 80;
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
	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }
	// ���̎擾
	Vec2 getPos() const { return m_pos; }

protected:
	// �O���t�B�b�N�n���h��
	int m_handle;
	//���b�ŉ�ʂɓ����Ă��邩
	int m_inCount;
	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
	//SceneMain�̃|�C���^
	SceneMain* m_pMain;
	//���݂��邩
	bool    m_isExist;
	//���e�̊Ԋu
	int m_shotInterval;
	int m_waitFrame;
};

