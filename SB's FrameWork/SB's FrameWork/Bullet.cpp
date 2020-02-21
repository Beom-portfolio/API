#include "StdAfx.h"
#include "Bullet.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "BulletEffect.h"
#include "Stage.h"

void CBullet::Initialize(void)
{
	m_bDeadCheck = false;

	switch(eType)
	{
	case BULLET_PISTOL:
		m_strName = "PISTOL_BULLET";
		m_tInfo.fCX = 20;
		m_tInfo.fCY = 20;
		m_iAtt		= 1;
		m_fSpeed = 30.f;
		break;

	case BULLET_TOMA:
		m_strName = "TOMA_BULLET";
		m_tInfo.fCX = 100;
		m_tInfo.fCY = 100;
		m_fSpeed = 10.f;
		break;

	case BULLET_HEAVY:
		m_strName = "HEAVY_BULLET";
		m_tInfo.fCX = 30;
		m_tInfo.fCY = 30;
		m_fSpeed = 40.f;
		--CStage::m_iHeavyBullet;
		break;

	case BULLET_BOSS:
		m_strName = "BOSS_BULLET";
		m_dwFrameTime = GetTickCount();
		m_tInfo.fCX = 200;
		m_tInfo.fCY = 500;
		m_fSpeed = 20.f;
		break;
	}
}


//프레임 
void CBullet::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case LEFT:
			m_tFrame = FRAME(0, 0, 2, 100);
			break;
		case RIGHT:
			m_tFrame = FRAME(0, 0, 0, 100);
			break;
		case UP:
			m_tFrame = FRAME(0, 0, 1, 100);
			break;
		case DOWN:
			m_tFrame = FRAME(0, 0, 3, 100);
			break;
//오른 위
		case RIGHT_UP_1:
			m_tFrame = FRAME(3, 3, 0, 100);
			break;
		case RIGHT_UP_2:
			m_tFrame = FRAME(6, 6, 0, 100);
			break;
		case RIGHT_UP_3:
			m_tFrame = FRAME(8, 8, 0, 100);
			break;
//오른 아래
		case RIGHT_DOWN_1:
			m_tFrame = FRAME(1, 1, 3, 100);
			break;
		case RIGHT_DOWN_2:
			m_tFrame = FRAME(3, 3, 3, 100);
			break;
		case RIGHT_DOWN_3:
			m_tFrame = FRAME(6, 6, 3, 100);
			break;
//왼 위
		case LEFT_UP_1:
			m_tFrame = FRAME(1, 1, 1, 100);
			break;
		case LEFT_UP_2:
			m_tFrame = FRAME(3, 3, 1, 100);
			break;
		case LEFT_UP_3:
			m_tFrame = FRAME(6, 6, 1, 100);
			break;
//왼 아래
		case LEFT_DOWN_1:
			m_tFrame = FRAME(3, 3, 2, 100);
			break;
		case LEFT_DOWN_2:
			m_tFrame = FRAME(7, 7, 2, 100);
			break;
		case LEFT_DOWN_3:
			m_tFrame = FRAME(9, 9, 2, 100);
			break;
//보스 
		case BOSSBULLETSTAY:
			m_tFrame = FRAME(0, 0, 0, 50);
			break;

		case BOSSBULLET:
			m_tFrame = FRAME(0, 32, 0, 20);
			break;
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;

		
		ActionState(BOSSBULLET, 32, EA_END);

	}

	if(eType == BULLET_BOSS)
	{
		if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
		{
			/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

			m_tFrame.iFrameStart = 0;

			if(m_dwState != BOSSBULLETSTAY)
			{
				m_dwState = BOSSBULLETSTAY;
			}
		}
	}

}

//각도
void CBullet::SetFrame(void)
{
	switch(eDir)
	{
	case BULLET_HEAVYDIR:
		{
		m_tInfo.fX += cos(m_fAngle * (PI/180)) *  m_fSpeed;
		m_tInfo.fY += -sin(m_fAngle * (PI/180)) *  m_fSpeed;
		break;
		}
	}
}


int CBullet::ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction)
{
	if(dwCurState == BOSSBULLET)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_END)
			{
				m_bDeadCheck = true;
				return 1;
			}
		}
	}
	return 0;
}

