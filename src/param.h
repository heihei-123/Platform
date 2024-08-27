#ifndef _PARAM_H_
#define _PARAM_H_

#include "util_urlopt.h"
#include "hlog1.h"
#include "cJSON/cJSON.h"
#include "openssl/sha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>

#define RESTFUL_GET_SESSION        "http://%s:%d/restful/authCMS/getSession?format=json"               //获取认证session
#define RESTFUL_REGISTER           "http://%s:%d/restful/authCMS/register?format=json"                 //客户端注册认证
//#define RESTFUL_DELCHECKED_SESSION  "http://%s:%d//restful/authCMS/delcheckedSession?format=json"       //删除已认证的客户端
#define RESTFUL_PORT (30080)
static int g_restful_port = RESTFUL_PORT;

#define ENGINE_GET_SESSION        "http://%s:%d/engine/rest/security/getSession"               //获取认证session
#define ENGINE_REGISTER           "http://%s:%d/engine/rest/security/register"                 //客户端注册认证
#define ENGINE_PORT (9090)
static int g_engine_port = ENGINE_PORT;


#define ENGINE_RES_PARAM  "{\"userName\":\"%s\",\"password\":\"%s\",\"sessionID\":\"%s\"}"      //注册报文

#define UTIL_MAX_URL_LEN (1024)
#define ENGINE_CHAR_64 (1024)

#define RESTFUL_ADDNODE        "http://%s:%d/restful/authCMS/addNode?format=json"              //添加授权节点
#define RESTFUL_QUENODE        "http://%s:%d/restful/authCMS/nodeList?format=json"             //查询已授权节点
#define RESTFUL_DELETENODE     "http://%s:%d/restful/authCMS/deleteNode?format=json"           //删除已授权节点

#define ENGINE_GETSERVERINFO       "http://%s:%d/engine/rest/algorithm/getServerInfo"            //引擎节点查询
#define ENGINE_SETALGORITHM        "http://%s:%d/engine/rest/algorithm/setAlgorithm"             //算法分配
#define ENGINE_GETALGORITHM        "http://%s:%d/algorithm"                                       //算法查询
#define ALGORITHM_PORT (9071)
static int g_algorithm_port = ALGORITHM_PORT;

#define RESTFUL_ALLOCATE           "http://%s:%d/restful/authCMS/allocate?format=json"           //申请令牌

#define ENGINE_SETTASKINFO        "http://%s:%d/engine/rest/task/setTaskInfo"                      //任务下发
//#define ENGINE_GETTASKINFO        "http://%s:%d/engine/rest/task/getHistoryTaskStatus"             //历史任务查询
#define ENGINE_GETTASKINFO        "http://%s:%d/engine/rest/task/getTaskStatus"                    //任务状态查询
#define ENGINE_DELETETASK         "http://%s:%d/engine/rest/task/deleteTask"                       //删除任务



//注册结构体
typedef struct _RESG_PARAM_
{
    int    iIterations;
    int    bIrrerverible;
    char     *szUserName;
    char     *szPassword;
    char     *szSession;
    char     *szChallenge;
    char     *szSalt;
}RESG_PARAM;

//添加授权结构体
typedef struct {
    char index[1024];
    char nodeName[1024];
    char nodeIp[1024];
    int  nodePort;
} ADDNodeInfo;
/*
//添加授权结构体
typedef struct {
    ADDNodeInfo *addnodeList;
}ADDNODE;
*/

//删除授权结构体
typedef struct{
    char nodeID[1024];
}DeleteNodeInfo;

// 算法信息结构体
typedef struct{
    char nodeId[1024];
    char algorithmId[1024];
    char url[1024];
    char md5[1024];
    char algorithmName[1024];
    char authorizedAbilityId[1024];
    char authorizedAbilityIdList[1024];
    char authorized[1024];
    char algAuthAddress[1024];
    int allocateAbility;
    float allocateResource;
    struct {
        char algorithmconfig[1024];
        char adjustConfig[1024];
        char vendorId[1024];
        char targetType[1024];
        char modelVersion[1024];
    } algorithmInfo;
} AlgorithmInfo;
/*
//算法分配结构体（算法列表）
typedef struct {
    AlgorithmInfo *algorithms;
} SETALGORITHM;
*/

//申请令牌结构体
typedef struct{
    char index[1024];
    char targetType[1024];
    char source[1024];
    int  require;
    int  bAutoExpand;
}AllocateInfo;

//下发任务结构体
typedef struct{
    char taskId[1024];
    char nodeId[1024];
    char algorithmId[1024];
    char taskType[1024];
    char resourceType[1024];
    float resource;
    typedef struct{
    }taskInfo;
}TaskListInfo;
/*
//历史任务查询结构体
typedef struct{
    char taskId[1024];
    char nodeId[1024];
    char taskFinishStatus[1024];
    int taskNumber;
}HistoryTaskInfo;
*/
typedef struct{
    char taskId[1024];
}TaskStatusInfo;

//删除任务结构体
typedef struct{
    char taskId[1024];
}DeleteTaskInfo;

// 获取认证Session_AuthCMS
int restful_parse_session_val(char *pAutInfo, RESG_PARAM *pstSessInfo);

int restful_getSession(RESG_PARAM *pstSessInfo, const char *pAddr);

//客户端认证注册_AuthCMS
int restful_parse_register_val(const char *pOutData);

int restful_register(RESG_PARAM *pResgParam, const char *pAddr);

//static int restful_parse_delchecked_val(const char *pOutData);

//static int restful_delchecked(const char *pAddr);

//获取认证Session_HPCServer
int engine_parse_session_val(char *pAutInfo, RESG_PARAM *pstSessInfo);

int engine_getSession(RESG_PARAM *pstSessInfo, const char *pAddr);

//客户端认证注册_HPCServer
int engine_parse_register_val(const char *pOutData);

int engine_register(RESG_PARAM *pResgParam, const char *pAddr);

//sha256加密算法
void sha256_encode(char* input, size_t input_len, char* output);

//添加授权节点
int add_parse_node_val(const char *pOutData);

int add_node(ADDNodeInfo *pAddNode, const char *pAddr, int count);

//查询授权节点
int query_parse_node_val(char *pAutInfo);

int query_node(const char *pAddr);

//删除授权节点
int delete_parse_node_val(const char *pOutData);

int delete_node(DeleteNodeInfo *pDeleteNode, const char *pAddr, int count);

//申请令牌
int apply_token(AllocateInfo *pAllocateInfo, const char *pAddr, int count);

int apply_parse_token_val(const char *pOutData);

//配置算法
int set_algori(AlgorithmInfo *pSetAlgori, const char *pAddr, int count);

int set_parse_algori_val(const char *pOutData);

//查询引擎节点
int get_serverinfo(const char *pAddr);

int get_parse_serverinfo_val(char *pAutInfo);

//查询算法
int get_algori(const char *pAddr);

int get_parse_algori_val(char *pAutInfo);

//下发任务
int set_task(TaskListInfo *pSetTask, const char *pAddr, int count);

int set_parse_task_val(const char *pOutData);

/*
//历史任务查询
int get_task(HistoryTaskInfo pGetTask, const char *pAddr);

int get_parse_task_val(const char *pOutData);
*/

//任务状态查询
int get_task(TaskStatusInfo *pGetTask, const char *pAddr, int count);

int get_parse_task_val(const char *pOutData);

//删除任务
int delete_task(DeleteTaskInfo *pDeletetTask, const char *pAddr, int count);

int delete_parse_task_val(const char *pOutData);
#endif