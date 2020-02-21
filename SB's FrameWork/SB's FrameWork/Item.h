#pragma once
#include "gameobject.h"

class CItem :
	public CGameObject
{
private:
	eItem	eType;

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CItem(void);
	CItem(float m_tInfo_x, float m_tInfo_y, eItem _eType);
	virtual ~CItem(void);
};
