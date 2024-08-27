#include "param.h"

int restful_parse_session_val(char *pAutInfo, RESG_PARAM *pstSessInfo)
{
	int iRetVal = HPR_ERROR;
	cJSON *pRoot = NULL;
	cJSON *pItem = NULL;

	do
	{
		if (NULL == pAutInfo || NULL == pstSessInfo)
		{
			DEMO_ERROR ("param is null!pAutInfo[%p] pSessInfo[%p]", pAutInfo, pstSessInfo);
			break;
		}

		DEMO_INFO ("%s", pAutInfo);
		pRoot = cJSON_Parse(pAutInfo);
		if (NULL == pRoot)
		{
			break;
		}

		pItem = cJSON_GetObjectItem(pRoot, "errorCode");
		if (NULL == pItem || pItem->type != cJSON_Number || pItem->valueint != 0)
		{
			break;
		}

		cJSON *pData = cJSON_GetObjectItem(pRoot, "data");
		if (NULL != pData)
		{
			pItem = cJSON_GetObjectItem(pData, "sessionID");
			if (pItem != NULL && pItem->type == cJSON_String && pItem->valuestring != NULL)
			{
				strcpy(pstSessInfo->szSession, pItem->valuestring);
			}

			pItem = cJSON_GetObjectItem(pData, "challenge");
			if (pItem != NULL && pItem->type == cJSON_String && pItem->valuestring != NULL)
			{
				strcpy(pstSessInfo->szChallenge, pItem->valuestring);
			}

			pItem = cJSON_GetObjectItem(pData, "iterations");
			if (pItem != NULL && pItem->type == cJSON_Number)
			{
				pstSessInfo->iIterations = pItem->valueint;
			}

			pItem = cJSON_GetObjectItem(pData, "isIrreversible");
			if (pItem != NULL && pItem->type == cJSON_Number)
			{
				pstSessInfo->bIrrerverible = (pItem->valueint == 1);
			}

			pItem = cJSON_GetObjectItem(pData, "salt");
			if (pItem != NULL && pItem->type == cJSON_String && pItem->valuestring != NULL)
			{
				strcpy(pstSessInfo->szSalt, pItem->valuestring);
				//printf("%s", pItem->valuestring);
			}
		}

		FILE *file = fopen("register_data.txt", "w");
    	if (file == NULL) {
        	printf("Failed to open file.\n");
    	}
		fprintf(file, "%s", pAutInfo);
		fclose(file);

		iRetVal = HPR_OK;
	}while(0);

	printf("%s\n", pAutInfo);

	if (NULL != pRoot)
	{
		cJSON_Delete(pRoot);
		pRoot = NULL;
	}

	return iRetVal;
}


