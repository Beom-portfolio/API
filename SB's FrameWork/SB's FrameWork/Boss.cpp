#include "StdAfx.h"
#include "Boss.h"
#include "Player.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Factory.h"
#include "Bullet.h"
#include "Granade.h"
#include "BulletEffect.h"



void CBoss::Initialize(void)
{
	//CSoundMgr::GetInstance()->LoadSoundFile();

	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

	m_Time = GetTickCount();

	m_dwState = BOSS_STAND;
	m_dwPrevState = BOSS_STAND;

	
	m_dwFrameTime = GetTickCount();

	m_MotionTime = GetTickCount();
	m_AttackTime = GetTickCount();
	m_DeadTime   = GetTickCount();

	m_strName = "BOSS_STAND";
	
	m_tInfo.fCX = 500;
	m_tInfo.fCY = 500;

	m_bDeadCheck = false;
	m_SoundChange = false;

	m_iHp = 200;
	iDeadCount = 0;

}

void CBoss::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{

		case BOSS_STAND:
			m_tFrame = FRAME(0, 4, 0, 50);
			m_strName = "BOSS_STAND";
			break;
		case BOSS_FIRE:
			m_tFrame = FRAME(0, 7, 0, 100);
			break;
		case BOSS_LAZER:
			m_tFrame = FRAME(0, 0, 0, 0);
			break;
		case BOSS_DEAD:
			m_tFrame = FRAME(0, 0, 0, 0);
			break;
			
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;

		ActionState(BOSS_FIRE, 7, EA_ATTACK); 

	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != BOSS_STAND)
		{
			m_dwState = BOSS_STAND;
		}
	}

}

void CBoss::SetFrame(void)
{


	if(m_MotionTime + 5000 <= GetTickCount())
	{

		m_dwState = BOSS_FIRE;
		m_strName = "BOSS_FIRE";

		m_MotionTime = GetTickCount();
	}


	if(m_AttackTime + 2000 <= GetTickCount())
	{
		if(m_bAtt == true)
		{
			m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

			Attack(m_PlayerInfo.fX, m_PlayerInfo.fY - 600);

			m_dwState = BOSS_STAND;
			m_strName = "BOSS_STAND";

			m_bAtt = false;
		}
		m_AttackTime = GetTickCount();
	}
	
}

int CBoss::ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction)
{
	if(dwCurState == BOSS_FIRE)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_ATTACK)
			{
				m_bAtt = true;
			}
		}
	}
	return 0;
}

int CBoss::Update(void)
{
	
	
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

	if(m_PlayerInfo.fX >= 15100 || m_MoveStart == true)
	{

		if(m_SoundChange == false)
		{
			CSoundMgr::GetInstance()->PlayBGMSound(L"Boss.mp3");
			m_SoundChange = true;
		}



		m_MoveStart = true;

		SetFrame();
		FrameMove();

		CGameObject::Update();

		m_Rect.left		= m_Rect.left + 100				+  m_ptScroll.x;
		m_Rect.top		= m_Rect.top  + 140				+ m_ptScroll.y;
		m_Rect.right	= m_Rect.right - 100			+  m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom - 180			+ m_ptScroll.y;

		//CollisionLine_M();

		if(m_iHp <= 0)
		{


			m_bDeadCheck = true;
			m_dwState = BOSS_DEAD;
			
			if(m_DeadTime + 500 <= GetTickCount())
			{
				srand(unsigned int(time(NULL)));

				int A = rand() % 50;
				int _A = rand() % 100;
				int B = rand() % 50;					

				pEffect = new CBulletEffect(m_tInfo.fX - A  + _A, m_tInfo.fY + B, EFFECT_BIGEXPLOSION);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);

				++iDeadCount;

				m_DeadTime = GetTickCount();
			}

			if(iDeadCount == 6)
			{
				CSoundMgr::GetInstance()->PlaySound(L"MissionComplete.mp3");
				CSoundMgr::GetInstance()->PlayBGMSound(L"StageClear.mp3");
				
				m_MoveStart = false;
				return 1;
			}
			return 0;
		}
	}
	else
	{
		m_MoveStart = false;
	}
	return 0;
}

void CBoss::Render(HDC _hdc)
{
	if(m_bDeadCheck == true)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)	- 20	 +   m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)   + 100 +   m_ptScroll.y
			,540
			,540
			,(*m_mapBmp)["BOSS_DEAD"]->GetMemDC()	
			,0			//이미지에서의 시작 위치 X
			,0			//이미지에서의 시작 위치 Y
			,500		//이미지의 범위 X
			,500		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}	
	else
	{
		//몸
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f) - 20	 +   m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)   + 145 +   m_ptScroll.y
			,540
			,540
			,(*m_mapBmp)["BOSS_BODY"]->GetMemDC()	
			,0			//이미지에서의 시작 위치 X
			,0			//이미지에서의 시작 위치 Y
			,500		//이미지의 범위 X
			,500		//이미지의 범위 Y
			,RGB(255, 0, 255)  );


		//머리
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)	+   m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)	+   m_ptScroll.y
			,500
			,500
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}

	if(m_bAtt == true)
	{
		m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();

		//레이저
		TransparentBlt(_hdc
			,int(m_PlayerInfo.fX - m_tInfo.fCX / 2.f)	+  250 +   m_ptScroll.x
			,0
			,5
			,600
			,(*m_mapBmp)["BOSS_LAZER"]->GetMemDC()	
			,0			//이미지에서의 시작 위치 X
			,0			//이미지에서의 시작 위치 Y
			,5		//이미지의 범위 X
			,600		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}


	if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}
}

void CBoss::Release(void)
{

}

CBoss::CBoss(void)
{
}

CBoss::CBoss(float m_tInfo_x, float m_tInfo_y)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	Initialize();
}

CBoss::~CBoss(void)
{
	Release();
}

void CBoss::Attack(float m_tInfo_x, float m_tInfo_y)
{
	CGameObject* pBullet = new CBullet(m_tInfo_x, m_tInfo_y , BULLET_DOWN, BULLET_BOSS, BOSSBULLETSTAY);

	CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);

}