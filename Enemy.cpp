#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "SceneMain.h"
//a

namespace
{
	//キャラの速度
	constexpr float kEnemySpeedX = -1.0f;
	constexpr float kEnemySpeedY = 0.0f;
	//ショットの発射間隔
	constexpr float kShotInterval = 8.0f;
	//動く間隔
	constexpr int kMoveTime = 180;
}

void Enemy::init()
{
	//敵の初期化
	m_pos.x = 500;			//敵のx座標
	m_pos.y = 200;				//敵のy座標

	m_vec.x = kEnemySpeedX;		//敵のx座標の移動の大きさ
	m_vec.y = kEnemySpeedY;		//敵のy座標の移動の大きさ

	m_inCount = 20;			//何秒待つか(60で1秒待つ)

	m_isExist = false;			//敵が存在しているか

	m_shotInterval = 240;

	m_waitFrame = kMoveTime;
}

void Enemy::update()
{

	int randShot = GetRand(99);
	int randMove = GetRand(99);

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理
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
		/*else
		{
			if (m_pMain->createShotFall(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}*/
	}

	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}


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

	if (randMove > 50)
	{

	}

	else if (randMove > 20)
	{

	}

	m_pos.x += m_vec.x;


	//指定数秒待つ
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//移動の実行
	m_pos += m_vec;

	if (m_pos.x < Game::kScreenWidth / 0.1)
	

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


