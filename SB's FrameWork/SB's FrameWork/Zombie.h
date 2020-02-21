#pragma once
#include "gameobject.h"

class CZombie :
	public CGameObject
{
private:
	eGranadeType	eType;

	DWORD	m_MotionTime;

	bool		m_bDirection;

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
	int ActionState(DWORD dwCurState , int _FrameIndex, eCurAction eAction);
public:
	CZombie(void);
	CZombie::CZombie(float m_tInfo_x, float m_tInfo_y);
	virtual ~CZombie(void);
};
