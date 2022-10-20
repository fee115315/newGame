#include "Title.h"
#include "End.h"
#include "DxLib.h"
#include "SceneMain.h"

void End::init()
{
	m_isEnd = false;
	m_handle = LoadGraph("data/nisi.png");
	x = 0;
	y = 0;
}

TitleBase* End::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//ボタンを押して終了
	if (padState & PAD_INPUT_2)
	{
		DxLib_End();
	}
	return this;
}

void End::draw()
{
	DrawGraph(x, y, m_handle, false);
	DrawString(150, m_textPosY, "まだまだ甘いね", GetColor(200, 200, 255));
	DrawString(0, 0, "Xボタンで終了", GetColor(200, 200, 255));
}