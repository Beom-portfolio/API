#pragma once
#include "gameobject.h"

class CBullet :
	public CGameObject
{
private:
	eBulletDirection eDir;

	eBulletType		 eType;

	//각도 받기

	float		m_fAngle;

	bool		m_bDeadCheck;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;

	DWORD m_dwFrameTime;

private:
	void FrameMove(void);
	void SetFrame(void);

	int ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction);


public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CBullet(void);
	CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir, eBulletType _eType);
	CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir, eBulletType _eType, float _fAngle, DWORD _CurState);
	CBullet::CBullet(float m_tInfo_x, float m_tInfo_y, eBulletDirection _eDir, eBulletType _eType, DWORD _CurState);
	virtual ~CBullet(void);
};