int CBullet::Update(void)
{

	FrameMove();
	SetFrame();

	switch(eDir)
	{
	case BULLET_LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case BULLET_RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	case BULLET_UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case BULLET_DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	case BULLET_HEAVYDIR:
		break;
	}

	CGameObject::Update();


	switch(eType)
	{
	case BULLET_PISTOL:
		break;

	case BULLET_HEAVYDIR:
		break;

	case BULLET_TOMA:
		m_Rect.left		= m_Rect.left	+ 30  + m_ptScroll.x;
		m_Rect.top		= m_Rect.top	+ 30  + m_ptScroll.y;
		m_Rect.right	= m_Rect.right  - 30  + m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom - 30  + m_ptScroll.y;
		break;

	case BULLET_BOSS:
		m_Rect.left		= m_Rect.left	+ 30  + m_ptScroll.x;
		m_Rect.top		= m_Rect.top	+ 30  + m_ptScroll.y;
		m_Rect.right	= m_Rect.right  - 30  + m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom - 30  + m_ptScroll.y;
		break;
	}
	
	//플레이어와 불렛 충돌
	CGameObject* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();


	if( CCollisionMgr::GetInstance()->CollisionBullet(pPlayer->GetRect(), &m_Rect) == true )
	{
		switch(eType)
		{
		case BULLET_TOMA:
			pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			//플레이어 피통
			--CStage::m_iLife;
			return 1;
		case BULLET_BOSS:
			pEffect = new CBulletEffect(pPlayer->GetInfo().fX, pPlayer->GetInfo().fY, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
			//플레이어 피통
			--CStage::m_iLife;
			return 0;
		}
	}

	//불렛과 몬스터 충돌
	list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
	list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

	for(iter; iter != iter_end; ++iter)
	{
		if( CCollisionMgr::GetInstance()->CollisionBullet((*iter)->GetRect(), &m_Rect) == true )
		{
			switch(eType)
			{
			case BULLET_PISTOL:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				(*iter)->SetDamage(1);
				return 1;
			case BULLET_HEAVY:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				(*iter)->SetDamage(1);
				return 1;
			}	
		}
	}

	//불렛과 보스 충돌
	list<CGameObject*>::iterator iter_B = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].begin();
	list<CGameObject*>::iterator iter_B_end = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].end();

	for(iter_B; iter_B != iter_B_end; ++iter_B)
	{
		if( CCollisionMgr::GetInstance()->CollisionBullet((*iter_B)->GetRect(), &m_Rect) == true )
		{
			switch(eType)
			{
			case BULLET_PISTOL:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				(*iter_B)->SetDamage(1);
				return 1;
			case BULLET_HEAVY:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				(*iter_B)->SetDamage(1);
				return 1;
			}	
		}
	}

	//불렛과 라인 충돌
	if(CollisionLine_BG() == true)
	{
		switch(eType)
			{
			case BULLET_PISTOL:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				return 1;
			case BULLET_HEAVY:
				pEffect = new CBulletEffect(m_tInfo.fX , m_tInfo.fY, EFFECT_PISTOL);
				CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				return 1;
			case BULLET_TOMA:
			pEffect = new CBulletEffect(m_tInfo.fX, m_tInfo.fY, EFFECT_MGRANADE);
			CObjMgr::GetInstance()->AddGameObject(pEffect, OBJ_EFFECT);
				return 1;
			}	
	}


	//불렛과 윈도우창 충돌

	if(eType == BULLET_TOMA)
	{
		if(m_tInfo.fY > iWINCY )
			return 1;
	}
	else if(eType == BULLET_HEAVY || eType == BULLET_PISTOL)
	{
		if(m_tInfo.fX < 0|| m_tInfo.fY < 0)
			return 1;


		else if(m_tInfo.fX > iWINCX || m_tInfo.fY > iWINCY )
			return 1;
	}

	if(m_bDeadCheck == true)
	{	
		m_bDeadCheck = false;
		return 1;
	}
	
	if(eType == BULLET_BOSS)
	{
		if(m_tInfo.fY > 1750)
		{
			m_fSpeed = 0;
			m_dwState = BOSSBULLET;
		}
		else
		{
			m_dwState = BOSSBULLETSTAY;
		}
	}



	return 0;
}

void CBullet::Render(HDC _hdc)
{ 
	if(eType == BULLET_HEAVY)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			,60//(int)m_tInfo.fCX
			,60//(int)m_tInfo.fCY
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)		//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(0, 0, 0)  );
	}
	else if(eType == BULLET_PISTOL)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
			,(int)m_tInfo.fCX
			,(int)m_tInfo.fCY
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,0			//이미지에서의 시작 위치 X
			,0			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(0, 248, 0)  );
	}
	else if(eType == BULLET_TOMA)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)	+ m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)	+ m_ptScroll.y
			,(int)m_tInfo.fCX
			,(int)m_tInfo.fCY
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,0			//이미지에서의 시작 위치 X
			,0			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(0, 248, 0)  );
	}
	else 
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)	+ m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)	+ m_ptScroll.y
			,(int)m_tInfo.fCX
			,(int)m_tInfo.fCY
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)				//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
	}


	if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}

}

void CBullet::Release(void)
{

}

CBullet::CBullet(void)
{
}

CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir,eBulletType _eType)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eDir = _eDir;
	eType = _eType;
	Initialize();
}

CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir, eBulletType _eType, float _fAngle, DWORD _CurState)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eDir = _eDir;
	eType = _eType;
	m_fAngle = _fAngle;
	m_dwState = _CurState;

	Initialize();
}

CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir, eBulletType _eType, DWORD _CurState)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eDir = _eDir;
	eType = _eType;
	m_dwState = _CurState;

	Initialize();
}


CBullet::~CBullet(void)
{
	Release();
}

