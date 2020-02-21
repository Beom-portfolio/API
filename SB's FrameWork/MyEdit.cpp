#include "StdAfx.h"
#include "MyEdit.h"
#include "GameObject.h"

void CMyEdit::Initialize(void)
{
	CGameObject::SetBitBmp(&m_mapBmp);

	m_mapBmp.insert( make_pair("BACKGROUND",
		(new CBitBmp)->LoadBmp(L"../Resource/Back.bmp") ) );

	m_mapBmp.insert( make_pair("BACKBUFFER",
		(new CBitBmp)->LoadBmp(L"../Resource/BackBuffer.bmp") ) );
	
	m_mapBmp.insert( make_pair("TILE",
		(new CBitBmp)->LoadBmp(L"../Resource/Tile.bmp") ) );

}

int CMyEdit::Update(void)
{
	return 0;
}

void CMyEdit::Render(HDC _hdc)
{
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,0					//�׷��� ��ġ X
		,0					//�׷��� ��ġ Y
		,iWINCX		//�׷��� ũ�� X
		,iWINCY		//�׷��� ũ�� Y
		,m_mapBmp["BACKGROUND"]->GetMemDC()		//�ε��� �̹���
		,0		//�̹��������� ���� ��ġ X
		,0		//�̹��������� ���� ��ġ Y
		,SRCCOPY);

	BitBlt(_hdc
		,0					//�׷��� ��ġ X
		,0					//�׷��� ��ġ Y
		,iWINCX		//�׷��� ũ�� X
		,iWINCY		//�׷��� ũ�� Y
		,m_mapBmp["BACKBUFFER"]->GetMemDC()		//�ε��� �̹���
		,0		//�̹��������� ���� ��ġ X
		,0		//�̹��������� ���� ��ġ Y
		,SRCCOPY);
}

void CMyEdit::Release(void)
{

}

CMyEdit::CMyEdit(void)
{
}

CMyEdit::~CMyEdit(void)
{
	Release();
}
