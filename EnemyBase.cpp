#include "EnemyBase.h"
#include "DxLib.h"
#include "game.h"


EnemyBase::EnemyBase()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::init()
{
	//�G�̏�����
	m_pos.x = 400;		//�G��x���W
	m_pos.y = 80;		//�G��y���W

	m_vec.x = 0.0f;		//�G��x���W�̈ړ��̑傫��
	m_vec.y = 0.0f;		//�G��y���W�̈ړ��̑傫��

	m_inCount = 240;	//���b�҂�(60��1�b�҂�)

	m_isExist = false;	//�G�����݂��Ă��邩
}

void EnemyBase::update()
{
	//3�b�҂�
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//�ړ��̎��s
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

void EnemyBase::draw()
{
	//false�Ȃ���s���Ȃ�
	if (!m_isExist)return;
	//�\��
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}