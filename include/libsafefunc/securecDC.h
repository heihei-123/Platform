/********************************************************************************

 **** Copyright (C), 2022, Hikvision Co., Ltd. ****

 ********************************************************************************
 * File Name     : securecDC.h
 * Date            : 2022-09-1
 * Description   : 1、安全函数封装，支持异常打印
                        2、通用头文件整合
 * Version        : 1.0
 * Function List :
 *
 * Record          :
 * 1.Date          : 2022-09-1
 *   Author        : wangshida
 *   Modification : Created file

*************************************************************************************************************/


#ifndef _SECUREC_DC_H_
#define _SECUREC_DC_H_

#include "hprsecurec.h"
#include "hlog/log.h"

/*通用头文件，按需添加*/
#include <vector>
#include <string>
#include <mutex>
#include <atomic>
#include <map>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#if (defined _WIN32 || defined _WIN64)
#define SECUREC_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "SecurecErr", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#else
#define SECUREC_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "SecurecErr", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#endif

/*
 * Description: The HPR_Memset_s function copies the value of c (converted to an unsigned char) into each of
 * the first count characters of the object pointed to by dest.
 * Parameter: dest - destination address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: c - the value to be copied
 * Parameter: count - copies count bytes of value to dest
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_MEMSET_S(dest, destMax, c, count) ({ \
	int errno_t = HPR_Memset_s(dest, destMax, c, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Memset_s error[%d] dest[%p] destMax[%zu] c[%d] count[%zu]", errno_t, dest, (size_t)destMax, c, (size_t)count); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Memmove_s function copies n characters from the object pointed to by src
 * into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_MEMMOVE_S(dest, destMax, src, count) ({ \
	int errno_t = HPR_Memmove_s(dest, destMax, src, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Memmove_s error[%d] dest[%p] destMax[%zu] src[%p] count[%zu]", errno_t, dest, (size_t)(destMax), src, (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Memcpy_s function copies n characters from the object pointed to
 * by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count bytes from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_MEMCPY_S(dest, destMax, src, count) ({ \
	int errno_t = HPR_Memcpy_s(dest, destMax, src, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Memcpy_s error[%d] dest[%p] destMax[%zu] src[%p] count[%zu]", errno_t, dest, (size_t)(destMax), src, (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Strcpy_s function copies the string pointed to by strSrc (including
 * the terminating null character) into the array pointed to by strDest
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_STRCPY_S(strDest, destMax, strSrc) ({ \
	int errno_t = HPR_Strcpy_s(strDest, destMax, strSrc); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Strcpy_s error[%d] strDest[%s] destMax[%zu] strSrc[%s]", errno_t, strDest, (size_t)(destMax), strSrc); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Strncpy_s function copies not more than n successive characters (not including
 * the terminating null character) from the array pointed to by strSrc to the array pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Parameter: strSrc - source  address
 * Parameter: count - copies count characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_STRNCPY_S(strDest, destMax, strSrc, count) ({ \
	int errno_t = HPR_Strncpy_s(strDest, destMax, strSrc, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Strncpy_s error[%d] strDest[%s] destMax[%zu] strSrc[%s] count[%zu]", errno_t, strDest, (size_t)(destMax), strSrc, (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Strcat_s function appends a copy of the string pointed to by strSrc (including
 * the terminating null character) to the end of the string pointed to by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null wide character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_STRCAT_S(strDest, destMax, strSrc) ({ \
	int errno_t = HPR_Strcat_s(strDest, destMax, strSrc); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Strcat_s error[%d] strDest[%s] destMax[%zu] strSrc[%s]", errno_t, strDest, (size_t)(destMax), strSrc); \
	} \
	errno_t; \
})

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
#define HPR_STRNCAT_S(strDest, destMax, strSrc, count) ({ \
	int errno_t = HPR_Strncat_s(strDest, destMax, strSrc, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Strncat_s error[%d] strDest[%s] destMax[%zu] strSrc[%s] count[%zu]", errno_t, strDest, (size_t)(destMax), strSrc, (size_t)(count)); \
	} \
	errno_t; \
})

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
#define HPR_VSPRINTF_S(strDest, destMax, format, ...) HPR_Vsprintf_s(strDest, destMax, format, __VA_ARGS__)

/*
 * Description: The HPR_Sprintf_s function is equivalent to the sprintf function except for the parameter destMax
 * and the explicit runtime-constraints violation
 * Parameter: strDest -  produce output according to a format ,write to the character string strDest.
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null byte '\0')
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null byte '\0'),
 * If an error occurred Return: -1.
*/
#define HPR_SPRINTF_S(strDest, destMax, format, ...) HPR_Sprintf_s(strDest, destMax, format, __VA_ARGS__)

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
#define HPR_VSNPRINTF_S(strDest, destMax, count, format, ...) HPR_Vsnprintf_s(strDest, destMax, count, format, __VA_ARGS__)

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
#define HPR_SNPRINTF_S(strDest, destMax, count, format, ...) HPR_Snprintf_s(strDest, destMax, count, format, __VA_ARGS__)

