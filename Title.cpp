#include "Title.h"
#include "DxLib.h"
#include "SceneMain.h"

void Title::init()
{
	m_isEnd = false;
	m_handle = LoadGraph("data/yonen.png");
	x = 0;
	y = 0;
}

TitleBase* Title::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//ゲームスタート
	if (padState & PAD_INPUT_1)
	{
		return(new SceneMain);
	}
	return this;
}

void Title::draw()
{
	DrawGraph(x, y, m_handle, false);
	DrawString(280, 250, "大原ウォーズ", GetColor(255, 255, 122));
	DrawString(0, 0, "ゲームスタート->Zボタン", GetColor(0, 0, 0));
}