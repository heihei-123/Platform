#include <iostream>
#include <cstring>
#include "param.h"
#include "hprsafefunc.h"
#include "base_define.h"

void processSession(const char *system, const char *arg)
{
    RESG_PARAM *pstSessInfo = new RESG_PARAM; 

    pstSessInfo->szUserName = new char[1024];
    printf("请输入用户名: ");
    scanf("%s",  pstSessInfo->szUserName); 
    pstSessInfo->szPassword = new char[1024];
    printf("请输入密码: ");
    scanf("%s",pstSessInfo->szPassword); 

    pstSessInfo->szSession = new char[1024];
    pstSessInfo->szChallenge = new char[1024];
    pstSessInfo->szSalt = new char[1024];

    int iReturn = HPR_ERROR;
    if (strcmp(system, "AuthCMS") == 0) {
        iReturn = restful_getSession(pstSessInfo, arg);
        //std::cout << "success1" << std::endl;
    }
    else if (strcmp(system, "HPCServer") == 0) {
        iReturn = engine_getSession(pstSessInfo, arg);
        //std::cout << "success1" << std::endl;
    }

    if (iReturn == HPR_ERROR){
        DEMO_ERROR();
        //std::cout << "fail1" << std::endl;
        return;
    }

    if (strcmp(system, "AuthCMS") == 0) {
        iReturn = restful_register(pstSessInfo, arg);
        //std::cout << "success2" << std::endl;
    }
    else if (strcmp(system, "HPCServer") == 0) {
        iReturn = engine_register(pstSessInfo, arg);
        //std::cout << "success2" << std::endl;
    }

    if (iReturn == HPR_ERROR){
        DEMO_ERROR();
        //std::cout << "fail2" << std::endl;
        return;
    }
    //std::cout << iReturn << std::endl;
    delete[] pstSessInfo->szPassword;
    delete[] pstSessInfo->szUserName;
    delete[] pstSessInfo->szSession;
    delete[] pstSessInfo->szChallenge;
    delete[] pstSessInfo->szSalt;
    delete pstSessInfo;
}

void processAddNode(char *argv[], int count)
{   
    if (count == 0){
        return;
    }

    ADDNodeInfo p[count];
    for (int i = 0; i < count; i++){
        snprintf(p[i].index,sizeof(p[i].index),"%d", i + 1);
        strcpy(p[i].nodeName, argv[4 + i]);
        strcpy(p[i].nodeIp, argv[4 + i]);
        p[i].nodePort = 30043;
    }

    add_node(p, argv[2], count);
    
    /*从文件中获取
    ADDNodeInfo p[10];
    int count = 0;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].index, token, sizeof(p[count].index) - 1);
            p[count].index[strcspn(p[count].index, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].nodeName, token, sizeof(p[count].nodeName) - 1);
            p[count].nodeName[strcspn(p[count].nodeName, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].nodeIp, token, sizeof(p[count].nodeIp) - 1);
            p[count].nodeIp[strcspn(p[count].nodeIp, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            if (token != NULL) {
                p[count].nodePort = atoi(token);
            }
        }
        count++;
    }
    fclose(file);
    add_node(p, arg, count);
    */
    /*信息固化在程序里
    ADDNodeInfo *p = new ADDNodeInfo;
    strcpy(p->index, "1");
    strcpy(p->nodeName, "123");
    strcpy(p->nodeIp, "127.0.0.1");
    p->nodePort = 30043;
    int count = 1;
    add_node(p, arg, count);
    
    delete[] p->index;
    delete[] p->nodeName;
    delete[] p->nodeIp;
    delete p;
    */

}

void processQueryNode(const char *arg)
{
    query_node(arg);
}

void processSetAlgori(const char *arg)
{
    int count = 1;
    AlgorithmInfo *s = new AlgorithmInfo;
    strcpy(s->nodeId, "9E367C7FD7F9443E92B4D41CED3D0C30_127.0.0.1_9500");
    strcpy(s->algorithmId, "123");
    strcpy(s->url, "123");
    strcpy(s->md5, "123");
    strcpy(s->algorithmName, "123");
    strcpy(s->authorizedAbilityId, "123");
    strcpy(s->authorizedAbilityIdList, "123");
    strcpy(s->authorized, "123");
    strcpy(s->algAuthAddress, "123");
    s->allocateAbility = 50;
    s->allocateResource = 1.0;
    strcpy(s->algorithmInfo.algorithmconfig, "123");
    strcpy(s->algorithmInfo.adjustConfig, "123");
    strcpy(s->algorithmInfo.vendorId, "123");
    strcpy(s->algorithmInfo.targetType, "123");
    strcpy(s->algorithmInfo.modelVersion, "123");

    set_algori(s, arg, count);

    free(s);
}

void processGetAlgori(const char *arg)
{
    get_algori(arg);
}

void processDeleteNode(const char *arg)
{
    DeleteNodeInfo p[10];
    int count = 0;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].nodeID, token, sizeof(p[count].nodeID) - 1);
            p[count].nodeID[strcspn(p[count].nodeID, "\n")] = 0; // 去除换行符
        }
        count++;
    }
    fclose(file);
    delete_node(p, arg, count);
}

void processApplyToken(const char *arg)
{
    AllocateInfo p[10];
    int count = 0;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].index, token, sizeof(p[count].index) - 1);
            p[count].index[strcspn(p[count].index, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].targetType, token, sizeof(p[count].targetType) - 1);
            p[count].targetType[strcspn(p[count].targetType, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].source, token, sizeof(p[count].source) - 1);
            p[count].source[strcspn(p[count].source, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            if (token != NULL) {
                p[count].require = atoi(token);
            }
            token = strtok(NULL, " ");
            if (token != NULL) {
                p[count].bAutoExpand = atoi(token);
            }
        }
        count++;
    }
    fclose(file);
    apply_token(p, arg, count);
}

