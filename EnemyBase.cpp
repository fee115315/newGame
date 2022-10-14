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
	//ìGÇÃèâä˙âª
	m_pos.x = 400;		//ìGÇÃxç¿ïW
	m_pos.y = 80;		//ìGÇÃyç¿ïW

	m_vec.x = 0.0f;		//ìGÇÃxç¿ïWÇÃà⁄ìÆÇÃëÂÇ´Ç≥
	m_vec.y = 0.0f;		//ìGÇÃyç¿ïWÇÃà⁄ìÆÇÃëÂÇ´Ç≥

	m_inCount = 240;	//âΩïbë“Ç¬Ç©(60Ç≈1ïbë“Ç¬)

	m_isExist = false;	//ìGÇ™ë∂ç›ÇµÇƒÇ¢ÇÈÇ©
}

void EnemyBase::update()
{
	//3ïbë“Ç¬
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//à⁄ìÆÇÃé¿çs
	m_pos += m_vec;

	//âÊñ ì‡Ç…ì¸Ç¡ÇΩÇÁtrue
	if (m_pos.y > 0 || m_pos.y < Game::kScreenHeight ||
		m_pos.x > 0 || m_pos.x < Game::kScreenWidth)
	{
		m_isExist = true;
	}
	//âÊñ äOÇ…èoÇΩÇÁfalse
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}

void EnemyBase::draw()
{
	//falseÇ»ÇÁé¿çsÇµÇ»Ç¢
	if (!m_isExist)return;
	//ï\é¶
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}