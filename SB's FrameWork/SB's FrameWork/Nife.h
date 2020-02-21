#pragma once
#include "gameobject.h"

class CNife :
	public CGameObject
{
//플레이어 모션
private:
	//속도.
	float	m_fSpeed;		//플레이어 이동속도
	
	float   m_fTime;

private:
	bool	m_bDirection;
	bool	m_bJump;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;

	DWORD m_dwFrameTime;

private:
	void FrameMove(void);
	void SetFrame(void);

private:
	void KeyInput(void);
	void Jump(void);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CNife(void);
	virtual ~CNife(void);
};