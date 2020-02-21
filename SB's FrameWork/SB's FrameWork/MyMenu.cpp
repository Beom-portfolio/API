#include "StdAfx.h"
#include "MyMenu.h"
#include "SceneMgr.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
//#include "MyButton.h"
#include "GameObject.h"

CMyMenu::CMyMenu(void)
{
}

CMyMenu::~CMyMenu(void)
{
	Release();
}

void CMyMenu::Initialize(void)
{
	CGameObject::SetBitBmp(&m_mapBmp);

	//�� ó�� ���۽� ������ 0�� ���·� ����.
	if(m_iCoin == 0)
		m_iCoin = 0;

	//////////////////// �̹��� �ε� /////////////////////////

	m_mapBmp.insert( make_pair("BACKGROUND1",
		(new CBitBmp)->LoadBmp(L"../Sprite/MyMenu/BackGround.bmp") ) );

	m_mapBmp.insert( make_pair("BACKGROUND2",
		(new CBitBmp)->LoadBmp(L"../Sprite/MyMenu/BackBuffer.bmp") ) );

	m_mapBmp.insert( make_pair("COIN_NUM_TEN",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_ONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );

	m_mapBmp.insert( make_pair("BACKBUFFER",
		(new CBitBmp)->LoadBmp(L"../Sprite/BackBuffer1.bmp") ) );
	
	m_mapBmp.insert( make_pair("START",
		(new CBitBmp)->LoadBmp(L"../Sprite/MyMenu/start.bmp") ) );
	
	
	////�����̴� �ð�
	m_TimeCount = GetTickCount();
	//�����̴� �ð� üũ
	m_iDrawID_Menu = 0;

	////�����Է� �����ð�
	m_TimeCoin = GetTickCount();
	
	m_bStartPoint = false;

	//////////////////// ��ü ���� //////////////////////////
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("START", 200, 500, 150, 150)), OBJ_UI);
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("EDIT", 400, 500, 150, 150)), OBJ_UI);
	//CObjMgr::GetInstance()->AddGameObject( (new CMyButton("EXIT", 600, 500, 150, 150)), OBJ_UI);
}

int CMyMenu::Update(void)
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
	
	if(m_TimeCount + 1000 <= GetTickCount())
	{
		if(m_iDrawID_Menu == 1)	
			m_iDrawID_Menu = 0;
		else
			m_iDrawID_Menu = 1;

		m_TimeCount = GetTickCount();
	}



	CObjMgr::GetInstance()->Update();



	if( ( (dwKey & KEY_ONE) || (dwKey & KEY_TWO) ) && m_iCoin != 0)
	{
		m_iCoin -= 1;
		CSceneMgr::GetInstance()->SetScene(SCENE_SELECT_PLAYER);
	}

	if(m_iCoin > 0)
	{
		m_bStartPoint = true;
	}

	return 0;
}

void CMyMenu::Render(HDC _hdc)
{
	//�ñ��� �κ� (���� ���۸�)

	if(m_bStartPoint == false)
	{
		if(m_iDrawID_Menu == 1)
		{
			BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
				,0				//�׷��� ��ġ X
				,0				//�׷��� ��ġ Y
				,iWINCX			//�׷��� ũ�� X
				,iWINCY			//�׷��� ũ�� Y
				,m_mapBmp["BACKGROUND1"]->GetMemDC()
				,0							//�̹��������� ���� ��ġ X
				,0							//�̹��������� ���� ��ġ Y
				,SRCCOPY);					//�޴� ������ �����.
		}
		//CObjMgr::GetInstance()->Render(m_mapBmp["BACKGROUND"]->GetMemDC());
		else if(m_iDrawID_Menu == 0)
		{
			BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
				,0					
				,0					
				,iWINCX		
				,iWINCY		
				,m_mapBmp["BACKGROUND2"]->GetMemDC()	
				,0		
				,0		
				,SRCCOPY);
		}
	}
	else
	{
		BitBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,0					
			,0					
			,iWINCX		
			,iWINCY		
			,m_mapBmp["BACKGROUND2"]->GetMemDC()	
			,0		
			,0		
			,SRCCOPY);

		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,217
			,492
			,393
			,22
			,m_mapBmp["START"]->GetMemDC()
			,0
			,0
			,393 		
			,22
			,RGB(255, 0, 255)	);
	}

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

void CMyMenu::Release(void)
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

