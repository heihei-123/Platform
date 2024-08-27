/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HRP_Utils.h
 * Desc:        OS Layer Component.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

/*! 
    \file HPR_Utils.h
    \brief HPR Utils Manager.

    Details.
*/

#ifndef __HPR_UTILS_H__
#define __HPR_UTILS_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

#if defined LLONG_MAX
    #define HPR_INT64_MAX (LLONG_MAX) //(HPR_INT64)(0x7fffffffffffffff)
    #define HPR_INT64_MIN (LLONG_MIN) //((HPR_INT64)0x7fffffffffffffff) - (HPR_INT64)1)
#else
    #define HPR_INT64_MAX (HPR_INT64)(0x7fffffffffffffff)
    #define HPR_INT64_MIN ((HPR_INT64)(0x7fffffffffffffff) - (HPR_INT64)1)
#endif
#define HPR_INT32_MAX (INT_MAX)
#define HPR_INT32_MIN (INT_MIN)

#if defined(OS_WINDOWS)
    #define HPR_Vsnprintf _vsnprintf
    //#define HPR_Snprintf _snprintf
#elif defined(OS_POSIX)
    #define HPR_Vsnprintf vsnprintf
    //#define HPR_Snprintf snprintf
#else
    #error OS Not Implement Yet.
#endif

#if defined (HPR_SUPPORT_NOTHROW)
#define HPR_NEW_RETURN(POINTER,CONSTRUCTURE) \
    do { POINTER = new (::std::nothrow) CONSTRUCTURE;\
    if (POINTER == 0) {return NULL;}\
    return POINTER;\
    }while(0)
#else
#define HPR_NEW_RETURN(POINTER,CONSTRUCTURE) \
    do {    try {POINTER = new CONSTRUCTURE;\
            return POINTER;}\
    catch (::std::bad_alloc & a){POINTER=0,return NULL}\
        }while(0)
#endif


#define HPR_SAFE_FREE(p) do{if(p){free(p);(p=NULL);}}while(0);
#define HPR_SAFE_DELETE(p) do{if(p){(delete (p));p=NULL;}}while(0);
#define HPR_SAFE_DELETE_ARR(p) do{if(p){(delete []p);(p=NULL);}}while(0);
#define HPR_POINTER_REF(p,b) do{if(p){*(p) = (b);}}while(0);
#define HPR_SAFE_CLOSE(p) do{if(-1!=(p)){close(p);((p)=-1);}}while(0);

#define HPR_MAX_VALUE(a,b) (((a)>(b))?(a):(b))
#define HPR_MIN_VALUE(a,b) (((a)>(b))?(b):(a))

#define HPR_SAFE_BZERO(src, len) do {\
    /*it is not safe when len = n* sizeof(dst)*/\
    if ((src) && ((len) > 0) && (0 == (len) % ((char *)((src) + 1) - (char *)(src))))\
        {memset((char*)(src), 0, (len));}\
    else{printf("src=%p,len=0x%llx,bzero faild!\n", (src), (UINT64)(len));}}while(0);
    
/**
 * HPR_Debug format and print data in debug mode.
 * @param format (IN) string format.
 * @return void
 * @sa HPR_OutputDebug
 */
HPR_DECLARE HPR_VOID  CALLBACK HPR_Debug(const char* format, ...);

/**
 * HPR_OutputDebug format and print data in debug/release mode.
 * @param format (IN) string format.
 * @return void
 * @sa HPR_Debug
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_OutputDebug(const char* format, ...);

/**
 * HPR_OutputDebugString output string directly in debug/release mode.
 * @param format (IN) string pointer.
 * @return void
 * @sa HPR_OutputDebug
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_OutputDebugString(const char* lpOutputString);

/**
 * HPR_USleep suspend execute for millisecond intervals
 * @param millisecond (IN) count of millisecond interval
 * @return void
 * @sa HPR_USleep
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_Sleep(HPR_INT32 millisecond);

/**
 * HPR_USleep suspend execute for microsecond intervals
 * @param nUSec (IN) count of microsecond interval
 * @return void
 * @sa HPR_Sleep
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_USleep(HPR_INT64 nUSec);

/**
 * Function: HPR_Rand
 * Desc:    获取随机数,随机数种子由内部HPR_GetTimeTick()获取
 * Input:   
 * Output:
 * Return:  随机数
 */
HPR_DECLARE HPR_UINT32 CALLBACK HPR_Rand();

/**
 * Function: HPR_ZeroMemory
 * Desc:    把内存清零调用 memset(mem, 0, len);
 * Input:   @param mem : 内存首指针
            @param len : 内存长度
 * Output:
 * Return:  
 */
HPR_DECLARE HPR_VOID CALLBACK HPR_ZeroMemory(void* mem, int len);

/**
 * Function: HPR_GetCPUNumber
 * Desc:    获取CPU个数
 * Input:   
 * Output:
 * Return:  
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetCPUNumber();

typedef unsigned char HPR_UUID[16];
HPR_DECLARE HPR_INT32 CALLBACK HPR_GetUUID(HPR_UUID uuid);
HPR_DECLARE HPR_INT32 CALLBACK HPR_StringFromUUID(HPR_UUID uuid, char* uuidString, HPR_INT32 len);
HPR_DECLARE HPR_INT32 CALLBACK HPR_Snprintf
(char *str, size_t size, const char *format, ...);

#endif
