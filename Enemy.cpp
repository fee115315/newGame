#include "Enemy.h"
#include "game.h"

namespace
{
	constexpr float kEnemySpeedX = -2.0f;
	constexpr float kEnemySpeedY = 0.0f;
}

void Enemy::init()
{
	//“G‚Ì‰Šú‰»
	m_pos.x = 500;				//“G‚ÌxÀ•W
	m_pos.y = 130;				//“G‚ÌyÀ•W

	m_vec.x = kEnemySpeedX;		//“G‚ÌxÀ•W‚ÌˆÚ“®‚Ì‘å‚«‚³
	m_vec.y = kEnemySpeedY;		//“G‚ÌyÀ•W‚ÌˆÚ“®‚Ì‘å‚«‚³

	m_inCount = 240;			//‰½•b‘Ò‚Â‚©(60‚Å1•b‘Ò‚Â)

	m_isExist = false;			//“G‚ª‘¶İ‚µ‚Ä‚¢‚é‚©
}

void Enemy::update()
{
	//3•b‘Ò‚Â
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//ˆÚ“®‚ÌÀs
	m_pos += m_vec;

	if (m_pos.x < Game::kScreenWidth / 1.5)
	{
		m_vec.x = 0.0f;
	}

	//‰æ–Ê“à‚É“ü‚Á‚½‚çtrue
	if (m_pos.y > 0 || m_pos.y < Game::kScreenHeight ||
		m_pos.x > 0 || m_pos.x < Game::kScreenWidth)
	{
		m_isExist = true;
	}
	//‰æ–ÊŠO‚Éo‚½‚çfalse
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}