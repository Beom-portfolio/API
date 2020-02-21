#include "StdAfx.h"
#include "Nife.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"

CNife::CNife(void)
{
}

CNife::~CNife(void)
{
	Release();
}

void CNife::Initialize(void)
{	
	////플레이어 움직임 체크

	m_fTime	   = 0.f;
	m_bJump	   = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//시간 지연
	

	m_tInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

	m_tFrame = FRAME(0, 5, 0, 30);

	m_strName = "NULL";

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

}

void CNife::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case STATE_KNIFEATT:
			m_tFrame = FRAME(0, 5, 0, 30);
			break;

		case STATE_SEATKNIFEATT:
			m_tFrame = FRAME(0, 3, 0, 30);
			break;
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != STATE_STAND)
		{
			m_dwState = STATE_STAND;
		}
	}

}

void CNife::SetFrame(void)
{
	srand(unsigned int(time(NULL)));

	int Rand = rand() % 2;

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(dwKey & KEY_LEFT && dwKey & KEY_CTRL)
	{
		if(Rand == 0)
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEATT_LEFT";
		}
		else
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEATT2_LEFT";
		}
	}

	if(dwKey & KEY_RIGHT && dwKey & KEY_CTRL)
	{
		if(Rand == 0)
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEATT_RIGHT";
		}
		else
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEATT2_RIGHT";
		}
	}

	//앉아서 때리기
	if(dwKey & KEY_DOWN && dwKey & KEY_LEFT && dwKey & KEY_CTRL)
	{
		if(Rand == 0)
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEDOWNATT_LEFT";
		}
		else
		{
			m_dwState = STATE_SEATKNIFEATT;
			m_strName = "PLAYER_KNIFEDOWNATT2_LEFT";
		}
	}

	if(dwKey & KEY_DOWN && dwKey & KEY_RIGHT && dwKey & KEY_CTRL)
	{
		if(Rand == 0)
		{
			m_dwState = STATE_KNIFEATT;
			m_strName = "PLAYER_KNIFEDOWNATT_RIGHT";
		}
		else
		{
			m_dwState = STATE_SEATKNIFEATT;
			m_strName = "PLAYER_KNIFEDOWNATT2_RIGHT";
		}
	}
	
}

//키입력
void CNife::KeyInput(void)
{
	srand(unsigned int(time(NULL)));

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();
	
	if(!dwKey)
		m_strName = "NULL";

}

int  CNife::Update(void)
{
	KeyInput();		//플레이어 조정	
	SetFrame();
	FrameMove();
	
	m_tInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

	CGameObject::Update();

	return 0;
}

void CNife::Render(HDC _hdc)
{

	if(m_strName == "NULL")
		return;

	/////이미지 출력
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(75, 169, 218)  );

}

void CNife::Release(void)
{

}
