#include "StdAfx.h"
#include "Big.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"

CBig::CBig(void)
{
}

CBig::~CBig(void)
{
	Release();
}

void CPlayer::Initialize(void)
{	
	////�÷��̾� ������ üũ

	m_fTime	   = 0.f;
	m_bJump	   = false;
	m_bJumpDown = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//�ð� ����
	m_Time = GetTickCount();


	m_tInfo = INFO(400, 200, 400, 267);
	m_strName = "PLAYER_STAND_RIGHT";

	m_tFrame = FRAME(0, 3, 0, 100);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

}

void CPlayer::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//���°� �����.
		switch(m_dwState)
		{
		case STATE_STAND:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_WALK:
			m_tFrame = FRAME(0, 11, 0, 50);
			break;

		case STATE_JUMP:
			m_tFrame = FRAME(0, 5, 0, 100);
			break;

		case STATE_SEAT:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_SEATMOVE:
			m_tFrame = FRAME(0, 6, 0, 100);
			break;

		case STATE_UPSEE:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_SHOOT:
			m_tFrame = FRAME(0, 8, 0, 40);
			break;

		case STATE_UPSHOOT:
			m_tFrame = FRAME(0, 9, 0, 40);
			break;

		case STATE_SEATSHOOT:
			m_tFrame = FRAME(0, 4, 0, 40);
			break;

		case STATE_JUMPDOWNSHOOT:
			m_tFrame = FRAME(0, 3, 0, 40);
			break;

		case STATE_JUMPDOWNSEE:
			m_tFrame = FRAME(0, 0, 0, 100);
			break;
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != STATE_STAND)
		{
			m_dwState = STATE_STAND;
		}
	}

}

void CPlayer::SetFrame(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	//��������
	if(dwKey & KEY_LEFT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_LEFT";

		if(m_bDirection == false)
			m_bDirection = true;

	}

	if(dwKey & KEY_RIGHT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_RIGHT";

		if(m_bDirection == true)
			m_bDirection = false;
	}

	//���ڸ� ����
	if(dwKey & KEY_SPACE)
	{

		m_dwState = STATE_JUMP;
		
		if(m_bDirection == false)
			m_strName = "PLAYER_JUMP_RIGHT";
		else
			m_strName = "PLAYER_JUMP_LEFT";
		
	}

	//�ٸ鼭 ����
	if(dwKey & KEY_LEFT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_LEFT";
		
		if(m_bDirection == false)
			m_bDirection = true;
	}

	//�ٸ鼭 ����
	if(dwKey & KEY_RIGHT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_RIGHT";	
	
		if(m_bDirection == true)
			m_bDirection = false;
	}

	//�ɱ�
	if(dwKey & KEY_DOWN)
	{
		m_dwState = STATE_SEAT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SEAT_RIGHT";
		else
			m_strName = "PLAYER_SEAT_LEFT";
	}

	//�����鼭 ������
	if(dwKey & KEY_DOWN && dwKey & KEY_LEFT)
	{
		m_dwState = STATE_SEATMOVE;

		m_strName = "PLAYER_SEATWALK_LEFT";

		if(m_bDirection == false)
			m_bDirection = true;
	}

	if(dwKey & KEY_DOWN && dwKey & KEY_RIGHT)
	{
		m_dwState = STATE_SEATMOVE;

		m_strName = "PLAYER_SEATWALK_RIGHT";

		if(m_bDirection == true)
			m_bDirection = false;
	}

	//���� ����
	if(dwKey & KEY_UP)
	{
		m_dwState = STATE_UPSEE;

		if(m_bDirection == false)
			m_strName = "PLAYER_UPSEE_RIGHT";
		else
			m_strName = "PLAYER_UPSEE_LEFT";
	}

	//�����ϸ鼭 ���� ����
	if(m_bJump == true && dwKey & KEY_DOWN)
	{
		m_dwState = STATE_JUMPDOWNSEE;

		if(m_bDirection == false)
			m_strName = "PLAYER_JUMPDOWNSEE_RIGHT";
		else
			m_strName = "PLAYER_JUMPDOWNSEE_LEFT";
	}

	//�ѽ��
	if(dwKey & KEY_CTRL)
	{
		m_dwState = STATE_SHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SHOOT_RIGHT";
		else
			m_strName = "PLAYER_SHOOT_LEFT";
	}
	
	if(dwKey & KEY_DOWN && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_SEATSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SEATSHOOT_RIGHT";
		else
			m_strName = "PLAYER_SEATSHOOT_LEFT";

	}

	//���� �ѽ��
	if(dwKey & KEY_UP && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_UPSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_UPSHOOT_RIGHT";
		else
			m_strName = "PLAYER_UPSHOOT_LEFT";
	}

	//�����ϸ鼭 �Ʒ��� �ѽ��
	if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_JUMPDOWNSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_DOWNSHOOT_RIGHT";
		else
			m_strName = "PLAYER_DOWNSHOOT_LEFT";
	}

	if(dwKey & KEY_N)
	{
		m_dwState = STATE_KNIFEATT;
		
		if(m_bDirection == false)
			m_strName = "PLAYER_KNIFEATT_RIGHT";
		else
			m_strName = "PLAYER_KNIFEATT_LEFT";
	}
}

