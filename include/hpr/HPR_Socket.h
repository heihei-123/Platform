/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HRP_Socket.h
 * Desc:        OS Layer Component.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

/*! 
    \file HPR_Socket.h
    \brief HPR Socket Manager.

    Details.
*/

#ifndef __HPR_SOCKET_H__
#define __HPR_SOCKET_H__

#include "HPR_Config.h"
#include "HPR_Types.h"
#include "HPR_Addr.h"
#include "HPR_Time.h"

#if defined(OS_WINDOWS)
    #define HPR_SOCK_ERROR SOCKET_ERROR
    #define HPR_INVALID_SOCKET INVALID_SOCKET
    #define HPR_SHUT_RD     SD_RECEIVE
    #define HPR_SHUT_WR     SD_SEND
    #define HPR_SHUT_RDWR   SD_BOTH
    static HPR_BOOL g_bWSAStartup = HPR_FALSE;
#elif defined(OS_POSIX)
    #define HPR_SOCK_ERROR      -1
    #define HPR_INVALID_SOCKET -1
    #define HPR_SHUT_RD     SHUT_RD
    #define HPR_SHUT_WR     SHUT_WR
    #define HPR_SHUT_RDWR   SHUT_RDWR
#else
    #error OS Not Implement Yet.
#endif


#define HPR_SAFE_CLOSE_FD(iFd) do{if(HPR_INVALID_SOCKET != (iFd))\
        {HPR_CloseSocket((iFd));((iFd)=HPR_INVALID_SOCKET);}\
        }while(0);

/* 关闭fd并消除nowait状态 */
#define HPR_CLOSE_FD_NOTIMEWAIT(fd) do{if(HPR_INVALID_SOCKET != (fd))\
        {HPR_LingerOn((fd), 0);\
        HPR_CloseSocket((fd));\
        (fd) = HPR_INVALID_SOCKET;}}while(0);


/**
 * HPR_CreateSocket
 * @param iAf (IN) address family AF_INET/AF_INET6
 * @param iType (IN) socket type SOCK_DGRAM/SOCK_STREAM
 * @param iProto (IN) 0
 * @return HPR_INVALID_SOCKET fail, else success.
 * @sa HPR_CloseSocket()
 */
HPR_DECLARE HPR_SOCK_T CALLBACK HPR_CreateSocket(HPR_INT32 iAf, HPR_INT32 iType, HPR_INT32 iProto);

/**
 * HPR_CloseSocket
 * @param iSockFd (IN) socket fd get by HPR_CreateSocket
 * @param bForce (IN) judge if force to close socket, call shutdown
 * @return 0 success, -1 fail.
 * @sa HPR_CreateSocket()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CloseSocket(HPR_SOCK_T iSockFd);

/**
 * HPR_CloseSocket
 * @param iSockFd (IN) socket fd get by HPR_CreateSocket
 * @param bForce (IN) judge if force to close socket, call shutdown ,default is HPR_FALSE
 * @return 0 success, -1 fail.
 * @sa HPR_CreateSocket()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CloseSocketEx(HPR_SOCK_T iSockFd, HPR_BOOL bForce);


/**
 * HPR_ShutDown shutdown socket fd.
 * @param iSockFd (IN) socket fd.
 * @param iHow (IN) how to shut. HPR_SHUT_RD/HPR_SHUT_WR/HPR_SHUT_RDWR
 * @see HPR_SHUT_RD,HPR_SHUT_RDWR, HPR_SHUT_WR
 * @return 0 success, -1 fail.
 * @sa HPR_CloseSocket(),HPR_CreateSocket()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_ShutDown(HPR_SOCK_T iSockFd, HPR_INT32 iHow);

/**
 * HPR_Bind bind socket fd to address.
 * @param iSockFd (IN) socket fd.
 * @param pHprAddr (IN) HPR_ADDR_T address.
 * @return 0 success, -1 fail.
 * @sa HPR_CreateSocket()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Bind(HPR_SOCK_T iSockFd, HPR_ADDR_T* pHprAddr);

/**
 * HPR_Listen listen on port (tcp)
 * @param iSockFd (IN) socket fd
 * @param iBackLog (IN) listen queue long.
 * @return 0 success, -1 fail.
 * @sa HPR_Bind(),HPR_CreateSocket()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Listen(HPR_SOCK_T iSockFd, HPR_INT32 iBackLog);

/**
 * HPR_Accept accept remote connect (tcp)
 * @param iSockFd (IN) socket fd.
 * @param pHprAddr (OUT) remote address.default is NULL
 * @param nTimeOut (IN) connect timeout,default is HPR_INFINITE
 * @return HPR_INVALID_SOCKET fail, else success.
 * @see HPR_INVALID_SOCKET
 * @sa HPR_Bind(),HPR_CreateSocket(),HPR_Listen()
 */
