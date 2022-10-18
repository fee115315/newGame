#include "ShotP.h"
#include "game.h"
#include "DxLib.h"

void ShotP::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 50;
	m_vec.y = 0;
}

void ShotP::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}

void ShotP::draw()
{
	if (!m_isExist)return;
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}