void processGetServer(const char *arg)
{
    get_serverinfo(arg);
}

void processSetTask(const char *arg)
{
    TaskListInfo p[10];
    int count = 0;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].taskId, token, sizeof(p[count].taskId) - 1);
            p[count].taskId[strcspn(p[count].taskId, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].nodeId, token, sizeof(p[count].nodeId) - 1);
            p[count].nodeId[strcspn(p[count].nodeId, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p[count].algorithmId, token, sizeof(p[count].algorithmId) - 1);
            p[count].algorithmId[strcspn(p[count].algorithmId, "\n")] = 0; // 去除换行符

            token = strtok(NULL, " ");
            strncpy(p[count].taskType, token, sizeof(p[count].taskType) - 1);
            p[count].taskType[strcspn(p[count].taskType, "\n")] = 0; // 去除换行符

            token = strtok(NULL, " ");
            strncpy(p[count].resourceType, token, sizeof(p[count].resourceType) - 1);
            p[count].resourceType[strcspn(p[count].resourceType, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            if (token != NULL) {
                p[count].resource = atof(token);
            }
        }
        count++;
    }
    fclose(file);
    set_task(p, arg, count);
}

void processGetTask(const char *arg)
{
    TaskStatusInfo p[10];
    int count = 0;
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].taskId, token, sizeof(p[count].taskId) - 1);
            p[count].taskId[strcspn(p[count].taskId, "\n")] = 0; // 去除换行符
        }
        count++;
    }
    fclose(file);
    get_task(p, arg, count);
}

/*
void processGetTask(const char *arg)
{
    HistoryTaskInfo p;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p.taskId, token, sizeof(p.taskId) - 1);
            p.taskId[strcspn(p.taskId, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p.nodeId, token, sizeof(p.nodeId) - 1);
            p.nodeId[strcspn(p.nodeId, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            strncpy(p.taskFinishStatus, token, sizeof(p.taskFinishStatus) - 1);
            p.taskFinishStatus[strcspn(p.taskFinishStatus, "\n")] = 0; // 去除换行符
            
            token = strtok(NULL, " ");
            if (token != NULL) {
                p.taskNumber = atof(token);
            }
        }
    }
    fclose(file);
    get_task(p, arg);
}
*/

void processDeleteTask(const char *arg)
{
    DeleteTaskInfo p[10];
    int count = 0;

    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file.\n");
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        token = strtok(line, " ");
        if (token != NULL) {
            strncpy(p[count].taskId, token, sizeof(p[count].taskId) - 1);
            p[count].taskId[strcspn(p[count].taskId, "\n")] = 0; // 去除换行符
        }
        count++;
    }
    fclose(file);
    delete_task(p, arg, count);
}

int main(int argc, char* argv[])
{
    if (argc == 2 && strcmp(argv[1], "-h") == 0){
        std::cout << "-r AuthCMS : 客户端注册" <<std::endl;
        std::cout << "-a AuthCMS : 添加授权节点" <<std::endl;
        std::cout << "-q AuthCMS : 查询授权节点" <<std::endl;
        std::cout << "-d AuthCMS : 删除授权节点" <<std::endl;
        std::cout << "-p AuthCMS : 申请令牌" <<std::endl;
        std::cout << "-r HPCServer : 客户端注册" <<std::endl;
        std::cout << "-s HPCServer : 配置算法" <<std::endl;
        std::cout << "-q HPCServer : 查询引擎节点" <<std::endl;
        std::cout << "-g HPCServer : 查询算法" <<std::endl;
        std::cout << "-st HPCServer : 下发任务" <<std::endl;
        std::cout << "-gt HPCServer : 任务状态查询" <<std::endl;
        //std::cout << "-gt HPCServer : 历史任务查询" <<std::endl;
        std::cout << "-dt HPCServer : 删除任务" <<std::endl;
        return 0;
    }
    
    if (argc < 4)
    {
        std::cout << "argc < 4" << std::endl;
        return 0;
    }

    HPR_Init();
	hlog_init("log4cxx.properties", HPR_FALSE);
    
    if (strcmp(argv[3], "AuthCMS") == 0) {
        if (strcmp(argv[1], "-r") == 0) {
            processSession("AuthCMS", argv[2]);
        }

        if (strcmp(argv[1], "-a") == 0) {
            processAddNode(argv, argc - 4);
        }

        if (strcmp(argv[1], "-q") == 0) {
            processQueryNode(argv[2]);
        }

        if (strcmp(argv[1], "-d") == 0) {
            processDeleteNode(argv[2]);
        }

        if (strcmp(argv[1], "-p") == 0) {
            processApplyToken(argv[2]);
        }
    }
    else if (strcmp(argv[3], "HPCServer") == 0) {
        if (strcmp(argv[1], "-r") == 0) {
            processSession("HPCServer", argv[2]);
        }

        if (strcmp(argv[1], "-s") == 0) {
            processSetAlgori(argv[2]);
        }

        if (strcmp(argv[1], "-q") == 0) {
            processGetServer(argv[2]);
        }

        if (strcmp(argv[1], "-g") == 0) {
            processGetAlgori(argv[2]);
        }

        if (strcmp(argv[1], "-st") == 0) {
            processSetTask(argv[2]);
        }
        /*
        if (strcmp(argv[1], "-gt") == 0) {
            processGetTask(argv[2]);
        }
        */

       if (strcmp(argv[1], "-gt") == 0) {
            processGetTask(argv[2]);
        }

        if (strcmp(argv[1], "-dt") == 0) {
            processDeleteTask(argv[2]);
        }
    }
    
    return 0;
}

