#include "DxLib.h"
#include "SceneMain.h"
#include "ShotBound.h"
#include "ShotNormal.h"
#include "ShotFall.h"
#include "ShotP.h"
#include "Back.h"
#include "Enemy.h"
#include "EnemyBase.h"

#include <cassert>


namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
	// �v���C���[�̃T�C�Y
	constexpr int kPlayerGraphicSizeX = 32;
	constexpr int kPlayerGraphicSizeY = 32;
	// �V���b�g�̃T�C�Y
	constexpr int kShotGraphicSizeX = 16.0f;
	constexpr int kShotGraphicSizeY = 16.0f;
}

SceneMain::SceneMain()
{
	m_hPlayerGraphic = -1;
	m_hShotGraphic = -1;
	m_hTestSound = -1;
	m_hbackGraphic = -1;
}
SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	//�O���t�B�b�N�̃��[�h
	m_hPlayerGraphic = LoadGraph("data/player.bmp");
	//�w�i�̃��[�h
	m_hbackGraphic = LoadGraph("data/ino.png");
	m_back.setHandle(m_hbackGraphic);
	//�G�̃��[�h
	m_hEnemyGraphic = LoadGraph("data/ana.png");
	m_enemy.setHandle(m_hEnemyGraphic);
	//�G�̒e�̃��[�h
	m_hShotEnemyGraphic = LoadGraph("data/shot.bmp");
	m_enemy.setShotHandle(m_hShotEnemyGraphic);
	//�e�̃��[�h
	m_hShotGraphic = LoadGraph("data/shot.bmp");
	//�T�E���h�̃��[�h
	LoadSoundMem("music/cursor7.mp3");

	m_player.setHandle(m_hPlayerGraphic);
	m_player.init();
	m_player.setMain(this);
	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

// �I������
void SceneMain::end()
{
	//�O���t�B�b�N�A�����[�h
	DeleteGraph(m_hPlayerGraphic);
	DeleteGraph(m_hShotGraphic);
	DeleteGraph(m_hbackGraphic);
	DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotEnemyGraphic);
	//�T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);

		delete pShot;
		pShot = nullptr;
	}
}

// ���t���[���̏���
void SceneMain::update()
{
	if (Collision_Detection())
	{
		DxLib_End();
	}
	int padstate = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padstate & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}

	
	m_player.update();
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);

		if (!pShot)		//null�̏ꍇ�������Ȃ�
		{
			it++;
			continue;
		}

		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}
	m_back.update();
	
}

// ���t���[���̕`��
void SceneMain::draw()
{
	m_back.draw();
	m_player.draw();
	m_enemy.draw();

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}

	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
}

bool SceneMain::createShotNormal(Vec2 pos,int vect)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos,vect);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotFall(Vec2 pos)
{
	ShotFall* pShot = new ShotFall;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotBound(Vec2 pos)
{
	ShotBound* pShot = new ShotBound;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::createShotP(Vec2 pos)
{
	ShotP* pShot = new ShotP;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	return true;
}

bool SceneMain::Collision_Detection()
{
	m_player.getPos();
	m_enemy.getPos();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->getPos();

		float shotLeft = pShot->getPos().x;
		float shotRight = pShot->getPos().x + kShotGraphicSizeX;
		float shotTop = pShot->getPos().y;
		float shotBottom = pShot->getPos().y + kShotGraphicSizeY;

		float playerLeft = m_player.getPos().x + 10;
		float playerRight = m_player.getPos().x + kPlayerGraphicSizeX - 10;
		float playerTop = m_player.getPos().y + 10;
		float playerBottom = m_player.getPos().y + kPlayerGraphicSizeY - 10;

		if (playerLeft > shotRight)
		{
			it++;
			continue;
		}
		if (playerRight < shotLeft)
		{
			it++;
			continue;
		}
		if (playerTop > shotBottom)
		{
			it++;
			continue;
		}
		if (playerBottom < shotTop)
		{
			it++;
			continue;
		}
		return true;
	}
	return false;
}