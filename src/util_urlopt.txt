/**	@file		urlopt.cpp
 *	@note		Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief		url操作
 *
 *	@author		lipengfei
 *	@date		2015/01/22
 *	@note		历史记录：
 *	@note		V1.0.0
 *	@warning
 */

#include "util_urlopt.h"
#include <string>

int				g_nInitCount			= 0;

/** @fn		size_t GetOptCallBack(void *pBuf, size_t nSize, size_t nCount, void *pUser)
 *  @brief	URLGet 操作的回调函数
 *	@param	-I	 - void * pBuf           缓存
 *	@param	-I	 - size_t nSize         大小
 *	@param	-I	 - size_t nCount        个数
 *	@param	-I	 - void * pUser         用户数据
 *	@return size_t                      总的数据
 */
size_t GetFileCallBack(void *pBuf, size_t nSize, size_t nCount, void *pUser)
{
    if (pUser   == NULL ||
        pBuf    == NULL)
    {
        return 0;
    }
    IVMS_URL_GET_CB_PARAM           *pstParam   = (IVMS_URL_GET_CB_PARAM*)pUser;

    if (nSize * nCount + pstParam->nDataLen > pstParam->nTotalLen)
    {
        // 数据超出了值
        return 0;
    }

    fwrite(pBuf, nSize * nCount, 1, pstParam->fileFd);
//    memcpy(pstParam->pData + pstParam->nDataLen, pBuf, nSize * nCount);
    pstParam->nDataLen += nSize * nCount;

    return nSize * nCount;
}

/** @fn		size_t GetOptCallBack(void *pBuf, size_t nSize, size_t nCount, void *pUser)
 *  @brief	URLGet 操作的回调函数
 *	@param	-I	 - void * pBuf           缓存
 *	@param	-I	 - size_t nSize         大小
 *	@param	-I	 - size_t nCount        个数
 *	@param	-I	 - void * pUser         用户数据
 *	@return size_t                      总的数据
 */
size_t GetOptCallBack(void *pBuf, size_t nSize, size_t nCount, void *pUser)
{
    if (pUser   == NULL ||
        pBuf    == NULL)
    {
        return 0;
    }
    IVMS_URL_GET_CB_PARAM           *pstParam   = (IVMS_URL_GET_CB_PARAM*)pUser;

    if (nSize * nCount + pstParam->nDataLen > pstParam->nTotalLen)
    {
        // 数据超出了值
        return 0;
    }

    memcpy(pstParam->pData + pstParam->nDataLen, pBuf, nSize * nCount);
    pstParam->nDataLen += nSize * nCount;

    return nSize * nCount;
}

size_t GetOptCallBackString(void *pBuf, size_t nSize, size_t nCount, void *pUser)
{
    if (pUser   == NULL || pBuf    == NULL)
    {
        return 0;
    }
    char *pTempBuf = (char *)pBuf;

    std::string &buffer = *(static_cast<std::string*>(pUser));
    for (size_t i = 0; i < nSize * nCount; ++i)
    {
    		buffer += *pTempBuf;
    		++pTempBuf;
    }
   #if 0
    _IVMS_URL_GET_CB_PARAM_STRING    *pstParam   = (_IVMS_URL_GET_CB_PARAM_STRING*)pUser;

    if (nSize * nCount + pstParam->nDataLen > pstParam->nTotalLen)
    {
        // 数据超出了值
        return 0;
    }
    pstParam->strData.append((char *)pBuf, nSize * nCount);

    //memcpy(pstParam->pData + pstParam->nDataLen, pBuf, nSize * nCount);
    pstParam->nDataLen += nSize * nCount;
	#endif
    return nSize * nCount;
}


size_t GetOptCallBack_(void *pBuf, size_t nSize, size_t nCount, void *pUser)
{
    if (pUser   == NULL ||
        pBuf    == NULL)
    {
        return 0;
    }
    IVMS_URL_GET_CB_PARAM           *pstParam   = (IVMS_URL_GET_CB_PARAM*)pUser;

    if (nSize * nCount + pstParam->nDataLen > pstParam->nTotalLen)
    {
    	unsigned char *pTemBuf = NULL;
    	pstParam->nTotalLen = (nSize * nCount + pstParam->nDataLen) > (pstParam->nTotalLen * 2)?(nSize * nCount + pstParam->nDataLen):(pstParam->nTotalLen * 2);
    	pTemBuf = (unsigned char *)realloc(pstParam->pData, pstParam->nTotalLen);
    	if (pTemBuf != NULL)
    	{
    		pstParam->pData = pTemBuf;
    	}
    	else
    	{
    		if (pstParam->pData != NULL)
    		{
    			free (pstParam->pData);
    		}
    		return 0;
    	}
        // 数据超出了值
    }

    memcpy(pstParam->pData + pstParam->nDataLen, pBuf, nSize * nCount);
    pstParam->nDataLen += nSize * nCount;

    return nSize * nCount;
}

/** @fn		IVMS_DECLARE int URLOPT_Init()
 *  @brief	模块初始化
 *	@return IVMS_DECLARE int    0表示成功，否则失败
 */
