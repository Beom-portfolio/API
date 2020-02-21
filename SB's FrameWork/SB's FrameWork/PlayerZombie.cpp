#include "StdAfx.h"
#include "PlayerZombie.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Factory.h"
#include "Bullet.h"
#include "Granade.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "Player.h"
#include "PlayerLeg.h"
#include "SoundMgr.h"

CPlayerZombie::CPlayerZombie(void)
{
}

CPlayerZombie::CPlayerZombie(float _fx, float _fy)
{
	m_tInfo.fX = _fx;
	m_tInfo.fY = _fy;

	Initialize();
}

CPlayerZombie::~CPlayerZombie(void)
{
	Release();
}

void CPlayerZombie::Initialize(void)
{

	//CSoundMgr::GetInstance()->LoadSoundFile();

	//�Ѿ�
	m_fBarrelX = 0.f;
	m_fBarrelY = 60.f;

	m_ShotTime = GetTickCount();
	m_ThrowTime = GetTickCount();

	////�÷��̾� ������ üũ
	m_fTime	   = 0.f;
	m_bJump	   = false;

	m_fSpeed = 4.f;

	m_bDirection = false;


//�ð� ����
	m_Time = GetTickCount();

	m_tInfo.fCX =	256; 
	m_tInfo.fCY =	1500;

	//���ִ�
	m_strName = "PLAYER_ZOMBIE_STANDUP";

	//������
	m_tFrame = FRAME(0, 72, 0, 50);

	m_dwState = PZOMBIE_CHANGE;

	m_dwPrevState = PZOMBIE_CHANGE;

	m_dwFrameTime = GetTickCount();

	if(CStage::m_bHeavy == true)
	{
		CStage::m_bHeavy = false;
		CStage::m_bPistolInfiniteBullet = true;
	}

	CStage::m_bZombieDeadCheck = false;
	CStage::m_bZombie = true;
}

void CPlayerZombie::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//���°� �����.
		switch(m_dwState)
		{
			//���ִ� ���
		case PZOMBIE_STAND:
			m_tFrame = FRAME(0, 11, 0, 100);
			break;
			//�ȴ� ���
		
		case PZOMBIE_WALK:
			//���������θ� ���� �� ����
			m_tFrame = FRAME(0, 23, 0, 50);
			break;
			
			//���� ���
		
		case PZOMBIE_ATT:
			//������ ��� ����
			m_tFrame = FRAME(0, 11, 0, 10);
			break;
			//���� ���
		
		case PZOMBIE_JUMP:
			m_tFrame = FRAME(0, 15, 0, 30);
			break;
		
			//��ź
		case PZOMBIE_GRANDE:
			m_tFrame = FRAME(0, 32, 0, 75);
			break;
		
			//�״� ���
		case PZOMBIE_DEAD:
			m_tFrame = FRAME(0, 35, 0, 90);
			break;
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;

		ActionState(PZOMBIE_CHANGE, 72, EA_CHANGEEND);
		//ActionState(PZOMBIE_DEAD, 35, EA_DEAD);

	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != PZOMBIE_STAND)
		{
			m_dwState = PZOMBIE_STAND;   
			m_tInfo.fCX = 256;
			m_tInfo.fCY = 256;
			m_strName = "PLAYER_ZOMBIE_STAND";
		}
	}

}

int CPlayerZombie::ActionState( DWORD dwCurState , int _FrameIndex, eCurAction eAction)
{
	if(dwCurState == PZOMBIE_CHANGE)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_CHANGEEND)
			{
				m_dwState = PZOMBIE_STAND;
				m_tInfo.fCX =	256;
				m_tInfo.fCY =	256;
				m_strName = "PLAYER_ZOMBIE_STAND";
				return 0;
			}
		}
	}
	else if(dwCurState == PZOMBIE_DEAD)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_DEAD)
			{
				pPlayer = new CPlayer(m_tInfo.fX - 40, m_tInfo.fY);
				pPlayer_Leg = new CPlayerLeg(m_tInfo.fX - 40, m_tInfo.fY);
				
				CObjMgr::GetInstance()->AddGameObject(pPlayer, OBJ_PLAYER);
				CObjMgr::GetInstance()->AddGameObject(pPlayer_Leg, OBJ_PLAYER_LEG);


				return 1;
			}
		}
	}
	else if(dwCurState == PZOMBIE_ATT)
	{
		if(m_tFrame.iFrameStart == _FrameIndex)
		{
			if(eAction == EA_ATTACK)
			{
				CSoundMgr::GetInstance()->PlaySound(L"semishoot.wav");
				Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_RIGHT, BULLET_PISTOL);

				return 0;
			}
		}
	}
	return 0;
}

