#pragma once

#include "gameobject.h"

class CMyButton:
	public CGameObject
{
private:
	int		m_iDrawID;

public:
	virtual void Initialize(void);
	virtual int Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMyButton(void);
	CMyButton(string strName, float _fx, float _fy, float _fcx, float _fcy);
	virtual ~CMyButton(void);
};