int URLOPT_Init()
{
    if (g_nInitCount == 0)
    {
        CURLcode    nRet   = CURLE_OK;

        nRet     = curl_global_init(CURL_GLOBAL_ALL);
        if (nRet != CURLE_OK)
        {
            printf("curl_global_init error %d\n", nRet);

            return HPR_ERROR;
        }


    }

    g_nInitCount ++;

    return HPR_OK;
}

/** @fn		IVMS_DECLARE void URLOPT_Fini()
 *  @brief	模块销毁
 *	@return IVMS_DECLARE void
 */
void URLOPT_Fini()
{
    if (g_nInitCount > 0)
    {
        g_nInitCount --;
        if (g_nInitCount == 0)
        {
            curl_global_cleanup();
        }
    }
}


/** @fn		int URLOPT_PostFile(char *szUrl, unsigned char *pData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	上传图片
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pData    上传的数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-I	 - unsigned char * pOutData 传出 数据
 *	@param	-I	 - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_PostFile(char *szUrl, unsigned char *pData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
{
    if (szUrl   == NULL ||
        pData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

    CURL                    *pHandle        = NULL;
    CURLcode                nRet            = CURLE_OK;
    curl_slist              *pOptionList    = NULL;
    curl_httppost           *pFormPost      = NULL;
    curl_httppost           *pLastElem      = NULL;
    char                    szName[32]      = {0};
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));
    sprintf(szName, "%ld.jpg", time(NULL));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    pOptionList = curl_slist_append(pOptionList, "Expect:");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);



    (void)curl_formadd(&pFormPost, &pLastElem,
        CURLFORM_COPYNAME, "image",
        CURLFORM_BUFFER, szName,
        CURLFORM_BUFFERPTR, pData,
        CURLFORM_BUFFERLENGTH, nInLen,
        CURLFORM_CONTENTTYPE, "image",
        CURLFORM_END);

	/* POST 参数*/
	//curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pData);
	/* POST 参数的大小*/
	//curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, pFormPost);
    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);

    //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	/*设置5S超时时间*/
 	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);


    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
        curl_formfree(pFormPost);
		curl_slist_free_all(pOptionList);
        return nRet;

    }
    curl_easy_cleanup(pHandle);
    curl_formfree(pFormPost);
	curl_slist_free_all(pOptionList);

    *pOutLen    = stParam.nDataLen;
    return HPR_OK;
}




/** @fn		int URLOPT_PostFile_Str(char *szUrl, std::string strData, std::string &strOutData, unsigned int &pOutLen, unsigned int nTimeOut)
 *  @brief	上传图片
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - std::string strData    上传的数据
 *	@param	-O	 - std::string &strOutData  传出 数据
 *	@param	-O	 - unsigned int &pOutLen    长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_PostFile_Str(char *szUrl, std::string strData, std::string &strOutData, unsigned int &pOutLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut)
{
    if (szUrl == NULL || NULL == pstruParams)
    {
        return HPR_ERROR;
    }

    CURL                    *pHandle        = NULL;
    CURLcode                nRet            = CURLE_OK;
    curl_slist              *pOptionList    = NULL;
    curl_httppost           *pFormPost      = NULL;
    curl_httppost           *pLastElem      = NULL;
    char                    szName[32]      = {0};
    IVMS_URL_GET_CB_PARAM_STRING   stParam;

	stParam.fileFd = NULL;
	stParam.nDataLen = 0;
	stParam.nTotalLen = 0;
	stParam.strData = "";

	//memset(&stParam,	 0,  sizeof(stParam));
#if 0
	stParam.nTotalLen	= *pLen;
	stParam.nDataLen 	= 0;
	stParam.strData		  = strOutData;
#endif

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    pOptionList = curl_slist_append(pOptionList, "Expect:");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
	HPR_Strncpy(szName, pstruParams->szFileName, sizeof(szName));
	if (NULL != pstruParams && 0 != strlen(pstruParams->szAuthBuff))
    {
        pOptionList = curl_slist_append(pOptionList, pstruParams->szAuthBuff);    //算法仓库认证
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }
    if (NULL != pstruParams && 0 != strlen(pstruParams->szHeaderToken))
    {
        char szAppendToken[256] = {0};
        snprintf(szAppendToken, sizeof(szAppendToken), "token:%s", pstruParams->szHeaderToken);
        pOptionList = curl_slist_append(pOptionList, szAppendToken);    //增加校验token
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }
	
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	(void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, 0); 

	

	(void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, 0); 

    (void)curl_formadd(&pFormPost, &pLastElem,
        CURLFORM_PTRNAME, szName,
        CURLFORM_BUFFER, szName,
        CURLFORM_BUFFERPTR, strData.c_str(),
        CURLFORM_BUFFERLENGTH, strData.size(),
        //CURLFORM_CONTENTTYPE, "bin",
        CURLFORM_END);

	 

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, pFormPost);
    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);

    //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBackString);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&strOutData);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	/*设置5S超时时间*/
 	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);


    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
        curl_formfree(pFormPost);
		curl_slist_free_all(pOptionList);
        return nRet;

    }
    curl_easy_cleanup(pHandle);
    curl_formfree(pFormPost);
	curl_slist_free_all(pOptionList);

	pOutLen  = (unsigned int)strOutData.size();
    
    return HPR_OK;
}





