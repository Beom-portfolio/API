#include "StdAfx.h"
#include "Toma.h"
#include "Player.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Bullet.h"
#include "BulletEffect.h"


void CToma::Initialize(void)
{
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
//
	m_Time = GetTickCount();

	m_dwState = TOMA_STAND;
	m_dwPrevState = TOMA_STAND;

	m_dwFrameTime = GetTickCount();

	m_MotionTime = GetTickCount();
//
	m_strName = "TOMA_LEFT";
	m_tFrame = FRAME(0, 11, 0, 100);
	m_tInfo.fCX = 300;
	m_tInfo.fCY = 300;
	
	m_fSpeed = 4.f;

	m_bDirection = false;
	m_bDeadCheck = false;

	m_iHp = 40;
}

void CToma::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case TOMA_STAND:
			m_tFrame = FRAME(0, 11, 0, 100);
			break;
		case TOMA_WALK:
			m_tFrame = FRAME(0, 11, 0, 100);
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

		m_tFrame.iFrameStart = 0;

		if(m_dwState != TOMA_STAND)
		{
			m_dwState = TOMA_STAND;
		}
	}

}

void CToma::SetFrame(void)
{
	m_PlayerInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();



	if(m_PlayerInfo.fX  < m_tInfo.fX)
	{
		m_bDirection = true;
		m_strName = "TOMA_LEFT";

		//적이 정확히 내 위치로 왔을때 공격 
		if(m_PlayerInfo.fX  + 10 >= m_tInfo.fX  && m_PlayerInfo.fX - 10 <= m_tInfo.fX  )
		{

			if(m_MotionTime + 400 <= GetTickCount())
			{
				Attack(m_tInfo.fX  + m_ptScroll.x, m_tInfo.fY + 65 + m_ptScroll.y);		
				m_MotionTime = GetTickCount();
			}
			
		}
		else
		{
			//플레이어가 근처에 없을시 이동
			m_dwState = TOMA_WALK;

			m_tInfo.fX -= m_fSpeed;
		}
	}
	else if(m_PlayerInfo.fX  > m_tInfo.fX)
	{
		m_bDirection = false;
		m_strName = "TOMA_RIGHT";

		if(m_PlayerInfo.fX + 10 >= m_tInfo.fX   && m_PlayerInfo.fX - 10 <= m_tInfo.fX  )
		{
			if(m_MotionTime + 400 <= GetTickCount())
			{
				Attack(m_tInfo.fX  + m_ptScroll.x , m_tInfo.fY + 65 + m_ptScroll.y);
				m_MotionTime = GetTickCount();
			}

		}
		else
		{
			//플레이어가 근처에 없을시 이동
			m_dwState = TOMA_WALK;

			m_tInfo.fX += m_fSpeed;
		}
	}


}

int CToma::Update(void)
{
	SetFrame();
	FrameMove();

	CGameObject::Update();

	m_Rect.left		= m_Rect.left	+50 +  m_ptScroll.x;
	m_Rect.top		= m_Rect.top	+50 +  m_ptScroll.y;
	m_Rect.right	= m_Rect.right	-50 +  m_ptScroll.x;
	m_Rect.bottom	= m_Rect.bottom	-100+  m_ptScroll.y;
	
	if(m_iHp <= 0)
	{
		//m_bDeadCheck = true;
		pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_BIGEXPLOSION);
		CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
		CSoundMgr::GetInstance()->PlaySound(L"explode.wav");
		return 1;
	}

		
	return 0;
}

void CToma::Render(HDC _hdc)
{
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)  +  m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)  +  m_ptScroll.y
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(0, 248, 0)  );

	if(!(CObjMgr::GetInstance()->GetList()[OBJ_BULLET].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_BULLET].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BULLET].end();

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

void CToma::Release(void)
{

}

CToma::CToma(void)
{
}

CToma::CToma(float m_tInfo_x, float m_tInfo_y)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	Initialize();
}

CToma::~CToma(void)
{
	Release();
}


void CToma::Attack(float m_tInfo_x, float m_tInfo_y)
{
	CGameObject* pBullet = new CBullet(m_tInfo_x - m_ptScroll.x, m_tInfo_y - m_ptScroll.y, BULLET_DOWN, BULLET_TOMA);

	CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);

}