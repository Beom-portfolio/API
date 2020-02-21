#pragma once
#include "gameobject.h"

class CBoss :
	public CGameObject
{

private:
	eBulletType	eType;

	bool		m_bDirection;

	DWORD		m_MotionTime;
	DWORD		m_AttackTime;

	//플레이어 좌표
	INFO		m_PlayerInfo;

	CGameObject* pBullet;

	//
	bool		m_bAtt;
	bool		m_bCharge;	
	bool		m_MoveStart;
	bool		m_SoundChange;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;
	DWORD m_dwFrameTime;

	DWORD m_Time;

	DWORD m_DeadTime;

	int iDeadCount;

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
	void Attack(float m_tInfo_x, float m_tInfo_y);

public:
	CBoss(void);
	CBoss::CBoss(float m_tInfo_x, float m_tInfo_y);
	virtual ~CBoss(void);
};
