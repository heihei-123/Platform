/*
 * CopyRight:   HangZhou Hikvision System Technology Co., Ltd. All  Right Reserved.
 * FileName:    HRP_Hpr.h
 * Desc:        OS Layer Component.
 * Author:      schina
 * Date:        2009-03-02
 * Contact:     zhaoyiji@hikvision.com.cn
 * History:     Created By Zhaoyiji 2009-03-02
 * */

/*! 
    \file HPR_Hpr.h
    \brief HPR Hpr Manager.

    Details.
*/

#ifndef __HPR_HPR_H__
#define __HPR_HPR_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

/**
 * HPR_Init 初始化HPR库,使用HPR库必须首先调用这个函数
 * @param void
 * @return 0成功，-1失败。
 * @sa HPR_Fini().
 */
HPR_DECLARE HPR_INT32 CALLBACK CALLBACK HPR_Init();
HPR_DECLARE HPR_INT32 CALLBACK CALLBACK HPR_InitEx();

/**
 * HPR_Fini 销毁HPR库,最后调用
 * @param void
 * @return void
 * @sa HPR_Init().
 */
HPR_DECLARE HPR_VOID CALLBACK CALLBACK HPR_Fini();
HPR_DECLARE HPR_VOID CALLBACK CALLBACK HPR_FiniEx();

#endif


