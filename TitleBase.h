#pragma once

// ゲームシーン基底クラス
class TitleBase
{
public:
	TitleBase() {}
	virtual ~TitleBase() {}


	virtual void init() {}
	virtual void end() {}

	virtual TitleBase* update() { return this; }
	virtual void draw() {}

};