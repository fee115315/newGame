#include "EnemyBase.h"
#include "DxLib.h"
#include "game.h"


EnemyBase::EnemyBase()
{
	m_handle = -1;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::init()
{
	//敵の初期化
	m_pos.x = 400;		//敵のx座標
	m_pos.y = 80;		//敵のy座標

	m_vec.x = 0.0f;		//敵のx座標の移動の大きさ
	m_vec.y = 0.0f;		//敵のy座標の移動の大きさ

	m_inCount = 240;	//何秒待つか(60で1秒待つ)

	m_isExist = false;	//敵が存在しているか
}

void EnemyBase::update()
{
	//3秒待つ
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//移動の実行
	m_pos += m_vec;

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

void EnemyBase::draw()
{
	//falseなら実行しない
	if (!m_isExist)return;
	//表示
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}