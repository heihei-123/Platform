/*
 * hprsafefunc.h是hikvision 基于hw boundcheck 安全函数库封装的适合hikvision使用的安全函数库
 * 当前版本号V1.0.0，初始创建版本，后续版本迭代记录在此增加说明
 *
 * V1.0.0 --初始版本,创建日期 2022-09-20
 */
 
#ifndef __HPR_SAFE_FUNC_H__
#define __HPR_SAFE_FUNC_H__

#include "hprsecurec.h"

#ifdef __cplusplus
extern "C" {
#endif

#define COUNT_ARGS_IMPL2(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,_65,_66,_67,_68,_69,_70,_71,_72,_73,_74,_75,_76,_77,_78,_79,_80,_81,_82,_83,_84,_85,_86,_87,_88,_89,_90,_91,_92,_93,_94,_95,_96,_97,_98,_99,_100,_101,_102,_103,_104,_105,_106,_107,_108,_109,_110,_111,_112,_113,_114,_115,_116,_117,_118,_119,_120,_121,_122,_123,_124,N,...) N
#define COUNT_ARGS_IMPL1(args) COUNT_ARGS_IMPL2 args
#define COUNT_ARGS(...) COUNT_ARGS_IMPL1((__VA_ARGS__, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1))

#if defined(__GNUC__) || defined(__clang__)
__attribute__((unused)) extern __thread int __hpr_safec_errno_t;
__attribute__((unused)) extern __thread int __hpr_safec_check_arg_errno_t;
__attribute__((unused)) extern __thread char* __hpr_safec_str_t;
extern void __hpr_safec_error_handle(const char *filename, const int line, const char *function, const char *safefunc, int err);
#endif

#ifdef _MSC_VER
__declspec(dllimport) extern int __hpr_safec_errno_t;
__declspec(dllimport) extern int __hpr_safec_check_arg_errno_t;
__declspec(dllimport) extern char* __hpr_safec_str_t;
__declspec(dllimport) extern void __hpr_safec_error_handle(const char *filename, const int line, const char *function, const char *safefunc, int err);
#endif

/*用于设置安全函数错误返回时错误信息的输出接口,各业务部自行设置实现*/
void set_err_handle_cb(errorhandle errhandle);

/*******************HPR_MEMSET_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Memset_s function copies the value of c (converted to an unsigned char)
 *     into each of the first count characters of the object pointed to by dest.
 *
 * <INPUT PARAMETERS>
 *    dest                Pointer to destination.
 *    destMax             The size of the buffer.
 *    c                   Character to set.
 *    count               Number of characters.
 *
 * <OUTPUT PARAMETERS>
 *    dest buffer         is updated.
 *
 * <RETURN VALUE>
 *    EOK                 Success
 *    EINVAL              dest == NULL and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *    ERANGE              destMax > SECUREC_MEM_MAX_LEN or (destMax is 0 and count > destMax)
 *    ERANGE_AND_RESET    count > destMax and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN and dest != NULL
 *
 *    if return ERANGE_AND_RESET then fill dest to c ,fill length is destMax
 */
#define HPR_MEMSET_S(dest, destMax, c, count)    (__hpr_safec_errno_t = HPR_Memset_s(dest, destMax, c, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMSET_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMSET_NATIVE_S(dest, destMax, c, count)    HPR_Memset_s(dest, destMax, c, count)

/*******************HPR_MEMMOVE_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Memmove_s function copies count bytes of characters from src to dest.
 *    This function can be assigned correctly when memory overlaps.
 * <INPUT PARAMETERS>
 *    dest                    Destination object.
 *    destMax                 Size of the destination buffer.
 *    src                     Source object.
 *    count                   Number of characters to copy.
 *
 * <OUTPUT PARAMETERS>
 *    dest buffer             is updated.
 *
 * <RETURN VALUE>
 *    EOK                     Success
 *    EINVAL                  dest is  NULL and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *    EINVAL_AND_RESET        dest != NULL and src is NULL and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *    ERANGE                  destMax > SECUREC_MEM_MAX_LEN or destMax is 0
 *    ERANGE_AND_RESET        count > destMax and dest  !=  NULL and src != NULL and destMax != 0
 *                            and destMax <= SECUREC_MEM_MAX_LEN
 *
 *    If an error occurred, dest will  be filled with 0 when dest and destMax valid.
 *    If some regions of the source area and the destination overlap, HPR_Memmove_s
 *    ensures that the original source bytes in the overlapping region are copied
 *    before being overwritten.
 */
#define HPR_MEMMOVE_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Memmove_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMMOVE_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMMOVE_NATIVE_S(dest, destMax, src, count)    HPR_Memmove_s(dest, destMax, src, count)

/*******************HPR_MEMCPY_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Memcpy_s function copies n characters from the object pointed to by src into the object pointed to by dest
 *
 * <INPUT PARAMETERS>
 *    dest                      Destination buffer.
 *    destMax                   Size of the destination buffer.
 *    src                       Buffer to copy from.
 *    count                     Number of characters to copy
 *
 * <OUTPUT PARAMETERS>
 *    dest buffer               is updated.
 *
 * <RETURN VALUE>
 *    EOK                      Success
 *    EINVAL                   dest is  NULL and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *    EINVAL_AND_RESET         dest != NULL and src is NULL and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *    ERANGE                   destMax > SECUREC_MEM_MAX_LEN or destMax is 0
 *    ERANGE_AND_RESET         count > destMax and destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN
 *                             and dest  !=  NULL  and src != NULL
 *    EOVERLAP_AND_RESET       dest buffer and source buffer are overlapped and
 *                             count <= destMax destMax != 0 and destMax <= SECUREC_MEM_MAX_LEN and dest  !=  NULL
 *                             and src != NULL  and dest != src
 *
 *    if an error occurred, dest will be filled with 0.
 *    If the source and destination overlap, the behavior of HPR_Memcpy_s is undefined.
 *    Use HPR_Memmove_s to handle overlapping regions.
 */
#define HPR_MEMCPY_S(dest, destMax, src, count)    (__hpr_safec_errno_t = HPR_Memcpy_s(dest, destMax, src, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_MEMCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_MEMCPY_NATIVE_S(dest, destMax, src, count)    HPR_Memcpy_s(dest, destMax, src, count)

/*******************HPR_STRCPY_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Strcpy_s function copies the string pointed to  strSrc
 *          (including the terminating null character) into the array pointed to by strDest
 *    The destination string must be large enough to hold the source string,
 *    including the terminating null character. HPR_Strcpy_s will return EOVERLAP_AND_RESET
 *    if the source and destination strings overlap.
 *
 * <INPUT PARAMETERS>
 *    strDest                          Location of destination string buffer
 *    destMax                        Size of the destination string buffer.
 *    strSrc                            Null-terminated source string buffer.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                         is updated.
 *
 * <RETURN VALUE>
 *    EOK                               Success
 *    EINVAL                          strDest is  NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    EINVAL_AND_RESET       strDest !=  NULL and strSrc is NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    ERANGE                         destMax is 0 and destMax > SECUREC_STRING_MAX_LEN
 *    ERANGE_AND_RESET      strDest have not enough space  and all other parameters are valid  and not overlap
 *    EOVERLAP_AND_RESET   dest buffer and source buffer are overlapped and all  parameters are valid
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_STRCPY_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Strcpy_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRCPY_NATIVE_S(strDest, destMax, strSrc)    HPR_Strcpy_s(strDest, destMax, strSrc)

/*******************HPR_STRNCPY_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *   The HPR_Strncpy_s function copies not more than n successive characters (not including the terminating null character)
 *                     from the array pointed to by strSrc to the array pointed to by strDest.
 *
 * <INPUT PARAMETERS>
 *    strDest                          Destination string.
 *    destMax                          The size of the destination string, in characters.
 *    strSrc                            Source string.
 *    count                              Number of characters to be copied.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                           is updated
 *
 * <RETURN VALUE>
 *    EOK                               Success
 *    EINVAL                          strDest is  NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    EINVAL_AND_RESET       strDest !=  NULL and strSrc is NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    ERANGE                         destMax is 0 and destMax > SECUREC_STRING_MAX_LEN
 *    ERANGE_AND_RESET      strDest have not enough space  and all other parameters are valid  and not overlap
 *    EOVERLAP_AND_RESET   dest buffer and source buffer are overlapped and all  parameters are valid
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_STRNCPY_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Strncpy_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRNCPY_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRNCPY_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Strncpy_s(strDest, destMax, strSrc, count)

/*******************HPR_STRCAT_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *  The HPR_Strcat_s function appends a copy of the string pointed to by strSrc (including the terminating null character)
 *  to the end of the  string pointed to by strDest.
 *  The initial character of strSrc overwrites the terminating null character of strDest.
 *  HPR_Strcat_s will return EOVERLAP_AND_RESET if the source and destination strings overlap.
 *
 *  Note that the second parameter is the total size of the buffer, not the
 *  remaining size.
 *
 * <INPUT PARAMETERS>
 *  strDest             Null-terminated destination string buffer.
 *  destMax             Size of the destination string buffer.
 *  strSrc              Null-terminated source string buffer.
 *
 * <OUTPUT PARAMETERS>
 *    strDest             is updated
 *
 * <RETURN VALUE>
 *    EOK                 Success
 *    EINVAL              strDest is  NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    EINVAL_AND_RESET    (strDest unterminated  and all other parameters are valid) or
 *                        (strDest != NULL and strSrc is NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN)
 *    ERANGE              destMax is 0 and destMax > SECUREC_STRING_MAX_LEN
 *    ERANGE_AND_RESET      strDest have not enough space  and all other parameters are valid  and not overlap
 *    EOVERLAP_AND_RESET   dest buffer and source buffer are overlapped and all  parameters are valid
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_STRCAT_S(strDest, destMax, strSrc)    (__hpr_safec_errno_t = HPR_Strcat_s(strDest, destMax, strSrc));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRCAT_NATIVE_S(strDest, destMax, strSrc)    HPR_Strcat_s(strDest, destMax, strSrc)

/*******************HPR_STRNCAT_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Strncat_s function appends not more than n successive  characters
 *    (not including the terminating null  character)
 *     from the array pointed to by strSrc to the end of the  string pointed to by strDest
 *    The HPR_Strncat_s function try to append the first D characters of strSrc to
 *    the end of strDest, where D is the lesser of count and the length of strSrc.
 *    If appending those D characters will fit within strDest (whose size is given
 *    as destMax) and still leave room for a null terminator, then those characters
 *    are appended, starting at the original terminating null of strDest, and a
 *    new terminating null is appended; otherwise, strDest[0] is set to the null
 *    character.
 *
 * <INPUT PARAMETERS>
 *    strDest            Null-terminated destination string.
 *    destMax            Size of the destination buffer.
 *    strSrc             Null-terminated source string.
 *    count              Number of character to append, or truncate.
 *
 * <OUTPUT PARAMETERS>
 *    strDest            is updated
 *
 * <RETURN VALUE>
 *    EOK                Success
 *    EINVAL             strDest is  NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN
 *    EINVAL_AND_RESET      (strDest unterminated  and all other parameters are valid)or
 *                        (strDest !=  NULL and strSrc is NULL and destMax != 0 and destMax <= SECUREC_STRING_MAX_LEN)
 *    ERANGE                         destMax is 0 and destMax > SECUREC_STRING_MAX_LEN
 *    ERANGE_AND_RESET      strDest have not enough space  and all other parameters are valid  and not overlap
 *    EOVERLAP_AND_RESET   dest buffer and source buffer are overlapped and all  parameters are valid
 *
 *    If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_STRNCAT_S(strDest, destMax, strSrc, count)    (__hpr_safec_errno_t = HPR_Strncat_s(strDest, destMax, strSrc, count));\
do{\
	if(EOK != __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRNCAT_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_STRNCAT_NATIVE_S(strDest, destMax, strSrc, count)    HPR_Strncat_s(strDest, destMax, strSrc, count)

/*******************HPR_VSPRINTF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Vsprintf_s function is equivalent to the vsprintf function
 *    except for the parameter destMax and the explicit runtime-constraints violation
 *    The HPR_Vsprintf_s function takes a pointer to an argument list, and then formats
 *    and writes the given data to the memory pointed to by strDest.
 *    The function differ from the non-secure versions only in that the secure
 *    versions support positional parameters.
 *
 * <INPUT PARAMETERS>
 *    strDest                Storage location for the output.
 *    destMax                Size of strDest
 *    format                 Format specification.
 *    argList                pointer to list of arguments
 *
 * <OUTPUT PARAMETERS>
 *    strDest                is updated
 *
 * <RETURN VALUE>
 *    return  the number of characters written, not including the terminating null character,
 *    return -1  if an  error occurs.
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_VSPRINTF_S(strDest, destMax, format, argList)    (__hpr_safec_errno_t = HPR_Vsprintf_s(strDest, destMax, format, argList));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSPRINTF_NATIVE_S(strDest, destMax, format, argList)    HPR_Vsprintf_s(strDest, destMax, format, argList)

/*******************HPR_SPRINTF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Sprintf_s function is equivalent to the sprintf function
 *    except for the parameter destMax and the explicit runtime-constraints violation
 *    The HPR_Sprintf_s function formats and stores a series of characters and values
 *    in strDest. Each argument (if any) is converted and output according to
 *    the corresponding format specification in format. The format consists of
 *    ordinary characters and has the same form and function as the format argument
 *    for printf. A null character is appended after the last character written.
 *    If copying occurs between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    strDest                 Storage location for output.
 *    destMax                Maximum number of characters to store.
 *    format                  Format-control string.
 *    ...                        Optional arguments
 *
 * <OUTPUT PARAMETERS>
 *    strDest                 is updated
 *
 * <RETURN VALUE>
 *    return the number of bytes stored in strDest, not counting the terminating null character.
 *    return -1 if an error occurred.
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_SPRINTF_S(strDest, destMax, format, ...)    (__hpr_safec_errno_t = HPR_Sprintf_s(strDest, destMax, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SPRINTF_NATIVE_S(strDest, destMax, format, ...)    HPR_Sprintf_s(strDest, destMax, format, ##__VA_ARGS__)

/*******************HPR_VSNPRINTF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Vsnprintf_s function is equivalent to the vsnprintf function
 *     except for the parameter destMax/count and the explicit runtime-constraints violation
 *    The HPR_Vsnprintf_s function takes a pointer to an argument list, then formats
 *    and writes up to count characters of the given data to the memory pointed
 *    to by strDest and appends a terminating null.
 *
 * <INPUT PARAMETERS>
 *    strDest                  Storage location for the output.
 *    destMax                The size of the strDest for output.
 *    count                    Maximum number of character to write(not including
 *                                the terminating NULL)
 *    format                   Format-control string.
 *    argList                     pointer to list of arguments.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                is updated
 *
 * <RETURN VALUE>
 *    return  the number of characters written, not including the terminating null
 *    return -1 if an  error occurs.
 *    return -1 if count < destMax and the output string  has been truncated
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 */
#define HPR_VSNPRINTF_S(strDest, destMax, count, format, argList)    (__hpr_safec_errno_t = HPR_Vsnprintf_s(strDest, destMax, count, format, argList));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSNPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSNPRINTF_NATIVE_S(strDest, destMax, count, format, argList)    HPR_Vsnprintf_s(strDest, destMax, count, format, argList)

/*******************HPR_SNPRINTF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Snprintf_s function is equivalent to the snprintf function
 *    except for the parameter destMax/count and the explicit runtime-constraints violation
 *    The HPR_Snprintf_s function formats and stores count or fewer characters in
 *    strDest and appends a terminating null. Each argument (if any) is converted
 *    and output according to the corresponding format specification in format.
 *    The formatting is consistent with the printf family of functions; If copying
 *    occurs between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    strDest                 Storage location for the output.
 *    destMax                 The size of the storage location for output. Size
 *                                 in bytes for HPR_Snprintf_s or size in words for snwprintf_s.
 *    count                    Maximum number of character to store.
 *    format                  Format-control string.
 *    ...                        Optional arguments.
 *
 * <OUTPUT PARAMETERS>
 *    strDest                 is updated
 *
 * <RETURN VALUE>
 *    return  the number of characters written, not including the terminating null
 *    return -1 if an  error occurs.
 *    return -1 if count < destMax and the output string  has been truncated
 *
 * If there is a runtime-constraint violation, strDest[0] will be set to the '\0' when strDest and destMax valid
 *
 */
#define HPR_SNPRINTF_S(strDest, destMax, count, format, ...)    (__hpr_safec_errno_t = HPR_Snprintf_s(strDest, destMax, count, format, ##__VA_ARGS__));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SNPRINTF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SNPRINTF_NATIVE_S(strDest, destMax, count, format, ...)    HPR_Snprintf_s(strDest, destMax, count, format, ##__VA_ARGS__)

/*******************HPR_SCANF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Scanf_s function is equivalent to fscanf_s with the argument stdin interposed before the arguments to scanf_s
 *     The HPR_Scanf_s function reads data from the standard input stream stdin and
 *    writes the data into the location that's given by argument. Each argument
 *    must be a pointer to a variable of a type that corresponds to a type specifier
 *    in format. If copying occurs between strings that overlap, the behavior is
 *    undefined.
 *
 * <INPUT PARAMETERS>
 *    format                  Format control string.
 *    ...                       Optional arguments.
 *
 * <OUTPUT PARAMETERS>
 *    ...                       The converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Returns the number of fields successfully converted and assigned;
 *    the return value does not include fields that were read but not assigned.
 *    A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 *    return -3 if the args num is error.
 */
#define HPR_SCANF_S(format, ...)    (__hpr_safec_errno_t = ((__hpr_safec_check_arg_errno_t=checkArgs(format, COUNT_ARGS(__VA_ARGS__)))<0 ? __hpr_safec_check_arg_errno_t : HPR_Scanf_s(format, ##__VA_ARGS__)));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SCANF_NATIVE_S(format, ...)    HPR_Scanf_s(format, ##__VA_ARGS__)

/*******************HPR_VSCANF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *     The HPR_Vscanf_s function is equivalent to HPR_Scanf_s, with the variable argument list replaced by argList,
 *     The HPR_Vscanf_s function reads data from the standard input stream stdin and
 *    writes the data into the location that's given by argument. Each argument
 *    must be a pointer to a variable of a type that corresponds to a type specifier
 *    in format. If copying occurs between strings that overlap, the behavior is
 *    undefined.
 *
 * <INPUT PARAMETERS>
 *    format                Format control string.
 *    argList               pointer to list of arguments
 *
 * <OUTPUT PARAMETERS>
 *    argList               the converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Returns the number of fields successfully converted and assigned;
 *    the return value does not include fields that were read but not assigned.
 *    A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 */
#define HPR_VSCANF_S(format, argList)    (__hpr_safec_errno_t = HPR_Vscanf_s(format, argList));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSCANF_NATIVE_S(format, argList)    HPR_Vscanf_s(format, argList)

/*******************HPR_SSCANF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Sscanf_s function is equivalent to fscanf_s,
 *     except that input is obtained from a string (specified by the argument buffer) rather than from a stream
 *    The sscanf function reads data from buffer into the location given by each
 *    argument. Every argument must be a pointer to a variable with a type that
 *    corresponds to a type specifier in format. The format argument controls the
 *    interpretation of the input fields and has the same form and function as
 *    the format argument for the scanf function.
 *    If copying takes place between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    buffer                 Stored data.
 *    format                 Format control string, see Format Specifications.
 *    ...                    Optional arguments.
 *
 * <OUTPUT PARAMETERS>
 *    ...                    The converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Each of these functions returns the number of fields successfully converted
 *    and assigned; the return value does not include fields that were read but
 *    not assigned.
 *    A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 *    return -3 if the args num is error.
 */
#define HPR_SSCANF_S(buffer, format, ...)    (__hpr_safec_errno_t = ((__hpr_safec_check_arg_errno_t=checkArgs(format, COUNT_ARGS(__VA_ARGS__)))<0 ? __hpr_safec_check_arg_errno_t : HPR_Sscanf_s(buffer, format, ##__VA_ARGS__)));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_SSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_SSCANF_NATIVE_S(buffer, format, ...)    HPR_Sscanf_s(buffer, format, ##__VA_ARGS__)

/*******************HPR_VSSCANF_S*******************/
/*
 * <NAME>
 *    HPR_Vsscanf_s
 *
 *
 * <FUNCTION DESCRIPTION>
 *    The HPR_Vsscanf_s function is equivalent to sscanf_s, with the variable argument list replaced by argList
 *    The HPR_Vsscanf_s function reads data from buffer into the location given by
 *    each argument. Every argument must be a pointer to a variable with a type
 *    that corresponds to a type specifier in format. The format argument controls
 *    the interpretation of the input fields and has the same form and function
 *    as the format argument for the scanf function.
 *    If copying takes place between strings that overlap, the behavior is undefined.
 *
 * <INPUT PARAMETERS>
 *    buffer                Stored data
 *    format                Format control string, see Format Specifications.
 *    argList               pointer to list of arguments
 *
 * <OUTPUT PARAMETERS>
 *    argList               the converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Each of these functions returns the number of fields successfully converted
 *    and assigned; the return value does not include fields that were read but
 *    not assigned. A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 */
#define HPR_VSSCANF_S(buffer, format, argList)    (__hpr_safec_errno_t = HPR_Vsscanf_s(buffer, format, argList));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VSSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VSSCANF_NATIVE_S(buffer, format, argList)    HPR_Vsscanf_s(buffer, format, argList)

/*******************HPR_FSCANF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Fscanf_s function is equivalent to fscanf except that the c, s,
 *    and [ conversion specifiers apply to a pair of arguments (unless assignment suppression is indicated by a*)
 *    The fscanf function reads data from the current position of stream into
 *    the locations given by argument (if any). Each argument must be a pointer
 *    to a variable of a type that corresponds to a type specifier in format.
 *    format controls the interpretation of the input fields and has the same
 *    form and function as the format argument for scanf.
 *
 * <INPUT PARAMETERS>
 *    stream              Pointer to FILE structure.
 *    format              Format control string, see Format Specifications.
 *    ...                 Optional arguments.
 *
 * <OUTPUT PARAMETERS>
 *    ...                 The converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Each of these functions returns the number of fields successfully converted
 *    and assigned; the return value does not include fields that were read but
 *    not assigned. A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 *    return -3 if the args num is error.
 */
#define HPR_FSCANF_S(stream, format, ...)    (__hpr_safec_errno_t = ((__hpr_safec_check_arg_errno_t=checkArgs(format, COUNT_ARGS(__VA_ARGS__)))<0 ? __hpr_safec_check_arg_errno_t : HPR_Fscanf_s(stream, format, ##__VA_ARGS__)));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_FSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_FSCANF_NATIVE_S(stream, format, ...)    HPR_Fscanf_s(stream, format, ##__VA_ARGS__)

/*******************HPR_VFSCANF_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Vfscanf_s function is equivalent to fscanf_s, with the variable argument list replaced by argList
 *    The HPR_Vfscanf_s function reads data from the current position of stream into
 *    the locations given by argument (if any). Each argument must be a pointer
 *    to a variable of a type that corresponds to a type specifier in format.
 *    format controls the interpretation of the input fields and has the same
 *    form and function as the format argument for scanf.
 *
 * <INPUT PARAMETERS>
 *    stream               Pointer to FILE structure.
 *    format               Format control string, see Format Specifications.
 *    argList              pointer to list of arguments
 *
 * <OUTPUT PARAMETERS>
 *    argList              the converted value stored in user assigned address
 *
 * <RETURN VALUE>
 *    Each of these functions returns the number of fields successfully converted
 *    and assigned; the return value does not include fields that were read but
 *    not assigned. A return value of 0 indicates that no fields were assigned.
 *    return -1 if an error occurs.
 */
#define HPR_VFSCANF_S(stream, format, argList)    (__hpr_safec_errno_t = HPR_Vfscanf_s(stream, format, argList));\
do{\
	if(0 > __hpr_safec_errno_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_VFSCANF_S", __hpr_safec_errno_t);\
	}\
}while(0);

#define HPR_VFSCANF_NATIVE_S(stream, format, argList)    HPR_Vfscanf_s(stream, format, argList)

/*******************HPR_STRTOK_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Strtok_s function parses a string into a sequence of strToken,
 *    replace all characters in strToken string that match to strDelimit set with 0.
 *    On the first call to HPR_Strtok_s the string to be parsed should be specified in strToken.
 *    In each subsequent call that should parse the same string, strToken should be NULL
 * <INPUT PARAMETERS>
 *    strToken            String containing token or tokens.
 *    strDelimit          Set of delimiter characters.
 *    context             Used to store position information between calls
 *                             to HPR_Strtok_s
 * <OUTPUT PARAMETERS>
 *   context               is updated
 * <RETURN VALUE>
 *   On the first call returns the address of the first non \0 character, otherwise NULL is returned.
 *   In subsequent calls, the strtoken is set to NULL, and the context set is the same as the previous call,
 *   return NULL if the *context string length is equal 0, otherwise return *context.
 */
#define HPR_STRTOK_S(strToken, strDelimit, context)    (__hpr_safec_str_t = HPR_Strtok_s(strToken, strDelimit, context));\
do{\
	if(NULL == __hpr_safec_str_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_STRTOK_S", 0);\
	}\
}while(0);

#define HPR_STRTOK_NATIVE_S(strToken, strDelimit, context)    HPR_Strtok_s(strToken, strDelimit, context)

/*******************HPR_GETS_S*******************/
/*
 * <FUNCTION DESCRIPTION>
 *    The HPR_Gets_s function reads at most one less than the number of characters
 *    specified by destMax from the std input stream, into the array pointed to by buffer
 *    The line consists of all characters up to and including
 *    the first newline character ('\n'). HPR_Gets_s then replaces the newline
 *    character with a null character ('\0') before returning the line.
 *    If the first character read is the end-of-file character, a null character
 *    is stored at the beginning of buffer and NULL is returned.
 *
 * <INPUT PARAMETERS>
 *    buffer                         Storage location for input string.
 *    destMax                        The size of the buffer.
 *
 * <OUTPUT PARAMETERS>
 *    buffer                         is updated
 *
 * <RETURN VALUE>
 *    buffer                         Successful operation
 *    NULL                           Improper parameter or read fail
 */
#define HPR_GETS_S(buffer, destMax)    (__hpr_safec_str_t = HPR_Gets_s(buffer, destMax));\
do{\
	if(NULL == __hpr_safec_str_t)\
	{\
		__hpr_safec_error_handle(__FILE__, __LINE__, __FUNCTION__, "HPR_GETS_S", 0);\
	}\
}while(0);

#define HPR_GETS_NATIVE_S(buffer, destMax)    HPR_Gets_s(buffer, destMax)


#ifdef __cplusplus
}
#endif

#endif /*__HPR_SAFE_FUNC_H__*/

