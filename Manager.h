#pragma once

#include "TitleBase.h"

class Manager
{
public:
	// �V�[���̎�ޒ�`
	typedef enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindMain,
		kSceneKindMy,

		kSceneKindNum
	}SceneKind;

public:
	Manager();
	virtual ~Manager();

	void init(SceneKind kind = kSceneKindTitle);
	void end();

	void update();
	void draw();


private:
	SceneKind	m_kind;

	TitleBase* m_pScene;
};
