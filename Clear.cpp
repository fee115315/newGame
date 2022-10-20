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
	//ボタンを押して終了
	if (padState & PAD_INPUT_2)
	{
		DxLib_End();
	}
	return this;
}

void Clear::draw()
{
	DrawGraph(x, y, m_handle, false);
	DrawString(150, m_textPosY, "おめでとう！上手だね君！", GetColor(200, 200, 255));
	DrawString(0, 0, "Xボタンで終了", GetColor(0, 0, 0));
}