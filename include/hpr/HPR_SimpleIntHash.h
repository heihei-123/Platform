/*
 * ====================================================================
 * Copyright 2007-2008 Hikvision Digital Technology Co., Ltd.
 *
 *        Filename:  HPR_SimpleIntHash.h
 *
 *     Description:  简单hash的整数实现, 实现完全来源于glibc的hsearch_r.c文件。
 *                   只是简单修改了下，以方便使用
 *
 *          Author:  tyu, yutao NOSPAM hikvision DOT com
 *
 *            Date:  2009-11-27 17:47:03 中国标准时间
 *
 * Modification History:
 *            <version > <time> <author> <desc>
 * ====================================================================
 */

#ifndef __HPR_SIMPLE_INT_HASH_H__
#define __HPR_SIMPLE_INT_HASH_H__

#include "HPR_Config.h"
#include "HPR_Types.h"

typedef struct _HPR_INTITEM
{
    HPR_UINT32  key;
    HPR_VOIDPTR data;
}HPR_INTITEM;

/**
 * Function:    HPR_SimpleIntHashCreate
 * Desc:
 * Input:       @param
 * Output:      @param
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleIntHashCreate(HPR_INT32 size, HPR_HANDLE* hash_handle);

/**
 * Function:    HPR_SimpleIntHashCreate
 * Desc:
 * Input:       @param
                @param
 * Output:
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleIntHashEnter(HPR_INTITEM* item, HPR_HANDLE hash_handle);

/**
 * Function:    HPR_SimpleIntHashCreate
 * Desc:
 * Input:       @param
                @param
 * Output:      @param
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleIntHashFind(HPR_UINT32 key, HPR_VOIDPTR* data, HPR_HANDLE hash_handle);

/**
 * Function:    HPR_SimpleIntHashCreate
 * Desc:
 * Input:       @param
                @param
 * Output:
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleIntHashRemove(HPR_UINT32 key, HPR_HANDLE hash_handle);

/**
 * Function:    HPR_SimpleIntHashDestroy
 * Desc:
 * Input:       @param
 * Output:
 * Return:      if success return HPR_OK, otherwise return HPR_ERROR.
 * */
HPR_DECLARE HPR_INT32 CALLBACK HPR_SimpleIntHashDestroy(HPR_HANDLE hash_handle);

#endif

