#include "Title.h"
#include "DxLib.h"
#include "SceneMain.h"

void Title::init()
{
	m_isEnd = false;
	m_handle = LoadGraph("data/ana.png");
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
	DrawString(0, m_textPosY, "タイトル", GetColor(255, 255, 255));
	DrawString(0, m_textPosY + 20, "ゲームスタート->Aボタン", GetColor(255, 255, 255));
	DrawString(0, m_textPosY + 40, "オプション->STARTボタン", GetColor(255, 255, 255));
}