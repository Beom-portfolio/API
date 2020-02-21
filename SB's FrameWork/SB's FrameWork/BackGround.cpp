#include "StdAfx.h"
#include "BackGround.h"
#include "KeyMgr.h"
#include "Mouse.h"
#include "Factory.h"
#include "ObjMgr.h"


void CBackGround::Initialize(void)
{

	//라인 에디터
	//ZeroMemory(&m_StartLinePoint, sizeof(LINE));

	//m_bDrawCheck = false;

	//마우스 객체 추가

	LINE* pLine = new LINE;

	m_tInfo = INFO(0, -90, 15326, 2080);
	m_strName = "BACKGROUND";

	LoadData();
}

int CBackGround::Update(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	//if(dwKey & KEY_H)
	//{
	//	m_ptScroll.x += 10;
	//}
	//if(dwKey & KEY_J)
	//{
	//	m_ptScroll.x -= 10;
	//}
	if(dwKey & KEY_N)
	{
		m_ptScroll.y -= 10;
	}

	//LineDraw();

	return 0;
}

void CBackGround::Render(HDC _hdc)
{
	BitBlt(_hdc
		,m_tInfo.fX + m_ptScroll.x					//그려질 위치 X
		,m_tInfo.fY	+ m_ptScroll.y				//그려질 위치 Y
		,(int)m_tInfo.fCX		//그려질 크기 X
		,(int)m_tInfo.fCY		//그려질 크기 Y
		,(*m_mapBmp)[m_strName]->GetMemDC()		//로드한 이미지
		,0		//이미지에서의 시작 위치 X
		,0		//이미지에서의 시작 위치 Y
		,SRCCOPY);

	if(GetAsyncKeyState('Q'))
	{

		list<LINE*>::iterator iter = m_LineList.begin();

		for(iter; iter != m_LineList.end(); ++iter)
		{
			MoveToEx(_hdc, (int)(*iter)->fStartX + m_ptScroll.x, (int)(*iter)->fStartY + m_ptScroll.y, NULL);

			LineTo(_hdc, (int)(*iter)->fEndX + m_ptScroll.x, (int)(*iter)->fEndY + m_ptScroll.y);
		}
	}
}

void CBackGround::Release(void)
{

}

CBackGround::CBackGround(void)
{
}

CBackGround::~CBackGround(void)
{
	Release();
}

///라인 에디터
void CBackGround::LineDraw(void)
{
	POINT ptMouse = *dynamic_cast<CMouse*>(CObjMgr::GetInstance()->GetList()[OBJ_MOUSE].front())
		->GetMousePos();

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(dwKey & KEY_K)
	{
		//SaveData();
	}

	if(dwKey & KEY_L)
	{
		//LoadData();
	}

	if(dwKey & KEY_S)
	{
		m_StartLinePoint.fStartX = (float)ptMouse.x;
		m_StartLinePoint.fStartY = (float)ptMouse.y;
	}

	if(GetAsyncKeyState(VK_LBUTTON))
	{
		if(m_bDrawCheck)
			return;

		m_bDrawCheck = true;

		if(m_LineList.empty() == true)
		{
			m_LineList.push_back( new LINE(m_StartLinePoint.fStartX
				,m_StartLinePoint.fStartY
				,(float)ptMouse.x
				,(float)ptMouse.y) );
		}
		else
		{
			m_LineList.push_back( new LINE(m_StartLinePoint.fEndX
				,m_StartLinePoint.fEndY
				,(float)ptMouse.x - m_ptScroll.x
				,(float)ptMouse.y - m_ptScroll.y) );
		}

		m_StartLinePoint.fEndX = (float)ptMouse.x - m_ptScroll.x;
		m_StartLinePoint.fEndY = (float)ptMouse.y - m_ptScroll.y;

	}
	else
		m_bDrawCheck = false;
}

void CBackGround::SaveData(void)
{
	DWORD dwByte;

	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_WRITE,
		NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	list<LINE*>::iterator iter = m_LineList.begin();

	for( ; iter !=  m_LineList.end(); ++iter )
	{
		WriteFile(hFile, (*iter), sizeof(LINE), &dwByte, NULL);
	}

	CloseHandle(hFile);
}

void CBackGround::LoadData(void)
{
	DWORD dwByte;

	HANDLE hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ,
		NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while(true)
	{
		LINE* pLine = new LINE;

		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);

		if(dwByte == 0)
		{
			SAFE_DELETE(pLine);
			break;
		}

		m_LineList.push_back(pLine);
	}

	CloseHandle(hFile);
}
