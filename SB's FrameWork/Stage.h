#pragma once
#include "scene.h"

class CStage:
	public CScene
{
public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CStage(void);
	virtual ~CStage(void);
};
