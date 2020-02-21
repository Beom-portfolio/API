#pragma once

#include "gameobject.h"

class CPlayer :
	public CGameObject
{
//플레이어 모션
private:
	//속도.
	float	m_fSpeed;		//플레이어 이동속도

	DWORD	m_Time;
	DWORD	m_SoundTime;

	float	m_fTime;
	//bool	m_bJump;		//플레이어 점프

//총알
private:
	float	m_fBarrelX;
	float	m_fBarrelY;
	CGameObject*	pBullet;
	CGameObject*	pGranade;
	CGameObject*	pZombie;

	DWORD	m_ShotTime;

//대각선

	int ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction);

//폭탄
	DWORD	m_ThrowTime;

private:
	bool	m_bDirection;
	bool	m_bNifeCheck;

private:
	FRAME m_tFrame;
	DWORD m_dwState;
	DWORD m_dwPrevState;

	DWORD m_dwFrameTime;

	int iCount;

	float fTime;
	float fTimeDelayTime;

	//대각선
	bool bURTemp;
	bool bULTemp;
	bool bDRTemp;
	bool bDLTemp;

	bool _bURTemp;
	bool _bULTemp;
	bool _bDRemp;
	bool _bDLTemp;


private:
	void FrameMove(void);
	void SetFrame(void);

public:
	INFO	GetInfo(void) {return m_tInfo;}


private:
	void KeyInput(void);
	void Jump(void);

	void Shot(float fx, float fy, eBulletDirection _eDir, eBulletType _eType);
	void Throw(float fx, float fy, eGranadeType _eType, bool Direction);
	void ShotHeavy(float fx, float fy, eBulletDirection _eDir, eBulletType _eType, float _fAngle, DWORD _CurState);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	void CreateUR(void);
	void CreateDR(void);
	void CreateUL(void);
	void CreateDL(void);

public:
	CPlayer(void);
	CPlayer(float _fx, float _fy);
	virtual ~CPlayer(void);
};