HPR_DECLARE HPR_SOCK_T CALLBACK HPR_Accept(HPR_SOCK_T iSockFd, HPR_ADDR_T* pHprAddr, HPR_UINT32 nTimeOut);

/**
 * HPR_ConnectWithTimeOut connect to remote listen address. (tcp)
 * @param iSockFd (IN) socket fd.
 * @param pHprAddr (IN) struct HPR_ADDR_T.
 * @param iTimeOut (IN) connect timeout, if iTimeOut==0, it means connect with no timeout.default 
 * @                                                                            is HPR_INFINITE
 * @return 0 success, -1 fail.
 * @sa HPR_Accept
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_ConnectWithTimeOut(HPR_SOCK_T iSockFd, HPR_ADDR_T* pHprAddr, HPR_UINT32 nTimeOut);

/**
 * HPR_BroadCast set broadcast.
 * @param iSockFd (IN) socket fd.
 * @return 0 success -1 fail.
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_BroadCast(HPR_SOCK_T iSockFd);

/**
 * HPR_JoinMultiCastGroup join multicast group
 * @param iSockFd (IN) socket fd.
 * @param pLocal (IN) local address.
 * @param pMcastGroupAddr (IN) multicast group address.
 * @return 0 success, -1 fail.
 * @sa HPR_LeaveMultiCastGroup
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_JoinMultiCastGroup(HPR_SOCK_T iSockFd, HPR_ADDR_T* pLocal, HPR_ADDR_T* pMcastGroupAddr);

/**
 * HPR_LeaveMultiCastGroup leave multicast group.
 * @param iSockFd (IN) socket fd.
 * @param pLocal (IN) local address.
 * @param pMcastGroupAddr (IN) multicast group address.
 * @return 0 success, -1 fail.
 * @sa HPR_JoinMultiCastGroup
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_LeaveMultiCastGroup(HPR_SOCK_T iSockFd, HPR_ADDR_T* pLocal, HPR_ADDR_T* pMcastGroupAddr);

/**
 * HPR_SetNonBlock set enable/disable nonblock.
 * @param iSockFd (IN) socket fd.
 * @param bYesNo (IN) enable/disable nonblock.
 * @return 0 success, -1 fail.
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetNonBlock(HPR_SOCK_T iSockFd, HPR_BOOL bYesNo);

/**
 * HPR_SetTTL set ttl
 * @param iSockFd (IN) socket fd
 * @param iTTL (IN) ttl
 * @return 0 success, -1 fail.
 * @sa HPR_GetTTL
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetTTL(HPR_SOCK_T iSockFd, HPR_INT32 iTTL);

/**
 * Function:    HPR_SetMultiCastTTL
 * Desc:
 * Input:
 * Output:
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetMultiCastTTL(HPR_SOCK_T iSockFd, HPR_INT32 iTTL);

/**
 * HPR_GetTTL get ttl
 * @param iSockFd (IN) socket fd
 * @param iTTL (OUT) ttl
 * @return 0 success, -1 fail.
 * @sa HPR_SetTTL
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetTTL(HPR_SOCK_T iSockFd, HPR_INT32* iTTL);

/**
 * HPR_SetTOS set tos
 * @param iSockFd (IN)  socket fd
 * @param iTOS (IN)
 * @return 0 success, -1 fail.
 * @sa HPR_GetTOS
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetTOS(HPR_SOCK_T iSockFd, HPR_INT32 iTOS);

/**
 * HPR_GetTOS get tos
 * @param iSockFd (IN) socket fd
 * @param iTOS (OUT)
 * @return 0 success, -1 fail.
 * @sa HPR_SetTOS
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetTOS(HPR_SOCK_T iSockFd, HPR_INT32* iTOS);

/**
 * HPR_SetReuseAddr set enable/disable reuse address.
 * @param iSockFd (IN) socket fd.
 * @param bYesNo (IN) enable/disable reuse address.
 * @return 0 success, -1 fail.
 * @sa HPR_SetTimeOut
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetReuseAddr(HPR_SOCK_T iSockFd, HPR_BOOL bYesNo);

/**
 * HPR_SetTimeOut set socket fd I/O timeout.
 * @param iSockFd (IN) socket fd
 * @param iSndTimeO (IN) snd timeout
 * @param iRcvTimeO (IN) rcv timeout
 * @return 0 success, -1 fail.
 * @sa HPR_SetReuseAddr
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetTimeOut(HPR_SOCK_T iSockFd, HPR_INT32 iSndTimeO, HPR_INT32 iRcvTimeO);

/**
 * HPR_SetBuffSize set socket snd/rcv buffsize.
 * @param iSockFd socket fd.
 * @param iSndBuffSize (IN) snd buffer size.
 * @param iRcvBuffSize (IN) rcv buffer size.
 * @return 0 succes, -1 fail.
 * @sa HPR_GetBuffSize
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetBuffSize(HPR_SOCK_T iSockFd, HPR_INT32 iSndBuffSize, HPR_INT32 iRcvBuffSize);

/**
 * HPR_GetBuffSize get socket snd/rcv buffsize.
 * @param iSockFd socket fd.
 * @param iSndBuffSize (OUT) snd buffer size.
 * @param iRcvBuffSize (OUT) rcv buffer size.
 * @return 0 succes, -1 fail.
 * @sa HPR_SetBuffSize
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetBuffSize(HPR_SOCK_T iSockFd, HPR_INT32* iSndBuffSize, HPR_INT32* iRcvBuffSize);

/**
 * HPR_LingerOn disable linger (tcp)
 * @param iSockFd (IN) socket fd.
 * @param iTimeOutSec (IN) linger timeout
 * @return 0 success, -1 fail.
 * @sa HPR_LingerOff()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_LingerOff(HPR_SOCK_T iSockFd);

/**
 * HPR_LingerOn enable linger (tcp)
 * @param iSockFd (IN) socket fd.
 * @param nTimeOut (IN) linger time.
 * @return 0 success, -1 fail.
 * @sa HPR_LingerOn()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_LingerOn(HPR_SOCK_T iSockFd,HPR_UINT16 nTimeOutSec);

/**
 * HPR_SetNoDelay enable/disabel nagle algorithm (tcp)
 * @param iSockFd (IN) socket
 * @param bYesNo (IN) enable/disabel nagle algorithm
 * @return 0 success, -1 fail
 * @sa HPR_LingerOn(),HPR_LingerOff()
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SetNoDelay(HPR_SOCK_T iSockFd,HPR_BOOL bYesNo);

/**   
 * \fn hpr_set_fd_cloexec
 * \brief 设置clexec标记为使能
 * \brief fenggx@2014-9-28
 * \param[in] iSockFd - 待设置的fd
 * \param[out] n/a - n/a
 * \return  n/a 成功 HPR_OK /失败 ErrNo
**/
HPR_DECLARE HPR_INT32 CALLBACK hpr_set_fd_cloexec(HPR_SOCK_T iSockFd);

