#include "StdAfx.h"
#include "InsertCoin.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "MyButton.h"
#include "ObjMgr.h"

CInsertCoin::CInsertCoin(void)
{
}

CInsertCoin::~CInsertCoin(void)
{
}

void CInsertCoin::Initialize(void)
{
	CGameObject::SetBitBmp(&m_mapBmp);

	m_TimeCount = GetTickCount();

	m_iCoin = 0;
	m_iCoin_Ten = 0;
	m_iCoin_Ten_Count = 0;

	m_mapBmp.insert( make_pair("COIN_BACKGROUND",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Logo_Coin.bmp") ) );

	m_mapBmp.insert( make_pair("COIN_NUM_TEN",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_ONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num.bmp") ) );


}

int  CInsertCoin::Update(void)
{

	if(m_TimeCount + 100 <= GetTickCount())
	{
		if(GetAsyncKeyState('5'))
		{
			m_iCoin += 1;
			m_iCoin_Ten += 1;

			m_TimeCount = GetTickCount();
		}
	}

	
	//10�� �ڸ� ���� ���߱� ����

	if(	m_iCoin_Ten / 9 )
	{
		m_iCoin_Ten_Count += 1;
		m_iCoin_Ten = -1;
	}

	return 0;
}

void CInsertCoin::Render(HDC _hdc)
{
	BitBlt(m_mapBmp["COIN_BACKGROUND"]->GetMemDC()
		,0		//�׷��� ��ġ X
		,0		//�׷��� ��ġ Y
		,iWINCX	//�׷��� ũ�� X
		,iWINCY //�׷��� ũ�� Y
		,m_mapBmp["COIN_BACKGROUND"]->GetMemDC()
		,0		//�̹��������� ���� ��ġ X
		,0							//�̹��������� ���� ��ġ Y
		,SRCCOPY);		//�޴� ������ �����.

	CObjMgr::GetInstance()->Render(m_mapBmp["COIN_BACKGROUND"]->GetMemDC());

	BitBlt(_hdc
		,0					//�׷��� ��ġ X
		,0					//�׷��� ��ġ Y
		,iWINCX		//�׷��� ũ�� X
		,iWINCY		//�׷��� ũ�� Y
		,m_mapBmp["COIN_BACKGROUND"]->GetMemDC()		//�ε��� �̹���
		,0		//�̹��������� ���� ��ġ X
		,0		//�̹��������� ���� ��ġ Y
		,SRCCOPY);

	

	
	TransparentBlt(_hdc
		,712
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_TEN"]->GetMemDC()
		,11 * m_iCoin_Ten_Count
		,0
		,11 		
		,8
		,RGB(255, 0, 255)	);

	//���� 1�� �ڸ���


	TransparentBlt(_hdc
		,735
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_ONE"]->GetMemDC()
		,11 * (m_iCoin % 10)
		,0
		,11
		,8
		,RGB(255, 0, 255)	);
}

void CInsertCoin::Release(void)
{
}
