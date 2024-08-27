/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HRP_Semaphore.h
 * Desc:        OS Layer Component.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

/*! 
    \file HPR_Semaphore.h
    \brief HPR Semaphore Manager.

    Details.
*/

#ifndef __HPR_SEMAPHORE_H__
#define __HPR_SEMAPHORE_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

#if defined (OS_WINDOWS)
    typedef HPR_HANDLE HPR_SEM_T;
#elif defined(OS_POSIX)
    #include <semaphore.h>
#if (defined (__linux__) || defined(OS_S60))
    typedef sem_t HPR_SEM_T;
#else
    typedef sem_t* HPR_SEM_T;
#endif
#else
    #error OS Not Implement Yet.
#endif

/**
 * HPR_SemCreate
 * @param pSem (OUT) sem want to create.
 * @param nInitCount (IN) init resources after create.
 * @return 0 success, -1 fail.
 * @sa HPR_SemDestroy(),HPR_SemWait(),HPR_SemTimedWait(),HPR_SemPost()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SemCreate(HPR_SEM_T* pSem, HPR_UINT32 nInitCount);

/**
 * HPR_SemDestroy
 * @param pSem (IN) created by HPR_SemCreate
 * @return 0 success, -1 fail.
 * @sa HPR_SemCreate(),HPR_SemWait(),HPR_SemTimedWait(),HPR_SemPost()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SemDestroy(HPR_SEM_T* pSem);

/**
 * HPR_SemWait
 * @param pSem (IN) created by HPR_SemCreate
 * @return 0 success, -1 fail.
 * @sa HPR_SemCreate(),HPR_SemDestroy(),HPR_SemTimedWait(),HPR_SemPost()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SemWait(HPR_SEM_T* pSem);

/**
 * HPR_SemTimedWait
 * @param pSem (IN) created by HPR_SemCreate
 * @param nTimeOut (IN) wait timeout.
 * @return 0 success, -1 fail.
 * @sa HPR_SemCreate(),HPR_SemDestroy(),HPR_SemWait(),HPR_SemPost()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SemTimedWait(HPR_SEM_T* pSem, HPR_UINT32 nTimeOut);

/**
 * HPR_SemPost
 * @param pSem (IN) created by HPR_SemCreate
 * @return 0 success, -1 fail.
 * @sa HPR_SemCreate(),HPR_SemDestroy(),HPR_SemWait(),HPR_SemTimedWait()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SemPost(HPR_SEM_T* pSem);


#endif
