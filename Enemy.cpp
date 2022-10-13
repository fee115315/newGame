#include "Enemy.h"
#include "game.h"

namespace
{
	constexpr float kEnemySpeedX = -2.0f;
	constexpr float kEnemySpeedY = 0.0f;
}

void Enemy::init()
{
	//敵の初期化
	m_pos.x = 500;				//敵のx座標
	m_pos.y = 130;				//敵のy座標

	m_vec.x = kEnemySpeedX;		//敵のx座標の移動の大きさ
	m_vec.y = kEnemySpeedY;		//敵のy座標の移動の大きさ

	m_inCount = 240;			//何秒待つか(60で1秒待つ)

	m_isExist = false;			//敵が存在しているか
}

void Enemy::update()
{
	//3秒待つ
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//移動の実行
	m_pos += m_vec;

	if (m_pos.x < Game::kScreenWidth / 1.5)
	{
		m_vec.x = 0.0f;
	}

	//画面内に入ったらtrue
	if (m_pos.y > 0 || m_pos.y < Game::kScreenHeight ||
		m_pos.x > 0 || m_pos.x < Game::kScreenWidth)
	{
		m_isExist = true;
	}
	//画面外に出たらfalse
	if (m_pos.y < 0 || m_pos.y > Game::kScreenHeight ||
		m_pos.x < 0 || m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}