#pragma once

#include "Define.h"

class CBitBmp
{
private:
	HDC			m_hdc, m_MemDC;	
	//실제 그림이 저장되는 DC
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
