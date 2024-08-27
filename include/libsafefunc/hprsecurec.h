/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2014-2021. All rights reserved.
 * Licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan PSL v2.
 * You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v2 for more details.
 * Description: The user of this secure c library should include this header file in you source code.
 *              This header file declare all supported API prototype of the library,
 *              such as HPR_Memcpy_s, HPR_Strcpy_s, HPR_Wcscpy_s,HPR_Strcat_s, HPR_Strncat_s, HPR_Sprintf_s, HPR_Scanf_s, and so on.
 * Create: 2014-02-25
 * Notes: Do not modify this file by yourself.
 */

#ifndef __HPR_SECUREC_H__
#define __HPR_SECUREC_H__

#include "hprsecurectype.h"
#ifndef SECUREC_HAVE_STDARG_H
#define SECUREC_HAVE_STDARG_H 1
#endif

#if SECUREC_HAVE_STDARG_H
#include <stdarg.h>
#endif

#ifndef SECUREC_HAVE_ERRNO_H
#define SECUREC_HAVE_ERRNO_H 1
#endif

/* EINVAL ERANGE may defined in errno.h */
#if SECUREC_HAVE_ERRNO_H
#if SECUREC_IN_KERNEL
#include <linux/errno.h>
#else
#include <errno.h>
#endif
#endif

typedef void (*errorhandle)(const char *file, const int line, const char *function, const char *safefunc, int err);

/* Define error code */
#if defined(SECUREC_NEED_ERRNO_TYPE) || !defined(__STDC_WANT_LIB_EXT1__) || \
    (defined(__STDC_WANT_LIB_EXT1__) && (!__STDC_WANT_LIB_EXT1__))
#ifndef SECUREC_DEFINED_ERRNO_TYPE
#define SECUREC_DEFINED_ERRNO_TYPE
/* Just check whether macrodefinition exists. */
#ifndef errno_t
typedef int errno_t;
#endif
#endif
#endif

/* Success */
#ifndef EOK
#define EOK 0
#endif

#ifndef EINVAL
/* The src buffer is not correct and destination buffer can not be reset */
#define EINVAL 22
#endif

#ifndef EINVAL_AND_RESET
/* Once the error is detected, the dest buffer must be reset! Value is 22 or 128 */
#define EINVAL_AND_RESET 150
#endif

#ifndef ERANGE
/* The destination buffer is not long enough and destination buffer can not be reset */
#define ERANGE 34
#endif

#ifndef ERANGE_AND_RESET
/* Once the error is detected, the dest buffer must be reset! Value is 34 or 128 */
#define ERANGE_AND_RESET  162
#endif

#ifndef EOVERLAP_AND_RESET
/* Once the buffer overlap is detected, the dest buffer must be reset! Value is 54 or 128 */
#define EOVERLAP_AND_RESET 182
#endif

/* If you need export the function of this library in Win32 dll, use __declspec(dllexport) */
#ifndef SECUREC_API
#if defined(SECUREC_DLL_EXPORT)
#define SECUREC_API __declspec(dllexport)
#elif defined(SECUREC_DLL_IMPORT)
#define SECUREC_API __declspec(dllimport)
#else
/*
 * Standardized function declaration. If a security function is declared in the your code,
 * it may cause a compilation alarm,Please delete the security function you declared.
 * Adding extern under windows will cause the system to have inline functions to expand,
 * so do not add the extern in default
 */
#if defined(_MSC_VER)
#define SECUREC_API
#else
#define SECUREC_API extern
#endif
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if 0 /*not support to get the hw lib version, change by wangjunwei6 2022-08-08*/
/*
 * Description: The GetHwSecureCVersion function get SecureC Version string and version number.
 * Parameter: verNumber - to store version number (for example value is 0x500 | 0xa)
 * Return:   version string
 */
SECUREC_API const char *GetHwSecureCVersion(unsigned short *verNumber);
#endif

