#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "EnemyBase.h"
#include "Enemy.h"
#include "Enemy_2.h"
#include "Back.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	void init();
	// �I������
	void end();

	// ���t���[���̏���
	void update();
	// ���t���[���̕`��
	void draw();

	//�e�̐���
	bool createShotNormal(Vec2 pos,int vect);
	bool createShotFall(Vec2 pos, int vect);
	bool createShotBound(Vec2 pos, int vect);
	bool createShotP(Vec2 pos);
	// �����蔻��
	virtual bool Col_Shot();
	virtual bool Col_Enemy();
	virtual bool Col_Enemy2();

private:

	//�O���t�B�b�N�n���h��
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	int m_hbackGraphic;
	//�w�i
	Back m_back;
	// �v���C���[
	Player m_player;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;
	//�G�̃n���h��
	int m_hEnemyGraphic;
	//�G�̃n���h��2
	int m_hEnemyGraphic2;
	//�G�̒e
	int m_hShotEnemyGraphic;
	//�G�̒e2
	int m_hShotEnemyGraphic2;
	//player�̃��C�t
	int m_life;
	//���G����
	int m_hitInvi;   
	//�G
	Enemy m_enemy;
	//�G2
	Enemy_2 m_enemy2;

	int m_hTestSound;

	bool m_isEnd;
};