#include "StdAfx.h"
#include "GameObject.h"

map<string, CBitBmp*>* CGameObject::m_mapBmp;

void CGameObject::SetBitBmp(map<string, CBitBmp*>* pMap)
{
	m_mapBmp = pMap;
}

CGameObject::CGameObject(void)
{
}

CGameObject::CGameObject(string strName, float _fx, float _fy, float _fcx, float _fcy)
:m_tInfo(_fx, _fy, _fcx, _fcy)
,m_strName(strName)
{

}

CGameObject::~CGameObject(void)
{
}
