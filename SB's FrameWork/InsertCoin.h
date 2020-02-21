#pragma once
#include "scene.h"

///////////////////코인을 넣었을때 장면

class CInsertCoin
	:	public CScene
{
private:
	int		m_iDrawID_Insert;			//넣었을때.
	int		m_iCoin;					//게임안에서 쓸 코인갯수
	
	//10의 자리 숫자를 구하기 위함
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
