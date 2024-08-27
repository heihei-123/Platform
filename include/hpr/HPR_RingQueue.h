/**@file HPR_RingQueue.h
 * @note HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 * @brief  
 * @author   lly
 * @date     2012/03/21
 * @version  v1.0
 * @note ///Description here 
 * @note     History:        
 * @note     <author>   <time>    <version >   <desc>
 * @note     lly       2012/03/21   v1.0.0     create
 * @warning  
 */

#ifndef _HIK_HPR_RINGQUEUE_H_
#define _HIK_HPR_RINGQUEUE_H_

#ifdef CXXCOMPILE /* 只适用于C++ */
#include <new>

/**@class CRingQueuet<Type>
 * @brief  循环队列类实现
 * @brief  Author/Date  lly/2012-03-21
 */
template <typename Type>
class CRingQueue
{
public:
    CRingQueue(HPR_UINT32 nInitSize);
    ~CRingQueue(void);
public:

    typedef HPR_BOOL (* CALLBACK_FIND)(const Type &, const Type &);

    /**@fn    HPR_INT32 PushBack(const Type &Elem);
     * @brief  入队列
     * @brief  Author/Date  lly/2012-03-20
     * @param  [in]Elem: 队列元素
     * @param  [out]
     * @return HPR_OK/HPR_ERROR
     */
    HPR_INT32 PushBack(const Type &Elem);

    /**@fn    HPR_INT32 PopFront(Type &Elem);
     * @brief  出队列
     * @brief  Author/Date  lly/2012-03-20
     * @param  [in]
     * @param  [out]Elem: 队列第一个元素
     * @return HPR_OK/HPR_ERROR
     */
    HPR_INT32 PopFront(Type &Elem);

    /**@fn    HPR_INT32 Front(Type &Elem);
     * @brief  取队列第一个元素
     * @brief  Author/Date  lly/2012-03-21
     * @param  [in]
     * @param  [out]Elem: 队列第一个元素
     * @return HPR_OK/HPR_ERROR
     */
    HPR_INT32 Front(Type &Elem);

    /**@fn    HPR_BOOL Full(void)
     * @brief  判断队列是否已满
     * @brief  Author/Date  lly/2012-03-21
     * @param  [in]
     * @param  [out]
     * @return HPR_TRUE/HPR_FALSE
     */
    HPR_BOOL Full(void);

    /**@fn    HPR_BOOL Empty(void)
     * @brief  判断队列是否为空
     * @brief  Author/Date  lly/2012-03-21
     * @param  [in]
     * @param  [out]
     * @return HPR_TRUE/HPR_FALSE
     */
    HPR_BOOL Empty(void);

    /**@fn     HPR_BOOL Find_If(const Type &Elem, CALLBACK_FIND fnFind)
     * @brief  查找元素是否在队列中
     * @brief  Author/Date  lly/2012-06-12
     * @param  [in]Elem: 待查找的元素
     * @param  [in]fnFind: 回调函数
     * @param  [out]
     * @return HPR_TRUE/HPR_FALSE
     */
    HPR_BOOL Find_If(const Type &Elem, CALLBACK_FIND fnFind);

private:
    CRingQueue(const CRingQueue &);
    CRingQueue &operator =(const CRingQueue &);
private:
    Type *m_pQueue;
    HPR_UINT32 m_iFront;
    HPR_UINT32 m_iRear;
    HPR_UINT32 m_nInitSize;
};

template <typename Type>
CRingQueue<Type>::CRingQueue(HPR_UINT32 nInitSize)
:m_pQueue(NULL),
m_iFront(0),
m_iRear(0),
m_nInitSize(nInitSize + 1)
{
    m_pQueue = new(std::nothrow) Type[m_nInitSize];
}

template <typename Type>
CRingQueue<Type>::~CRingQueue(void)
{
    m_iFront = 0;
    m_iRear = 0;
    m_nInitSize = 0;
    if (NULL != m_pQueue)
    {
        delete m_pQueue;
        m_pQueue = NULL;
    }
}

template <typename Type>
HPR_INT32 CRingQueue<Type>::PushBack(const Type &Elem)
{
    if ((NULL == m_pQueue) || Full())
    {
        return HPR_ERROR;
    }
    m_pQueue[m_iRear] = Elem;
    m_iRear= (m_iRear+ 1) % m_nInitSize;
    return HPR_OK;
}

/**@fn    HPR_INT32 PushBack(const Type &Elem);
 * @brief  入队列
 * @brief  Author/Date  lly/2012-03-20
 * @param  [in]Elem: 队列元素
 * @param  [out]
 * @return HPR_OK/HPR_ERROR
 */
template <typename Type>
HPR_INT32 CRingQueue<Type>::PopFront(Type &Elem)
{
    if ((NULL == m_pQueue) || Empty())
    {
        return HPR_ERROR;
    }
    Elem = m_pQueue[m_iFront];
    m_iFront = (m_iFront + 1) % m_nInitSize;
    return HPR_OK;
}

/**@fn    HPR_INT32 Front(Type &Elem);
 * @brief  取队列第一个元素
 * @brief  Author/Date  lly/2012-03-21
 * @param  [in]
 * @param  [out]Elem: 队列第一个元素
 * @return HPR_OK/HPR_ERROR
 */
template <typename Type>
HPR_INT32 CRingQueue<Type>::Front(Type &Elem)
{
    if ((NULL == m_pQueue) || Empty())
    {
        return HPR_ERROR;
    }
    Elem = m_pQueue[m_iFront];
    return HPR_OK;
}

/**@fn    HPR_BOOL Full(void)
 * @brief  判断队列是否已满
 * @brief  Author/Date  lly/2012-03-21
 * @param  [in]
 * @param  [out]
 * @return HPR_TRUE/HPR_FALSE
 */
template <typename Type>
HPR_BOOL CRingQueue<Type>::Full(void)
{
    return (m_iRear + 1) % (HPR_INT32)m_nInitSize == m_iFront;
}

/**@fn    HPR_BOOL Empty(void)
 * @brief  判断队列是否为空
 * @brief  Author/Date  lly/2012-03-21
 * @param  [in]
 * @param  [out]
 * @return HPR_TRUE/HPR_FALSE
 */
template <typename Type>
HPR_BOOL CRingQueue<Type>::Empty(void)
{
    return m_iFront == m_iRear;
}

/**@fn     HPR_BOOL Find_If(const Type &Elem, CALLBACK_FIND fnFind)
 * @brief  查找元素是否在队列中
 * @brief  Author/Date  lly/2012-06-12
 * @param  [in]Elem: 待查找的元素
 * @param  [in]fnFind: 回调函数
 * @param  [out]
 * @return HPR_TRUE/HPR_FALSE
 */
template <typename Type>
HPR_BOOL CRingQueue<Type>::Find_If(const Type &Elem, CALLBACK_FIND fnFind)
{
    HPR_BOOL bFind = HPR_FALSE;
    HPR_UINT32 iFront = m_iFront;
    while (iFront != m_iRear)
    {
        if (fnFind(Elem, m_pQueue[iFront]))
        {
            bFind = HPR_TRUE;
            break;
        }
        iFront = (iFront + 1) % m_nInitSize;
    }
    return bFind;
}

#endif /* CXXCOMPILE */

#endif /* _HIK_HPR_RINGQUEUE_H_ */
