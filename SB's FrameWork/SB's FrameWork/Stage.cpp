#include "StdAfx.h"
#include "Stage.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "GameObject.h"
#include "Player.h"
#include "Mouse.h"
#include "Factory.h"
#include "KeyMgr.h"
#include "PlayerLeg.h"
#include "BackGround.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Toma.h"
#include "Zombie.h"
#include "Boss.h"
#include "Item.h"

//�Ѿ˼� �� �����
//�׸��� �Ұ����� ���� �ְ� ���� ó��
bool CStage::m_bHeavy				 = false;
int  CStage::m_iHeavyBullet		     = 0;
bool CStage::m_bGranade			     = true;
int  CStage::m_iGranadeBullet	     = 10;
bool CStage::m_bPistolInfiniteBullet = false;
int  CStage::m_iLife				 = 17;
bool CStage::m_bZombie				 = false;
bool CStage::m_bZombieDeadCheck		 = true;



CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize(void)
{
	//���� ��ȯ
	m_bFirstCast  = false;
	m_bSecondCast = false;
	m_bThirdCast = false;
	m_bForthCast = false;
	m_bFifthCast = false;



	////////
	CGameObject::SetBitBmp(&m_mapBmp);	//set���� �������!!

	m_mapBmp.insert( make_pair("BACKBUFFER",
		(new CBitBmp)->LoadBmp(L"../Sprite/BackBuffer2.bmp") ) );

	////�������� �뷡
	//CSoundMgr::GetInstance()->LoadSoundFile();	//�������� �뷡 �ε�
	

	CSoundMgr::GetInstance()->PlayBGMSound(L"StageMusic.mp3");
	
	CSoundMgr::GetInstance()->PlaySound(L"MissionStart.mp3");	

	//�ð�
	m_dwTime = GetTickCount();
	//60
	m_iTime = 60;


	////�����Է� �����ð�
	m_TimeCoin = GetTickCount();
	//
	////////////////////////////////////////////////////////////////////////////////
	
	/////////////////////�÷��̾�

	//�ƹ��͵� ������
	m_mapBmp.insert( make_pair("NONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/none.bmp") ) );

	//��������
	//��
	m_mapBmp.insert( make_pair("PLAYER_STAND_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/stand.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_STAND_LEG_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Bottom/stand.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_STAND_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/stand.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_STAND_LEG_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Bottom/stand.bmp") ) );

	//������
	//��
	m_mapBmp.insert( make_pair("PLAYER_WALK_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/run.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_WALK_LEG_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Bottom/run.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_WALK_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/run.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_WALK_LEG_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Bottom/run.bmp") ) );


	//�����Ҷ�
	//���ڸ�����
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMP_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/jump.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_JUMP_LEG_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Bottom/jump.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMP_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/jump.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_JUMP_LEG_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Bottom/jump.bmp") ) );
	
	//�ٸ鼭 ����
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMPRUN_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/jump_run.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_JUMPRUN_LEG_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Bottom/jump_run.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMPRUN_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/jump_run.bmp") ) );
	m_mapBmp.insert( make_pair("PLAYER_JUMPRUN_LEG_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Bottom/jump_run.bmp") ) );

	//���϶�
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEAT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/down.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEAT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/down.bmp") ) );

	//���̸鼭 ������ ����
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEATWALK_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/down_move.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEATWALK_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/down_move.bmp") ) );


	//���� �ϸ鼭 ���϶�
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMPDOWNSEE_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/under.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_JUMPDOWNSEE_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/under.bmp") ) );


	//���κ���
	//��
	m_mapBmp.insert( make_pair("PLAYER_UPSEE_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/up.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_UPSEE_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/up.bmp") ) );

	
	//�ѽ��
	//��
	m_mapBmp.insert( make_pair("PLAYER_SHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_SHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/shot.bmp") ) );

	//�����ѽ��
	//�ѽ��
	//��
	m_mapBmp.insert( make_pair("PLAYER_UPSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/up_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_UPSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/up_shot.bmp") ) );

	//���̸鼭 �ѽ��
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEATSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/down_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_SEATSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/down_shot.bmp") ) );

	//�����ϸ鼭 �Ʒ��� �ѽ��
	//��
	m_mapBmp.insert( make_pair("PLAYER_DOWNSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/under_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_DOWNSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/under_shot.bmp") ) );

	////////Į
	//����1
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEATT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/Nife/attack1.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEATT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/Nife/attack1.bmp") ) );

	//����2
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEATT2_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/Nife/attack2.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEATT2_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/Nife/attack2.bmp") ) );

	//��������1
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEDOWNATT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/Nife/down_attack1.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEDOWNATT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/Nife/down_attack1.bmp") ) );

	//��������2
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEDOWNATT2_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/Nife/down_attack2.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("PLAYER_KNIFEDOWNATT2_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/Nife/down_attack2.bmp") ) );

	///////////////////////
	//���ӽŰ�
	//��������.
	//��
	m_mapBmp.insert( make_pair("HEAVY_STAND_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/stand.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_STAND_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/stand.bmp") ) );


	//�۶�
	//��
	m_mapBmp.insert( make_pair("HEAVY_WALK_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/run.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_WALK_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/run.bmp") ) );

	//���ڸ�����
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMP_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/jump.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMP_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/jump.bmp") ) );

	//�ٸ鼭����
	//��
	m_mapBmp.insert( make_pair("HEAVY_RUNJUMP_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/jump_run.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_RUNJUMP_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/jump_run.bmp") ) );

	//�ɱ�
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEAT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/down.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEAT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/down.bmp") ) );

	//�����鼭 �����ΰ���
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEATWALK_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/down_move.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEATWALK_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/down_move.bmp") ) );

	//���� ����
	//��
	m_mapBmp.insert( make_pair("HEAVY_UPSEE_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/up.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_UPSEE_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/up.bmp") ) );

	//�����ϸ鼭 ���� ����
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPDOWN_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/under.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPDOWN_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/under.bmp") ) );
	
	/////////////////���ӽŰ� �ѽ��

	//���ڸ��ѽ��
	//��
	m_mapBmp.insert( make_pair("HEAVY_SHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_SHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/shot.bmp") ) );

	//�������ѽ��
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEATSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/down_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_SEATSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/down_shot.bmp") ) );

	//���� �ѽ��
	//��
	m_mapBmp.insert( make_pair("HEAVY_UPSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/up_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_UPSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/up_shot.bmp") ) );
	
	//���� �ϸ鼭 �Ʒ��� �ѽ��
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPDOWNSHOOT_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/under_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPDOWNSHOOT_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/under_shot.bmp") ) );

	//���� �ø��鼭 �밢��
	//��
	m_mapBmp.insert( make_pair("HEAVY_CROSSUP_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/up_lu_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_CROSSUP_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/up_ru_shot.bmp") ) );

	////������ ������ �����鼭 �밢��
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPCROSSDOWN_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Top/heavy/down_lu_shot.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("HEAVY_JUMPCROSSDOWN_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Top/heavy/down_ru_shot.bmp") ) );

	/////����ź ������ ���
	//����
	//��
	m_mapBmp.insert( make_pair("BOMB_THROW_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/Bomb.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("BOMB_THROW_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/Bomb.bmp") ) );

	//�ɾƼ�
	//��
	m_mapBmp.insert( make_pair("BOMB_SEATTHROW_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Left/down_bomb.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("BOMB_SEATTHROW_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/down_bomb.bmp") ) );
	

	///////////////////////////////�Ѿ�//////////////////////////////////////
	//�⺻ �Ѿ�
	m_mapBmp.insert( make_pair("PISTOL_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/Weapon/Pistol/Pistol.bmp") ) );
	//ȿ��
	m_mapBmp.insert( make_pair("PISTOL_EFFECT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Effect/Normal.bmp") ) );

	//�ӽŰ�
	m_mapBmp.insert( make_pair("HEAVY_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/Weapon/HeavyMachine/Heavy.bmp") ) );

	//32, 32
	//10��

	//////////////////////////////����ź////////////////////////////////////
	//�⺻ ����ź
	m_mapBmp.insert( make_pair("PLAYER_GRANADE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Weapon/Bomb/Bomb.bmp") ) );

	// ȿ��
	m_mapBmp.insert( make_pair("GRANADE_EFFECT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Effect/player_bomb.bmp") ) );
	
	//100 , 200
	//23��
	
	//�������� �޹�� �ε�
	m_mapBmp.insert( make_pair("BACKGROUND",
		(new CBitBmp)->LoadBmp(L"../Sprite/Map/map.bmp") ) );

	//////////////////////////////����///////////////////////
	//�Ϲݺ���
	//��
	m_mapBmp.insert( make_pair("MONSTER_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Monster_Left.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("MONSTER_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Monster_Right.bmp") ) );

	//����
	//
	m_mapBmp.insert( make_pair("MONSTER_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/MonsterBullet/Boom_Bullet.bmp") ) );
	//ȿ��
	m_mapBmp.insert( make_pair("MGRANADE_EFFECT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Effect/medium_explosion.bmp") ) );
	
	//50, 50
	//28��
	

	///////////////////////////////////���
	//��
	m_mapBmp.insert( make_pair("TOMA_LEFT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Toma/Left/Stand.bmp") ) );
	//��
	m_mapBmp.insert( make_pair("TOMA_RIGHT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Toma/Right/Stand.bmp") ) );

	//����
	//
	m_mapBmp.insert( make_pair("TOMA_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/Weapon/All/toma_bullet.bmp") ) );
	//ȿ��
	//m_mapBmp.insert( make_pair("MGRANADE_EFFECT",
		//(new CBitBmp)->LoadBmp(L"../Sprite/Effect/medium_explosion.bmp") ) );
	

	//�״¸��(����)
	m_mapBmp.insert( make_pair("BIG_EFFECT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Effect/big_explosion.bmp") ) );

	//170, 170
	//28��

	//////////////////////////////////////////����
	//����
	m_mapBmp.insert( make_pair("ZOMBIE_GIRL",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Zombie/Zombiegirl.bmp") ) );
	
	//����
	m_mapBmp.insert( make_pair("ZOMBIE_WALK",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Zombie/Zombiewalk.bmp") ) );

	m_mapBmp.insert( make_pair("ZOMBIE_ATTACK",
		(new CBitBmp)->LoadBmp(L"../Sprite/Monster/Zombie/Zombieattack.bmp") ) );


	//����
	//
	m_mapBmp.insert( make_pair("ZOMBIE_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/MonsterBullet/Zombiebullet.bmp") ) );

	//ȿ��
	m_mapBmp.insert( make_pair("ZOMBIE_BULLET_EFFECT",
		(new CBitBmp)->LoadBmp(L"../Sprite/MonsterBullet/Fat_Zombie_Line.bmp") ) );

	//�״¸��
	m_mapBmp.insert( make_pair("ZOMBIE_DEAD",
		(new CBitBmp)->LoadBmp(L"../Sprite/MonsterBullet/Fat_Zombie_Obj.bmp") ) );
	
	//////////////////////////////////////////////�÷��̾� ����
	

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_STANDUP",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/Change1.bmp") ) );

	//73��
	//256
	//1500
	

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_STAND",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/stand.bmp") ) );

	//12
	//256
	//256

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_WALK",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/walk.bmp") ) );

	//24
	//256
	//256
	

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_JUMP",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/jump.bmp") ) );

	//16
	//256
	//256

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_FIRE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/shot.bmp") ) );

	//12
	//256
	//256

	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_GRANADE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/bomb.bmp") ) );

	//33
	//256
	//256


	m_mapBmp.insert( make_pair("PLAYER_ZOMBIE_DEATH",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Zombie/dead.bmp") ) );

	//36
	//512
	//512

	//UI
	//���� ǥ��
	m_mapBmp.insert( make_pair("INFINIT",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/Infinit.bmp") ) );

	//��������
	m_mapBmp.insert( make_pair("LIFE_BAR",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/Life_Bar.bmp") ) );

	//������ �Ҹ�â
	m_mapBmp.insert( make_pair("LIFE_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/Life_Bullet.bmp") ) );

	//������ ��ŸƮ
	m_mapBmp.insert( make_pair("PRESSSTART",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/PressStart.bmp") ) );

	//���ھ�
	m_mapBmp.insert( make_pair("SCORE",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/score2.bmp") ) );

	//�ð�
	m_mapBmp.insert( make_pair("TIME",
		(new CBitBmp)->LoadBmp(L"../Sprite/UI/Time.bmp") ) );


	//ũ����(����)
	m_mapBmp.insert( make_pair("CREDIT",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/credit.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_TEN",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );
	
	m_mapBmp.insert( make_pair("COIN_NUM_ONE",
		(new CBitBmp)->LoadBmp(L"../Sprite/InsertCoin/Coin_Num_Ten.bmp") ) );


	/////�Ҿƹ���
	m_mapBmp.insert( make_pair("NPC_BIND",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/NPC/R_bind.bmp") ) );

	m_mapBmp.insert( make_pair("NPC_SHOW",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/NPC/R_item.bmp") ) );

	m_mapBmp.insert( make_pair("NPC_RUN",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/NPC/R_run.bmp") ) );

	m_mapBmp.insert( make_pair("NPC_RUNOUT",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/NPC/R_runout.bmp") ) );

	
	//������
	m_mapBmp.insert( make_pair("ITEM_HEAVY",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/Item/Heavy.bmp") ) );
	
	m_mapBmp.insert( make_pair("ITEM_BOMB",
		(new CBitBmp)->LoadBmp(L"../Sprite/Resource/Item/Bomb.bmp") ) );

	////����

	
	m_mapBmp.insert( make_pair("BOSS_BODY",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/body.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_STAND",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/stand.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_CHARGE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/charge.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_FIRE",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/fire.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_LAZER",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/lazer.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_BULLET",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/bullet.bmp") ) );

	m_mapBmp.insert( make_pair("BOSS_DEAD",
		(new CBitBmp)->LoadBmp(L"../Sprite/Boss/dead.bmp") ) );


	//////////////////////////////////////////////////////////////////////////

	//�÷��̾� �ʱ�ȭ

	CObjMgr::GetInstance()->Initialize();

	CObjMgr::GetInstance()->AddGameObject(CFactory<CPlayer>::CreateGameObject(145, 577), OBJ_PLAYER);

	CObjMgr::GetInstance()->AddGameObject(CFactory<CPlayerLeg>::CreateGameObject(145, 577), OBJ_PLAYER_LEG);

	CObjMgr::GetInstance()->AddGameObject(CFactory<CBackGround>::CreateGameObject(), OBJ_BACKGROUND);

	//����

	pEnemy = new CBoss(14890, 1642);

	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_BOSS);

//if(m_bFirstCast == false)
	//{

	//����

	pEnemy = new CEnemy(800, 530);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(50, 550);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(643, 565);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bFirstCast = true;
	//}

	//else if(m_bSecondCast == false && (iPlayer_X + 800) >= 1300)
	//{
	pEnemy = new CEnemy(1397 /*+ CGameObject::m_ptScroll.*/, 530);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);
	
	pEnemy = new CEnemy(1604, 538);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1738, 584);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1832, 588);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1965, 586);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);
	
	pEnemy = new CToma(2395, 225);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(2795, 562);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bSecondCast = true;
	//}

	//else if(m_bThirdCast == false && (iPlayer_X + 800) >= 3300)
	//{
//

	pEnemy = new CEnemy(3327, 528);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(3930, 380);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(4141, 318);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(4464, 229);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(3930, 380);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(5487, 318);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(6532, 229);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(7895, 206);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(5698, 533);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(6911, 916);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bThirdCast = true;
	//}

	//else if(m_bForthCast == false && (iPlayer_X + 800) >= 7100)
	//{
	pEnemy = new CToma(7198, 684);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(7464, 1010);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8029, 1397);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8159, 1437);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8200, 1445);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8300, 1446);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8645, 1429);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8345, 1427);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8986, 1755);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9408, 1850);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9623, 1852);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CToma(9627, 1419);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9800, 1850);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bForthCast = true;
	//}

	//else if(m_bFifthCast == false && (iPlayer_X + 800) >= 10100)
	//{
	pEnemy = new CEnemy(10148, 1808);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(10367, 1842);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11223, 1795);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(11553, 1835);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(11650, 1814);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11223, 1795);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11700, 1835);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11900, 1814);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(12230, 1841);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11936, 1815);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(12699, 1869);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(13446, 1959);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(13857, 1990);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bFifthCast = true;
	//}


	//������
	pItem = new CItem(1587, 498, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(7422, 940, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(12557, 1745, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(13500, 1800, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(12558, 1745, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(12559, 1745, ITEM_HEAVY);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(4117, 286, ITEM_BOMB);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);

	pItem = new CItem(3117, 200, ITEM_BOMB);
	CObjMgr::GetInstance()->AddGameObject(pItem, OBJ_ITEM);


	
	//�丶


	//����




	
	//�丶


	//����
	//pEnemy = new CEnemy(400, 100);

	//CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//pEnemy = new CToma(400, 100);

	//CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//pEnemy = new CZombie(400, 100);

	//CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);


}

int  CStage::Update(void)
{
	//�������� �뷡 �ݺ�
	//CSoundMgr::GetInstance()->PlayBGMSound(L"StageMusic.mp3");
	
	//����
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

	//���ͽ���
	//MonsterSpawn();


	//UI
	//�ð�
	if(m_dwTime + 3000 <= GetTickCount())
	{
		--m_iTime;
		m_dwTime = GetTickCount();
	}

	//��ź
	if(m_iGranadeBullet <= 0)
	{
		m_bGranade = false;
	}

	//�ӽŰ�
	if(m_iHeavyBullet <= 0)
	{
		m_bHeavy = false;
		m_bPistolInfiniteBullet = true;
	}

	//���ӿ�����Ʈ �Ŵ������� ������Ʈ.
	CObjMgr::GetInstance()->Update();


	return 0;
}

void CStage::Render(HDC _hdc)
{
	//CObjMgr::GetInstance()->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());

	CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front()->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
	
	//
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_BOSS].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].end();
		
		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}

	if(!(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER_LEG].empty()))
		CObjMgr::GetInstance()->GetList()[OBJ_PLAYER_LEG].front()->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
	
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].empty()))
		CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
	//Y ���� �ٸ����� ��ü�� ������ ����.

	///////////����
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();
		
		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}



	//�Ѿ�
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_BULLET].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_BULLET].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_BULLET].end();

		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}

	//��ź
		if(!(CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_GRANADE].end();

		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}

	//�Ѿ� ����Ʈ
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_EFFECT].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_EFFECT].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_EFFECT].end();
		
		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}

	//������
	if(!(CObjMgr::GetInstance()->GetList()[OBJ_ITEM].empty()))
	{
		list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_ITEM].begin();
		list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_ITEM].end();

		for(iter; iter != iter_end ; ++iter)
		{
			(*iter)->Render(m_mapBmp["BACKBUFFER"]->GetMemDC());
		}
	}


	//UI
	//�Ѿ˼� ���� UI ����
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,0
		,0
		,300
		,64
		,m_mapBmp["LIFE_BULLET"]->GetMemDC()
		,0
		,0
		,300
		,64
		,RGB(0, 255, 0)	);

	//���� PRESS START
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,500
		,0
		,500
		,50
		,m_mapBmp["PRESSSTART"]->GetMemDC()
		,0
		,0
		,500
		,50
		,RGB(0, 255, 0)	);
	
	//�ð�
	//10
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,230
		,-120
		,300
		,300
		,m_mapBmp["TIME"]->GetMemDC()
		,300 * (m_iTime / 10)
		,0
		,300
		,300
		,RGB(255, 255, 255)	);

	//1
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
		,280
		,-120
		,300
		,300
		,m_mapBmp["TIME"]->GetMemDC()
		,300 * (m_iTime % 10)
		,0
		,300
		,300
		,RGB(255, 255, 255)	);

	//����
	if(m_bPistolInfiniteBullet == true)
	{
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,170
			,23
			,35
			,18

			,m_mapBmp["INFINIT"]->GetMemDC()
			,0
			,0
			,20
			,8
			,RGB(255, 255, 255)	);
	}

	//�����
	if(m_bHeavy == true)
	{
		//�Ѿ˼�
		//100
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,120
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,100 * (m_iHeavyBullet / 100)
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
		//10
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,140
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,100 * ((m_iHeavyBullet % 100) / 10)
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
		//1
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,160
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,100 * (m_iHeavyBullet % 10)
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
	}

	//��ź
	if(m_bGranade == true)
	{
		//10
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,200
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,100 * (m_iGranadeBullet / 10)
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
		//1
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,220
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,100 * (m_iGranadeBullet % 10)
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
	}
	else
	{
		//1
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,220
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,0
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
		//1
		TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,220
			,-18
			,100
			,100
			,m_mapBmp["SCORE"]->GetMemDC()
			,0
			,0
			,100
			,100
			,RGB(255, 255, 255)	);
	}

	//����
	
	TransparentBlt(m_mapBmp["BACKBUFFER"]->GetMemDC()
			,7
			,25
			,(m_iLife * 7)
			,12
			,m_mapBmp["LIFE_BAR"]->GetMemDC()
			,0
			,0
			,119
			,12
			,RGB(0, 0, 0)	);

	//ũ����

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

	//����

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
			,11183		
			,1530		
			,m_mapBmp["BACKBUFFER"]->GetMemDC()	
			,0		
			,0		
			,SRCCOPY);	


}