/** @fn		int URLOPT_Post(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
{
    IVMS_URL_GET_CB_PARAM   stParam;
    HPR_INT32   iRet        = HPR_ERROR;
    long long int   i64HttpCode;
    CURL       *pHandle     = NULL;
    CURLcode    nRet        = CURLE_OK;
	curl_slist *pOptionList = NULL;

    if (szUrl   == NULL || pInData == NULL || nInLen  <= 0 || pOutLen == NULL || pOutData == NULL)
    {
        return HPR_ERROR;
    }

    do
    {
        memset(&stParam,    0,  sizeof(stParam));

        stParam.nTotalLen    = *pOutLen;
        stParam.nDataLen     = 0;
        stParam.pData        = pOutData;

        pHandle      = curl_easy_init();
        if (pHandle  == NULL)
        {
            break;
        }

        (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);
        //url地址
        (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
        //post参数

        (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
        (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

         //对返回的数据进行操作的函数地址
        (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
        //这是write_data的第四个参数值
        (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
        //设置问非0表示本次操作为post
        (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);

        /* 避免产生超时信号,配合TIMEOUT使用 */
        (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
        (void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
        (void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
        pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            break;
        }

        (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

        // 执行
        nRet = curl_easy_perform(pHandle);
        if (nRet != CURLE_OK)
        {
            //释放curl资源
            printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
            break;
        }

        (void)curl_easy_getinfo(pHandle, CURLINFO_RESPONSE_CODE, &i64HttpCode);
        if (i64HttpCode != 200)
        {
            printf("http return error![%lld]\n", i64HttpCode);
            iRet = i64HttpCode;
            break;
        }

        *pOutLen    = stParam.nDataLen;
        iRet = HPR_OK;
    }while(0);

    if (pHandle != NULL)
    {
        curl_easy_cleanup(pHandle);
    }

    if (pOptionList != NULL)
    {
        curl_slist_free_all(pOptionList);
    }

    return iRet;
}

int URLOPT_Post_Con(URLOPT_POST_CONDITION *pCondition)
{
    char *szUrl;
    unsigned char *pInData;
    unsigned int nInLen;
    unsigned char *pOutData;
    unsigned int *pOutLen;
    unsigned int nTimeOut;

    if (pCondition == NULL)
    {
        return HPR_ERROR;
    }

    szUrl = pCondition->szUrl;
    pInData = pCondition->pInData;
    nInLen = pCondition->nInLen;
    pOutData = pCondition->pOutData;
    pOutLen = pCondition->pOutLen;
    if (pCondition->nTimeOut < 5)
        nTimeOut = 5;
    else
        nTimeOut = pCondition->nTimeOut;

    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //post参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    //设置问非0表示本次操作为post
    (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

	pOptionList = curl_slist_append(pOptionList, get_accept_type(pCondition->eAcceptType));
	pOptionList = curl_slist_append(pOptionList, get_content_type(pCondition->eContenType));
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pOutLen    = stParam.nDataLen;
    return HPR_OK;
}

/** @fn		int URLOPT_Put(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 *///未验证 2018.9.25添加
int URLOPT_Put_Con(URLOPT_POST_CONDITION *pCondition)
{
    char *szUrl;
    unsigned char *pInData;
    unsigned int nInLen;
    unsigned char *pOutData;
    unsigned int *pOutLen;
    unsigned int nTimeOut;

    if (pCondition == NULL)
    {
        return HPR_ERROR;
    }

    szUrl = pCondition->szUrl;
    pInData = pCondition->pInData;
    nInLen = pCondition->nInLen;
    pOutData = pCondition->pOutData;
    pOutLen = pCondition->pOutLen;
    if (pCondition->nTimeOut < 5)
        nTimeOut = 5;
    else
        nTimeOut = pCondition->nTimeOut;

    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //put参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    //设置问非0表示本次操作为put
    (void)curl_easy_setopt(pHandle, CURLOPT_CUSTOMREQUEST, "PUT");
    //curl_easy_setopt(pHandle, CURLOPT_PUT,1);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

	pOptionList = curl_slist_append(pOptionList, get_accept_type(pCondition->eAcceptType));
	pOptionList = curl_slist_append(pOptionList, get_content_type(pCondition->eContenType));
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pOutLen    = stParam.nDataLen;
    return HPR_OK;
}

/** @fn		int URLOPT_Post_V2(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_V2(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
{
    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //post参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, (long)nInLen);

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    //设置问非0表示本次操作为post
    (void)curl_easy_setopt(pHandle, CURLOPT_POST, (long)1);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, (long)1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, (long)nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, (long)nTimeOut);
//	curl_easy_setopt(pHandle, CURLOPT_VERBOSE, 1);

	pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

 	// 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		//printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
		if (115 == errno)
		{
		    nRet = curl_easy_perform(pHandle);
		    if (nRet != CURLE_OK)
		    {
				//printf("curl_easy_perform error02![%d][%s]\n", nRet, curl_easy_strerror(nRet));
		        curl_easy_cleanup(pHandle);
				curl_slist_free_all(pOptionList);
		        return nRet;
		    }
		}
		else
		{
			//释放curl资源
	        curl_easy_cleanup(pHandle);
			curl_slist_free_all(pOptionList);
	        return HPR_ERROR;
		}
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pOutLen    = stParam.nDataLen;

    return HPR_OK;
}

/** @fn		int URLOPT_Post_With_Params_String(char *szUrl, unsigned char *pInData, unsigned int nInLen, std::string &strOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作，调用融合大数据ISAPI接口使用
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - std::string &strOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_With_Params_String(char *szUrl, const unsigned char *pInData, unsigned int nInLen, std::string &strOutData, unsigned int &pOutLen,  URLOPT_ADDITION_PARAMS *pstruParams,unsigned int nTimeOut)
{
    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0 ||
        pstruParams == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
	
    IVMS_URL_GET_CB_PARAM_STRING   stParam;
    stParam.fileFd = NULL;
    stParam.nDataLen = 0;
    stParam.nTotalLen = 0;
    stParam.strData = "";

    //memset(&stParam,    0,  sizeof(stParam));
#if 0
    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.strData        = strOutData;
#endif
    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
    	printf("curl_easy_init error\n");
        return HPR_ERROR;
    }
	

	(void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //post参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);
	/*basic认证*/
	if(HPR_TRUE == pstruParams->bBasic)
	{
		//(void)curl_easy_setopt(pHandle, CURLOPT_USERPWD, "user_hikrss:HikRSs_88075998");
		(void)curl_easy_setopt(pHandle, CURLOPT_USERPWD, pstruParams->szUserPwd);
		(void)curl_easy_setopt(pHandle, CURLOPT_HTTPAUTH , CURLAUTH_BASIC);
	}
	

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBackString);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, &strOutData);
    //设置问非0表示本次操作为post
    (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);
	
	(void)curl_easy_setopt(pHandle, CURLOPT_CRLF, 1); 
    //设置https
    if(pstruParams->bHttps)
    {
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, HPR_FALSE);//设定为不验证证书和HOST
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, HPR_FALSE);
    }

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

	

	pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	

	if(HPR_TRUE == pstruParams->burlencoded)
	{
		pOptionList = curl_slist_append(pOptionList, "Content-Type: application/x-www-form-urlencoded");
		if (NULL == pOptionList)
		{
			printf("curl_slist_append error\n");
			curl_easy_cleanup(pHandle);
			return HPR_ERROR;
		}
	}
	else
	{
		pOptionList = curl_slist_append(pOptionList, "Content-Type: application/json");
		if (NULL == pOptionList)
		{
			printf("curl_slist_append error\n");
			curl_easy_cleanup(pHandle);
			return HPR_ERROR;
		}
	}
	#if 1
	char szTemp[50] = {0};
	snprintf(szTemp,49,"Content-Length: %d",nInLen);
	std::string strConten;
	strConten.assign(szTemp,strlen(szTemp));

	pOptionList = curl_slist_append(pOptionList, strConten.c_str());
	if (NULL == pOptionList)
	{
		printf("curl_slist_append error\n");
		curl_easy_cleanup(pHandle);
		return HPR_ERROR;
	}
	#endif
		
	if(pstruParams->bHttps)
    {
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, HPR_FALSE);//设定为不验证证书和HOST
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, HPR_FALSE);
    }
	
	
	if (NULL != pstruParams && 0 != strlen(pstruParams->szAuthBuff))
	{
	    	pOptionList = curl_slist_append(pOptionList, pstruParams->szAuthBuff);    //算法仓库认证
	    	if (NULL == pOptionList)
	    	{
	        	printf("curl_slist_append error\n");
	        	curl_easy_cleanup(pHandle);
	        	return HPR_ERROR;
	    	}
	}

   	if (NULL != pstruParams && 0 != strlen(pstruParams->szHeaderToken))
	{
	    	char szAppendToken[256] = {0};
	    	snprintf(szAppendToken, sizeof(szAppendToken), "token:%s", pstruParams->szHeaderToken);
	    	pOptionList = curl_slist_append(pOptionList, szAppendToken);    //增加校验token
	    	if (NULL == pOptionList)
	    	{
	        	printf("curl_slist_append error\n");
	        	curl_easy_cleanup(pHandle);
	        	return HPR_ERROR;
	    	}
	}
	
	pOptionList = curl_slist_append(pOptionList, "Transfer-Encoding:");    //不进行分段传输
	if (NULL == pOptionList)
	{
    	printf("curl_slist_append Transfer error\n");
    	curl_easy_cleanup(pHandle);
    	return HPR_ERROR;
	}
	
	//(void)curl_easy_setopt(pHandle, CURLOPT_HTTP_TRANSFER_DECODING, 0);
	
	
	(void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	
	
    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    pOutLen    = (unsigned int)strOutData.size();
    //strOutData = stParam.strData;
    return HPR_OK;
}


