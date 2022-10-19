#include "DxLib.h"
#include "game.h"
#include "player.h"

#include "SceneMain.h"

namespace
{
	// X方向、Y方向の最大速度
	constexpr float kSpeedMax = 8.0f;
	constexpr float kAcc = 0.4f;
	//ショットの発射間隔
	constexpr float kShotInterval = 16;
}

Player::Player()
{
	m_handle = -1;
	m_pMain = nullptr;
	m_shotInterval = 0;
}

Player::~Player()
{
	
}

void Player::init()
{
	m_pos.x = Game::kScreenWidth /6 - kPlayerGraphicSizeX/6 ;
	m_pos.y = Game::kScreenHeight - kPlayerGraphicSizeY - 250;
	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
	m_shotInterval = 8;
	GetGraphSizeF(m_handle, &m_Graphsize.x, &m_Graphsize.y);
}

void Player::update()
{
	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotP(getPos()))
			{
				m_shotInterval = kShotInterval;
			}
		}
	}

	
	//キャラの移動
	if (padState & PAD_INPUT_UP)
	{
		m_vec.y -= kAcc;
		if (m_vec.y < -kSpeedMax)	m_vec.y = -kSpeedMax;
	}
	else if (padState & PAD_INPUT_DOWN)
	{
		m_vec.y += kAcc;
		if (m_vec.y > kSpeedMax)	m_vec.y = kSpeedMax;
	}
	else
	{
		m_vec.y *= 0.9f;
	}
		if (m_pos.x + m_Graphsize.x > Game::kScreenWidth)
		{
			m_vec.x = 0;
			m_pos.x = Game::kScreenWidth - m_Graphsize.x;
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
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
			m_vec.x = 0;
		}

	if (padState & PAD_INPUT_LEFT)
	{
		m_vec.x -= kAcc;
		if (m_vec.x < -kSpeedMax)	m_vec.x = -kSpeedMax;
	}
	else if (padState & PAD_INPUT_RIGHT)
	{
		m_vec.x += kAcc;
		if (m_vec.x > kSpeedMax)	m_vec.x = kSpeedMax;
	}
	else
	{
		m_vec.x *= 0.9f;
	}

		if (m_pos.x + m_Graphsize.x > Game::kScreenWidth)
		{
			m_vec.x = 0;
			m_pos.x = Game::kScreenWidth - m_Graphsize.x;
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
		if (m_pos.x < 0)
		{
			m_pos.x = 0;
			m_vec.x = 0;
		}
		
	m_pos += m_vec;

	
	
	

}

void Player::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}