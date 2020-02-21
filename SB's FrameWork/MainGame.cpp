#include "StdAfx.h"
#include "MainGame.h"
#include "SceneMgr.h"

//코인을 extern으로 놓음.
int		m_iCoin = 0;

CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);

	CSceneMgr::GetInstance()->Initialize();
	CSceneMgr::GetInstance()->SetScene(SCENE_MENU);
}

int CMainGame::Update(void)
{
	CSceneMgr::GetInstance()->Update();

	return 0;
}

void CMainGame::Render(void)
{
	//Rectangle(m_hdc, 0, 0, iWINCX, iWINCY);
	CSceneMgr::GetInstance()->Render(m_hdc);

}

void CMainGame::Release(void)
{
	CSceneMgr::GetInstance()->DestroyInstance();

	ReleaseDC(g_hWnd, m_hdc);
}
