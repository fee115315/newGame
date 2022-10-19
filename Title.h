#pragma once

#include "TitleBase.h"

class Title : public TitleBase
{
public:
	Title()
	{
		m_textPosY = 0;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~Title() {}


	virtual void init() override;
	virtual void end()override {}

	virtual TitleBase* update()override;
	virtual void draw()override;

private:
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;

	bool m_isEnd;

	int m_handle;
	//座標
	double x, y;
};