#if SECUREC_ENABLE_MEMSET
/*
 * Description: The HPR_Memset_s function copies the value of c (converted to an unsigned char) into each of
 * the first count characters of the object pointed to by dest.
 * Parameter: dest - destination address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: c - the value to be copied
 * Parameter: count - copies count bytes of value to dest
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Memset_s(void *dest, size_t destMax, int c, size_t count);
#endif

#ifndef SECUREC_ONLY_DECLARE_MEMSET
#define SECUREC_ONLY_DECLARE_MEMSET     0
#endif

#if !SECUREC_ONLY_DECLARE_MEMSET

#if SECUREC_ENABLE_MEMMOVE
/*
 * Description: The HPR_Memmove_s function copies n characters from the object pointed to by src
 * into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Memmove_s(void *dest, size_t destMax, const void *src, size_t count);
#endif

#if SECUREC_ENABLE_MEMCPY
/*
 * Description: The HPR_Memcpy_s function copies n characters from the object pointed to
 * by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Memcpy_s(void *dest, size_t destMax, const void *src, size_t count);
#endif

#if SECUREC_ENABLE_STRCPY
/*
 * Description: The HPR_Strcpy_s function copies the string pointed to by strSrc (including
 * the terminating null character) into the array pointed to by strDest
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Strcpy_s(char *strDest, size_t destMax, const char *strSrc);
#endif

#if SECUREC_ENABLE_STRNCPY
/*
 * Description: The HPR_Strncpy_s function copies not more than n successive characters (not including
 * the terminating null character) from the array pointed to by strSrc to the array pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source  address
 * Parameter: count - copies count characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Strncpy_s(char *strDest, size_t destMax, const char *strSrc, size_t count);
#endif

#if SECUREC_ENABLE_STRCAT
/*
 * Description: The HPR_Strcat_s function appends a copy of the string pointed to by strSrc (including
 * the terminating null character) to the end of the string pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null wide character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Strcat_s(char *strDest, size_t destMax, const char *strSrc);
#endif

#if SECUREC_ENABLE_STRNCAT
/*
 * Description: The HPR_Strncat_s function appends not more than n successive characters (not including
 * the terminating null character)
 * from the array pointed to by strSrc to the end of the string pointed to by strDest.
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source address
 * Parameter: count - copies count characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
SECUREC_API errno_t HPR_Strncat_s(char *strDest, size_t destMax, const char *strSrc, size_t count);
#endif

#if SECUREC_ENABLE_VSPRINTF
/*
 * Description: The HPR_Vsprintf_s function is equivalent to the vsprintf function except for the parameter destMax
 * and the explicit runtime-constraints violation
 * Parameter: strDest -  produce output according to a format,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null wide character)
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.
 */
SECUREC_API int HPR_Vsprintf_s(char *strDest, size_t destMax, const char *format,
                           va_list argList) SECUREC_ATTRIBUTE(3, 0);
#endif

#if SECUREC_ENABLE_SPRINTF
/*
 * Description: The HPR_Sprintf_s function is equivalent to the sprintf function except for the parameter destMax
 * and the explicit runtime-constraints violation
 * Parameter: strDest -  produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.
*/
SECUREC_API int HPR_Sprintf_s(char *strDest, size_t destMax, const char *format, ...) SECUREC_ATTRIBUTE(3, 4);
#endif

#if SECUREC_ENABLE_VSNPRINTF
/*
 * Description: The HPR_Vsnprintf_s function is equivalent to the vsnprintf function except for
 * the parameter destMax/count and the explicit runtime-constraints violation
 * Parameter: strDest -  produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null  byte '\0')
 * Parameter: count - do not write more than count bytes to strDest(not including the terminating null  byte '\0')
 * Parameter: format - format string
 * Parameter: argList - instead of  a variable number of arguments
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning -1 when truncation occurs.
 */
SECUREC_API int HPR_Vsnprintf_s(char *strDest, size_t destMax, size_t count, const char *format,
                            va_list argList) SECUREC_ATTRIBUTE(4, 0);
#endif

#if SECUREC_ENABLE_SNPRINTF
/*
 * Description: The HPR_Snprintf_s function is equivalent to the snprintf function except for
 * the parameter destMax/count and the explicit runtime-constraints violation
 * Parameter: strDest - produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null  byte '\0')
 * Parameter: count - do not write more than count bytes to strDest(not including the terminating null  byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning -1 when truncation occurs.
 */
