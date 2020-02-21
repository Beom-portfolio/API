#include "StdAfx.h"
#include "Zombie.h"
#include "Player.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Factory.h"
#include "Bullet.h"
#include "Granade.h"
#include "BulletEffect.h"


void CZombie::Initialize(void)
{
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
//
	m_Time = GetTickCount();

	m_dwState = ZOMBIE_WALK;
	m_dwPrevState = ZOMBIE_WALK;

	m_dwFrameTime = GetTickCount();

	m_MotionTime = GetTickCount();
//
	m_strName = "ZOMBIE_WALK";
	m_tFrame = FRAME(0, 13, 0, 50);
	m_tInfo.fCX = 256;
	m_tInfo.fCY = 256;
	m_fSpeed = 3.f;

	m_bDirection = false;
	m_bDeadCheck = false;

	m_iHp = 15;
}

void CZombie::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case ZOMBIE_WALK:
			m_tFrame = FRAME(0, 13, 0, 50);
			break;
		case ZOMBIE_ATTACK:
			m_tFrame = FRAME(0, 18, 0, 50);
			break;
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;

		ActionState(m_dwState, 11, EA_ATTACK);

		//if(m_dwState == ENEMY_THROW)
		//{
		//	if(m_tFrame.iFrameStart == 10)
		//	{
		//		//공격.
		//	}
		//}
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != ZOMBIE_WALK)
		{
			m_dwState = ZOMBIE_WALK;
		}
	}

}

void CZombie::SetFrame(void)
{
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
	
	static bool bTemp = false;
	
	if(m_PlayerInfo.fX < m_tInfo.fX )
	{
		//적이 가까이 왔을때 공격 
		if(m_PlayerInfo.fX + 500 >= m_tInfo.fX)
		{
			if(m_MotionTime + 3000 <= GetTickCount())
			{
				if(bTemp == false)
				{
					m_dwState = ZOMBIE_WALK;
					m_strName = "ZOMBIE_WALK";

					bTemp = true;
				}
				else
				{
					m_dwState = ZOMBIE_ATTACK;
					m_strName = "ZOMBIE_ATTACK";

					bTemp = false;
				}

				m_MotionTime = GetTickCount();
			}

			
		}
		else
		{
			//플레이어가 근처에 없을시 이동
			m_dwState = ZOMBIE_WALK;
			m_strName = "ZOMBIE_WALK";

			m_tInfo.fX -= m_fSpeed;
		}
	}
}

int CZombie::ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction)
{
	if(dwCurState == ZOMBIE_ATTACK)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_ATTACK)
			{
				//동적생성.
				CGameObject* pGranade = new CGranade(m_tInfo.fX - 50 + m_ptScroll.x, m_tInfo.fY - 20 /*+ m_ptScroll.y*/, GRANADE_ZOMBIE ,true);
				CObjMgr::GetInstance()->AddGameObject(pGranade, OBJ_GRANADE);
				return 0;
			}
		}
	}
	return 0;
}

int CZombie::Update(void)
{
	SetFrame();
	FrameMove();
	
	CGameObject::Update();

	m_Rect.left		 = m_Rect.left + 35 + m_ptScroll.x;
	m_Rect.top		 = m_Rect.top  + 30 + m_ptScroll.y;
	m_Rect.right	 = m_Rect.right - 180 + m_ptScroll.x;
	m_Rect.bottom	 = m_Rect.bottom - 130 + m_ptScroll.y;

	CollisionLine_M();

	if(m_iHp <= 0)
	{
		pEffect = new CBulletEffect(m_tInfo.fX - 50, m_tInfo.fY, EFFECT_BIGEXPLOSION);
		CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);

		return 1;
	}


	return 0;
}

void CZombie::Render(HDC _hdc)
{
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f) + 30 + m_ptScroll.y
		,120
		,120
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,m_tInfo.fCX	//이미지의 범위 X
		,m_tInfo.fCY		//이미지의 범위 Y
		,RGB(255, 0, 255)  );

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

void CZombie::Release(void)
{

}

CZombie::CZombie(void)
{
}

CZombie::CZombie(float m_tInfo_x, float m_tInfo_y)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	Initialize();
}

CZombie::~CZombie(void)
{
	Release();
}
