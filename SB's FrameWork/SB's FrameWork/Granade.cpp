#include "StdAfx.h"
#include "Granade.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "BulletEffect.h"
#include "Stage.h"
#include "PlayerZombie.h"

void CGranade::Initialize(void)
{
	//CSoundMgr::GetInstance()->LoadSoundFile();

	m_Time = GetTickCount();

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

	switch(eType)
	{
	case GRANADE_PLAYER:
		m_strName = "PLAYER_GRANADE";
		m_tFrame = FRAME(0, 31, 0, 10);
		m_tInfo.fCX = 30;
		m_tInfo.fCY = 30;
		m_fSpeed = 40.f;
		break;

	case GRANADE_MONSTER:
		m_strName = "MONSTER_BULLET";
		m_tFrame = FRAME(0, 15, 0, 10);
		m_tInfo.fCX = 150;
		m_tInfo.fCY = 150;
		m_fSpeed = 40.f;
		break;

	case GRANADE_ZOMBIE:
		m_strName = "ZOMBIE_BULLET";
		m_tFrame = FRAME(0, 12, 0, 60);
		m_tInfo.fCX = 200;
		m_tInfo.fCY = 290;
		m_fSpeed = 15.f;
		break;
	}
}

void CGranade::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case STATE_STAND:
			m_tFrame = FRAME(0, 31, 0, 10);
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

		if(m_dwState != STATE_STAND)
		{
			m_dwState = STATE_STAND;
		}
	}

}

void CGranade::SetFrame(void)
{

}

