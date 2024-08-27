/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HPR_Types.h
 * Desc:        define CC Types files.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

#include "HPR_Inttypes.h"

#ifndef __HPR_TYPES_H__
#define __HPR_TYPES_H__

    typedef /*signed*/ char     HPR_INT8;
    typedef unsigned char   HPR_UINT8;
    typedef /*signed*/ short    HPR_INT16;
    typedef unsigned short  HPR_UINT16;
    typedef /*signed*/ int      HPR_INT32;
    typedef unsigned int    HPR_UINT32;
    typedef void*           HPR_VOIDPTR;
    typedef /*signed*/ long     HPR_LONG;
    typedef unsigned long   HPR_ULONG;

    #define HPR_VOID void

#if defined(_MSC_VER)
    typedef /*signed*/ __int64  HPR_INT64;
    typedef unsigned __int64 HPR_UINT64;
    typedef HANDLE          HPR_HANDLE;

#if (_MSC_VER >= 1310)
    #if defined _WIN32_WCE
        #include <crtdefs.h>
    #else
        #include <stddef.h>
    #endif
    typedef uintptr_t       HPR_UINT;
    typedef intptr_t        HPR_INT;
#endif

    #ifndef socklen_t
        typedef int socklen_t;
    #endif

    typedef int (CALLBACK *HPR_PROC)();

#elif defined(__GNUC__) || defined(__SYMBIAN32__)
    #if defined(__LP64__)
        typedef /*signed*/ long HPR_INT64;
        typedef unsigned long HPR_UINT64;
    #else
        typedef /*signed*/ long long HPR_INT64;
        typedef unsigned long long HPR_UINT64;
    #endif  //defined(__LP64__)
    typedef void*           HPR_HANDLE;

    #include <ctype.h>
    /*typedef uintptr_t HPR_UINT;
    typedef intptr_t HPR_INT;*/

    typedef void*   HPR_PROC;
#endif      //#if defined(_MSC_VER)

#define HPR_SUPPORT_INT64 1

#define HPR_OK      0
#define HPR_ERROR   -1

#ifndef  HPR_BOOL
    #define HPR_BOOL HPR_INT32
    #define HPR_TRUE  1
    #define HPR_FALSE 0
#endif
#ifdef MEGAEYES_DSP_VER
    #define HPR_STATUS HPR_INT32
#endif

#define HPR_INVALID_HANDLE NULL

/*bit Operatoren */
#define   HPR_BIT_OR    |
#define   HPR_BIT_AND   &

#define   HPR_SET_BIT32(iData,iShift)  ((iData)|=((HPR_UINT32)1 << (iShift)))
#define   HPR_CLN_BIT32(iData,iShift)  ((iData)&=(~((HPR_UINT32)1 << (iShift))))
#define   HPR_CHK_BIT32(iData,iShift)  ((((iData) >> (iShift)) & (HPR_UINT32)1))

#define   HPR_SET_BIT64(iData,iShift)  ((iData)|=((HPR_UINT64)1 << (iShift)))
#define   HPR_CLN_BIT64(iData,iShift)  ((iData)&=(~((HPR_UINT64)1 << (iShift))))
#define   HPR_CHK_BIT64(iData,iShift)  ((((iData) >> (iShift)) & (HPR_UINT64)1))

/*logical Operators*/
#define   HPR_OR     ||
#define   HPR_AND    &&
#define   HPR_EQ(iDataFst,iDataSed)      ((iDataFst)==(iDataSed))
#define   HPR_NOT_EQ(iDataFst,iDataSed)  ((iDataFst)!=(iDataSed))

/*shift Operators*/
#define   HPR_SH_LEFT(iData,iShift)         ((iData)=(iData)<<(iShift))
#define   HPR_SH_RIGHT(iData,iShift)        ((iData)=(iData)>>(iShift))   

/*compare Operators*/
#define   HPR_MORE_THAN(iDataFst,iDataSed)          ((iDataFst)>(iDataSed))
#define   HPR_MORE_THAN_EQ(iDataFst,iDataSed)       ((iDataFst)>=(iDataSed))
#define   HPR_LESS_THAN(iDataFst,iDataSed)          ((iDataFst)<(iDataSed))
#define   HPR_LESS_THAN_EQ(iDataFst,iDataSed)       ((iDataFst)<=(iDataSed))

#define HPR_CON_OP(Condition, ResultY, ResultN) ((Condition)?(ResultY):(ResultN))

#define MAX_DATA_UINT8       0xff                     /*8位的最大数*/
#define MAX_DATA_UINT16      0xffff                   /*16位的最大数*/
#define MAX_DATA_UINT32      0xffffffff               /*32位的最大数*/
#define MAX_DATA_UINT64      0xffffffffffffffff       /*64位的最大数*/

#endif      //#ifndef __HPR_TYPES_H__
