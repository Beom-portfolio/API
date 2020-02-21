#pragma once

#include "Define.h"

class CBitBmp
{
private:
	HDC			m_hdc, m_MemDC;	
	//���� �׸��� ����Ǵ� DC
	HBITMAP		m_bitmap, m_oldbitmap;

public:
	HDC		GetMemDC(void){ return m_MemDC; }

public:
	CBitBmp* LoadBmp(PTCHAR pFileName);
	void	 Release(void);

public:
	CBitBmp(void);
	~CBitBmp(void);
};
