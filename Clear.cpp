#include "Title.h"
#include "Clear.h"
#include "DxLib.h"
#include "SceneMain.h"

void Clear::init()
{
	m_isEnd = false;
	m_handle = LoadGraph("data/nisisi.png");
	x = 0;
	y = 0;
}

TitleBase* Clear::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//�{�^���������ďI��
	if (padState & PAD_INPUT_2)
	{
		DxLib_End();
	}
	return this;
}

void Clear::draw()
{
	DrawGraph(x, y, m_handle, false);
	DrawString(150, m_textPosY, "���߂łƂ��I��肾�ˌN�I", GetColor(200, 200, 255));
	DrawString(0, 0, "X�{�^���ŏI��", GetColor(0, 0, 0));
}