#ifndef _CONST_H_
#define _CONST_H_

//â ����
const int iWINCX = 800;
const int iWINCY = 600;

//Ű ����

//�÷��̾�
const DWORD KEY_LEFT  = 0x00000001;
const DWORD KEY_RIGHT = 0x00000002;
const DWORD KEY_UP    = 0x00000004;
const DWORD KEY_DOWN  = 0x00000008;
const DWORD KEY_SPACE = 0x00000010;

const DWORD KEY_CTRL  = 0x00000020;
const DWORD KEY_Z	  = 0x00000040;


//�޴�
const DWORD KEY_ONE    = 0x00000080;
const DWORD KEY_TWO    = 0x00000100;
const DWORD KEY_FIVE   = 0x00000200;
const DWORD KEY_RETURN = 0x00000400;


//��ũ���� ���� Ű
const DWORD KEY_H	   = 0x00000800;
const DWORD KEY_J	   = 0x00001000;
const DWORD KEY_N	   = 0x00002000;

//
const DWORD KEY_K	   = 0x00004000;
const DWORD KEY_L	   = 0x00008000;
const DWORD KEY_S      = 0x00010000;


const DWORD STATE_STAND			 = 0x00000001;		//��������
const DWORD STATE_WALK			 = 0x00000002;		//������
const DWORD STATE_JUMP			 = 0x00000004;		//�۶�
const DWORD STATE_SEAT			 = 0x00000008;		//������
const DWORD STATE_UPSEE			 = 0x00000010;		//���κ���
const DWORD STATE_SHOOT			 = 0x00000020;		//��
const DWORD STATE_UPSHOOT		 = 0x00000040;		//���� ��
const DWORD STATE_SEATSHOOT		 = 0x00000080;		//�ɾƼ� ��
const DWORD STATE_JUMPDOWNSHOOT	 = 0x00000100;		//���������� ��
const DWORD STATE_SEATMOVE		 = 0x00000200;		//�ɾƼ� ������
const DWORD STATE_JUMPDOWNSEE	 = 0x00000400;		//�����ϸ鼭 �غ���

const DWORD STATE_KNIFEATT			= 0x00000800;	//Į����
const DWORD STATE_SEATKNIFEATT 		= 0x00001000;	//

const DWORD STATE_MACHINGUNSHOOT	= 0x00002000;	//���ӽŰ� ���ڸ�
const DWORD STATE_MACHINGUNCROSS	= 0x00004000;	//���ӽŰ� �밢��

const DWORD STATE_THROWBOMB			= 0x00008000;	//����ź

const DWORD STATE_DEAD				= 0x00010000;	//����

#endif