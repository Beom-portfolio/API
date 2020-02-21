#include "StdAfx.h"
#include "SelectPlayer.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SoundMgr.h"
#include "GameObject.h"

CSelectPlayer::CSelectPlayer(void)
{
}

CSelectPlayer::~CSelectPlayer(void)
{
	Release();
}


void CSelectPlayer::Initialize(void)
{

	//���ý�	����
	m_iDrawID_LOGO   = 0;
	m_iDrawID_SELECT = 0;

	m_iDrawID_SELECTED = 0;

	//���� ����
	m_LOGO_Time   = GetTickCount();
	m_SELECT_Time = GetTickCount();

	////�����Է� �����ð�
	m_TimeCoin = GetTickCount();

	/////////////////////���� �ε�///////////////////////
	CSoundMgr::GetInstance()->PlayBGMSound(L"Barracks.mp3");



	//////////////////////�̹��� �ε�//////////////////////
	m_mapBmp.insert( make_pair("SELECTMAIN",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/1.bmp") ) );

	m_mapBmp.insert( make_pair("P1LOGO",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/P1.bmp") ) );

	m_mapBmp.insert( make_pair("BACKBUFFER",
		(new CBitBmp)->LoadBmp(L"../Sprite/BackBuffer1.bmp") ) );

	/////////////////////////////////////////////////////////
	m_mapBmp.insert( make_pair("MARCO1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Marco1.bmp") ) );
	m_mapBmp.insert( make_pair("MARCO2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Marco2.bmp") ) );
//
	m_mapBmp.insert( make_pair("ERI1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Eri1.bmp") ) );
	m_mapBmp.insert( make_pair("ERI2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Eri2.bmp") ) );
//
	m_mapBmp.insert( make_pair("TARMA1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma1.bmp") ) );
	m_mapBmp.insert( make_pair("TARMA2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma2.bmp") ) );