SECUREC_API int HPR_Snprintf_s(char *strDest, size_t destMax, size_t count, const char *format,
                           ...) SECUREC_ATTRIBUTE(4, 5);
#endif

#if SAFEFUNC_SNPRINTF_TRUNCATED
/*
 * Description: The vsnprintf_truncated_s function is equivalent to the vsnprintf_s function except
 * no count parameter and return value
 * Parameter: strDest -  produce output according to a format ,write to the character string strDest
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null  byte '\0')
 * Parameter: format - format string
 * Parameter: argList - instead of  a variable  number of arguments
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning destMax - 1 when truncation occurs
*/
SECUREC_API int vsnprintf_truncated_s(char *strDest, size_t destMax, const char *format,
                                      va_list argList) SECUREC_ATTRIBUTE(3, 0);

/*
 * Description: The snprintf_truncated_s function is equivalent to the snprintf_s function except
 * no count parameter and return value
 * Parameter: strDest - produce output according to a format,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.Pay special attention to returning destMax - 1 when truncation occurs.
 */
SECUREC_API int snprintf_truncated_s(char *strDest, size_t destMax,
                                     const char *format, ...) SECUREC_ATTRIBUTE(3, 4);
#endif

/*for easy check the args*/
SECUREC_API int checkArgs(const char* format, int args_count);

#if SECUREC_ENABLE_SCANF
/*
 * Description: The HPR_Scanf_s function is equivalent to fscanf_s with the argument stdin
 * interposed before the arguments to HPR_Scanf_s
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Scanf_s(const char *format, ...);
#endif

#if SECUREC_ENABLE_VSCANF
/*
 * Description: The HPR_Vscanf_s function is equivalent to HPR_Scanf_s, with the variable argument list replaced by argList
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Vscanf_s(const char *format, va_list argList);
#endif

#if SECUREC_ENABLE_SSCANF
/*
 * Description: The HPR_Sscanf_s function is equivalent to fscanf_s, except that input is obtained from a
 * string (specified by the argument buffer) rather than from a stream
 * Parameter: buffer - read character from buffer
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Sscanf_s(const char *buffer, const char *format, ...);
#endif

#if SECUREC_ENABLE_VSSCANF
/*
 * Description: The HPR_Vsscanf_s function is equivalent to sscanf_s, with the variable argument list
 * replaced by argList
 * Parameter: buffer -  read character from buffer
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Vsscanf_s(const char *buffer, const char *format, va_list argList);
#endif

#if SECUREC_ENABLE_FSCANF
/*
 * Description: The HPR_Fscanf_s function is equivalent to fscanf except that the c, s, and [ conversion specifiers
 * apply to a pair of arguments (unless assignment suppression is indicated by a *)
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Fscanf_s(FILE *stream, const char *format, ...);
#endif

#if SECUREC_ENABLE_VFSCANF
/*
 * Description: The HPR_Vfscanf_s function is equivalent to fscanf_s, with the variable argument list
 * replaced by argList
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
SECUREC_API int HPR_Vfscanf_s(FILE *stream, const char *format, va_list argList);
#endif

#if SECUREC_ENABLE_STRTOK
/*
 * Description: The HPR_Strtok_s function parses a string into a sequence of strToken,
 * replace all characters in strToken string that match to strDelimit set with 0.
 * On the first call to strtok_s the string to be parsed should be specified in strToken.
 * In each subsequent call that should parse the same string, strToken should be NULL
 * Parameter: strToken - the string to be delimited
 * Parameter: strDelimit - specifies a set of characters that delimit the tokens in the parsed string
 * Parameter: context - is a pointer to a char * variable that is used internally by strtok_s function
 * Return:  On the first call returns the address of the first non \0 character, otherwise NULL is returned.
 * In subsequent calls, the strtoken is set to NULL, and the context set is the same as the previous call,
 * return NULL if the *context string length is equal 0, otherwise return *context.
 */
SECUREC_API char *HPR_Strtok_s(char *strToken, const char *strDelimit, char **context);
#endif