//Setframe���� ó�� �� �� �ֵ���



void CPlayerZombie::SetFrame(void)
{

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	/*if( m_bChageCheck == true && !(m_dwState =  PZOMBIE_CHANGE))
	{
		if(!dwKey)
		{
			m_fBarrelX = 0.f;
			m_fBarrelY = 25.f;

			m_dwState =  PZOMBIE_STAND;
			m_strName = "PLAYER_ZOMBIE_STAND";
			m_tInfo.fCX =	256;
			m_tInfo.fCY =	256;
			

		}
	}*/


	if(CStage::m_bHeavy == false)				/////////////////�⺻ ���϶�
	{
		//���������θ� ���� �� ����.

		//������
		if(dwKey & KEY_RIGHT)
		{
			m_dwState = PZOMBIE_WALK;
			m_tInfo.fCX =	256;
			m_tInfo.fCY =	256;
			m_strName = "PLAYER_ZOMBIE_WALK";
		}

		//���ڸ� ����
		if(dwKey & KEY_SPACE)
		{

			m_dwState = PZOMBIE_JUMP;
			m_tInfo.fCX =	256;
			m_tInfo.fCY =	256;
			m_strName = "PLAYER_ZOMBIE_JUMP";
		}

		//�ѽ��
		if(dwKey & KEY_CTRL)
		{
			m_dwState = PZOMBIE_ATT;
			m_tInfo.fCX =	300;
			m_tInfo.fCY =	300;
			m_strName = "PLAYER_ZOMBIE_FIRE";
		}
	}													////////////////////////////////
	else if(CStage::m_bHeavy == true)			//���ӽŰ��� �Ծ�����.
	{
		CStage::m_bHeavy = false;
	}

	/////////////////����ź////////////////////////////////������
	//����
	if(dwKey & KEY_Z)
	{
		m_dwState = PZOMBIE_GRANDE;
		m_tInfo.fCX =	256;
		m_tInfo.fCY =	256;
		m_strName = "PLAYER_ZOMBIE_GRANADE";
	}


	//������
	
	if(CStage::m_bZombieDeadCheck == true)
	{
		m_dwState = PZOMBIE_DEAD;
		m_tInfo.fCX =	512;
		m_tInfo.fCY =	512;
		m_strName = "PLAYER_ZOMBIE_DEATH";
	}


}

//Ű�Է�
void CPlayerZombie::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	//BackGroundX : 15326
	float fBackGroundX = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCX;
	
	//BackGroundY : 2080
	float fBackGroundY = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCY;

	if(dwKey & KEY_RIGHT)
	{
		m_fBarrelX = 0.f;
		m_fBarrelY = 60.f;

		m_tInfo.fX += m_fSpeed;

		if (m_fBarrelX < 0)
			m_fBarrelX *= -1;

		
		if(m_tInfo.fX >= iWINCX / 2.f && m_ptScroll.x > - (fBackGroundX - iWINCX) )
			m_ptScroll.x -= (long)m_fSpeed;

		
	}

	
	if(dwKey & KEY_LEFT)
	{
		m_tInfo.fX -= m_fSpeed;

		if (m_fBarrelX < 0)
			m_fBarrelX *= -1;
		
		if(m_ptScroll.x < 0 && m_tInfo.fX < (fBackGroundX - iWINCX / 2.f) )
			m_ptScroll.x += (long)m_fSpeed;
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

	//���� ��!

	if(dwKey & KEY_CTRL)
	{
		if(CStage::m_bHeavy == false)
		{
			//if(m_ShotTime + 200 <= GetTickCount())
			//{
			//	//����
			//	
			//	Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_RIGHT, BULLET_PISTOL);
			//	
			//	m_ShotTime = GetTickCount();
			//}

			ActionState(PZOMBIE_ATT,1, EA_ATTACK);

		}
		else
		{
			CStage::m_bHeavy = false;	
		}
	}


	//��ź�� ������
	if(m_ThrowTime + 1000 <= GetTickCount())
	{
		if(dwKey & KEY_Z)
		{
			if(CStage::m_bGranade == true)
			{
				if(m_bDirection == false)
				{
					//Throw(m_tInfo.fX + 40, m_tInfo.fY - 30, GRANADE_PLAYER, m_bDirection);
					//--CStage::m_iGranadeBullet;
				}
			}
		}

		m_ThrowTime = GetTickCount();
	}
	
	//�跲 ���ڸ� ��ġ

}