/** @fn		int URLOPT_Post_isapi(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作，调用融合大数据ISAPI接口使用
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_With_Params(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char *pOutData, unsigned int *pOutLen,  URLOPT_ADDITION_PARAMS *pstruParams,unsigned int nTimeOut)
{
    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //post参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    //设置问非0表示本次操作为post
    (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);
    //设置https
    if(pstruParams->bHttps)
    {
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, HPR_FALSE);//设定为不验证证书和HOST
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, HPR_FALSE);
    }

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

	pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
		curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	pOptionList = curl_slist_append(pOptionList, "Content-Type: application/json");
	if (NULL == pOptionList)
	{
		printf("curl_slist_append error\n");
		curl_easy_cleanup(pHandle);
		return HPR_ERROR;
	}

	#if 1
	char szTemp[50] = {0};
	snprintf(szTemp,49,"Content-Length: %d",nInLen);
	std::string strConten;
	strConten.assign(szTemp,strlen(szTemp));

	pOptionList = curl_slist_append(pOptionList, strConten.c_str());
	if (NULL == pOptionList)
	{
		printf("curl_slist_append error\n");
		curl_easy_cleanup(pHandle);
		return HPR_ERROR;
	}
	#endif


	if (NULL != pstruParams && 0 != strlen(pstruParams->szAuthBuff))
	{
	    	pOptionList = curl_slist_append(pOptionList, pstruParams->szAuthBuff);    //算法仓库认证
	    	if (NULL == pOptionList)
	    	{
        		printf("curl_slist_append error\n");
        		curl_easy_cleanup(pHandle);
        		return HPR_ERROR;
	    	}
	}

   	if (NULL != pstruParams && 0 != strlen(pstruParams->szHeaderToken))
	{
	    	char szAppendToken[256] = {0};
	    	snprintf(szAppendToken, sizeof(szAppendToken), "token:%s", pstruParams->szHeaderToken);
	    	pOptionList = curl_slist_append(pOptionList, szAppendToken);    //增加校验token
	    	if (NULL == pOptionList)
	    	{
        		printf("curl_slist_append error\n");
        		curl_easy_cleanup(pHandle);
        		return HPR_ERROR;
	    	}
	}

	
	pOptionList = curl_slist_append(pOptionList, "Transfer-Encoding:");    //不进行分段传输
	if (NULL == pOptionList)
	{
    	printf("curl_slist_append Transfer error\n");
    	curl_easy_cleanup(pHandle);
    	return HPR_ERROR;
	}
	//(void)curl_easy_setopt(pHandle, CURLOPT_HTTP_TRANSFER_DECODING, 0);
	
	(void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pOutLen    = stParam.nDataLen;
    return HPR_OK;
}

/** @fn		int URLOPT_Post_isapi(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作，调用融合大数据ISAPI接口使用
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_isapi(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
{
    if (szUrl   == NULL ||
        pInData == NULL ||
        nInLen  <= 0    ||
        pOutLen == NULL ||
        pOutData == NULL)
    {
        return HPR_ERROR;
    }

	curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    stParam.nTotalLen    = *pOutLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pOutData;

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        return HPR_ERROR;
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);

    //url地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //post参数

    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
    (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);

     //对返回的数据进行操作的函数地址
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    //这是write_data的第四个参数值
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    //设置问非0表示本次操作为post
    (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

	pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	pOptionList = curl_slist_append(pOptionList, "Content-Type: application/json");
	if (NULL == pOptionList)
	{
		printf("curl_slist_append error\n");
		curl_easy_cleanup(pHandle);
		return HPR_ERROR;
	}
	(void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        //释放curl资源
		printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pOutLen    = stParam.nDataLen;
    return HPR_OK;
}


/** @fn		int URLOPT_Get(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut)
 *  @brief	URL的get命令
 *	@param	-I	 - char * szUrl             url
 *	@param	-O	 - unsigned char * pData    获取到的数据
 *	@param	-O&I - unsigned int * pLen      数据长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Get(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut)
{
    if (pData   == NULL ||
        szUrl   == NULL ||
        pLen    == NULL)
    {
        return HPR_ERROR;
    }

    curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
		printf("pHandle error\n");
        return HPR_ERROR;
    }

    stParam.nTotalLen    = *pLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pData;

    // 设置下载地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //设置写数据的函数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    // 设置回调参数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);

	pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
    /*设置重定向*/
    (void)curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1);


    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }

    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pLen   = stParam.nDataLen;

    return HPR_OK;
}


