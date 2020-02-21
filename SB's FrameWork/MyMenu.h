#pragma once
#include "scene.h"

/////////메뉴(코인 넣기전)를 출력하기 위한 클래스 ( 화면 깜빡임 )

class CMyMenu :
	public CScene
{
private:
	int		m_iDrawID_Menu;
	

	DWORD	m_TimeCount;
	DWORD	m_TimeCoin;


public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	
public:
	CMyMenu(void);
	virtual ~CMyMenu(void);
};
