#pragma once
#include "gameobject.h"

class CPlayerLeg :
	public CGameObject
{
private:
	//�ӵ�
	float	m_fSpeed;
	////���� �Ĵٺ��� 
	bool	m_bUpCheck;
	//
	////�ޱ׸���
	////bool	m_bDuckCheck;

	////����.
	DWORD	m_Time;
	float	m_fTime;
	//bool	m_bJump;		//�÷��̾� ����

	bool	m_bJumpDown;	//�����ϸ鼭 �Ʒ�.

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