/** @fn		int URLOPT_Del(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut)
 *  @brief	URL的delete命令
 *	@param	-I	 - char * szUrl             url
 *	@param	-O	 - unsigned char * pData    获取到的数据
 *	@param	-O&I - unsigned int * pLen      数据长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Del(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut)
{
    if (pData   == NULL ||
        szUrl   == NULL ||
        pLen    == NULL)
    {
        return HPR_ERROR;
    }

    curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
    		printf("pHandle error\n");
        return HPR_ERROR;
    }

    stParam.nTotalLen    = *pLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pData;

    // 设置地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    // 设置写数据的函数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    // 设置回调参数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
	// 设置删除
	(void)curl_easy_setopt(pHandle, CURLOPT_CUSTOMREQUEST, "DELETE");

	/* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);

    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }

    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);

    *pLen   = stParam.nDataLen;

    return HPR_OK;
}
int OPS_URLOPT_Get(char *szUrl, char *szHeaderToken, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut)
{
    if (pData   == NULL ||
        szUrl   == NULL ||
        pLen    == NULL)
    {
        return HPR_ERROR;
    }
    curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;
    char szHeaderBuff[1024] = {0};
    memset(&stParam,    0,  sizeof(stParam));
    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
    	printf("pHandle error\n");
        return HPR_ERROR;
    }
    stParam.nTotalLen    = *pLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pData;
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
    snprintf(szHeaderBuff, sizeof(szHeaderBuff), "%s%s%s\r\n",
        "Accept: application/json\r\n",
        "Token: ",
        szHeaderToken);
	pOptionList = curl_slist_append(pOptionList, szHeaderBuff);
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
	(void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
	(void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
    (void)curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1);
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        curl_easy_cleanup(pHandle);
		curl_slist_free_all(pOptionList);
        return nRet;
    }
    curl_easy_cleanup(pHandle);
	curl_slist_free_all(pOptionList);
    *pLen   = stParam.nDataLen;
    return HPR_OK;
}


/**
 * @fn           : URLOPT_Get_With_Params_String
 * @brief        : 调用libcurl传入参数
 * @param  -I    : char *szUrl
 * @param  -I    : std::string &strOutData
 * @param  -I    : unsigned int *pLen
 * @param  -I    : URLOPT_ADDITION_PARAMS *pstruParams   新增各参数由该结构传入
 * @param  -I    : unsigned int nTimeOut
 * @return       :
 * @date         : 2019/06/26
 * @note         :
 */
