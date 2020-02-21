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


	/////////fmod 인터페이스
private:
	FMOD_SYSTEM*		m_pSystem;	//fmod 시스템 포인터
	FMOD_CHANNEL*		m_pEffect;	//효과음
	FMOD_CHANNEL*		m_pMainBGM;	//배경음
	FMOD_CHANNEL*		m_pSkill;	//스킬
	FMOD_CHANNEL*		m_pMonster; //몬스터 소리

	FMOD_RESULT			m_Result;	//fmod실행중에 에러체크

	unsigned int		m_iVersion;

	map<TCHAR*, FMOD_SOUND*>		m_mapSound;


	//기능 함수를 구현하자.
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
