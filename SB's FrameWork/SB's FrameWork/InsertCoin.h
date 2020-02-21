#pragma once
#include "scene.h"

///////////////////������ �־����� ���

class CInsertCoin
	:	public CScene
{
private:
	int		m_iDrawID_Insert;			//�־�����.
	int		m_iCoin;					//���Ӿȿ��� �� ���ΰ���
	
	//10�� �ڸ� ���ڸ� ���ϱ� ����
	int		m_iCoin_Ten;
	int		m_iCoin_Ten_Count;

	DWORD	m_TimeCount;

public:
	int		GetCoin(void) { return m_iCoin; }

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	

public:
	CInsertCoin(void);
	virtual ~CInsertCoin(void);
};
