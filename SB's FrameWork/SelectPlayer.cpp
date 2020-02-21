#include "StdAfx.h"
#include "SelectPlayer.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "ObjMgr.h"
#include "GameObject.h"

CSelectPlayer::CSelectPlayer(void)
{
}

CSelectPlayer::~CSelectPlayer(void)
{
	Release();
}


void CSelectPlayer::Initialize(void)
{
	CGameObject::SetBitBmp(&m_mapBmp);

	//선택시	색깔
	m_iDrawID_LOGO   = 0;
	m_iDrawID_SELECT = 0;

	m_iDrawID_SELECTED = 0;

	//선택 지연
	m_LOGO_Time   = GetTickCount();
	m_SELECT_Time = GetTickCount();

	//////////////////////이미지 로드//////////////////////
	m_mapBmp.insert( make_pair("SELECTMAIN",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/1.bmp") ) );

	m_mapBmp.insert( make_pair("P1LOGO",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/P1.bmp") ) );

	/////////////////////////////////////////////////////////
	m_mapBmp.insert( make_pair("MARCO1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Marco1.bmp") ) );
	m_mapBmp.insert( make_pair("MARCO2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Marco2.bmp") ) );
//
	m_mapBmp.insert( make_pair("ERI1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Eri1.bmp") ) );
	m_mapBmp.insert( make_pair("ERI2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Eri2.bmp") ) );
//
	m_mapBmp.insert( make_pair("TARMA1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma1.bmp") ) );
	m_mapBmp.insert( make_pair("TARMA2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma2.bmp") ) );
//선택시
	m_mapBmp.insert( make_pair("TARMA3",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma3.bmp") ) );
//
	m_mapBmp.insert( make_pair("FIO1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Fio1.bmp") ) );
	m_mapBmp.insert( make_pair("FIO2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Fio2.bmp") ) );
	/////////////////////////////////////////////////////////
	
}

int  CSelectPlayer::Update(void)
{

	if(m_SELECT_Time + 200 <= GetTickCount())
	{
		if(GetAsyncKeyState(VK_LEFT))
		{
			m_iDrawID_SELECT -= 1;

			if(m_iDrawID_SELECT < 0)
			{
				m_iDrawID_SELECT = 3;
			}
		}

		if(GetAsyncKeyState(VK_RIGHT))
		{
			m_iDrawID_SELECT += 1;

			if(m_iDrawID_SELECT > 3)
			{
				m_iDrawID_SELECT = 0;
			}
		}

		if(GetAsyncKeyState(VK_RETURN))
		{
			m_iDrawID_LOGO = 1;
			m_iDrawID_SELECTED = 1;

			//음악 파일 재생(Tarma)
			m_SELECTED_Time = GetTickCount();
		}

		m_SELECT_Time = GetTickCount();
	}

	//캐릭터(Tarma) 선택시 
	if(m_SELECTED_Time + 5000 <= GetTickCount())
	{
		CSceneMgr::GetInstance()->SetScene(SCENE_MENU);
		m_SELECTED_Time = GetTickCount();
	}


	if(m_LOGO_Time + 300 <= GetTickCount())
	{
		if(m_iDrawID_LOGO == 0)
			m_iDrawID_LOGO = 1;	
		else 
			m_iDrawID_LOGO = 0;

		m_LOGO_Time = GetTickCount();	
	}

	return 0;
}

void CSelectPlayer::Render(HDC _hdc)
{
	//BitBlt(_hdc
	//	,0
	//	,0
	//	,iWINCX
	//	,iWINCY
	//	,m_mapBmp["SELECTMAIN"]->GetMemDC()
	//	,0
	//	,0
	//	,SRCCOPY);
	
	//메인화면
	TransparentBlt(_hdc
		,0
		,0
		,iWINCX
		,iWINCY
		,m_mapBmp["SELECTMAIN"]->GetMemDC()
		,0
		,0
		,iWINCX
		,iWINCY
		,RGB(0, 255, 0)		);

	//로고창	72, 50		규칙 180
	BitBlt(_hdc
		,90	+ (180 * m_iDrawID_SELECT)
		,126
		,72
		,50
		,m_mapBmp["P1LOGO"]->GetMemDC()
		,72 * m_iDrawID_LOGO
		,0
		,SRCCOPY);


////////////////////////////캐릭터/////////////////////////////////

//마르코
	BitBlt(m_mapBmp["SELECTMAIN"]->GetMemDC()
		,44
		,192
		,174
		,324
		,m_mapBmp["MARCO1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	
	if(m_iDrawID_SELECT == 0)
	{
	BitBlt(_hdc
		,44
		,192
		,174
		,324
		,m_mapBmp["MARCO2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

//에리
	BitBlt(m_mapBmp["SELECTMAIN"]->GetMemDC()
		,223
		,192
		,174
		,324
		,m_mapBmp["ERI1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 1)
	{
	BitBlt(_hdc
		,223
		,192
		,174
		,324
		,m_mapBmp["ERI2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

//타마
	BitBlt(m_mapBmp["SELECTMAIN"]->GetMemDC()
		,402
		,192
		,174
		,324
		,m_mapBmp["TARMA1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 2)
	{
	BitBlt(_hdc
		,402
		,192
		,174
		,324
		,m_mapBmp["TARMA2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

		if(m_iDrawID_SELECTED == 1)
		{
		//선택시
			BitBlt(_hdc
				,402
				,192
				,174
				,324
				,m_mapBmp["TARMA3"]->GetMemDC()
				,0
				,0
				,SRCCOPY);
		}
	}

//피오
	BitBlt(m_mapBmp["SELECTMAIN"]->GetMemDC()
		,582
		,192
		,174
		,324
		,m_mapBmp["FIO1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 3)
	{
	BitBlt(_hdc
		,582
		,192
		,174
		,324
		,m_mapBmp["FIO2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

}
void CSelectPlayer::Release(void)
{

}
