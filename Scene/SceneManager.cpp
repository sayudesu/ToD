#include "SceneManager.h"
#include <cassert>
#include "SceneBase.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "../Util/Pad.h"

SceneManager::SceneManager():
	m_pScene()
{
}
SceneManager::~SceneManager()
{

}

void SceneManager::Init()
{
	m_pScene.reset(new SceneTitle);
	m_pScene->Init();
}

void SceneManager::End()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->End();
}

void SceneManager::Update()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	Pad::update();
	SceneBase* pScene = m_pScene->Update();
	if (pScene != m_pScene.get())
	{
		// �O�̃V�[���̏I������
		m_pScene->End();

		m_pScene.reset(pScene);
		m_pScene->Init();
	}
}

void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->Draw();
}