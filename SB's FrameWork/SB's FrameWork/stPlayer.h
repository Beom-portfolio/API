#pragma once
#include "scene.h"

class CPlayer;

class CstPlayer :
	public CScene
{
public:
	INFO			m_pPlayer;
	CPlayer*		m_p;

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CstPlayer(void);
	virtual ~CstPlayer(void);
};
