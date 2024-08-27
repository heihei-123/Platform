/**@file HPR_FdPool.h
 * @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 * @brief  
 * @author   lly
 * @date     2012/03/10
 * @version  v1.0
 * @note ///Description here 
 * @note     History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note     lly       2012/03/10   v1.0.0     create
 * @warning  
 */
#ifndef __HIK_HPR_FD_POOL_H__
#define __HIK_HPR_FD_POOL_H__

#include "HPR_Guard.h"
#include "HPR_Types.h"
#include "HPR_RingQueue.h"

class CFdPoll
{
public:
    CFdPoll(HPR_INT32 iMinFd, HPR_INT32 iMaxFd);
    ~CFdPoll(void);
protected:
    CFdPoll(void){}
    CRingQueue<HPR_INT32> *m_pFdQueue;
    HPR_MUTEX_T m_FdLock;
public:

    /**@fn     HPR_INT32 Alloc(HPR_INT32 *pFd)
     * @brief  分配一个fd
     * @brief  Author/Date  lly/2012-03-10
     * @param  [in]nInitSize
     * @param  [out]pFd: fd
     * @return HPR_OK/HPR_ERROR
     */
    HPR_INT32 Alloc(HPR_INT32 *pFd);

    /**@fn     HPR_INT32 Free(HPR_INT32 iFd)
     * @brief  回收一个fd
     * @brief  Author/Date  lly/2012-03-10
     * @param  [in]iFd: fd
     * @param  [out]
     * @return HPR_OK/HPR_ERROR
     */
    HPR_INT32 Free(HPR_INT32 iFd);
private:
    /* 防止浅拷贝 */
    CFdPoll(const CFdPoll &);
    CFdPoll &operator =(const CFdPoll &);
};

#endif /* __HIK_HPR_FD_POOL_H__ */
