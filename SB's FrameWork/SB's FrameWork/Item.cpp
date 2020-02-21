#include "StdAfx.h"
#include "Item.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "Factory.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "Player.h"
#include "Stage.h"
#include "CollisionMgr.h"


void CItem::Initialize(void)
{

	switch(eType)
	{
	case ITEM_HEAVY:
		m_strName = "ITEM_HEAVY";
		m_tInfo.fCX = 32;
		m_tInfo.fCY = 30;
		break;

	case ITEM_BOMB:
		m_strName = "ITEM_BOMB";
		m_tInfo.fCX = 200;
		m_tInfo.fCY = 200;
		break;
	}

}

int CItem::Update(void)
{

	CGameObject::Update();

	switch(eType)
	{
	case ITEM_HEAVY:
		m_Rect.left		= m_Rect.left	 +  m_ptScroll.x;
		m_Rect.top		= m_Rect.top	 +  m_ptScroll.y;
		m_Rect.right	= m_Rect.right	 +  m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom	 +  m_ptScroll.y;
		break;

	case ITEM_BOMB:
		m_Rect.left		= m_Rect.left	  +  m_ptScroll.x;
		m_Rect.top		= m_Rect.top	  +  m_ptScroll.y;
		m_Rect.right	= m_Rect.right	  +  m_ptScroll.x;
		m_Rect.bottom	= m_Rect.bottom	  +  m_ptScroll.y;
		break;
	}
	

	CollisionLine_M();


	//플레이어와 아이템 충돌
	CGameObject* pPlayer = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front();


	if( CCollisionMgr::GetInstance()->CollisionBullet(pPlayer->GetRect(), &m_Rect) == true )
	{
		switch(eType)
		{
		case ITEM_HEAVY:
			CSoundMgr::GetInstance()->PlaySound(L"HeavyMachineGun.mp3");
			if(CStage::m_bHeavy == false)
			{
				CStage::m_bPistolInfiniteBullet = false;
				CStage::m_bHeavy = true;
				CStage::m_iHeavyBullet += 100;
			}
			else
			{
				CStage::m_iHeavyBullet += 100;
			}
			return 1;
		
		case ITEM_BOMB:
			if(CStage::m_bGranade == false)
			{
				CStage::m_bGranade = true;
				CStage::m_iGranadeBullet += 10;
			}
			else
			{
				CStage::m_iGranadeBullet += 10;
			}
			return 1;
		}
	}




	return 0;
}

void CItem::Render(HDC _hdc)
{

	switch(eType)
	{
	case ITEM_BOMB:
		
		TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)  +  m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)  +  m_ptScroll.y
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,0			//이미지에서의 시작 위치 X
		,0		//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(255, 0, 255)  );
		
		break;
	
	case ITEM_HEAVY:
		
		TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)  +  m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)  +  m_ptScroll.y
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,0	//이미지에서의 시작 위치 X
		,0		//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(255, 255, 255)  );
		
		break;
	}

		if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}

	
}

void CItem::Release(void)
{

}


CItem::CItem(void)
{
}

CItem::CItem(float m_tInfo_x, float m_tInfo_y, eItem _eType)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eType = _eType;
	Initialize();
}


CItem::~CItem(void)
{
	Release();
}
