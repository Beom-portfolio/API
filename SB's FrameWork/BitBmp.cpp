#include "StdAfx.h"
#include "BitBmp.h"

CBitBmp::CBitBmp(void)
{
}

CBitBmp::~CBitBmp(void)
{
	Release();
}

CBitBmp* CBitBmp::LoadBmp(PTCHAR pFileName)
{
	m_hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);
	//택스쳐를 그릴수 있는 DC생성.

	m_bitmap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(!m_bitmap)
		MessageBox(g_hWnd, pFileName, L"이미지 로드 실패", NULL);

	m_oldbitmap = (HBITMAP)SelectObject(m_MemDC, m_bitmap);

	ReleaseDC(g_hWnd, m_hdc);

	return this;
}

void CBitBmp::Release(void)
{
	SelectObject(m_MemDC, m_oldbitmap);
	DeleteObject(m_bitmap);
	DeleteDC(m_MemDC);
}