#if SECUREC_ENABLE_GETS && !SECUREC_IN_KERNEL
/*
 * Description: The HPR_Gets_s function reads at most one less than the number of characters specified
 * by destMax from the stream pointed to by stdin, into the array pointed to by buffer
 * Parameter: buffer - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Return:    buffer if there was no runtime-constraint violation,If an error occurred Return: NULL.
 */
SECUREC_API char *HPR_Gets_s(char *buffer, size_t destMax);
#endif

#endif


/* Those functions are used by macro,must declare hare, also for without function declaration warning */
extern errno_t __strncpy_error(char *strDest, size_t destMax, const char *strSrc, size_t count);
extern errno_t __strcpy_error(char *strDest, size_t destMax, const char *strSrc);

#if SAFEFUNC_WITH_PERFORMANCE_ADDONS
/* Those functions are used by macro */
extern errno_t memset_sOptAsm(void *dest, size_t destMax, int c, size_t count);
extern errno_t memset_sOptTc(void *dest, size_t destMax, int c, size_t count);
extern errno_t memcpy_sOptAsm(void *dest, size_t destMax, const void *src, size_t count);
extern errno_t memcpy_sOptTc(void *dest, size_t destMax, const void *src, size_t count);

/* The strcpy_sp is a macro, not a function in performance optimization mode. */
#define strcpy_sp(dest, destMax, src)  ((__builtin_constant_p((destMax)) && \
    __builtin_constant_p((src))) ?  \
    SECUREC_STRCPY_SM((dest), (destMax), (src)) : \
    HPR_Strcpy_s((dest), (destMax), (src)))

/* The strncpy_sp is a macro, not a function in performance optimization mode. */
#define strncpy_sp(dest, destMax, src, count)  ((__builtin_constant_p((count)) && \
    __builtin_constant_p((destMax)) && \
    __builtin_constant_p((src))) ?  \
    SECUREC_STRNCPY_SM((dest), (destMax), (src), (count)) : \
    HPR_Strncpy_s((dest), (destMax), (src), (count)))

/* The strcat_sp is a macro, not a function in performance optimization mode. */
#define strcat_sp(dest, destMax, src) ((__builtin_constant_p((destMax)) && \
    __builtin_constant_p((src))) ?  \
    SECUREC_STRCAT_SM((dest), (destMax), (src)) : \
    HPR_Strcat_s((dest), (destMax), (src)))

/* The strncat_sp is a macro, not a function in performance optimization mode. */
#define strncat_sp(dest, destMax, src, count) ((__builtin_constant_p((count)) &&  \
    __builtin_constant_p((destMax)) && \
    __builtin_constant_p((src))) ?  \
    SECUREC_STRNCAT_SM((dest), (destMax), (src), (count)) : \
    HPR_Strncat_s((dest), (destMax), (src), (count)))

/* The memcpy_sp is a macro, not a function in performance optimization mode. */
#define memcpy_sp(dest, destMax, src, count)  (__builtin_constant_p((count)) ? \
    (SECUREC_MEMCPY_SM((dest), (destMax), (src), (count))) : \
    (__builtin_constant_p((destMax)) ? \
    (((size_t)(destMax) > 0 && \
    (((unsigned long long)(destMax) & (unsigned long long)(-2)) < SECUREC_MEM_MAX_LEN)) ? \
    memcpy_sOptTc((dest), (destMax), (src), (count)) : ERANGE) : \
    memcpy_sOptAsm((dest), (destMax), (src), (count))))

/* The memset_sp is a macro, not a function in performance optimization mode. */
#define memset_sp(dest, destMax, c, count)  (__builtin_constant_p((count)) ? \
    (SECUREC_MEMSET_SM((dest), (destMax), (c), (count))) : \
    (__builtin_constant_p((destMax)) ? \
    (((((unsigned long long)(destMax) & (unsigned long long)(-2)) < SECUREC_MEM_MAX_LEN)) ? \
    memset_sOptTc((dest), (destMax), (c), (count)) : ERANGE) : \
    memset_sOptAsm((dest), (destMax), (c), (count))))

#endif


#ifdef __cplusplus
}
#endif
#endif

