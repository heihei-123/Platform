#include "param.h"

int add_parse_node_val(const char *pOutData)
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

		FILE *file = fopen("addnode_data.txt", "w");
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
函    数    名:add_node
函  数  描  述:添加授权节点
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int add_node(ADDNodeInfo *pAddNode, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[2048] = {0}; 
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);

	do
	{
		if (NULL == pAddNode)
		{
			break;
		}

	    snprintf(szBody, sizeof(szBody), "{\"nodeInfoList\":[");

        // 遍历 pAddNode 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1,
            "{\"index\":\"%s\",\"nodeName\":\"%s\",\"nodeIp\":\"%s\",\"nodePort\":%d}",
            pAddNode[i].index, pAddNode[i].nodeName, pAddNode[i].nodeIp, pAddNode[i].nodePort);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);

		//printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), RESTFUL_ADDNODE, pAddr, g_restful_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = add_parse_node_val(szOutData);
	}while(0);

	return iRetVal;
}


int query_parse_node_val(char *pAutInfo)
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

		FILE *file = fopen("querynode_data.txt", "w");
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
函    数    名:query_node
函  数  描  述:查询已授权节点
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int query_node(const char *pAddr)
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

		snprintf(szUrl, sizeof(szUrl), RESTFUL_QUENODE, pAddr, g_restful_port);
		iRetVal = URLOPT_Get(szUrl, (HPR_UINT8 *)szReturn, (HPR_UINT32 *)&nLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR("get [%s] faild! retval[%d]", szUrl, iRetVal);
			break;
		}

		iRetVal = query_parse_node_val(szReturn);
		if (HPR_OK != iRetVal)
		{
			break;
		}

		iRetVal = HPR_OK;
	}while(0);

	return iRetVal;
}

int delete_parse_node_val(const char *pOutData)
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

		FILE *file = fopen("deletenode_data.txt", "w");
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
函    数    名:delete_node
函  数  描  述:删除授权节点
输  入  参  数:
输  出  参  数:
返  回  类  型:int
备          注:
作          者:
时          间:
*************************************************************/
int delete_node(DeleteNodeInfo *pDeleteNode, const char *pAddr, int count)
{
	int iRetVal = HPR_ERROR;
	char szBody[2048] = {0}; 
	char szUrl[UTIL_MAX_URL_LEN] = {0};
	char szOutData[1024 * 4] = {0};
	int iLen = sizeof(szOutData);

	do
	{
		if (NULL == pDeleteNode)
		{
			break;
		}

	    snprintf(szBody, sizeof(szBody), "{\"nodeInfoList\":[");

        // 遍历 pDeleteNode 数据结构，并格式化为 JSON 字符串组装报文
        for (size_t i = 0; i < count; ++i) {
            if (i > 0) {
                strncat(szBody, ",", strlen(","));
            }
            snprintf(szBody + strlen(szBody), sizeof(szBody) - strlen(szBody) - 1, "{\"nodeID\":\"%s\"}", pDeleteNode[i].nodeID);
        }

        //字符串的结尾
        strncat(szBody, "]}\"", sizeof(szBody) - strlen(szBody) - 1);

		//printf("%s\n", szBody);

		snprintf(szUrl,sizeof(szUrl), RESTFUL_DELETENODE, pAddr, g_restful_port);

		DEMO_DEBUG("url:[%s]", szUrl);
		DEMO_DEBUG("body:[%s]", szBody);

		iRetVal = URLOPT_Post(szUrl, (HPR_UINT8 *)szBody, strlen(szBody), (HPR_UINT8 *)szOutData, (HPR_UINT32 *)&iLen, 5);
		if (HPR_OK != iRetVal)
		{
			DEMO_ERROR();
			break;
		}

		DEMO_DEBUG("%s", szOutData);
		iRetVal = delete_parse_node_val(szOutData);
	}while(0);

	return iRetVal;
}