#include "StdAfx.h"
#include "MainGame.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "Factory.h"
#include "Player.h"
#include "Stage.h"

//������ extern���� ����.
int		m_iCoin = 0;

CMainGame::CMainGame(void)
{
	//##����
	CSoundMgr::GetInstance()->LoadSoundFile();

	//#ifndef _DEBUG_CHECK_
	AllocConsole(); 
	freopen( "CONOUT$",  "wt", stdout);
	SetConsoleTitleA("Debug");
	//#endif
}

CMainGame::~CMainGame(void)
{
	Release();
	//#ifndef _DEBUG_CHECK_
	FreeConsole();
	//#endif
}

void CMainGame::Initialize(void)
{
	m_hdc = GetDC(g_hWnd);

	CSceneMgr::GetInstance()->Initialize();
	CSceneMgr::GetInstance()->SetScene(SCENE_MENU);
	//CSceneMgr::GetInstance()->SetScene(SCENE_STAGE);
}

int CMainGame::Update(void)
{
	CSceneMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->SetKeyState();


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

	//##����
	CSoundMgr::GetInstance()->Destroy();

	CKeyMgr::GetInstance()->DestroyInstance();
}

