/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HPR_Config.h
 * Desc:        OS Layer Component.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

/*! \file HPR_Config.h
 */

#ifndef __OS_CONFIG_H__
#define __OS_CONFIG_H__

#define  HPR_OS_NOT_SUPPORT "OS Not Implement Yet."

//////////////////////////////////////////////////////////////////////////
//支持c++编译
#if defined (__cplusplus)
#define CXXCOMPILE 1
#endif
//////////////////////////////////////////////////////////////////////////

#if (defined(_WIN32) || defined(_WIN32_WCE) || defined(WIN64))
    #pragma warning(disable: 4819) //unicode字符警告

    //MSVC Version (vs98/vs2003/vs2005/vs2008/vs2010)
    #if (_MSC_VER >= 1600)      //vs2010
        #pragma warning(disable: 4996)
        #define MSVC_2010
    #elif (_MSC_VER >= 1500)    //vs2008
        #pragma warning(disable: 4996)
        #define MSVC_2008
    #elif (_MSC_VER >= 1400)    //vs2005
        #define MSVC_2005
    #elif (_MSC_VER >= 1310)    //vs2003
        #define _WIN32_WINNT 0x0500
        #define MSVC_2003       
    #else                       //vs98
        #define _WIN32_WINNT 0x0500
        #pragma warning(disable: 4786)
        #define MSVC_98
    #endif

    #if defined(_WIN32_WCE)
        #define OS_WINCE  1
    #endif
    #if defined(WIN64)
        #define OS_WINDOWS64    1
    #endif

    #pragma warning(disable:4100)
    #pragma warning(disable:4127)

    #ifndef CALLBACK
    #define CALLBACK __stdcall
    #endif

    #include <winsock2.h>   
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <Mswsock.h>
    
    #define OS_WINDOWS  1
    #define HPR_EXPORTS 1
    #define HPR_INFINITE INFINITE

    /* edited by  fenggx begin!*/
    #if defined(HPR_EXPORTS)
        #ifdef __cplusplus
            #define HPR_DECLARE extern "C" __declspec(dllexport)
        #else
            #define HPR_DECLARE __declspec(dllexport)
        #endif
        #define HPR_DECLARE_CLASS __declspec(dllexport)
        #define HPR_DECLARE_CXX __declspec(dllexport)
    #else
        #ifdef __cplusplus
            #define HPR_DECLARE extern "C" __declspec(dllimport)
        #else
            #define HPR_DECLARE __declspec(dllimport)
        #endif
        
        #define HPR_DECLARE_CLASS __declspec(dllimport)
        #define HPR_DECLARE_CXX __declspec(dllimport)
    #endif
    /* edited by  fenggx end!*/

#elif (defined(__linux__) || defined(__APPLE__) || defined(__SYMBIAN32__) || defined(ANDROID))
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdarg.h>
    #include <unistd.h> 
    #include <sys/socket.h>
    #include <sys/ioctl.h>
    #include <sys/time.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/types.h>
    #include <netdb.h>
    #include <errno.h>
    #include <string.h>
    #include <net/if.h>
    #include <assert.h>
    #include <time.h>
    
    #if (defined(__SYMBIAN32__) || defined(ANDROID))
        #include <sys/stat.h>
    #else
        //#include <uuid/uuid.h>
    #endif

    #define OS_POSIX    1
    #define HPR_INFINITE 0xFFFFFFFF
    #define WAIT_TIMEOUT    258

    #if defined(__LP64__)
        #define OS_POSIX64  1
    #endif

    #if defined (__APPLE__)
        #include<TargetConditionals.h>
        #include <sys/stat.h>
        #include <sys/sockio.h>

        #define OS_APPLE    1

        #if defined(TARGET_OS_IPHONE)
            #define OS_IPHONE   1
        #elif defined(TARGET_OS_MAC)
            #define OS_MAC   1
        #endif
    #endif

    #if defined(__SYMBIAN32__)
        #define OS_S60      1
    #endif

    #if defined(ANDROID)
        #define OS_ANDROID      1
    #endif
        
    /* edited by  fenggx begin!*/
    #ifdef __cplusplus
        #define HPR_DECLARE extern "C"
    #else
        #define HPR_DECLARE
    #endif
    /* edited by  fenggx end!*/

    
    #define HPR_DECLARE_CLASS 
    #define HPR_DECLARE_CXX

    #ifndef CALLBACK
        #define CALLBACK
    #else
        #undef CALLBACK
        #define CALLBACK
    #endif
#else
    #error OS Not Implement Yet.
#endif  // end #if (defined(WIN32) || defined(_WIN32_WCE))

#define HPR_OK          0
#define HPR_ERROR       -1
#define HPR_NOSUPPORT   1 /* NO support == OK */

#define OS_SUPPORT_IPV6 1

// added by fenggx begin!
#include "HPR_Types.h"
// added by fenggx end!

// edited by fenggx begin!
#if defined (OS_WINDOWS)

#elif defined(OS_POSIX)
    #include <sys/stat.h>
    #include <mqueue.h>
#else
    #error OS Not Implement Yet.
#endif
// edited by fenggx end!

#ifdef MEMWATCH
#include "../../memwatch.h"
#endif

#ifdef DMALLOC
#include "../../dmalloc.h"
#endif

#endif  // end #ifndef __OS_CONFIG_H__
