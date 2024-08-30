#include "param.h"

int apply_parse_token_val(const char *pOutData)
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

		FILE *file = fopen("AllocateInfo_data.txt", "w");
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
函    数    名:apply_toke
函  数  描  述:申请令牌
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int apply_token(AllocateInfo *pAllocateInfo, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[2048] = {0}; 
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);

	do
	{
		if (NULL == pAllocateInfo)
		{
			break;
		}

	    snprintf(szBody, sizeof(szBody), "{\"allocateInfo\":[");

        // 遍历 pAllocateInfo 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1, "{\"index\":\"%s\",\"targetType\":\"%s\",\
            \"source\":\"%s\",\"require\":%d,\"bAutoExpand\":%d}", pAllocateInfo[i].index, pAllocateInfo[i].targetType,
            pAllocateInfo[i].source, pAllocateInfo[i].require, pAllocateInfo[i].bAutoExpand);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);

		//printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), RESTFUL_ALLOCATE, pAddr, g_restful_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = apply_parse_token_val(szOutData);
	}while(0);

	return iRetVal;
}