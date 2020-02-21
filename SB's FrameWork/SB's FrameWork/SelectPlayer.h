#pragma once
#include "scene.h"

class CSelectPlayer :
	public CScene
{

private:
	DWORD m_LOGO_Time;
	int m_iDrawID_LOGO;

//선택
	DWORD m_SELECT_Time;
	int m_iDrawID_SELECT;

//선택시
	DWORD m_SELECTED_Time;
	int m_iDrawID_SELECTED;

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CSelectPlayer(void);
	virtual ~CSelectPlayer(void);
};
