#pragma once
#include "scene.h"

/////////�޴�(���� �ֱ���)�� ����ϱ� ���� Ŭ���� ( ȭ�� ������ )

class CMyMenu :
	public CScene
{
private:
	int		m_iDrawID_Menu;
	

	DWORD	m_TimeCount;


	bool	m_bStartPoint;


public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	
public:
	CMyMenu(void);
	virtual ~CMyMenu(void);
};
