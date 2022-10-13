#include "Back.h"
#include "DxLib.h"
#include "game.h"
#include "SceneMain.h"


Back::Back()
{
	m_handle = -1;
}

Back::~Back()
{

}

void Back::init()
{
	GetGraphSizeF(m_handle, &m_backSize.x, &m_backSize.y);

	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
}

void Back::update()
{
	m_pos.x+= 1;

	if (m_pos.x == 700)
		m_pos.x = 0;
}

void Back::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
	DrawGraphF(m_pos.x-700, m_pos.y, m_handle, true);
}