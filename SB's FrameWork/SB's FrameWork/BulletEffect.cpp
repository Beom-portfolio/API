#include "StdAfx.h"
#include "BulletEffect.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"

void CBulletEffect::Initialize(void)
{
	m_dwState = EFFECT_MGRANADE;
	m_dwPrevState = EFFECT_MGRANADE;

	m_dwFrameTime = GetTickCount();

	switch(eType)
	{
	case EFFECT_MGRANADE:
		m_strName = "MGRANADE_EFFECT";
		m_tFrame = FRAME(0, 27, 0, 10);
		m_tInfo.fCX = 50;
		m_tInfo.fCY = 50;
		break;

	case EFFECT_GRANADE:
		m_strName = "GRANADE_EFFECT";
		m_tFrame = FRAME(0, 22, 0, 10);
		m_tInfo.fCX = 100;
		m_tInfo.fCY = 200;
		break;

	case EFFECT_PISTOL:
		m_strName = "PISTOL_EFFECT";
		m_tFrame = FRAME(0, 9, 0, 30);
		m_tInfo.fCX = 32;
		m_tInfo.fCY = 32;
		break;

	case EFFECT_BIGEXPLOSION:
		m_strName = "BIG_EFFECT";
		m_tFrame = FRAME(0, 27, 0, 30);
		m_tInfo.fCX = 170;
		m_tInfo.fCY = 170;
		break;
	}
}

void CBulletEffect::FrameMove(void)
{
	//if(m_dwState != m_dwPrevState)
	//{
	//	//상태가 변경됨.
	//	switch(m_dwState)
	//	{
	//	case EFFECT_MGRANADE:
	//		m_tFrame = FRAME(0, 31, 0, 10);
	//		break;
	//	}

	//	m_dwPrevState = m_dwState;
	//}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		m_tFrame.iFrameStart = 0;

		if(m_dwState != EFFECT_MGRANADE)
		{
			m_dwState = EFFECT_MGRANADE;
		}
	}

}

bool CBulletEffect::EffectEnd(int _FrameIndex)
{
	if(m_tFrame.iFrameStart == _FrameIndex)
	{
		return true;
	}

	return false;
}


void CBulletEffect::SetFrame(void)
{
	
}

int CBulletEffect::Update(void)
{
	SetFrame();
	FrameMove();

	CGameObject::Update();

	m_Rect.left   = m_Rect.left    + m_ptScroll.x;
	m_Rect.top    = m_Rect.top	   + m_ptScroll.y;
	m_Rect.right  = m_Rect.right   + m_ptScroll.x;
	m_Rect.bottom = m_Rect.bottom  + m_ptScroll.y;

	switch(eType)
	{
	case EFFECT_MGRANADE:
		if(EffectEnd(27) == true)
		{
			return 1;
		}
		else
			break;

	case EFFECT_GRANADE:
		if(EffectEnd(22) == true)
		{
			return 1;
		}
		else
			break;

	case EFFECT_PISTOL:
		if(EffectEnd(9) == true)
		{
			return 1;
		}
		else
			break;

	case EFFECT_BIGEXPLOSION:
		if(EffectEnd(27) == true)
		{
			return 1;
		}
		else
			break;
	}

	
	return 0;
}

void CBulletEffect::Render(HDC _hdc)
{

	switch(eType)
	{
	case EFFECT_GRANADE:
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)  
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)  - 40
			,(int)m_tInfo.fCX + 10
			,(int)m_tInfo.fCY + 10
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
		
		break;
	case EFFECT_PISTOL:
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
		break;

	default:
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)  + m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f)  + m_ptScroll.y
			,(int)m_tInfo.fCX + 10 
			,(int)m_tInfo.fCY + 10
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
			,(int)m_tInfo.fCX		//이미지의 범위 X
			,(int)m_tInfo.fCY		//이미지의 범위 Y
			,RGB(255, 0, 255)  );
		break;
	}

		if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	}
}

void CBulletEffect::Release(void)
{

}

CBulletEffect::CBulletEffect(void)
{
}

CBulletEffect::CBulletEffect(float m_tInfo_x, float m_tInfo_y, eEffectType _eType)
{
	m_tInfo.fX = m_tInfo_x;
	m_tInfo.fY = m_tInfo_y;
	eType = _eType;
	Initialize();
}

CBulletEffect::~CBulletEffect(void)
{
	Release();
}