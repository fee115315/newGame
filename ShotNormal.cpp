#include "ShotNormal.h"
#include "game.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotNormal::start(Vec2 pos,int vect)
{
	ShotBase::start(pos);

	m_vec.x = kShotSpeed * vect;
	m_vec.y = 1.4f;
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.x > Game::kScreenWidth)
	{
		m_isExist = false;
	}
}