void CStage::Release(void)
{
	CSceneMgr::GetInstance()->DestroyInstance();
}


void CStage::MonsterSpawn(void)
{
	int iPlayer_X = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo().fX;

	//���͸� �̰��� �߰�
	//�𵧱�

	//if(m_bFirstCast == false)
	//{

	pEnemy = new CEnemy(800, 530);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(50, 550);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(643, 565);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bFirstCast = true;
	//}

	//else if(m_bSecondCast == false && (iPlayer_X + 800) >= 1300)
	//{
	pEnemy = new CEnemy(1397 /*+ CGameObject::m_ptScroll.*/, 530);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);
	
	pEnemy = new CEnemy(1604, 538);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1738, 584);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1832, 588);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(1965, 586);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);
	
	pEnemy = new CToma(2395, 225);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(2795, 562);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bSecondCast = true;
	//}

	//else if(m_bThirdCast == false && (iPlayer_X + 800) >= 3300)
	//{
//

	pEnemy = new CEnemy(3327, 528);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(3930, 380);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(4141, 318);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(4464, 229);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(3930, 380);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(5487, 318);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(6532, 229);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(7895, 206);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(5698, 533);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(6911, 916);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bThirdCast = true;
	//}

	//else if(m_bForthCast == false && (iPlayer_X + 800) >= 7100)
	//{
	pEnemy = new CToma(7198, 684);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(7464, 1010);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8029, 1397);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8159, 1437);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8200, 1445);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8300, 1446);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8645, 1429);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(8345, 1427);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(8986, 1755);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9408, 1850);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9623, 1852);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CToma(9627, 1419);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(9800, 1850);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bForthCast = true;
	//}

	//else if(m_bFifthCast == false && (iPlayer_X + 800) >= 10100)
	//{
	pEnemy = new CEnemy(10148, 1808);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(10367, 1842);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11223, 1795);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(11553, 1835);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(11650, 1814);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11223, 1795);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11700, 1835);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11900, 1814);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CZombie(12230, 1841);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(11936, 1815);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(12699, 1869);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(13446, 1959);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	pEnemy = new CEnemy(13857, 1990);
	CObjMgr::GetInstance()->AddGameObject(pEnemy, OBJ_MONSTER);

	//m_bFifthCast = true;
	//}



	
	//�丶


	//����

}