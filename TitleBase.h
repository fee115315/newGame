#pragma once

// �Q�[���V�[�����N���X
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