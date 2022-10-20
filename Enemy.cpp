#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "SceneMain.h"


namespace
{
	constexpr float kSizeX = 20.0f;
	constexpr float kSizeY = 89.0f;
	//�L�����̑��x
	constexpr float kSpeedX = 1.4f;
	//�V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 6.0f;
	//�����Ԋu
	constexpr int kMoveTime = 50;
}

void Enemy::init()
{
	//�G�̏�����
	m_pos.x = 570;			//�G��x���W
	m_pos.y = 20;				//�G��y���W

	m_vec.x = kSpeedX;		//�G��x���W�̈ړ��̑傫�� 

	m_inCount = 30;			//���b�҂�(60��1�b�҂�)

	m_isExist = false;			//�G�����݂��Ă��邩

	m_shotInterval = 160;     //�e��ł܂ł̊Ԋu

	m_waitFrame = kMoveTime;
}

void Enemy::update()
{

	int randShot = GetRand(99);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	

	//�V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (randShot > 50)
		{
			if (m_pMain->createShotFall(getPos(), -1))
			{
				m_shotInterval = kShotInterval;
			}
		}
		else if (randShot > 20)
		{
			if (m_pMain->createShotNormal(getPos(),-1))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	//���E�ɓ�����ƈ�莞�ԓ������~�܂�
	if (m_waitFrame > 1)
	{
		m_waitFrame--;
		return;
	}

	//���E�̒[�ɕt���Ƃ܂������o��
	if (m_pos.x < 0)
	{
		m_vec.x *= -1;
		m_waitFrame = kMoveTime;
	}
	if (m_pos.x > Game::kScreenWidth - kEnemyGraphicSizeX)
	{
		m_vec.x *= -1;
		m_waitFrame = kMoveTime;
	}

	m_pos.x += m_vec.x;


	//�w�萔�b�҂�
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//���E�ړ�
	if (m_pos.x + m_Graphsize.x > Game::kScreenWidth)
	{
		m_vec.x = 0;
		m_pos.x = Game::kScreenWidth - m_Graphsize.x;
	}
	if (m_pos.x < 0)
	{
		m_pos.x = 0;
		m_vec.x = 0;
	}
	if (m_pos.y + m_Graphsize.y > Game::kScreenHeight)
	{
		m_vec.y = 0;
		m_pos.y = Game::kScreenHeight - m_Graphsize.y;
	}
	if (m_pos.y < 0)
	{
		m_pos.y = 0;
		m_vec.y = 0;
	}

	m_pos += m_vec;


	//��ʓ��ɓ�������true
	if (m_pos.y > 0 || m_pos.y < Game::kScreenHeight ||
		m_pos.x > 0 || m_pos.x < Game::kScreenWidth)
	{
		m_isExist = true;
	}
	//��ʊO�ɏo����false
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

void Enemy::draw()
{
	//false�Ȃ���s���Ȃ�
	if (!m_isExist)return;
	//�\��
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}


