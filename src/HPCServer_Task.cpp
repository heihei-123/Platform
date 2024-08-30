#include "param.h"

int set_parse_task_val(const char *pOutData)
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

		FILE *file = fopen("settask_data.txt", "w");
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
函    数    名:set_task
函  数  描  述:下发任务
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int set_task(TaskListInfo *pSetTask, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);
	do
	{
		if (NULL == pSetTask)
		{
			break;
		}

		snprintf(szBody, sizeof(szBody), "{\"taskList\":[");

        // 遍历 pSetTask 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1,
            "{\"taskId\":\"%s\",\"nodeId\":\"%s\",\"algorithmId\":\"%s\",\"taskType\":\"%s\",\"resourceType\":\"%s\",\"resource\":%f,\"taskInfo\":{}}", 
            pSetTask[i].taskId, pSetTask[i].nodeId, pSetTask[i].algorithmId, pSetTask[i].taskType, pSetTask[i].resourceType, pSetTask[i].resource);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);
		printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), ENGINE_SETTASKINFO, pAddr, g_engine_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = set_parse_task_val(szOutData);
	}while(0);

	return iRetVal;
}
/*
int get_parse_task_val(const char *pOutData)
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

		FILE *file = fopen("gettask_data.txt", "w");
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
*/
/*************************************************************
函    数    名:get_task
函  数  描  述:历史任务查询
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
/*
int get_task(HistoryTaskInfo pGetTask, const char *pAddr)
{
	int iRetVal = HPR_ERROR;
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);
	do
	{
        snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1,
        "{\"taskId\":\"%s\",\"nodeId\":\"%s\",\"taskFinishStatus\":\"%s\",\"taskNumber\":%d}", 
        pGetTask.taskId, pGetTask.nodeId, pGetTask.taskFinishStatus, pGetTask.taskNumber);
        

		snprintf(szUrl,sizeof(szUrl), ENGINE_GETTASKINFO, pAddr, g_engine_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = get_parse_task_val(szOutData);
	}while(0);

	return iRetVal;
}
*/

int get_parse_task_val(const char *pOutData)
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

		FILE *file = fopen("gettask_data.txt", "w");
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
函    数    名:get_task
函  数  描  述:任务状态查询
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int get_task(TaskStatusInfo *pGetTask, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);
	do
	{
		if (NULL == pGetTask)
		{
			break;
		}

		snprintf(szBody, sizeof(szBody), "{\"taskList\":[");

        // 遍历 pGetTask 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1, "{\"taskId\":\"%s\"}", pGetTask[i].taskId);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);
		printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), ENGINE_GETTASKINFO, pAddr, g_engine_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = get_parse_task_val(szOutData);
	}while(0);

	return iRetVal;
}


int delete_parse_task_val(const char *pOutData)
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

		FILE *file = fopen("deletetask_data.txt", "w");
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
函    数    名:delete_task
函  数  描  述:删除任务
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int delete_task(DeleteTaskInfo *pDeletetTask, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[1024] = {0};           //组装的最终报文
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);
	do
	{
		if (NULL == pDeletetTask)
		{
			break;
		}

		snprintf(szBody, sizeof(szBody), "{\"taskList\":[");

        // 遍历 pSetTask 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1, "{\"taskId\":\"%s\"}", pDeletetTask[i].taskId);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);
		printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), ENGINE_DELETETASK, pAddr, g_engine_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = delete_parse_task_val(szOutData);
	}while(0);

	return iRetVal;
}