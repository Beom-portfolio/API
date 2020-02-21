#pragma once
#include "gameobject.h"


class CBackGround :
	public CGameObject
{

public:
	//��
	LINE			m_StartLinePoint;
	bool			m_bDrawCheck;
	

	//���� �׸��� ������
private:
	void LineDraw(void);
	void SaveData(void);
	void LoadData(void);

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);

public:
	CBackGround(void);
	virtual ~CBackGround(void);
};
