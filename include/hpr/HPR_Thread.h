/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HRP_Thread.h
 * Desc:        OS Layer Component.
 * Author:      guanguochen
 * Date:        2009-03-30
 * Contact:     guanguochen@hikvision.com.cn
 * History:     Created By guanguochen 2009-03-30
 * ADD histroy:  add HPR_ThreadDetached_CreateEx() by fenggx 2010-7-29
 * */

/*! 
    \file HPR_Thread.h
    \brief HPR Thread Manager.

    Details.
*/

#ifndef __HPR_THREAD_H__    
#define __HPR_THREAD_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

#if defined (OS_WINDOWS)
#define HPR_INVALID_THREAD (HANDLE)(NULL)
#elif defined (OS_POSIX)
#define HPR_INVALID_THREAD (pthread_t)(-1)
#endif

/**
 * HPR_Thread_Create create thread.
 * must call HPR_Thread_Wait() release thread resource;
 * @param StartAddress (IN) thread body
 * @param Params (IN) parameter input into thread body.
 * @param StackSize (IN) thread body stack size.
 * @param IsSuspend (IN) is thread suspend after create, only valid in windows.
 * @param Priority (IN) thread priority
 * @param SchedPolicy (IN) thread sched policy
 * @return NULL fail, else success.
 * @sa HPR_ThreadDetached_Create(),HPR_Thread_Wait()
 */
HPR_DECLARE HPR_HANDLE CALLBACK HPR_Thread_Create
(
	HPR_VOIDPTR(CALLBACK *StartAddress)(HPR_VOIDPTR), 
	HPR_VOID* Params, 
	HPR_UINT32 StackSize,
	HPR_INT32 Priority
);


/**
 * HPR_ThreadDetached_Create create thread with detached attr.
 *  thread resource will be release by OS kernal automatically
 * @param StartAddress (IN) thread body
 * @param Params (IN) parameter input into thread body.
 * @param StackSize (IN) thread body stack size.
 * @param Priority (IN) no use for win32
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_BOOL CALLBACK HPR_ThreadDetached_Create
(
	 HPR_VOIDPTR(CALLBACK *StartAddress)(HPR_VOIDPTR),
	 HPR_VOID* Params, 
	 HPR_UINT32 StackSize,
	 HPR_INT32 Priority
 );

// added by fenggx begin!
/**
 * HPR_ThreadDetached_CreateEx create thread with detached attr.
 *  thread resource will be release by OS kernal automatically
 * @param StartAddress (IN) thread body
 * @param Params (IN) parameter input into thread body.
 * @param StackSize (IN) thread body stack size.
 * @return HPR_HANDLE if success, HPR_INVALID_HANDLE if fail!
 * @sa HPR_ThreadDetached_CreateEx()
 */
HPR_DECLARE HPR_HANDLE CALLBACK HPR_ThreadDetached_CreateEx
(
    HPR_VOIDPTR(CALLBACK *StartAddress)(HPR_VOIDPTR),
    HPR_VOID* Params, 
    HPR_UINT32 StackSize, 
    HPR_INT32 Priority
);
// added by fenggx end

/**
 * HPR_Thread_Wait wait thread and release resource.
 * @param ThreadHandle (IN) thread handle, created by HPR_Thread_Create
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_Wait(HPR_HANDLE ThreadHandle);

/**
 * HPR_Thread_Suspend suspend thread
 * @param ThreadHandle (IN) thread handle, created by HPR_Thread_Create
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_Suspend(HPR_HANDLE ThreadHandle);

/**
 * HPR_Thread_Resume resume thread, only valid in windows
 * @param ThreadHandle (IN) thread handle, created by HPR_Thread_Create
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_Resume(HPR_HANDLE ThreadHandle);

/**
 * HPR_Thread_SetPriority set thread priority
 * @param ThreadHandle (IN) thread handle, created by HPR_Thread_Create
 * @param Priority (IN) sched priority
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_SetPriority(HPR_HANDLE ThreadHandle, HPR_INT32 Priority);

/**
 * HPR_Thread_SetSchedPolicy set thread sched policy
 * @param ThreadHandle (IN) thread handle, created by HPR_Thread_Create
 * @param SchedPolicy (IN) sched policy
 * @return 0 success, -1 fail
 * @sa HPR_Thread_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_SetSchedPolicy(HPR_HANDLE ThreadHandle, HPR_INT32 SchedPolicy);

/**
 * HPR_Thread_Exit exit thread.
 * @return 0 success, -1 fail.
 * @sa HPR_ThreadDetached_Create()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Thread_Exit();

/**
 * HPR_Thread_GetId
 * @param void
 * @return 线程ID
 * @sa
 */
HPR_DECLARE HPR_HANDLE CALLBACK HPR_Thread_GetSelfId();

/**
 * HPR_Thread_SetName.
 * @return 0 success, -1 fail.
 * @sa HPR_Thread_SetName()
 */
HPR_DECLARE HPR_INT32 HPR_Thread_SetName(const HPR_INT8 *ThreadName);
#endif
