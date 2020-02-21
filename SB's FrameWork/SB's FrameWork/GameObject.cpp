#include "StdAfx.h"
#include "GameObject.h"
#include "ObjMgr.h"

list<LINE*> CGameObject::m_LineList;
map<string, CBitBmp*>* CGameObject::m_mapBmp;
POINT		CGameObject::m_ptScroll;

void CGameObject::SetBitBmp(map<string, CBitBmp*>* pMap)
{
	m_mapBmp = pMap;
}

CGameObject::CGameObject(void)
{
	memset(&m_tInfo, 0, sizeof(INFO));
	memset(&m_Rect, 0, sizeof(RECT));
}

CGameObject::CGameObject(string strName, float _fx, float _fy, float _fcx, float _fcy)
:m_tInfo(_fx, _fy, _fcx, _fcy)
,m_strName(strName)
{

}

CGameObject::~CGameObject(void)
{
}

int CGameObject::Update(void)
{
	m_Rect.left		= static_cast<LONG>(m_tInfo.fX - m_tInfo.fCX / 2.f);	
	m_Rect.top		= static_cast<LONG>(m_tInfo.fY - m_tInfo.fCY / 2.f);	
	m_Rect.right		= static_cast<LONG>(m_tInfo.fX + m_tInfo.fCX / 2.f);	
	m_Rect.bottom		= static_cast<LONG>(m_tInfo.fY + m_tInfo.fCY / 2.f);	


	return 0;
}

void CGameObject::CollisionLine(bool& m_bJump)
{
	////BackGroundX : 15326
	float fBackGroundX = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCX;
	//
	////BackGroundY : 2080
	float fBackGroundY = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCY;

	for(list<LINE*>::iterator iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		//기울기를 구하자.
		if( (*iter)->fStartX <= m_tInfo.fX && (*iter)->fEndX > m_tInfo.fX )
		{
			//float fX = abs( (*iter)->fEndX - (*iter)->fStartX );
			//float fY = abs( (*iter)->fEndY - (*iter)->fStartY );

			float fX = ( (*iter)->fEndX - (*iter)->fStartX );
			float fY = -( (*iter)->fEndY - (*iter)->fStartY );

			//기울기.
			//float fSlope = fY / fX;

			float fSlope = 0;

			if(fY != 0)
				fSlope = fY / fX;

			float fHeight = (*iter)->fStartY - abs( (*iter)->fStartX - m_tInfo.fX ) * fSlope;

			
			//m_tInfo.fY = fHeight;

			if(m_bJump != true || m_tInfo.fY > fHeight)
			{
				m_bJump = false;
				m_tInfo.fY = fHeight;
			}

			//질문
			/*if(m_tInfo.fY < 0 && m_tInfo.fY < (fBackGroundY - iWINCY / 2.f) )
				m_ptScroll.y += (long)m_fSpeed;
			
			if(m_tInfo.fY >= iWINCY / 2.f && m_ptScroll.y > -(fBackGroundY - iWINCY) )
				m_ptScroll.y -= (long)m_fSpeed;*/
		}
	}
}

void CGameObject::CollisionLine_M(void)
{
	for(list<LINE*>::iterator iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		//기울기를 구하자.
		if( (*iter)->fStartX <= m_tInfo.fX && (*iter)->fEndX > m_tInfo.fX )
		{
			//float fX = abs( (*iter)->fEndX - (*iter)->fStartX );
			//float fY = abs( (*iter)->fEndY - (*iter)->fStartY );

			float fX = ( (*iter)->fEndX - (*iter)->fStartX );
			float fY = -( (*iter)->fEndY - (*iter)->fStartY );

			//기울기.
			//float fSlope = fY / fX;

			float fSlope = 0;

			if(fY != 0)
				fSlope = fY / fX;

			float fHeight = (*iter)->fStartY - abs( (*iter)->fStartX - m_tInfo.fX ) * fSlope;

			m_tInfo.fY = fHeight;

		}
	}
}

//점선 충돌.

bool CGameObject::CollisionLine_BG(void)
{
	for(list<LINE*>::iterator iter = m_LineList.begin();
		iter != m_LineList.end(); ++iter)
	{
		//기울기를 구하자.
		if( (*iter)->fStartX <= m_tInfo.fX && (*iter)->fEndX > m_tInfo.fX )
		{
			//float fX = abs( (*iter)->fEndX - (*iter)->fStartX );
			//float fY = abs( (*iter)->fEndY - (*iter)->fStartY );

			float fX = ( (*iter)->fEndX - (*iter)->fStartX );
			float fY = -( (*iter)->fEndY - (*iter)->fStartY );

			if(m_tInfo.fY >= (*iter)->fStartY || m_tInfo.fY >= (*iter)->fEndY)
				return true;

			//기울기.
			//float fSlope = fY / fX;

			//float fSlope = 0;

			//if(fY != 0)
			//	fSlope = fY / fX;

			//float fHeight = (*iter)->fStartY - abs( (*iter)->fStartX - m_tInfo.fX ) * fSlope;

			//if(m_tInfo.fY == fHeight)
			//	return true;
		}
	}
	return false;
}
