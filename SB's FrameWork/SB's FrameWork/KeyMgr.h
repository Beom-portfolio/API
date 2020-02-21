#pragma once

class CKeyMgr
{
private:
	static CKeyMgr* m_pInstance;

	DWORD m_dwKey;

public:
	static CKeyMgr* GetInstance(void)
	{
		if(m_pInstance == NULL)
			m_pInstance = new CKeyMgr;

		return m_pInstance;
	}

	void DestroyInstance(void)
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

public:
	void SetKeyState(void);
	DWORD GetKeyState(void);
	
private:
	CKeyMgr(void);
public:
	~CKeyMgr(void);
};
