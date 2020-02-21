#pragma once
#include "gameobject.h"

class CMouse :
	public CGameObject
{
private:
	POINT	m_ptMouse;

public:
	POINT* GetMousePos(void)
	{
		return &m_ptMouse;
	}

public:
	virtual void Initialize(void);	
	virtual int	 Update(void);		
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMouse(void);
	virtual ~CMouse(void);
};
