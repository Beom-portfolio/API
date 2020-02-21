#ifndef _MACRO_H_
#define _MACRO_H_

#define CREATE_SINGLETON(ClassName)			\
	private:								\
static ClassName* m_pInstance;				\
	public:									\
		 static ClassName* GetInstance(void)\
		 {									\
			if(m_pInstance == NULL)			\
				m_pInstance = new ClassName;\
			return m_pInstance;				\
		 }									\
											\
		void DestroyInstance(void)			\
		{									\
			if(m_pInstance)					\
			{								\
				delete m_pInstance;			\
				m_pInstance = NULL;			\
			}								\
		}									\

#define INIT_SINGLETON(ClassName)			\
	ClassName* ClassName::m_pInstance = NULL;\


#define RECT_CENTER(DataRect, TargetInfo)															\
				{																					\
				DataRect.left		= static_cast<LONG>(TargetInfo.fX - TargetInfo.fCX / 2.f);	\
				DataRect.top		= static_cast<LONG>(TargetInfo.fY - TargetInfo.fCY / 2.f);	\
				DataRect.right		= static_cast<LONG>(TargetInfo.fX + TargetInfo.fCX / 2.f);	\
				DataRect.bottom		= static_cast<LONG>(TargetInfo.fY + TargetInfo.fCY / 2.f);	\
				}																					\
//렉트구하는 함수.

#define SAFE_DELETE(p) if( (p) ) {delete (p); (p) = NULL;}

#endif