//Ű�Է�
void CPlayer::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!dwKey)
	{
		if(m_bDirection == false)
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_RIGHT";
		}
		else
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_LEFT";
		}
	}

	if(dwKey & KEY_LEFT)
	{
		m_tInfo.fX -= m_fSpeed;

	}

	if(dwKey & KEY_RIGHT)
	{
		m_tInfo.fX += m_fSpeed;	
			
	}

	//���� ����.
	/*if(dwKey & KEY_UP)
	{
		m_bUpCheck = true;
	}
	
	if(!(dwKey & KEY_UP))
	{
		m_bUpCheck = false;
	}*/

	//�ޱ׸���. (�����Ҷ��� ���� ����)
	if(m_bJump == false)
	{
		/*if(dwKey & KEY_DOWN)
		{
			m_tInfo.fCX = 40;
			m_tInfo.fCY = 50;
			m_fSpeed = 5.f;
		}
		if(!(dwKey & KEY_DOWN))
		{
			m_tInfo.fCX = 40;
			m_tInfo.fCY = 80;
			m_fSpeed = 10.f;
		}*/
	}


	//���� ���� �ÿ��� ���� �����ϰ�
	if(m_Time + 600 < GetTickCount())
	{
		if((dwKey & KEY_SPACE))
		{
			m_bJump = true;
			m_fTime = 0.f;
			m_Time = GetTickCount();
		}	
	}
	//����������.

	////�����ϸ鼭 ���� �ٶ󺼶�.
	//if(m_bJump == true)
	//{
	//	//���̴� �ڼ��� �����ϰ� �ϱ� ����.
	//	m_tInfo.fCX = 40;
	//	m_tInfo.fCY = 80;
	//	m_fSpeed = 10.f;

	//	if((dwKey & KEY_DOWN) && m_bJump == true)
	//	{
	//		m_bJumpDown = true;
	//	}
	//	
	//	if( !(dwKey & KEY_DOWN) )
	//	{
	//		m_bJumpDown = false;
	//	}
	//}
	//else
	//	m_bJumpDown = false;
}


void CPlayer::Jump(void)
{
	if(m_bJump == false)
		return;

	m_fTime += 0.5f;

	//����
	//�� * -sin(90 * PI / 180) + (�߷°��ӵ�:9.8 * �ð� * �ð�) / 2
	//m_tInfo.fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_tInfo.fY += float(25 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	
	//�ӽ� ����(�����浹 ��)
	if(m_tInfo.fY >= 500)
	{
		m_tInfo.fY = 500;
		m_bJump = false;
		return;
	}
}

int  CPlayer::Update(void)
{
	KeyInput();		//�÷��̾� ����
	Jump();			//����
	SetFrame();
	FrameMove();

	CGameObject::Update();

	return 0;
}

void CPlayer::Render(HDC _hdc)
{

	/////�̹��� ���
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
		,(int)m_tInfo.fCX		//�̹����� ���� X
		,(int)m_tInfo.fCY		//�̹����� ���� Y
		,RGB(75, 169, 218)  );

}

void CPlayer::Release(void)
{

}