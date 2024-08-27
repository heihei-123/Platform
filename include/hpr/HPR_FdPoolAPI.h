/**@file HPR_FdPoolAPI.h
 * @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 * @brief  This file supply api of fd poll
 * @author   lly
 * @date     2012/03/10
 * @version  v1.0
 * @note ///Description here 
 * @note     History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note     lly       2012/03/10   v1.0.0     create
 * @warning  
 */
 
#ifndef _HIK_FD_POLL_H_
#define _HIK_FD_POLL_H_

#include "HPR_Config.h"

#define FD_TYPE_FILE    0
#define FD_TYPE_SOCKET  1

/**@fn     HPR_DECLARE HPR_INT32 HPR_FdPoolInit(void)
 * @brief  初始化fd pool
 * @brief  Author/Date  lly/2012-03-10
 * @param  [in]
 * @param  [out]
 * @return HPR_OK/HPR_ERROR
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_FdPoolInit(void);

/**@fn     HPR_DECLARE HPR_FdPoolFina fd_poll_fina(void)
 * @brief  反初始化fd pool
 * @brief  Author/Date  lly/2012-03-10
 * @param  [in]
 * @param  [out]
 * @return HPR_OK/HPR_ERROR
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_FdPoolFina(void);

/**@fn     HPR_DECLARE HPR_INT32 HPR_FdPoolAlloc(HPR_INT32 iSrcFd, HPR_UINT32 nFdType, HPR_INT32 *pDstFd)
 * @brief  分配一个fd
 * @brief  Author/Date  lly/2012-03-10
 * @param  [in]iOldFd: Old fd
 * @param  [in]nFdType: fd type(FD_TYPE_FILE/FD_TYPE_SOCKET).
 * @param  [out]pNewFd: new fd
 * @return HPR_OK/HPR_ERROR
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_FdPoolAlloc(HPR_INT32 iOldFd, HPR_UINT32 nFdType, HPR_INT32 *pNewFd);

/**@fn     HPR_DECLARE HPR_INT32 HPR_FdPoolFree(HPR_INT32 iFd, HPR_UINT32 nFdType)
 * @brief  回收一个fd
 * @brief  Author/Date  lly/2012-03-10
 * @param  [in]iFd: fd
 * @param  [in]nFdType: fd type(FD_TYPE_FILE/FD_TYPE_SOCKET).
 * @param  [out]
 * @return HPR_OK/HPR_ERROR
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_FdPoolFree(HPR_INT32 iFd, HPR_UINT32 nFdType);

#endif /* _HIK_FD_POLL_H_ */