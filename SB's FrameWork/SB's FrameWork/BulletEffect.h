#pragma once
#include "gameobject.h"

class CBulletEffect :
	public CGameObject
{
private:
	eEffectType	eType;

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

public:
	bool EffectEnd(int _FrameIndex);

public:
	CBulletEffect(void);
	CBulletEffect(float m_tInfo_x, float m_tInfo_y, eEffectType _eType);
	virtual ~CBulletEffect(void);
};

