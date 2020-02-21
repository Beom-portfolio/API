#include "StdAfx.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "MyMenu.h"
#include "SelectPlayer.h"
#include "Stage.h"
#include "MyEdit.h"
#include "Boss.h"

INIT_SINGLETON(CSceneMgr);

CSceneMgr::CSceneMgr(void)
:m_pScene(NULL)
{
}

CSceneMgr::~CSceneMgr(void)
{
	Release();
}

void CSceneMgr::Initialize(void)
{

}

int CSceneMgr::Update(void)
{
	if(m_pScene)
		m_pScene->Update();

	return 0;
}

void CSceneMgr::Render(HDC _hdc)
{
	if(m_pScene)
		m_pScene->Render(_hdc);
}

void CSceneMgr::Release(void)
{

}

void CSceneMgr::SetScene(eSceneState eState)
{
	//현재 내 씬을 삭제한다.
	SAFE_DELETE(m_pScene);

	switch(eState)
	{
	case SCENE_LOGO:
		break;

	case SCENE_MENU:
		m_pScene = new CMyMenu;
		break;

	case SCENE_SELECT_PLAYER:
		m_pScene = new CSelectPlayer;
		break;

	case SCENE_STAGE:
		m_pScene = new CStage;
		break;

	case SCENE_EDIT:
		m_pScene = new CMyEdit;
		break;
	}

	m_pScene->Initialize();
}