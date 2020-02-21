#pragma once

#include "Include.h"

class CBitBmp;
class CGameObject
{
protected:
	INFO	m_tInfo;
	string	m_strName;

	//string m_strTag;

protected:
	static map<string, CBitBmp*>*	m_mapBmp;

public:
	static void SetBitBmp(map<string, CBitBmp*>* pMap);

public:
	RECT GetRect(void)
	{
		RECT rc =
		{
			long(m_tInfo.fX - m_tInfo.fCX / 2.f),
			long(m_tInfo.fY - m_tInfo.fCY / 2.f),
			long(m_tInfo.fX + m_tInfo.fCX / 2.f),
			long(m_tInfo.fY + m_tInfo.fCY / 2.f),
		};

		return rc;
	}

public:
	virtual void Initialize(void)PURE;
	virtual int  Update(void)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;

public:
	CGameObject(void);
	CGameObject(string strName, float _fx, float _fy, float _fcx, float _fcy);
	virtual ~CGameObject(void);
};
