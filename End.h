#pragma once

#include "TitleBase.h"

class End : public TitleBase
{
public:
	End()
	{
		m_textPosY = 350;
		m_textVecY = 0;
		m_isEnd = false;
	}
	virtual ~End() {}


	virtual void init()override;
	virtual void end()override {}

	virtual TitleBase* update()override;
	virtual void draw()override;

private:
	// テキスト表示位置変更
	int m_textPosY;
	int m_textVecY;
	int m_handle;
	bool m_isEnd;

	double x, y;
};
