#pragma once
#include "scene.h"

class CMyEdit :
	public CScene
{
public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CMyEdit(void);
	virtual ~CMyEdit(void);
};