int URLOPT_Get_With_Params_String(char *szUrl, std::string &strOutData, unsigned int &pLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut)
{
    if (szUrl   == NULL || pstruParams == NULL)
    {
        return HPR_ERROR;
    }

    curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM_STRING   stParam;

	stParam.fileFd = NULL;
	stParam.nDataLen = 0;
	stParam.nTotalLen = 0;
	stParam.strData = "";

	//memset(&stParam,	 0,  sizeof(stParam));
#if 0
	stParam.nTotalLen	= *pLen;
	stParam.nDataLen 	= 0;
	stParam.strData		  = strOutData;
#endif

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        printf("pHandle error\n");
        return HPR_ERROR;
    }


    // 设置下载地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //设置写数据的函数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBackString);
    // 设置回调参数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, &strOutData);

    //设置https
    if(pstruParams->bHttps)
    {
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, HPR_FALSE);//设定为不验证证书和HOST
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, HPR_FALSE);
    }

    pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    pOptionList = curl_slist_append(pOptionList, "Content-Type: application/json");//指定报文数据格式，避免被默认编码
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }

    if (NULL != pstruParams && 0 != strlen(pstruParams->szAuthBuff))
    {
        pOptionList = curl_slist_append(pOptionList, pstruParams->szAuthBuff);    //算法仓库认证
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }
    if (NULL != pstruParams && 0 != strlen(pstruParams->szHeaderToken))
    {
        char szAppendToken[256] = {0};
        snprintf(szAppendToken, sizeof(szAppendToken), "token:%s", pstruParams->szHeaderToken);
        pOptionList = curl_slist_append(pOptionList, szAppendToken);    //增加校验token
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    /* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
    (void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
    (void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
    /*设置重定向*/
    (void)curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1);


    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
        curl_slist_free_all(pOptionList);
        return nRet;
    }

    curl_easy_cleanup(pHandle);
    curl_slist_free_all(pOptionList);

	pLen  = (unsigned int)strOutData.size();
    //strOutData = stParam.strData;

    return HPR_OK;
}


/**
 * @fn           : URLOPT_Get_With_Params
 * @brief        : 调用libcurl传入参数
 * @param  -I    : char *szUrl
 * @param  -I    : unsigned char *pData
 * @param  -I    : unsigned int *pLen
 * @param  -I    : URLOPT_ADDITION_PARAMS *pstruParams   新增各参数由该结构传入
 * @param  -I    : unsigned int nTimeOut
 * @return       :
 * @date         : 2019/06/26
 * @note         :
 */