int CGranade::Update(void)
{
	SetFrame();
	FrameMove();
	
	if(m_bDirection == false)
	{
		if(m_fAngleY < 270.f)
		{
		m_fAngleY -= m_fAngleSpeed;
		}
	}
	else
	{
		if(m_fAngleY < 270.f)
		{
		m_fAngleY += m_fAngleSpeed;
		}
	}
	
	
	
	m_tInfo.fX += cos( m_fAngle * (PI / 180) ) * m_fSpeed;
	m_tInfo.fY += -sin( m_fAngleY * (PI / 180) ) * m_fSpeed;
	
	

	CGameObject::Update();

	switch(eType)
	{
	case GRANADE_PLAYER:
		break;

	case GRANADE_MONSTER:
		m_Rect.left		= m_Rect.left	+ 50 +	m_ptScroll.x;
		m_Rect.top		= m_Rect.top	+ 50 + m_ptScroll.y;
		m_Rect.right	= m_Rect.right  - 50 +	m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom - 50 + m_ptScroll.y;
		break;

	case GRANADE_ZOMBIE:
		m_Rect.left		=  m_Rect.left	  +20 +	m_ptScroll.x;
		m_Rect.top		=  m_Rect.top	  +20 + m_ptScroll.y;
		m_Rect.right	=  m_Rect.right   -150 +	m_ptScroll.x;
		m_Rect.bottom	=  m_Rect.bottom  -230 + m_ptScroll.y;
		break;
	}


	//몬스터와 폭탄

	list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
	list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
	
	for(iter; iter != iter_end; ++iter)
	{
		if( CCollisionMgr::GetInstance()->CollisionBullet((*iter)->GetRect(), &m_Rect) == true )
		{
			switch(eType)
			{
			case GRANADE_PLAYER:
				pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_GRANADE);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				CSoundMgr::GetInstance()->PlaySound(L"explode.wav");
				(*iter)->SetDamage(5);
				return 1;
			}	
			//return 1;
		}
	}

	//보스와 폭탄

	list<CGameObject*>::iterator iter_B = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].begin();
	list<CGameObject*>::iterator iter_B_end = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].end();
	
	for(iter_B; iter_B != iter_B_end; ++iter_B)
	{
		if( CCollisionMgr::GetInstance()->CollisionBullet((*iter_B)->GetRect(), &m_Rect) == true )
		{
			switch(eType)
			{
			case GRANADE_PLAYER:
				pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_GRANADE);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				CSoundMgr::GetInstance()->PlaySound(L"explode.wav");
				(*iter_B)->SetDamage(5);
				return 1;
			}	
			//return 1;
		}
	}


	//플레이어와 수류탄 충돌
	CGameObject* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();
	

	if( CCollisionMgr::GetInstance()->CollisionBullet(pPlayer->GetRect(), &m_Rect) == true )
	{
		switch(eType)
		{
		case GRANADE_MONSTER:
			pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			CSoundMgr::GetInstance()->PlaySound(L"explode.wav");
			--CStage::m_iLife;
			return 1;

			//맞으면 좀비 변신 해야됨
		case GRANADE_ZOMBIE:
			pEffect = new CBulletEffect(m_tInfo.fX - 50, m_tInfo.fY - 100, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			if(CStage::m_bZombie == false)
			{
				CStage::m_bZombie = true;
				
				
				list<CGameObject*>::iterator iter		 = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].begin();
				list<CGameObject*>::iterator iter_end	 = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].end();
				
	
			
				list<CGameObject*>::iterator iter_L		 = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER_LEG].begin();
				list<CGameObject*>::iterator iter_L_end	 = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER_LEG].end();
				
				pPlayerZombie = new CPlayerZombie((*iter)->GetInfo().fX, (*iter)->GetInfo().fY);
				
				//상체 삭제
				for(iter; iter != iter_end; )
				{
					SAFE_DELETE(*iter);
					iter = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].erase(iter);
				}
				
				//하체 삭제	
				for(iter_L; iter_L != iter_L_end; )
				{
					SAFE_DELETE(*iter_L);
					iter_L =  CObjMgr::GetInstance()->GetList()[OBJ_PLAYER_LEG].erase(iter_L);
				}
					
				CObjMgr::GetInstance()->AddGameObject(pPlayerZombie, OBJ_PLAYER);
			
			}
			else
			{
				pEffect = new CBulletEffect(m_tInfo.fX - 50, m_tInfo.fY - 100, EFFECT_MGRANADE);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);

				CStage::m_bZombie = false;
				CStage::m_bZombieDeadCheck = true;
			}
			return 1;
		}	
		//return 1;
	}


	//수류탄과 라인 충돌
	if(CollisionLine_BG() == true)
	{
		switch(eType)
			{
		case GRANADE_PLAYER:
			pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_GRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			return 1;
			
		case GRANADE_MONSTER:
			pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			return 1;

			//맞으면 좀비 변신 해야됨
			}	
	}


	//수류탄과 윈도우창 충돌

	if(eType == GRANADE_MONSTER || eType == GRANADE_ZOMBIE)
	{
		if(m_tInfo.fY > iWINCY )
			return 1;
	}
	else
	{
		if(m_tInfo.fX < 0|| m_tInfo.fY < 0)
			return 1;


		else if(m_tInfo.fX > iWINCX || m_tInfo.fY > iWINCY )
			return 1;
	}


	
	return 0;
}

void CGranade::Render(HDC _hdc)
{
	if(m_tInfo.fCX >= 200 && m_tInfo.fCY > 200)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)		+	m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)		+   m_ptScroll.y
			,(int)100
			,(int)100
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}
	else if(eType == GRANADE_PLAYER)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			,(int)m_tInfo.fCX + 10
			,(int)m_tInfo.fCY + 10
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}
	else
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)		 +	m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)		 +  m_ptScroll.y
			,(int)m_tInfo.fCX + 10
			,(int)m_tInfo.fCY + 10
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}

		if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}
}

void CGranade::Release(void)
{

}

CGranade::CGranade(void)
{
}

CGranade::CGranade(float m_tInfo_x, float m_tInfo_y, eGranadeType _eType, bool Direction)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eType = _eType;
	m_bDirection = Direction;
	m_fAngleSpeed = 6.f;
	
	if(Direction == false)
	{
		m_fAngle = 60.f;
		m_fAngleY = m_fAngle;
	}
	else
	{
		m_fAngle = 110.f;
		m_fAngleY = m_fAngle;
	}

	Initialize();
}

CGranade::~CGranade(void)
{
	Release();
}