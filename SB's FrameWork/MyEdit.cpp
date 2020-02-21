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
		,0					//그려질 위치 X
		,0					//그려질 위치 Y
		,iWINCX		//그려질 크기 X
		,iWINCY		//그려질 크기 Y
		,m_mapBmp["BACKGROUND"]->GetMemDC()		//로드한 이미지
		,0		//이미지에서의 시작 위치 X
		,0		//이미지에서의 시작 위치 Y
		,SRCCOPY);

	BitBlt(_hdc
		,0					//그려질 위치 X
		,0					//그려질 위치 Y
		,iWINCX		//그려질 크기 X
		,iWINCY		//그려질 크기 Y
		,m_mapBmp["BACKBUFFER"]->GetMemDC()		//로드한 이미지
		,0		//이미지에서의 시작 위치 X
		,0		//이미지에서의 시작 위치 Y
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
