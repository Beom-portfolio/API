#include "StdAfx.h"
#include "Enemy.h"
#include "Player.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Factory.h"
#include "Bullet.h"
#include "Granade.h"
#include "SoundMgr.h"

void CEnemy::Initialize(void)
{
	//CSoundMgr::GetInstance()->LoadSoundFile();

	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
//
	m_Time = GetTickCount();

	m_dwState = ENEMY_STAND;
	m_dwPrevState = ENEMY_STAND;

	m_dwFrameTime = GetTickCount();

	m_MotionTime = GetTickCount();
//
	m_strName = "MONSTER_LEFT";
	
	m_tInfo.fCX = 450;
	m_tInfo.fCY = 450;
	
	m_fSpeed = 5.f;

	m_bDirection = false;
	m_bDeadCheck = false;

	m_iHp = 1;

}

void CEnemy::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case ENEMY_STAND:
			m_tFrame = FRAME(0, 5, 0, 100);
			break;
		case ENEMY_WALK:
			m_tFrame = FRAME(0, 11, 1, 100);
			break;
		case ENEMY_THROW:
			m_tFrame = FRAME(0, 13, 2, 100);
			break;
		case ENEMY_DEAD:
			m_tFrame = FRAME(0, 8, 4, 50);
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;

		ActionState(m_dwState, 10, EA_ATTACK);
		ActionState(m_dwState, 8, EA_DEAD);
		
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;

		if(m_dwState != ENEMY_STAND)
		{
			m_dwState = ENEMY_STAND;
		}
	}

}

void CEnemy::SetFrame(void)
{
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
	static bool bTemp = false;
	
	if(m_PlayerInfo.fX + 1000 >= m_tInfo.fX && m_PlayerInfo.fX < m_tInfo.fX)
	{
		m_bDirection = true;
		m_strName = "MONSTER_LEFT";
		//적이 가까이 왔을때 공격 
		if(m_PlayerInfo.fX + 400 >= m_tInfo.fX)
		{
			if(m_MotionTime + 4000 <= GetTickCount())
			{
				if(bTemp == false)
				{
					m_dwState = ENEMY_THROW;
					bTemp = true;
				}
				else
				{
					m_dwState = ENEMY_STAND;
					bTemp = false;
				}

				m_MotionTime = GetTickCount();
			}
		}
		else
		{
			//플레이어가 근처에 없을시 이동
			m_dwState = ENEMY_WALK;

			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if(m_PlayerInfo.fX > m_tInfo.fX)
	{
		m_bDirection = false;
		m_strName = "MONSTER_RIGHT";

		if(m_PlayerInfo.fX - 400 <= m_tInfo.fX)
		{
			if(m_MotionTime + 4000 <= GetTickCount())
			{
				if(bTemp == false)
				{
					m_dwState = ENEMY_THROW;
					bTemp = true;
				}
				else
				{
					m_dwState = ENEMY_STAND;
					bTemp = false;
				}

				m_MotionTime = GetTickCount();
			}
		}
		else
		{
			//플레이어가 근처에 없을시 이동
			m_dwState = ENEMY_WALK;

			m_tInfo.fX += m_fSpeed;
		}
	}
	else
	{
		m_dwState = ENEMY_STAND;
	}
}

int CEnemy::ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction)
{
	if(dwCurState == ENEMY_THROW)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_ATTACK)
			{
				//동적생성.
				if(m_bDirection == false)
					pGranade = new CGranade(m_tInfo.fX + 70 , m_tInfo.fY - 40, GRANADE_MONSTER ,m_bDirection);
				else
					pGranade = new CGranade(m_tInfo.fX - 70 , m_tInfo.fY - 40, GRANADE_MONSTER ,m_bDirection);
				CObjMgr::GetInstance()->AddGameObject(pGranade, OBJ_GRANADE);
				return 0;
			}
		}
	}
	else if(dwCurState == ENEMY_DEAD)
	{

		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_DEAD)
			{
				m_bDeadCheck = true;
				return 0;
			}
		}
	}
	return 0;
}

int CEnemy::Update(void)
{
	SetFrame();
	FrameMove();

	CGameObject::Update();

	m_Rect.left		= m_Rect.left + 225 +  m_ptScroll.x;
	m_Rect.top		= m_Rect.top  + 150 +  m_ptScroll.y;
	m_Rect.right	= m_Rect.right - 175 +  m_ptScroll.x;
	m_Rect.bottom	= m_Rect.bottom - 220 +  m_ptScroll.y;

	CollisionLine_M();

	if(m_iHp <= 0)
	{
		
		m_dwState = ENEMY_DEAD;
		if(m_bDeadCheck == true)
		{
			return 1;
		}
	}




	return 0;
}

void CEnemy::Render(HDC _hdc)
{
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)	+   m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f) - 60	+ m_ptScroll.y
		,500
		,500
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(255, 255, 255)  );

	if(!(CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].end();

		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}

		if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}
}

void CEnemy::Release(void)
{
	
}

CEnemy::CEnemy(void)
{
}

CEnemy::CEnemy(float m_tInfo_x, float m_tInfo_y)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	Initialize();
}

CEnemy::~CEnemy(void)
{
	Release();
}
