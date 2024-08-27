/**	@file		OSHeader.h
 *	@note		Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief		
 *
 *	@author		lipengfei
 *	@date		2015/07/22
 *	@note		历史记录：
 *	@note		V1.0.0  
 *	@warning	
 */
#ifndef __OSHEADER_H__
#define __OSHEADER_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if (defined(_WIN32) || defined(WIN64))
/////////////////////////////////////////////////////////windows下
//#define  _CRT_SECURE_NO_WARNINGS

#define	OS_WINDOWS		1
#include <windows.h>


#ifndef CALLBACK
#define CALLBACK __stdcall
#endif


#define IVMS_EXPORTS	1

#if defined(IVMS_EXPORTS)
#define HPC_DECLERA extern "C" __declspec(dllexport)
#define HPC_DECLERA_CLASS  __declspec(dllimport)
#else
#define HPC_DECLERA extern "C" __declspec(dllimport)
#define HPC_DECLERA_CLASS  __declspec(dllimport)
#endif

#define STR_ALIGN_4                   

#elif (defined(__linux__))
///////////////////////////////////////////////////////////////// 其他系统

#define OS_POSIX	1

#include "unistd.h"
#include "time.h"
#include <sys/sysinfo.h>
#include<sys/mman.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <errno.h>

#ifndef CALLBACK
#define CALLBACK
#else
#undef CALLBACK
#define CALLBACK
#endif

#define HPC_DECLERA extern "C"
#define HPC_DECLERA_CLASS


#define STR_ALIGN_4               __attribute__ ((aligned (4)))            

#else
#error OS Not Implement Yet.
#endif	// end #if (defined(WIN32) || defined(_WIN_WCE))


#endif