int URLOPT_Get_With_Params(char *szUrl, unsigned char *pData, unsigned int *pLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut)
{
    if (pData   == NULL ||
        szUrl   == NULL ||
        pLen    == NULL)
    {
        return HPR_ERROR;
    }

    curl_slist              *pOptionList    = NULL;
    CURL                    *pHandle    = NULL;
    CURLcode                 nRet        = CURLE_OK;
    IVMS_URL_GET_CB_PARAM   stParam;

    memset(&stParam,    0,  sizeof(stParam));

    pHandle      = curl_easy_init();
    if (pHandle  == NULL)
    {
        printf("pHandle error\n");
        return HPR_ERROR;
    }

    stParam.nTotalLen    = *pLen;
    stParam.nDataLen     = 0;
    stParam.pData        = pData;

    // 设置下载地址
    (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
    //设置写数据的函数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack);
    // 设置回调参数
    (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);

    //设置https
    if(pstruParams->bHttps)
    {
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, HPR_FALSE);//设定为不验证证书和HOST
        (void)curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, HPR_FALSE);
    }

    pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }
    pOptionList = curl_slist_append(pOptionList, "Content-Type: application/json");//指定报文数据格式，避免被默认编码
    if (NULL == pOptionList)
    {
        printf("curl_slist_append error\n");
        curl_easy_cleanup(pHandle);
        return HPR_ERROR;
    }

    if (NULL != pstruParams && 0 != strlen(pstruParams->szAuthBuff))
    {
        pOptionList = curl_slist_append(pOptionList, pstruParams->szAuthBuff);    //算法仓库认证
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }
    if (NULL != pstruParams && 0 != strlen(pstruParams->szHeaderToken))
    {
        char szAppendToken[256] = {0};
        snprintf(szAppendToken, sizeof(szAppendToken), "token:%s", pstruParams->szHeaderToken);
        pOptionList = curl_slist_append(pOptionList, szAppendToken);    //增加校验token
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            curl_easy_cleanup(pHandle);
            return HPR_ERROR;
        }
    }

    (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);

    /* 避免产生超时信号,配合TIMEOUT使用 */
    (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
    (void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
    (void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
    /*设置重定向*/
    (void)curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1);


    // 执行
    nRet = curl_easy_perform(pHandle);
    if (nRet != CURLE_OK)
    {
        printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
        //释放curl资源
        curl_easy_cleanup(pHandle);
        curl_slist_free_all(pOptionList);
        return nRet;
    }

    curl_easy_cleanup(pHandle);
    curl_slist_free_all(pOptionList);
    *pLen   = stParam.nDataLen;

    return HPR_OK;
}

/** @fn		URLOPT_Get()
 *  @brief	URL的curl下载命令
 *  @param  szUrl             [in]      url地址
 *  @param  nExcuteTimeout    [in]      下载超时时间
 *  @param  fileFd            [in]      下载的目的文件流
 *  @param  MaxLen            [in]      可下载的最大长度
 *  @param  pLen              [out]     下载到的长度
 *	@return HPR_INT32  0表示成功，否则失败
 */
HPR_INT32 URLOPT_GetHttp (const char *szUrl, HPR_INT32 nExcuteTimeout, FILE *fileFd, unsigned long MaxLen, unsigned long *pLen)
{
    HPR_INT32 iRetVal = HPR_ERROR;
    CURL *pHandle = NULL;

    do
    {
        if (NULL == szUrl || NULL == pLen || NULL == fileFd || 0 == MaxLen)
        {
            printf("Param Error! szUrl[%p], pLen:[%p], fileFd:[%p], MaxLen: %lu", szUrl, pLen, fileFd, MaxLen);
    		break;
        }
        printf("szUrl: %s, nExcuteTimeout: %d, MaxLen: %lu", szUrl, nExcuteTimeout, MaxLen);

        /* 初始化curl */
        pHandle = curl_easy_init();
        if (NULL == pHandle)
        {
            printf("curl_easy_init Error!");
            break;
        }

        /* 设置相关参数 */
        CURLcode res = CURLE_OK;
        IVMS_URL_GET_CB_PARAM stParam;
        memset(&stParam, 0, sizeof(stParam));
        stParam.nTotalLen = MaxLen;
        stParam.nDataLen = 0;
        stParam.fileFd = fileFd;

        #if 1
        if (CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_URL, szUrl))                       //设置下载地址
            || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetFileCallBack)) //设置写数据的函数
            || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam))    //设置回调参数
            || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_FOLLOWLOCATION, 1))             //设置url重定向爬取功能
            //|| CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT_MS, 1000L))      //设置连接超时
            //|| CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_TIMEOUT_MS, nExcuteTimeout))    //add by yexiaoyogn 10 second time out
			|| CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_LOW_SPEED_LIMIT, 1))   //最低速率 1字节每秒  动态超时设置
			|| CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_LOW_SPEED_TIME, 10))   //低于最低速率的最长时间10s  动态超时设置
            || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 3))                   //add yexiaoyong set time out
    	    || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYPEER, false))         //设置认证问题
    	    || CURLE_OK != (res = curl_easy_setopt(pHandle, CURLOPT_SSL_VERIFYHOST, false)))        //设置认证问题
        {
            printf("curl_easy_setopt Error! %x,%s", res, curl_easy_strerror(res));

            break;
        }

        /* 执行并获取结果信息*/
        printf("curl_easy_perform Start!");
        res = curl_easy_perform(pHandle);
        if (res != CURLE_OK)
        {
            printf("curl_easy_setopt Error! %#x,%s", res, curl_easy_strerror(res));
            break;
        }
        printf("curl_easy_perform End!");

        HPR_LONG nStatCode = 0;
        res = curl_easy_getinfo(pHandle, CURLINFO_RESPONSE_CODE , &nStatCode);
        if (res != CURLE_OK || nStatCode != 200)
        {
            printf("curl_easy_getinfo Error! res: %#x,%s, nStatCode: %ld", res, curl_easy_strerror(res), nStatCode);
            *pLen = 0;
            break;
        }
        else
        {
            printf("curl_easy_getinfo Success! nStatCode: %ld, nDataLen: %d", nStatCode, stParam.nDataLen);
            *pLen = stParam.nDataLen;
        }
        #endif

        iRetVal = HPR_OK;
    }while(0);

    if (NULL != pHandle)
    {
        curl_easy_cleanup(pHandle);
        pHandle = NULL;
    }

    return iRetVal;
}

