#include "Enemy.h"
#include "game.h"

namespace
{
	constexpr float kEnemySpeedX = -2.0f;
	constexpr float kEnemySpeedY = 0.0f;
}

void Enemy::init()
{
	//�G�̏�����
	m_pos.x = 500;				//�G��x���W
	m_pos.y = 130;				//�G��y���W

	m_vec.x = kEnemySpeedX;		//�G��x���W�̈ړ��̑傫��
	m_vec.y = kEnemySpeedY;		//�G��y���W�̈ړ��̑傫��

	m_inCount = 240;			//���b�҂�(60��1�b�҂�)

	m_isExist = false;			//�G�����݂��Ă��邩
}

void Enemy::update()
{
	//3�b�҂�
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//�ړ��̎��s
	m_pos += m_vec;

	if (m_pos.x < Game::kScreenWidth / 1.5)
	{
		m_vec.x = 0.0f;
	}

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