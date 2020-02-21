#include "StdAfx.h"
#include "PlayerLeg.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Stage.h"

CPlayerLeg::CPlayerLeg(void)
{
}

CPlayerLeg::CPlayerLeg(float _fx, float _fy)
{
	m_tInfo.fX = _fx;
	m_tInfo.fY = _fy;
	Initialize();
}


CPlayerLeg::~CPlayerLeg(void)
{
	Release();
}

void CPlayerLeg::Initialize(void)
{	
	m_bUpCheck = false;

	m_fTime	   = 0.f;
	m_bJump	   = false;
	m_bJumpDown = false;

	
	m_fSpeed = 10.f;


	m_bDirection = false;
//시간 지연
	m_Time = GetTickCount();
	
	//m_tInfo = INFO(m_tInfo.fX, m_tInfo.fY, 400, 267);
	m_tInfo.fCX = 400;
	m_tInfo.fCY = 267;
	m_strName = "PLAYER_STAND_LEG_RIGHT";

	m_tFrame = FRAME(0, 2, 0, 100);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

}

void CPlayerLeg::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case STATE_STAND:
			if(m_bDirection == true)
			{
				m_tFrame = FRAME(0, 0, 0, 100);

				break;
			}
			else
			{
				m_tFrame = FRAME(0, 2, 0, 100);

				break;
			}

		case STATE_WALK:
			m_tFrame = FRAME(0, 11, 0, 50);
			break;

		case STATE_JUMP:
			m_tFrame = FRAME(0, 5, 0, 100);
			break;

		case STATE_SEAT:
			m_tFrame = FRAME(0, 0, 0, 100);
			break;

		case STATE_SEATMOVE:
			m_tFrame = FRAME(0, 6, 0, 100);
			break;

		case STATE_UPSEE:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_SHOOT:
			m_tFrame = FRAME(0, 8, 0, 100);
			break;

		case STATE_UPSHOOT:
			m_tFrame = FRAME(0, 9, 0, 100);
			break;

		case STATE_SEATSHOOT:
			m_tFrame = FRAME(0, 4, 0, 100);
			break;

		case STATE_JUMPDOWNSHOOT:
			m_tFrame = FRAME(0, 3, 0, 100);
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

void CPlayerLeg::SetFrame(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	//걸을떄.
	if(dwKey & KEY_LEFT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_LEG_LEFT";

		if(m_bDirection == false)
			m_bDirection = true;

	}

	if(dwKey & KEY_RIGHT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_LEG_RIGHT";

		if(m_bDirection == true)
			m_bDirection = false;
	}
	
	//제자리 점프
	if(dwKey & KEY_SPACE)
	{

		m_dwState = STATE_JUMP;
		
		if(m_bDirection == false)
			m_strName = "PLAYER_JUMP_LEG_RIGHT";
		else
			m_strName = "PLAYER_JUMP_LEG_LEFT";
		
	}

	//뛰면서 점프
	if(dwKey & KEY_LEFT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_LEG_LEFT";
		
		if(m_bDirection == false)
			m_bDirection = true;
	}

	//뛰면서 점프
	if(dwKey & KEY_RIGHT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_LEG_RIGHT";	
	
		if(m_bDirection == true)
			m_bDirection = false;
	}

	if(m_bJump == false && dwKey & KEY_DOWN)
	{
		if(!(dwKey & KEY_DOWN))
		{
			return;
		}

		m_dwState = STATE_SEAT;
	
		m_strName = "NONE";
	}
	

	
}

//키입력
void CPlayerLeg::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(dwKey & KEY_J)
	{
		m_fSpeed = 100;
	}

	if(!(dwKey))
	{
		m_fSpeed = 10.f;
	}

	if(!dwKey)
	{
		if(m_bDirection == false)
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_LEG_RIGHT";
		}
		else
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_LEG_LEFT";
		}
	}


	if(dwKey & KEY_LEFT)
	{
		m_tInfo.fX -= m_fSpeed;
			
	}

	if(dwKey & KEY_RIGHT)
	{
		m_tInfo.fX += m_fSpeed;	

	}

	//위를 볼때
	if(dwKey & KEY_UP)
	{
	
	}


	//쭈그릴때. (점프할때는 실행 안함)
	if(m_bJump == false)
	{
		if(dwKey & KEY_DOWN)
		{
			m_fSpeed = 5.f;
		}
		if(!(dwKey & KEY_DOWN))
		{
			m_fSpeed = 10.f;
		}
	}



	//지상에 있을 시에만 점프 가능하게
	if(m_Time + 600 < GetTickCount())
	{
		if((dwKey & KEY_SPACE))
		{
			m_bJump = true;
			m_fTime = 0.f;
			m_Time = GetTickCount();
		}	
	}

}


void CPlayerLeg::Jump(void)
{
	if(m_bJump == false)
		return;

	m_fTime += 0.5f;

	//공식
	//힘 * -sin(90 * PI / 180) + (중력가속도:9.8 * 시간 * 시간) / 2
	//m_tInfo.fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_tInfo.fY += float(25 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	
	//임시 방편(라인충돌 전)
}

int  CPlayerLeg::Update(void)
{


	CGameObject::Update();

	m_Rect.left   = m_Rect.left + 170   + m_ptScroll.x;
	m_Rect.top    = m_Rect.top  + 50	+ m_ptScroll.y;
	m_Rect.right  = m_Rect.right - 190	+ m_ptScroll.x;
	m_Rect.bottom = m_Rect.bottom - 140 + m_ptScroll.y;;	

	
	SetFrame();
	FrameMove();
	KeyInput();		//플레이어 조정
	Jump();			//점프

	CollisionLine(m_bJump);

	return 0;
}

void CPlayerLeg::Render(HDC _hdc)
{
	/////이미지 출력
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f) - 50 + m_ptScroll.y 
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)		//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)				//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(75, 169, 218)  );

	if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}

}

void CPlayerLeg::Release(void)
{

}
