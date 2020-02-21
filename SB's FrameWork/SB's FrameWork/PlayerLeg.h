#pragma once
#include "gameobject.h"

class CPlayerLeg :
	public CGameObject
{
private:
	//속도
	float	m_fSpeed;
	////위를 쳐다볼때 
	bool	m_bUpCheck;
	//
	////쭈그릴때
	////bool	m_bDuckCheck;

	////점프.
	DWORD	m_Time;
	float	m_fTime;
	//bool	m_bJump;		//플레이어 점프

	bool	m_bJumpDown;	//점프하면서 아래.

private:
	bool	m_bDirection;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;

	DWORD m_dwFrameTime;

private:
	void FrameMove(void);
	void SetFrame(void);

public:
	INFO	GetInfo(void) {return m_tInfo;}


private:
	void KeyInput(void);
	void Jump(void);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);


public:
	CPlayerLeg(void);
	CPlayerLeg(float _fx, float _fy);
	virtual ~CPlayerLeg(void);
};
