/*
 * CopyRight:	HangZhou Hikvision System Technology Co., Ltd. All	Right Reserved.
 * FileName:	HRP_Guard.h
 * Desc:		OS Layer Component.
 * Author:		schina
 * Date:		2009-03-02
 * Contact:		zhaoyiji@hikvision.com.cn
 * History:		Created By Zhaoyiji 2009-03-02
 * */

#ifndef __HPR_GUARD_H__
#define __HPR_GUARD_H__

#include "HPR_Mutex.h"

//////////////////////////////////////////////////////////////////////////
//c++ 编译器才支持
#if defined (CXXCOMPILE)
class HPR_DECLARE_CLASS HPR_Guard
{
public:
	HPR_Guard(HPR_MUTEX_T* pMutex)
	:m_pMutex(pMutex)
	{
		if(NULL != m_pMutex)
		{
            HPR_MutexLock(m_pMutex);
		}
	}
	
	~HPR_Guard()
	{
		if(NULL != m_pMutex)
		{
            HPR_MutexUnlock(m_pMutex);
		}
	}

private:
	HPR_MUTEX_T* m_pMutex;
};
#endif
//////////////////////////////////////////////////////////////////////////

#endif

