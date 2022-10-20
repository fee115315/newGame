#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>
#include "SceneMain.h"


namespace
{
	constexpr float kSizeX = 20.0f;
	constexpr float kSizeY = 89.0f;
	//キャラの速度
	constexpr float kSpeedX = 1.4f;
	//ショットの発射間隔
	constexpr float kShotInterval = 6.0f;
	//動く間隔
	constexpr int kMoveTime = 50;
}

void Enemy::init()
{
	//敵の初期化
	m_pos.x = 570;			//敵のx座標
	m_pos.y = 20;				//敵のy座標

	m_vec.x = kSpeedX;		//敵のx座標の移動の大きさ 

	m_inCount = 30;			//何秒待つか(60で1秒待つ)

	m_isExist = false;			//敵が存在しているか

	m_shotInterval = 160;     //弾を打つまでの間隔

	m_waitFrame = kMoveTime;
}

void Enemy::update()
{

	int randShot = GetRand(99);

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	

	//ショットを撃つ処理
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

	//左右に当たると一定時間動きが止まる
	if (m_waitFrame > 1)
	{
		m_waitFrame--;
		return;
	}

	//左右の端に付くとまた動き出す
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


	//指定数秒待つ
	if (m_inCount > 0)
	{
		m_inCount--;
		return;
	}

	//左右移動
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

void Enemy::draw()
{
	//falseなら実行しない
	if (!m_isExist)return;
	//表示
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}


