#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
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
	bool createShotNormal(Vec2 pos);
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic;
	int m_hShotGraphic;
	int m_hbackGraphic;
	//�w�i
	Back m_back;
	// �v���C���[
	Player m_player;
	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;

	int m_hTestSound;
};