#include "Manager.h"
#include <cassert>

#include "Title.h"
#include "SceneMain.h"
#include "End.h"


Manager::Manager()
{
	m_pScene = nullptr;
}
Manager::~Manager()
{

}

void Manager::init(SceneKind kind)
{
	m_kind = kind;
	switch (m_kind)
	{
	case Manager::kSceneKindTitle:
		m_pScene = new Title;
		break;
	case Manager::kSceneKindMain:
		m_pScene = new SceneMain;
		break;
	case Manager::kSceneKindNum:
		m_pScene = new End;
		break;
	default:
		assert(false);
		break;
	}
	m_pScene->init();
}

void Manager::end()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
	delete m_pScene;
}

void Manager::update()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	TitleBase* pScene = m_pScene->update();
	if (pScene != m_pScene)
	{
		//前のシーンの終了処理
		m_pScene->end();
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->init();
	}
}


void Manager::draw()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->draw();
}