/*
 * Description: The HPR_Scanf_s function is equivalent to fscanf_s with the argument stdin
 * interposed before the arguments to HPR_Scanf_s
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_SCANF_S(format, ...) HPR_Scanf_s(format, __VA_ARGS__)

/*
 * Description: The HPR_Vscanf_s function is equivalent to HPR_Scanf_s, with the variable argument list replaced by argList
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VSCANF_S(format, ...) HPR_Vscanf_s(format, __VA_ARGS__)

/*
 * Description: The HPR_Sscanf_s function is equivalent to fscanf_s, except that input is obtained from a
 * string (specified by the argument buffer) rather than from a stream
 * Parameter: buffer - read character from buffer
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_SSCANF_S(buffer, format, ...) HPR_Sscanf_s(buffer, format, __VA_ARGS__)

/*
 * Description: The HPR_Vsscanf_s function is equivalent to sscanf_s, with the variable argument list
 * replaced by argList
 * Parameter: buffer -  read character from buffer
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VSSCANF_S(buffer, format, ...) HPR_Vsscanf_s(buffer, format, __VA_ARGS__)

/*
 * Description: The HPR_Fscanf_s function is equivalent to fscanf except that the c, s, and [ conversion specifiers
 * apply to a pair of arguments (unless assignment suppression is indicated by a *)
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_FSCANF_S(stream, format, ...) HPR_Fscanf_s(stream, format, __VA_ARGS__)

/*
 * Description: The HPR_Vfscanf_s function is equivalent to fscanf_s, with the variable argument list
 * replaced by argList
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VFSCANF_S(stream, format, ...) HPR_Vfscanf_s(stream, format, __VA_ARGS__)

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
#define HPR_STRTOK_S(strToken, strDelimit, context) HPR_Strtok_s(strToken, strDelimit, context)

/*
 * Description: The HPR_Gets_s function reads at most one less than the number of characters specified
 * by destMax from the stream pointed to by stdin, into the array pointed to by buffer
 * Parameter: buffer - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null character)
 * Return:    buffer if there was no runtime-constraint violation,If an error occurred Return: NULL.
 */
#define HPR_GETS_S(buffer, destMax) HPR_Gets_s(buffer, destMax)

/*
 * Description: The HPR_Wmemcpy_s function copies n successive wide characters from the object pointed to
 * by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WMEMCPY_S(dest, destMax, src, count) ({ \
	int errno_t = HPR_Wmemcpy_s(dest, destMax, src, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wmemcpy_s error[%d] destMax[%zu] count[%zu]", errno_t, (size_t)(destMax), (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wmemmove_s function copies n successive wide characters from the object
 * pointed to by src into the object pointed to by dest.
 * Parameter: dest - destination  address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: src - source address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WMEMMOVE_S(dest, destMax, src, count) ({ \
	int errno_t = HPR_Wmemmove_s(dest, destMax, src, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wmemmove_s error[%d] destMax[%zu] count[%zu]", errno_t, (size_t)(destMax), (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wcscpy_s function copies the wide string pointed to by strSrc(including the terminating
 * null wide character) into the array pointed to by strDest
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WCSCPY_S(strDest, destMax, strSrc) ({ \
	int errno_t = HPR_Wcscpy_s(strDest, destMax, strSrc); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wcscpy_s error[%d] destMax[%zu]", errno_t, (size_t)destMax); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wcsncpy_s function copies not more than n successive wide characters (not including the
 * terminating null wide character) from the array pointed to by strSrc to the array pointed to by strDest
 * Parameter: strDest - destination address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source address
 * Parameter: count - copies count wide characters from the src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WCSNCPY_S(strDest, destMax, strSrc, count) ({ \
	int errno_t = HPR_Wcsncpy_s(strDest, destMax, strSrc, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wcsncpy_s error[%d] destMax[%zu] count[%zu]", errno_t, (size_t)(destMax), (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wcscat_s function appends a copy of the wide string pointed to by strSrc (including the
 * terminating null wide character) to the end of the wide string pointed to by strDest
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source address
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WCSCAT_S(strDest, destMax, strSrc) ({ \
	int errno_t = HPR_Wcscat_s(strDest, destMax, strSrc); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wcscat_s error[%d] destMax[%zu]", errno_t, (size_t)destMax); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wcsncat_s function appends not more than n successive wide characters (not including the
 * terminating null wide character) from the array pointed to by strSrc to the end of the wide string pointed to
 * by strDest.
 * Parameter: strDest - destination  address
 * Parameter: destMax - The maximum length of destination buffer(including the terminating wide character)
 * Parameter: strSrc - source  address
 * Parameter: count - copies count wide characters from the  src
 * Return:    EOK if there was no runtime-constraint violation
 */