void CPlayerZombie::Jump(void)
{
	if(m_bJump == false)
		return;

	m_fTime += 0.5f;

	//����
	//�� * -sin(90 * PI / 180) + (�߷°��ӵ�:9.8 * �ð� * �ð�) / 2
	//m_tInfo.fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_tInfo.fY += float(10 * -1 + (0.98 * m_fTime * m_fTime) / 2);

}

int  CPlayerZombie::Update(void)
{


	CGameObject::Update();

	m_Rect.left		= m_Rect.left   + 20	  + m_ptScroll.x;
	m_Rect.top		= m_Rect.top    + 50	  + m_ptScroll.y;
	m_Rect.right	= m_Rect.right  - 195     + m_ptScroll.x;
	m_Rect.bottom	= m_Rect.bottom - 120     + m_ptScroll.y;

	KeyInput();		//�÷��̾� ����
	Jump();			//����
	SetFrame();
	FrameMove();

	CollisionLine(m_bJump);

	if(CStage::m_bZombie == false)
	{
		if(CStage::m_bZombieDeadCheck == true)
		{	
			if(ActionState(PZOMBIE_DEAD, 35, EA_DEAD) == 1)
			{
				//CStage::m_bZombie	= false;			 
				return 1;
			}
		}
	}



			//��Ʈ ���� (�浹ó���� ����)

	return 0;
}

void CPlayerZombie::Render(HDC _hdc)
{
	if(m_dwState == PZOMBIE_CHANGE)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + 15	+  m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f) - 30   +  m_ptScroll.y
			,130
			,800
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
			,(int)m_tInfo.fCX		//�̹����� ���� X
			,(int)m_tInfo.fCY		//�̹����� ���� Y
			,RGB(255, 0, 255)  );
	}
	else if(m_dwState == PZOMBIE_ATT)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + 30	+  m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f) + 53  - 30 + m_ptScroll.y
			,155
			,155
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
			,(int)m_tInfo.fCX		//�̹����� ���� X
			,(int)m_tInfo.fCY		//�̹����� ���� Y
			,RGB(255, 0, 255)  );
	}
	else if(m_dwState == PZOMBIE_DEAD)
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + 25	+  m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f) + 20   + m_ptScroll.y
			,300
			,300
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
			,(int)m_tInfo.fCX		//�̹����� ���� X
			,(int)m_tInfo.fCY		//�̹����� ���� Y
			,RGB(255, 0, 255)  );
	}
	else
	{
		TransparentBlt(_hdc
			,int(m_tInfo.fX - m_tInfo.fCX / 2.f)		+  m_ptScroll.x
			,int(m_tInfo.fY - m_tInfo.fCY / 2.f) + 53 - 40  + m_ptScroll.y
			,135
			,135
			,(*m_mapBmp)[m_strName]->GetMemDC()	
			,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
			,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
			,(int)m_tInfo.fCX		//�̹����� ���� X
			,(int)m_tInfo.fCY		//�̹����� ���� Y
			,RGB(255, 0, 255)  );
	}
	



	//��ź
		if(!(CObjMgr::GetInstance()->GetList()[OBJ_ZOMBIEGRANADE].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_ZOMBIEGRANADE].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_ZOMBIEGRANADE].end();

		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}



	if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
		MoveToEx(_hdc, m_tInfo.fX + m_ptScroll.x, m_tInfo.fY + m_ptScroll.y, NULL);
		LineTo(_hdc, m_tInfo.fX + m_fBarrelX +m_ptScroll.x, m_tInfo.fY - m_fBarrelY + m_ptScroll.y);
	}

}


void CPlayerZombie::Release(void)
{

}


void CPlayerZombie::Shot(float fx, float fy, eBulletDirection _eDir, eBulletType _eType)
{
	pBullet = new CBullet(fx + m_ptScroll.x, fy + m_ptScroll.y, _eDir, _eType);

	CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);
}


void CPlayerZombie::Throw(float fx, float fy, eGranadeType _eType, bool Direction)
{
	pGranade = new CGranade(fx, fy, _eType, Direction);

	CObjMgr::GetInstance()->AddGameObject(pGranade, OBJ_ZOMBIEGRANADE);
}
