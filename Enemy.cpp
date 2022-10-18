#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "SceneMain.h"


namespace
{
	//�L�����̑��x
	constexpr float kEnemySpeedX = -1.0f;
	constexpr float kEnemySpeedY = 0.0f;
	//�V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 8.0f;
	//�����Ԋu
	constexpr int kMoveTime = 180;
}

void Enemy::init()
{
	//�G�̏�����
	m_pos.x = 500;			//�G��x���W
	m_pos.y = 150;				//�G��y���W

	m_vec.x = kEnemySpeedX;		//�G��x���W�̈ړ��̑傫�� 
	m_vec.y = kEnemySpeedY;		//�G��y���W�̈ړ��̑傫��

	m_inCount = 40;			//���b�҂�(60��1�b�҂�)

	m_isExist = false;			//�G�����݂��Ă��邩

	m_shotInterval = 240;

	m_waitFrame = kMoveTime;
}

void Enemy::update()
{

	int randShot = GetRand(99);
	int randMove = GetRand(99);

	// �p�b�h(�������̓L�[�{�[�h)����̓��͂��擾����
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	

	//�V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (randShot > 50)
		{
			if (m_pMain->createShotNormal(getPos(),-1))
			{
				m_shotInterval = kShotInterval;
			}
		}
		else if (randShot > 20)
		{
			if (m_pMain->createShotBound(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
		else
		{
			if (m_pMain->createShotFall(getPos(),-1))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	if (m_waitFrame > 1)
	{
		m_waitFrame--;
		return;
	}


	if (m_pos.x < 0)
	{
		m_vec.x *= -2;
		m_waitFrame = kMoveTime;
	}
	if (m_pos.x > Game::kScreenWidth - kEnemyGraphicSizeX)
	{
		m_vec.x *= -2;
		m_waitFrame = kMoveTime;
	}

	/*if (randMove > 50)
	{

	}

	else if (randMove > 20)
	{

	}*/

	m_pos.x += m_vec.x;


	//�w�萔�b�҂�
	/*if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}*/

	//�ړ��̎��s
	m_pos += m_vec;
	if (m_pos.x < 0)
	{
		m_vec.x *= -1;
	}
	if (m_pos.x > Game::kScreenWidth - kEnemyGraphicSizeX)
	{
		m_pos.x = Game::kScreenWidth - kEnemyGraphicSizeX
			;
		m_vec.x *= -1.2;
	}
	if (m_pos.y < 0)
	{
		m_vec.y *= -1;
		
	}
	if (m_pos.y > Game::kScreenHeight - kEnemyGraphicSizeY)
	{
		m_pos.y = Game::kScreenHeight - kEnemyGraphicSizeY;
		m_vec.y *= -1;

	}

	m_basePos += m_vec;
	m_sinRate += 0.08f;

	m_pos = m_basePos;
	m_pos.y += sinf(m_sinRate) * 100.0f;

	if (m_pos.x < Game::kScreenWidth / 1);

	//��ʓ��ɓ�������true
	if (m_pos.y+200 > 0 || m_pos.y < Game::kScreenHeight ||
		m_pos.x > 0 || m_pos.x < Game::kScreenWidth)
	{
		m_isExist = true;
	}
	//��ʊO�ɏo����false
	if (m_pos.y+200 < 0 || m_pos.y > Game::kScreenHeight ||
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
	DrawGraphF(m_pos.x, m_pos.y+200, m_handle, true);
}