//���ý�
	m_mapBmp.insert( make_pair("TARMA3",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Tarma3.bmp") ) );
//
	m_mapBmp.insert( make_pair("FIO1",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Fio1.bmp") ) );
	m_mapBmp.insert( make_pair("FIO2",
		(new CBitBmp)->LoadBmp(L"../Sprite/Select/Fio2.bmp") ) );
	/////////////////////////////////////////////////////////

	//ũ����(����)
	m_mapBmp.insert( make_pair("CREDIT",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/credit.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_TEN",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_ONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );


}

int  CSelectPlayer::Update(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(m_TimeCoin + 100 <= GetTickCount())
	{
		if(dwKey & KEY_FIVE)
		{
			m_iCoin += 1;
			CSoundMgr::GetInstance()->PlaySound(L"Insert_Coin.mp3");
			m_TimeCoin = GetTickCount();
		}
	}

	if(m_SELECT_Time + 50 <= GetTickCount())
	{
		if(dwKey & KEY_LEFT)
		{
			m_iDrawID_SELECT -= 1;

			if(m_iDrawID_SELECT < 0)
			{
				m_iDrawID_SELECT = 3;
			}
			
			m_SELECT_Time = GetTickCount();
		}

		if(dwKey & KEY_RIGHT)
		{
			m_iDrawID_SELECT += 1;

			if(m_iDrawID_SELECT > 3)
			{
				m_iDrawID_SELECT = 0;
			}

			m_SELECT_Time = GetTickCount();
		}

		//Tarma�� ��ư�� �÷�������
		if(m_iDrawID_SELECT == 2)
		{
			//���ͷ� ���ý�
			if( (dwKey & KEY_RETURN))
			{
				m_iDrawID_LOGO = 1;
				m_iDrawID_SELECTED = 1;

				//���� ���� ���(Tarma)
				CSoundMgr::GetInstance()->PlaySound(L"Tarma.mp3");

				m_SELECTED_Time = GetTickCount();
			}
		}

		//m_SELECT_Time = GetTickCount();
	}

	//ĳ����(Tarma) ���ý� 
	if(m_SELECTED_Time + 5000 <= GetTickCount())
	{
		CSceneMgr::GetInstance()->SetScene(SCENE_STAGE);
		m_SELECTED_Time = GetTickCount();
	}


	if(m_LOGO_Time + 300 <= GetTickCount())
	{
		if(m_iDrawID_LOGO == 0)
			m_iDrawID_LOGO = 1;	
		else 
			m_iDrawID_LOGO = 0;

		m_LOGO_Time = GetTickCount();	
	}

	return 0;
}

void CSelectPlayer::Render(HDC _hdc)
{
	//BitBlt(_hdc
	//	,0
	//	,0
	//	,iWINCX
	//	,iWINCY
	//	,m_mapBmp["SELECTMAIN"]->GetMemDC()
	//	,0
	//	,0
	//	,SRCCOPY);
	
	//����ȭ��
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,0
		,0
		,iWINCX
		,iWINCY
		,m_mapBmp["SELECTMAIN"]->GetMemDC()
		,0
		,0
		,iWINCX
		,iWINCY
		,RGB(0, 255, 0)		);

	//�ΰ�â	72, 50		��Ģ 180
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,90	+ (180 * m_iDrawID_SELECT)
		,126
		,72
		,50
		,m_mapBmp["P1LOGO"]->GetMemDC()
		,72 * m_iDrawID_LOGO
		,0
		,SRCCOPY);


////////////////////////////ĳ����/////////////////////////////////

//������
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,44
		,192
		,174
		,324
		,m_mapBmp["MARCO1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	
	if(m_iDrawID_SELECT == 0)
	{
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,44
		,192
		,174
		,324
		,m_mapBmp["MARCO2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

//����
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,223
		,192
		,174
		,324
		,m_mapBmp["ERI1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 1)
	{
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,223
		,192
		,174
		,324
		,m_mapBmp["ERI2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

//Ÿ��
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,402
		,192
		,174
		,324
		,m_mapBmp["TARMA1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 2)
	{
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,402
		,192
		,174
		,324
		,m_mapBmp["TARMA2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

		if(m_iDrawID_SELECTED == 1)
		{
		//���ý�
			BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
				,402
				,192
				,174
				,324
				,m_mapBmp["TARMA3"]->GetMemDC()
				,0
				,0
				,SRCCOPY);
		}
	}

//�ǿ�
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,582
		,192
		,174
		,324
		,m_mapBmp["FIO1"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

	if(m_iDrawID_SELECT == 3)
	{
	BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,582
		,192
		,174
		,324
		,m_mapBmp["FIO2"]->GetMemDC()
		,0
		,0
		,SRCCOPY);
	}

	//����
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,546
		,576
		,124
		,23
		,m_mapBmp["CREDIT"]->GetMemDC()
		,0
		,0
		,124
		,23
		,RGB(255, 0, 255)	);


	//���� 10�� �ڸ���
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,712
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_TEN"]->GetMemDC()
		,11 * (m_iCoin / 10)
		,0
		,11 		
		,8
		,RGB(255, 0, 255)	);

	//���� 1�� �ڸ���
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,737
		,576
		,25
		,22
		,m_mapBmp["COIN_NUM_ONE"]->GetMemDC()
		,11 * (m_iCoin % 10)
		,0
		,11
		,8
		,RGB(255, 0, 255)	);

	BitBlt(_hdc
		,0
		,0
		,iWINCX
		,iWINCY
		,m_mapBmp["BACKBUFFER"]->GetMemDC()
		,0
		,0
		,SRCCOPY);

}
void CSelectPlayer::Release(void)
{
	map<string, CBitBmp*>::iterator iter	 = m_mapBmp.begin();
	map<string, CBitBmp*>::iterator iter_end = m_mapBmp.end();

	for(iter; iter != iter_end; ++iter)
	{
		SAFE_DELETE(iter->second);
	}

	m_mapBmp.clear();

	CObjMgr::GetInstance()->DestroyInstance();
}
