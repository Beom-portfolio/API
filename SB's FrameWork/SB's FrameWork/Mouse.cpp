#include "StdAfx.h"
#include "Mouse.h"

CMouse::CMouse(void)
{
}

CMouse::~CMouse(void)
{
}

void CMouse::Initialize(void)
{
	m_tInfo.fCX = 50;
	m_tInfo.fCY = 50;

	m_ptMouse.x = 0;
	m_ptMouse.y = 0;
}

int CMouse::Update(void)
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	m_tInfo.fX = static_cast<float>(m_ptMouse.x);
	m_tInfo.fY = static_cast<float>(m_ptMouse.y);

	CGameObject::Update();

	return 0;
}	

void CMouse::Render(HDC _hdc)
{
	Ellipse(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
}

void CMouse::Release(void)
{

}

