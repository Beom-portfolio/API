#pragma once
#include "gameobject.h"

class CBig :
	public CGameObject
{
//�÷��̾� ���
private:
	//�ӵ�.
	float	m_fSpeed;		//�÷��̾� �̵��ӵ�

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
	CBig(void);
	virtual ~CBig(void);
};
