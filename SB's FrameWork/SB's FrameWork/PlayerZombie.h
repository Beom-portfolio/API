#pragma once
#include "gameobject.h"

class CPlayerZombie :
	public CGameObject
{
	//�÷��̾� ���
private:
	//�ӵ�.
	float	m_fSpeed;		//�÷��̾� �̵��ӵ�

	DWORD	m_Time;
	float	m_fTime;
	bool	m_bJump;		//�÷��̾� ����


	//�Ѿ�
private:
	float			m_fBarrelX;
	float			m_fBarrelY;
	CGameObject*	pBullet;
	CGameObject*	pGranade;

	DWORD			m_ShotTime;

	//�밢��

	int ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction);

	//��ź
	DWORD	m_ThrowTime;

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
	INFO GetInfo(void) {return m_tInfo;}

private:
	void KeyInput(void);
	void Jump(void);

	void Shot(float fx, float fy, eBulletDirection _eDir, eBulletType _eType);
	void Throw(float fx, float fy, eGranadeType _eType, bool Direction);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CPlayerZombie(void);
	CPlayerZombie(float _fx, float _fy);
	virtual ~CPlayerZombie(void);
};
