#include "StdAfx.h"
#include "MyButton.h"


void CMyButton::Initialize(void)
{

}

int CMyButton::Update(void)
{

	return 0;
}

void CMyButton::Render(HDC _hdc)
{
}

void CMyButton::Release(void)
{
}

CMyButton::CMyButton(void)
{
	m_iDrawID = 0;
}

CMyButton::CMyButton(string strName, float _fx, float _fy, float _fcx, float _fcy)
:CGameObject(strName, _fx, _fy, _fcx, _fcy)
{
	m_iDrawID = 0;
}

CMyButton::~CMyButton(void)
{
	Release();
}
