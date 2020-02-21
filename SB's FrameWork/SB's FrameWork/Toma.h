#pragma once
#include "gameobject.h"

class CToma :
	public CGameObject
{
private:
	eBulletType	eType;

	bool		m_bDirection;

	DWORD		m_MotionTime;

	//플레이어 좌표
	INFO		m_PlayerInfo;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;
	DWORD m_dwFrameTime;

	DWORD m_Time;
	


public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void FrameMove(void);
	void SetFrame(void);

private:
	void Attack(float m_tInfo_x, float m_tInfo_y);

public:
	CToma(void);
	CToma(float m_tInfo_x, float m_tInfo_y);
	virtual ~CToma(void);
};
