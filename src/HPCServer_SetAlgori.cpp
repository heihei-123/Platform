#include "param.h"

int set_parse_algori_val(const char *pOutData)
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
			}
			break;
		}

		FILE *file = fopen("setalgori_data.txt", "w");
    	if (file == NULL) {
        	printf("Failed to open file.\n");
        	return -1;
    	}

		fprintf(file, "%s", pOutData);
		fclose(file);

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
函    数    名:set_algori
函  数  描  述:算法分配
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int set_algori(AlgorithmInfo *pSetAlgori, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);
	do
	{
		if (NULL == pSetAlgori)
		{
			break;
		}

		snprintf(szBody, sizeof(szBody), "{\"algorithmInfoList\":[");

        // 遍历 pSetAlgori 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1,
            "{\"nodeId\":\"%s\",\"algorithmId\":\"%s\",\"url\":\"%s\",\"md5\":\"%s\",\"authorizedAbilityId\":\"%s\",\"authorizedAbilityIdList\":\"%s\",\
			\"authorized\":\"%s\",\"algAuthAddress\":\"%s\",\"allocateAbility\":%d,\"allocateResource\":%f,\"algorithmInfo\":{\
			\"algorithmconfig\":\"%s\",\"adjustConfig\":\"%s\",\"vendorId\":\"%s\",\"targetType\":\"%s\",\"modelVersion\":\"%s\"}}",
            pSetAlgori[i].nodeId, pSetAlgori[i].algorithmId, pSetAlgori[i].url, pSetAlgori[i].md5,
			pSetAlgori[i].authorizedAbilityId, pSetAlgori[i].authorizedAbilityIdList, pSetAlgori[i].authorized,
			pSetAlgori[i].algAuthAddress, pSetAlgori[i].allocateAbility, pSetAlgori[i].allocateResource, 
			pSetAlgori[i].algorithmInfo.algorithmconfig, pSetAlgori[i].algorithmInfo.adjustConfig, pSetAlgori[i].algorithmInfo.vendorId,
			pSetAlgori[i].algorithmInfo.targetType, pSetAlgori[i].algorithmInfo.modelVersion);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);
		printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), ENGINE_SETALGORITHM, pAddr, g_engine_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = set_parse_algori_val(szOutData);
	}while(0);

	return iRetVal;
}



int get_parse_serverinfo_val(char *pAutInfo)
{
	int iRetVal = HPR_ERROR;
	cJSON *pRoot = NULL;
	cJSON *pItem = NULL;

	do
	{
		if (NULL == pAutInfo)
		{
			DEMO_ERROR ("param is null!pAutInfo[%p]", pAutInfo);
			break;
		}

		DEMO_INFO ("%s", pAutInfo);
		pRoot = cJSON_Parse(pAutInfo);
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
			}
			break;
		}

		FILE *file = fopen("getserverinfo_data.txt", "w");
    	if (file == NULL) {
        	printf("Failed to open file.\n");
        	return -1;
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
函    数    名:get_serverinfo
函  数  描  述:引擎节点查询
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int get_serverinfo(const char *pAddr)
{
	int iRetVal = HPR_ERROR;
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szReturn[204800] = {0};
	int nLen = sizeof(szReturn);

	do
	{
		if (NULL == pAddr)
		{
			break;
		}

		snprintf(szUrl, sizeof(szUrl), ENGINE_GETSERVERINFO, pAddr, g_engine_port);
		iRetVal = URLOPT_Get(szUrl, (HPR_UINT8 *)szReturn, (HPR_UINT32 *)&nLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR("get [%s] faild! retval[%d]", szUrl, iRetVal);
			break;
		}

		iRetVal = get_parse_serverinfo_val(szReturn);
		if (HPR_OK != iRetVal)
		{
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	return iRetVal;
}



int get_parse_algori_val(char *pAutInfo)
{
	int iRetVal = HPR_ERROR;
	cJSON *pRoot = NULL;
	cJSON *pItem = NULL;

	do
	{
		if (NULL == pAutInfo)
		{
			DEMO_ERROR ("param is null!pAutInfo[%p]", pAutInfo);
			break;
		}

		DEMO_INFO ("%s", pAutInfo);
		pRoot = cJSON_Parse(pAutInfo);
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
			}
			break;
		}

		FILE *file = fopen("getalgori_data.txt", "w");
    	if (file == NULL) {
        	printf("Failed to open file.\n");
        	return -1;
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
函    数    名:get_algori
函  数  描  述:获取算法信息
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int get_algori(const char *pAddr)
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

		snprintf(szUrl, sizeof(szUrl), ENGINE_GETALGORITHM, pAddr, g_algorithm_port);
		iRetVal = URLOPT_Get(szUrl, (HPR_UINT8 *)szReturn, (HPR_UINT32 *)&nLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR("get [%s] faild! retval[%d]", szUrl, iRetVal);
			break;
		}

		iRetVal = set_parse_algori_val(szReturn);
		if (HPR_OK != iRetVal)
		{
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	return iRetVal;
}
