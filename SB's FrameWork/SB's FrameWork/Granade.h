#pragma once
#include "gameobject.h"

class CGranade :
	public CGameObject
{
private:
	eGranadeType	eType;

	float		m_fAngle;
	float		m_fAngleSpeed;

	bool		m_bDirection;

	float		m_fAngleY;
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

public:
	CGranade(void);
	CGranade(float m_tInfo_x, float m_tInfo_y, eGranadeType _eType, bool Direction);
	virtual ~CGranade(void);
};
