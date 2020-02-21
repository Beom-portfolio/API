#pragma once

#include "Include.h"

class CBitBmp;
class CGameObject
{
public:
	static	list<LINE*>	 m_LineList;
	static	POINT		 m_ptScroll;

protected:
	INFO	m_tInfo;
	string	m_strName;
	
	RECT    m_Rect;

	float   m_fSpeed;

	bool	m_bDeadCheck;

	bool	m_bJump;

	//효과용
	CGameObject*	pEffect;

	CGameObject*	pPlayer;
	CGameObject*	pPlayer_Leg;
	CGameObject*	pPlayerZombie;
	//string m_strTag;
	
	//hp
	int		m_iHp;

	//공격력
	int		m_iAtt;

protected:
	static map<string, CBitBmp*>*	m_mapBmp;

public:
	static void SetBitBmp(map<string, CBitBmp*>* pMap);
	
	void SetPos(float _fx, float _fy)
	{
		m_tInfo.fX = _fx;
		m_tInfo.fY = _fy;
	}


public:
	RECT* GetRect(void)
	{
		return &m_Rect;
	}

	INFO GetInfo(void) { return m_tInfo; }

	void CollisionLine(bool & m_bJump);
	void CollisionLine_M(void);
	bool CollisionLine_BG(void);

public:
	void SetDamage(int iAtt)
	{
		m_iHp -= iAtt;
		return;
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
