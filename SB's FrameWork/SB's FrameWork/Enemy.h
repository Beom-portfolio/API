#pragma once
#include "gameobject.h"

class CEnemy :
	public CGameObject
{
private:
	eGranadeType	eType;

	float		m_fAngle;
	float		m_fAngleSpeed;

	bool		m_bDirection;

	DWORD		m_MotionTime;

	//플레이어 좌표
	INFO		m_PlayerInfo;

	CGameObject* pGranade;

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
	CEnemy(void);
	CEnemy::CEnemy(float m_tInfo_x, float m_tInfo_y);
	virtual ~CEnemy(void);
};