#define HPR_WCSNCAT_S(strDest, destMax, strSrc, count) ({ \
	int errno_t = HPR_Wcsncat_s(strDest, destMax, strSrc, count); \
	if(EOK != errno_t) { \
		SECUREC_ERROR("HPR_Wcsncat_s error[%d] destMax[%zu] count[%zu]", errno_t, (size_t)(destMax), (size_t)(count)); \
	} \
	errno_t; \
})

/*
 * Description: The HPR_Wcstok_s function is the wide-character equivalent of the strtok_s function
 * Parameter: strToken - the string to be delimited
 * Parameter: strDelimit - specifies a set of characters that delimit the tokens in the parsed string
 * Parameter: context - is a pointer to a char * variable that is used internally by strtok_s function
 * Return:    a pointer to the first character of a token, or a null pointer if there is no token
 * or there is a runtime-constraint violation.
 */
#define HPR_WCSTOK_S(strToken, strDelimit, context) HPR_Wcstok_s(strToken, strDelimit, context)

/*
 * Description: The HPR_Vswprintf_s function is the wide-character equivalent of the vsprintf_s function
 * Parameter: strDest - produce output according to a format,write to the character string strDest
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null)
 * Parameter: format - format string
 * Parameter: argList - instead of a variable number of arguments
 * Return:    the number of characters printed(not including the terminating null wide character),
 * If an error occurred Return: -1.
 */
#define HPR_VSWPRINTF_S(strDest, destMax, format, ...) HPR_Vswprintf_s(strDest, destMax, format, __VA_ARGS__)

/*
 * Description: The HPR_Swprintf_s function is the wide-character equivalent of the sprintf_s function
 * Parameter: strDest - produce output according to a format,write to the character string strDest
 * Parameter: destMax - The maximum length of destination buffer(including the terminating null)
 * Parameter: format - format string
 * Return:    the number of characters printed(not including the terminating null wide character),
 * If an error occurred Return: -1.
 */
#define HPR_SWPRINTF_S(strDest, destMax, format, ...) HPR_Swprintf_s(strDest, destMax, format, __VA_ARGS__)

/*
 * Description: The HPR_Fwscanf_s function is the wide-character equivalent of the fscanf_s function
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_FWSCANF_S(stream, format, ...) HPR_Fwscanf_s(stream, format, __VA_ARGS__)

/*
 * Description: The HPR_Vfwscanf_s function is the wide-character equivalent of the vfscanf_s function
 * Parameter: stream - stdio file stream
 * Parameter: format - format string
 * Parameter: argList - instead of  a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VFWSCANF_S(stream, format, ...) HPR_Vfwscanf_s(stream, format, __VA_ARGS__)

/*
 * Description: The HPR_Wscanf_s function is the wide-character equivalent of the HPR_Scanf_s function
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_WSCANF_S(format, ...) HPR_Wscanf_s(format, __VA_ARGS__)

/*
 * Description: The HPR_Vwscanf_s function is the wide-character equivalent of the vscanf_s function
 * Parameter: format - format string
 * Parameter: argList - instead of  a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VWSCANF_S(format, ...) HPR_Vwscanf_s(format, __VA_ARGS__)

/*
 * Description: The HPR_Swscanf_s function is the wide-character equivalent of the sscanf_s function
 * Parameter: buffer - read character from buffer
 * Parameter: format - format string
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_SWSCANF_S(buffer, format, ...) HPR_Swscanf_s(buffer, format, __VA_ARGS__)

/*
 * Description: The HPR_Vswscanf_s function is the wide-character equivalent of the vsscanf_s function
 * Parameter: buffer -  read character from  buffer
 * Parameter: format - format string
 * Parameter: argList - instead of  a variable number of arguments
 * Return:    the number of input items assigned, If an error occurred Return: -1.
 */
#define HPR_VSWSCANF_S(buffer, format, ...) HPR_Vswscanf_s(buffer, format, __VA_ARGS__)

#endif

