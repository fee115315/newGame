#pragma once

#include "TitleBase.h"

class Manager
{
public:
	// シーンの種類定義
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