/**
 * HPR_Sendn send dada to socket fd (tcp).
 * @param iSockFd (IN) socket fd.
 * @param pBuf (IN) data pointer to send data.
 * @param iBufLen (IN) data count want to send.
 * @param iTimeOut (IN) send timeout.
 * @return count of data sent, -1 for error. 
 * @sa HPR_Recv
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Send(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufLen);

/**
 * HPR_Sendn send n byte dada to socket fd (tcp).
 * @param iSockFd (IN) socket fd.
 * @param pBuf (IN) data pointer to send data.
 * @param iBufLen (IN) data count want to send.
 * @param iTimeOut (IN) send timeout.default is HPR_INFINITE
 * @return count of data sent, -1 for error. 
 * @sa HPR_Recv
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Sendn(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufLen, HPR_UINT32 nTimeOut);

/**
 * HPR_Recvn recv data from socket fd (tcp).
 * @param iSockFd (IN) socket fd.
 * @param pBuf (OUT) data pointer to recv data.
 * @param iBufCount (IN) data length want to recv.
 * @return count of data received, -1 for error.
 * @sa HPR_Send
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Recv(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufCount);
HPR_DECLARE HPR_INT32 CALLBACK HPR_RecvWithTimeOut(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufCount, HPR_UINT32 nTimeOut);

/**
 * HPR_Recvn recv n bytes data from socket fd (tcp).
 * @param iSockFd (IN) socket fd.
 * @param pBuf (OUT) data pointer to recv data.
 * @param iBufCount (IN) data length want to recv.
 * @param iTimeOut (IN) recv timeout,default is HPR_INFINITE
 * @return count of data received, -1 for error.
 * @sa HPR_Recv
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Recvn(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufCount, HPR_UINT32 nTimeOut);


/**
 * HPR_SendTo sendto (udp)
 * @param iSockFd (IN) socket fd
 * @param pBuf (IN) data pointer
 * @param iBufLen (IN) max data buffer size
 * @param pHprAddr (IN) HPR_ADDR_T pointer.
 * @return count of data sent, -1 for errror.
 * @sa HPR_RecvFrom
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SendTo(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufLen, HPR_ADDR_T* pHprAddr);

/**
 * HPR_RecvFrom recvfrom (udp)
 * @param iSockFd (IN) socket fd
 * @param pBuf (OUT) data pointer.
 * @param iBufCount (IN) max data buffer size.
 * @param pHprAddr (OUT) HPR_ADDR_T pointer.
 * @return count of data received, -1 for error.
 * @sa HPR_SendTo
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_RecvFrom(HPR_SOCK_T iSockFd, HPR_VOIDPTR pBuf, HPR_INT32 iBufCount, HPR_ADDR_T* pHprAddr);

HPR_DECLARE HPR_INT32 CALLBACK HPR_Ioctl(HPR_SOCK_T iSockFd, HPR_INT32 iCmd, HPR_UINT32 *nData);

#if  defined(OS_WINDOWS)
    #define HPR_ERROR_EINTR WSAEINTR
#else
    #define HPR_ERROR_EINTR EINTR
#endif /* _WIN32 */

