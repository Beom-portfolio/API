#pragma once

#include "Include.h"

class CSoundMgr
{
private:
	static CSoundMgr*	m_pInstance;

public:
	static CSoundMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
		{
			m_pInstance = new CSoundMgr;
		}

		return m_pInstance;
	}

	void Destroy(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}


	/////////fmod �������̽�
private:
	FMOD_SYSTEM*		m_pSystem;	//fmod �ý��� ������
	FMOD_CHANNEL*		m_pEffect;	//ȿ����
	FMOD_CHANNEL*		m_pMainBGM;	//�����
	FMOD_CHANNEL*		m_pSkill;	//��ų
	FMOD_CHANNEL*		m_pMonster; //���� �Ҹ�

	FMOD_RESULT			m_Result;	//fmod�����߿� ����üũ

	unsigned int		m_iVersion;

	map<TCHAR*, FMOD_SOUND*>		m_mapSound;


	//��� �Լ��� ��������.
public:
	void Initialize(void);
	void LoadSoundFile(void);
	void PlaySound(TCHAR* pSoundKey);
	void PlayBGMSound(TCHAR* pSoundKey);
	void SoundAllStop(void);

public:
	map<TCHAR*, FMOD_SOUND*>* GetSoundMap(void)
	{
		return &m_mapSound;
	}

private:
	void ErrorCheck(FMOD_RESULT _result);


private:
	CSoundMgr(void);
public:
	~CSoundMgr(void);
};