/*************************************************************
函    数    名:restful_getSession
函  数  描  述:获取认证session
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int restful_getSession(RESG_PARAM *pstSessInfo, const char *pAddr)
{
	int iRetVal = HPR_ERROR;
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szReturn[2048] = {0};
	int nLen = sizeof(szReturn);

	do
	{
		if (NULL == pstSessInfo || NULL == pAddr)
		{
			break;
		}

		snprintf(szUrl, sizeof(szUrl), RESTFUL_GET_SESSION, pAddr, g_restful_port);
		iRetVal = URLOPT_Get(szUrl, (HPR_UINT8 *)szReturn, (HPR_UINT32 *)&nLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR("get [%s] faild! retval[%d]", szUrl, iRetVal);
			break;
		}

		iRetVal = restful_parse_session_val(szReturn, pstSessInfo);
		if (HPR_OK != iRetVal)
		{
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	

	return iRetVal;
}


int restful_parse_register_val(const char *pOutData)
{
	int iRetVal = HPR_ERROR;
	cJSON *pRoot = NULL;
	cJSON *pItem = NULL;

	do
	{
		if (NULL == pOutData)
		{
			break;
		}

		pRoot = cJSON_Parse(pOutData);
		if (NULL == pRoot)
		{
			break;
		}

		pItem = cJSON_GetObjectItem(pRoot, "errorCode");
		if (NULL == pItem)
		{
			break;
		}

		if (pItem->valueint != 0)
		{
			iRetVal = pItem->valueint;
			pItem = cJSON_GetObjectItem(pRoot, "errorMsg");
			if (pItem != NULL && pItem->valuestring != NULL)
			{
				DEMO_ERROR("errorMsg[%s]", pItem->valuestring);
				break;
			}
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	printf("%s\n", pOutData);
	if (NULL != pRoot)
	{
		cJSON_Delete(pRoot);
		pRoot = NULL;
	}

	return iRetVal;
}

/*************************************************************
函    数    名:restful_register
函  数  描  述:客户端注册认证
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int restful_register(RESG_PARAM *pResgParam, const char *pAddr)
{
	int iRetVal = HPR_ERROR;
	char szCodePW[ENGINE_CHAR_64 * 2] = {0}; //sha256加密后的密码
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);

	do
	{
		if (NULL == pResgParam)
		{
			break;
		}

		char szTmp[ENGINE_CHAR_64 * 4] = {0};
		if (pResgParam->bIrrerverible == 0)
		{
			/*当设备要求不可逆密码存储时
			SHA256 ((SHA256(password)+ challenge)) [iterations-1]*/
			//HPR_Snprintf(szTmp, sizeof(szTmp), "%s%s", pResgParam->szPassword, pResgParam->szChallenge);
			sha256_encode(pResgParam->szPassword, strlen(pResgParam->szPassword), szCodePW);
			snprintf(szTmp, sizeof(szTmp), "%s%s", szCodePW, pResgParam->szChallenge);
			sha256_encode(szTmp, strlen(szTmp), szCodePW);
		}else
		{
			/*当设备支持可逆密码存储时
			SHA256 ((SHA256(user, salt, password)+ challenge)) [iterations-1]*/
			snprintf(szTmp, sizeof(szTmp), "%s%s%s", pResgParam->szUserName, pResgParam->szSalt, pResgParam->szPassword);
			sha256_encode(szTmp, strlen(szTmp), szCodePW);
			snprintf(szTmp, sizeof(szTmp), "%s%s", szCodePW, pResgParam->szChallenge);
			sha256_encode(szTmp, strlen(szTmp), szCodePW);
		}

		for (char i = 1; i < pResgParam->iIterations; i++)
		{
			memset(szTmp, 0, sizeof(szTmp));
			snprintf(szTmp, sizeof(szTmp), "%s", szCodePW);


			memset(szCodePW, 0, sizeof(szCodePW));
			sha256_encode(szTmp, strlen(szTmp), szCodePW);
			DEMO_INFO("sha[%d]:tmp[%s] pw[%s]", i, szTmp, szCodePW);
		}
		snprintf(szBody, sizeof(szBody), ENGINE_RES_PARAM, pResgParam->szUserName, szCodePW, pResgParam->szSession);

		snprintf(szUrl,sizeof(szUrl), RESTFUL_REGISTER, pAddr, g_restful_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = restful_parse_register_val(szOutData);

	}while(0);

	return iRetVal;
}
/*
static int restful_parse_delchecked_val(const char *pOutData)
{
	int iRetVal = HPR_ERROR;
	cJSON *pRoot = NULL;
	cJSON *pItem = NULL;

	do
	{
		if (NULL == pOutData)
		{
			break;
		}

		pRoot = cJSON_Parse(pOutData);
		if (NULL == pRoot)
		{
			break;
		}

		pItem = cJSON_GetObjectItem(pRoot, "errorCode");
		if (NULL == pItem)
		{
			break;
		}

		if (pItem->valueint != 1)
		{
			iRetVal = pItem->valueint;
			pItem = cJSON_GetObjectItem(pRoot, "errorMsg");
			if (pItem != NULL && pItem->valuestring != NULL)
			{
				//ENGINE_ERR("errorMsg[%s]", pItem->valuestring);
			}
			break;
		}

        pItem = cJSON_GetObjectItem(pRoot, "statusCode");
		if (NULL == pItem)
		{
			break;
		}

		if (pItem->valueint != 1)
		{
			iRetVal = pItem->valueint;
			pItem = cJSON_GetObjectItem(pRoot, "subStatusCode");
			if (pItem != NULL && pItem->valuestring != NULL)
			{
				//ENGINE_ERR("subStatusCode[%s]", pItem->valuestring);
			}
            pItem = cJSON_GetObjectItem(pRoot, "statusString");
            if (pItem != NULL && pItem->valuestring != NULL)
			{
				//ENGINE_ERR("statusString[%s]", pItem->valuestring);
			}
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	if (NULL != pRoot)
	{
		cJSON_Delete(pRoot);
		pRoot = NULL;
	}

	return iRetVal;
}
*/

/*************************************************************
函    数    名:restful_delchecked
函  数  描  述:删除已认证的客户端
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
/*
static int restful_delchecked(const char *pAddr)
{
    int iRetVal = HPR_ERROR;
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szReturn[2048] = {0};
	int nLen = sizeof(szReturn);

	do
	{
		if (NULL == pAddr)
		{
			break;
		}

		HPR_Snprintf(szUrl, sizeof(szUrl), RESTFUL_DELCHECKED_SESSION, pAddr, g_restful_port);
		iRetVal = URLOPT_Get(szUrl, (HPR_UINT8 *)szReturn, (HPR_UINT32 *)&nLen, 5);
		if (HPR_OK != iRetVal)
		{
			//ENGINE_ERR ("get [%s] faild! retval[%d]", szUrl, iRetVal);
			break;
		}

		iRetVal = restful_parse_delchecked_val(szReturn);
		if (HPR_OK != iRetVal)
		{
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	return iRetVal;
}
*/