enum
{
    HPR_SOCKET_STATUS_OK = 0,
    HPR_SOCKET_STATUS_ERROR = -1,
    HPR_SOCKET_STATUS_OVERTIME = -2,
    HPR_SOCKET_STATUS_REMOTE_CLOSED = -3,
};

HPR_DECLARE HPR_INT32 CALLBACK HPR_Recv_WithErr
(
    HPR_SOCK_T iSockFd, 
    HPR_INT8*  pBuf, 
    HPR_INT32  iBufCount, 
    HPR_UINT32*  pTimeOut
);

HPR_DECLARE HPR_INT32 CALLBACK HPR_Recvn_WithErr
(
    HPR_SOCK_T iSockFd, 
    HPR_VOIDPTR pBuf, 
    HPR_INT32 iBufCount, 
    HPR_UINT32 nTimeOut,
    HPR_INT32* p_iSocket_Status
);

HPR_DECLARE HPR_INT32 CALLBACK HPR_Bind_ToDevice
(
    HPR_SOCK_T iSockFd, 
    const char* pIfName
);

/**
 * Function: HPR_Send_WithErr
 * Description: send  with timeout, only use connected socket!!!
 * \param[in]  iSockFd  - socket fd;
 * \param[out]  pBuf  - buffer for restoring data!
 * \param[in]  iBufCount  - len of msg data!
 * \param[in]  nTimeOut  - must one of following : 
 *                            - NO_WAIT
 *                            - WAIT_FOREVER
 *                            - max wait time(ms) 
 * \return:  length of send if success,0 if overtime, else HPR_ERROR;
 * \note ...
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Send_WithErr
(
    HPR_SOCK_T iSockFd, 
    HPR_INT8*  pBuf, 
    HPR_INT32  iBufCount, 
    HPR_UINT32  nTimeOut
);

/**
 * Function: HPR_Sendn_WithErr
 * Description: send  with timeout, only use connected socket!!!
 * \param[in]  iSockFd  - socket fd;
 * \param[out]  pBuf  - buffer for restoring data!
 * \param[in]  iBufCount  - len of msg data!
 * \param[in]  nTimeOut  - must one of following : 
 *                            - NO_WAIT
 *                            - WAIT_FOREVER
 *                            - max wait time(ms) 
 * \return:  length of send if success,0 if overtime, else HPR_ERROR;
 * \note ...
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_Sendn_WithErr
(
    HPR_SOCK_T iSockFd, 
    HPR_INT8*  pBuf, 
    HPR_INT32  iBufCount, 
    HPR_UINT32  nTimeOut,
    HPR_INT32* p_iSocket_Status
);

HPR_DECLARE HPR_INT32 CALLBACK HPR_SetMultiCastLoopV6
(HPR_SOCK_T iSockFd, HPR_BOOL bYesNo);

HPR_DECLARE HPR_INT32 CALLBACK HPR_SetMultiCastLoopV4
(HPR_SOCK_T iSockFd, HPR_BOOL bYesNo);

HPR_DECLARE HPR_INT32 CALLBACK HPR_SetMultiCastLoopEx
(HPR_SOCK_T iSockFd, HPR_UINT16 iFamily,HPR_BOOL bYesNo);

HPR_DECLARE HPR_INT32 CALLBACK HPR_SetMultiCastHopsV6
(HPR_SOCK_T iSockFd, HPR_INT32 flag);

HPR_DECLARE HPR_INT32 CALLBACK HPR_SetTCP_KeepAlive
(HPR_SOCK_T iSockFd, HPR_BOOL bYesNo, HPR_UINT32 maxTime);


#endif
