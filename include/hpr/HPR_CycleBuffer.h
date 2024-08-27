/*
 * ====================================================================
 * Copyright 2007-2008 Hikvision Digital Technology Co., Ltd.
 *
 *        Filename:  HPR_CycleBuffer.h
 * 
 *     Description:  循环缓冲区接口定义
 * 
 *          Author:  tyu, yutao NOSPAM hikvision DOT com
 *
 *            Date:  2009-11-26 19:45:03 中国标准时间
 *
 * Modification History:
 *            <version > <time> <author> <desc>
 * ====================================================================
 */

#ifndef __HPR_CYCLEBUFFER_H__
#define __HPR_CYCLEBUFFER_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

typedef HPR_INT32 (*CycleStreamCallBack)(HPR_UINT8* pCycBufBase, HPR_INT32 bufSize, HPR_INT32 readIdx, HPR_INT32 cycDataLen, HPR_VOIDPTR userData);

/**
 * Function:	HPR_CycleBufferInit
 * Desc:		
 * Input:		@param 
				@param 
 * Output:      @param
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferInit(HPR_HANDLE* pCycleBuf, HPR_INT32 bufSize, CycleStreamCallBack cb, HPR_VOIDPTR userData);

/**
 * Function:	HPR_CycleBufferInit
 * Desc:		
 * Input:		@param 
				@param 
 * Output:      @param
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */

HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferClear(HPR_HANDLE cycleBuf);

/**
 * Function:	HPR_CycleBufferWrite
 * Desc:		
 * Input:		@param 
				@param 
				@param 
 * Output
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferWrite(HPR_HANDLE cycleBuf, unsigned char* pBuf, HPR_INT32 len);

/**
 * Function:	HPR_CycleBufferRead
 * Desc:		
 * Input:		@param 
 * Output:      
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferRead(HPR_HANDLE cycleBuf);

/* @fn      HPR_CycleBufferCopy
 * @brief   copy cyc data to buf of pData.
 * @brief   Author/Date huangjs/2011-06-24.
 * @param   [in] pCycBufBase : cyc buf base.
 * @param   [in] iBufSize : cyc buf size.
 * @param   [in] iReadIdx : cyc buf read idx.
 * @param   [in] iCycDataLen : cyc buf data len.
 * @param   [in] *pData : user buf.
 * @param   [in] iCopyLen : copy data len.
 * @param   [out] N/A.
 * @return  ERROR/OK.
 */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferCopy
	(HPR_UINT8* pCycBufBase, HPR_INT32 iBufSize, HPR_INT32 iReadIdx,
	 HPR_INT32 iCycDataLen, HPR_UINT8* pData, HPR_INT32 iCopyLen);

/**
 * Function:	HPR_CycleBufferValue
 * Desc:		
 * Input:		@param 
 * Output:      @param
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferValue(HPR_HANDLE cycleBuf, HPR_INT32* len);

/**
 * Function:	HPR_CycleBufferDestroy
 * Desc:		
 * Input:		@param 
 * Output:
 * Return:		if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_CycleBufferDestroy(HPR_HANDLE cycleBuf);

#endif


