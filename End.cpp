#include "Title.h"
#include "End.h"
#include "DxLib.h"
#include "SceneMain.h"

void End::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

TitleBase* End::update()
{

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if (padState & PAD_INPUT_3)
	{
		DxLib_End();
	}
	return this;
}

void End::draw()
{
	DrawString(0, m_textPosY, "�G���h���", GetColor(255, 255, 255));
}