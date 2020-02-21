#pragma once
#include "gameobject.h"

class CPlayer :
	public CGameObject
{
public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);


public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
