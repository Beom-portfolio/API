#include "StdAfx.h"
#include "MyMenu.h"
#include "SceneMgr.h"
#include "BitBmp.h"
//#include "MyButton.h"
#include "ObjMgr.h"
#include "GameObject.h"

CMyMenu::CMyMenu(void)
{
}

CMyMenu::~CMyMenu(void)
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CGameObject::SetBitBmp(&m_mapBmp);

	//맨 처음 시작시 동전을 0개 상태로 놓음.
	if(m_iCoin == 0)
		m_iCoin = 0;

	//////////////////// 이미지 로드 /////////////////////////

	m_mapBmp.insert( make_pair("BACKGROUND",
		(new CBitBmp)->LoadBmp(L"../Sprite/MyMenu/BackGround.bmp") ) );

	m_mapBmp.insert( make_pair("BACKBUFFER",
		(new CBitBmp)->LoadBmp(L"../Sprite/MyMenu/BackBuffer.bmp") ) );

	m_mapBmp.insert( make_pair("COIN_NUM_TEN",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_ONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	////깜빡이는 시간
	m_TimeCount = GetTickCount();
	//깜빡이는 시간 체크
	m_iDrawID_Menu = 0;

	////코인입력 지연시간
	m_TimeCoin = GetTickCount();
	
	//////////////////// 객체 생성 //////////////////////////
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("START", 200, 500, 150, 150)), OBJ_UI);
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("EDIT", 400, 500, 150, 150)), OBJ_UI);
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("EXIT", 600, 500, 150, 150)), OBJ_UI);
}

int CMyMenu::Update(void)
{
	if(m_TimeCoin + 100 <= GetTickCount())
	{
		if(GetAsyncKeyState('5'))
		{
			m_iCoin += 1;
			m_TimeCoin = GetTickCount();
		}
	}
	
	if(m_TimeCount + 1000 <= GetTickCount())
	{
		if(m_iDrawID_Menu == 1)	
			m_iDrawID_Menu = 0;
		else
			m_iDrawID_Menu = 1;

		m_TimeCount = GetTickCount();
	}



	CObjMgr::GetInstance()->Update();



	if(GetAsyncKeyState('1') || GetAsyncKeyState('2'))
	{
		m_iCoin -= 1;
		CSceneMgr::GetInstance()->SetScene(SCENE_SELECT_PLAYER);
	}

	return 0;
}

void CMyMenu::Render(HDC _hdc)
{
	//궁금한 부분 (더블 버퍼링)

	if(m_iDrawID_Menu == 1)
	{
		BitBlt(_hdc
			,0				//그려질 위치 X
			,0				//그려질 위치 Y
			,iWINCX			//그려질 크기 X
			,iWINCY			//그려질 크기 Y
			,m_mapBmp["BACKGROUND"]->GetMemDC()
			,0							//이미지에서의 시작 위치 X
			,0							//이미지에서의 시작 위치 Y
			,SRCCOPY);					//메뉴 깜빡임 출력함.
	}
	//CObjMgr::GetInstance()->Render(m_mapBmp["BACKGROUND"]->GetMemDC());
	else if(m_iDrawID_Menu == 0)
	{
		BitBlt(_hdc
			,0					
			,0					
			,iWINCX		
			,iWINCY		
			,m_mapBmp["BACKBUFFER"]->GetMemDC()	
			,0		
			,0		
			,SRCCOPY);
	}

	//코인 10의 자리수
		TransparentBlt(_hdc
		,712
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_TEN"]->GetMemDC()
		,11 * (m_iCoin / 10)
		,0
		,11 		
		,8
		,RGB(255, 0, 255)	);

	//코인 1의 자리수
	TransparentBlt(_hdc
		,737
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_ONE"]->GetMemDC()
		,11 * (m_iCoin % 10)
		,0
		,11
		,8
		,RGB(255, 0, 255)	);

}

void CMyMenu::Release(void)
{
	
}
