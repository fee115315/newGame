#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "EnemyBase.h"
#include "Enemy.h"
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
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

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
	//�G�̒e
	int m_hShotEnemyGraphic;
	//�G
	Enemy m_enemy;

	int m_hTestSound;
};