static char dec2hex(short int c)
{
    if (0 <= c && c <= 9)
    {
        return c + '0';
    }
    else if (10 <= c && c <= 15)
    {
        return c + 'A' - 10;
    }
    else
    {
        return -1;
    }
}

/**
 * @fn           : URLEncodeString
 * @brief        : url编码
 * @param  -I    : const char *szUrl,输入待编码url
 * @param  -I    : int len,输入url长度
 * @param  -I    : std::string & strEncodeUrl, 输出编码过的url
 * @return       :
 * @date         : 2022/05/26
 * @note         :
 */
HPR_VOID URLEncodeString(const char *szurl, int len, std::string & strEncodeUrl)
{
	if(szurl == NULL)
	{
		return;
	}
    int i = 0;
    //len = strlen(url);
    for (i = 0; i < len; ++i)
	{
        char c = szurl[i];
        if (    ('0' <= c && c <= '9') ||
                ('a' <= c && c <= 'z') ||
                ('A' <= c && c <= 'Z') ||
                c == '/' || c == '.' || c == '&' || c == '_' || c == '=' || c == ':'||c == '?')
        {
			strEncodeUrl.push_back(c);
        }
        else
        {
            int j = (short int)c;
            if (j < 0)
                j += 256;
            int i1, i0;
            i1 = j / 16;
            i0 = j - i1 * 16;
			strEncodeUrl.push_back('%');
			strEncodeUrl.push_back(dec2hex(i1));
			strEncodeUrl.push_back(dec2hex(i0));
        }
	}
	strEncodeUrl.push_back('\0');
}



#if 0
/** @fn		int URLOPT_Post_malloc_result(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char **pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_malloc_result(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char **pOutData, unsigned int *pOutLen, unsigned int nTimeOut)
{
	curl_slist   *pOptionList = NULL;
    CURL         *pHandle     = NULL;
    CURLcode      nRet        = CURLE_OK;
    HPR_INT32     iRet        = HPR_ERROR;
    long long int i64HttpCode;
    IVMS_URL_GET_CB_PARAM   stParam;

    if (szUrl == NULL || pInData == NULL || nInLen  <= 0 || pOutLen == NULL || pOutData == NULL)
    {
        return HPR_ERROR;
    }

    do
    {
        memset(&stParam,    0,  sizeof(stParam));

        stParam.nTotalLen    = *pOutLen;
        stParam.nDataLen     = 0;
        stParam.pData = (unsigned char *)malloc(*pOutLen);
        if (stParam.pData == NULL)
        {
            break;
        }

        pHandle      = curl_easy_init();
        if (pHandle  == NULL)
        {
            break;
        }

        (void)curl_easy_setopt(pHandle, CURLOPT_HTTPPOST, 1);
        //url地址
        (void)curl_easy_setopt(pHandle, CURLOPT_URL, szUrl);
        //post参数
        (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDS, pInData);
        (void)curl_easy_setopt(pHandle, CURLOPT_POSTFIELDSIZE, nInLen);
         //对返回的数据进行操作的函数地址
        (void)curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, GetOptCallBack_);
        //这是write_data的第四个参数值
        (void)curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, (void*)&stParam);
        //设置问非0表示本次操作为post
        (void)curl_easy_setopt(pHandle, CURLOPT_POST,1);
        /* 避免产生超时信号,配合TIMEOUT使用 */
        (void)curl_easy_setopt(pHandle, CURLOPT_NOSIGNAL, 1);
        (void)curl_easy_setopt(pHandle, CURLOPT_CONNECTTIMEOUT, nTimeOut);
        (void)curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, nTimeOut);
        pOptionList = curl_slist_append(pOptionList, "Accept: application/json");
        if (NULL == pOptionList)
        {
            printf("curl_slist_append error\n");
            break;
        }
        (void)curl_easy_setopt(pHandle, CURLOPT_HTTPHEADER, pOptionList);
        // 执行
        nRet = curl_easy_perform(pHandle);
        if (nRet != CURLE_OK)
        {
            //释放curl资源
            printf("curl_easy_perform error![%d][%s]\n", nRet, curl_easy_strerror(nRet));
            break;
        }

        (void)curl_easy_getinfo(pHandle, CURLINFO_RESPONSE_CODE, &i64HttpCode);
        if (i64HttpCode != 200)
        {
            printf("http return error![%lld]\n", i64HttpCode);
            iRet = i64HttpCode;
            break;
        }

        *pOutLen    = stParam.nDataLen;
        *pOutData  = stParam.pData;

        iRet = HPR_OK;
    }while(0);

    if (pHandle != NULL)
    {
        curl_easy_cleanup(pHandle);
    }

    if (pOptionList != NULL)
    {
        curl_slist_free_all(pOptionList);
    }

    if (iRet != HPR_OK)
    {
        HPR_SAFE_FREE(stParam.pData);
    }
    return iRet;
}
#endif
