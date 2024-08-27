/**	@file		urlopt.h
 *	@note		Hikvision Digital Technology Co., Ltd. All Right Reserved.
 *	@brief		url的操作
 *
 *	@author		lipengfei
 *	@date		2015/01/22
 *	@note		历史记录：
 *	@note		V1.0.0
 *	@warning
 */
#ifndef __URLOPT_H__
#define __URLOPT_H__

#include "util_hpr_include.h"
#include "curl.h"
#include <string>

typedef enum
{
    TYPE_URLENCODED = 0,
    TYPE_DATA,
    TYPE_JSON,
    TYPE_XML
}CONTENT_TYPE;

#define get_content_type(x) \
    ((x == TYPE_DATA)?("Content-Type: multipart/form-data"): \
    ((x == TYPE_JSON)?("Content-Type: application/json"): \
    ((x == TYPE_XML)?("Content-Type: text/xml"):("Content-Type: application/x-www-form-urlencoded"))))

#define get_accept_type(x) \
    ((x == TYPE_DATA)?("Accept:  multipart/form-data"): \
    ((x == TYPE_JSON)?("Accept:  application/json"): \
    ((x == TYPE_XML)?("Accept:  text/xml"):("Accept:  application/x-www-form-urlencoded"))))

typedef struct _URLOPT_POST_CONDITION_
{
    char *szUrl;                       //url
    unsigned char *pInData;            //输入内容
    unsigned int nInLen;               //输入内容长度
    unsigned char *pOutData;           //输出内容
    unsigned int *pOutLen;             //输出内容长度
    CONTENT_TYPE  eAcceptType;          //允许接受数据格式类型
    CONTENT_TYPE  eContenType;          //提交数据格式类型
    unsigned int nTimeOut;             //超时时间
}URLOPT_POST_CONDITION;

/** @struct _IVMS_URL_GET_CB_PARAM_
 * 	@brief	数据回调参数
 *	@note
 */
typedef struct _IVMS_URL_GET_CB_PARAM_
{
    unsigned int        nTotalLen;              ///< 总长度
    unsigned int        nDataLen;               ///< 数据长度
    unsigned char       *pData;                 ///< 数据
    FILE                *fileFd;                // 文件地址
}IVMS_URL_GET_CB_PARAM;

typedef struct _IVMS_URL_GET_CB_PARAM_STRING
{
    unsigned int        nTotalLen;              ///< 总长度
    unsigned int        nDataLen;               ///< 数据长度
    std::string        strData;                 ///< 数据
    FILE                *fileFd;                // 文件地址
}IVMS_URL_GET_CB_PARAM_STRING;


typedef struct
{
    char szHeaderToken[256];                     ///< 报文头中token信息
    bool bHttps;                                ///< 是否https
    char szAuthBuff[128];                        ///< 认证信息串
    bool bBasic;								//是否是basic认证
	bool burlencoded;							//是否urlcode
	char szUserPwd[256];						//用户名密码
	char szFileName[64];						//上传文件的名称
}URLOPT_ADDITION_PARAMS;


/** @fn		IVMS_DECLARE int URLOPT_Init()
 *  @brief	模块初始化
 *	@return IVMS_DECLARE int    0表示成功，否则失败
 */
int URLOPT_Init();

/** @fn		IVMS_DECLARE void URLOPT_Fini()
 *  @brief	模块销毁
 *	@return IVMS_DECLARE void
 */
void URLOPT_Fini();


/** @fn		IVMS_DECLARE int URLOPT_Get(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut=5)
 *  @brief	URL的get命令
 *	@param	-I	 - char * szUrl             url
 *	@param	-O	 - unsigned char * pData    获取到的数据
 *	@param	-O&I - unsigned int * pLen      数据长度
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_Get(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut=5);
int OPS_URLOPT_Get(char *szUrl, char *szHeaderToken, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut=5);

/** @fn		IVMS_DECLARE int URLOPT_Post(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=5)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_Post(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=5);

int URLOPT_Post_Con(URLOPT_POST_CONDITION *pCondition);

int URLOPT_Put_Con(URLOPT_POST_CONDITION *pCondition);

/** @fn		IVMS_DECLARE int URLOPT_Post(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=5)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - unsigned char * pOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@return IVMS_DECLARE int                0表示成功，否则失败, 执行失败再尝试一次
 */
int URLOPT_Post_V2(char *szUrl, unsigned char *pInData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=15);

int URLOPT_Post_isapi(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=15);

/** @fn		IVMS_DECLARE int URLOPT_PostFile(char *szUrl, unsigned char *pData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=5)
 *  @brief	上传图片
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pData    上传的数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-I	 - unsigned char * pOutData 传出 数据
 *	@param	-I	 - unsigned int * pOutLen   长度
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_PostFile(char *szUrl, unsigned char *pData, unsigned int nInLen, unsigned char *pOutData, unsigned int *pOutLen, unsigned int nTimeOut=5);


/** @fn		int URLOPT_PostFile_Str(char *szUrl, std::string strData, std::string &strOutData, unsigned int &pOutLen, unsigned int nTimeOut)
 *  @brief	上传图片
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - std::string strData    上传的数据
 *	@param	-O	 - std::string &strOutData  传出 数据
 *	@param	-O	 - unsigned int &pOutLen    长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_PostFile_Str(char *szUrl, std::string strData, std::string &strOutData, unsigned int &pOutLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut);

/** @fn		IVMS_DECLARE int URLOPT_Del(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut=5)
 *  @brief	URL的delete命令
 *	@param	-I	 - char * szUrl             url
 *	@param	-O	 - unsigned char * pData    获取到的数据
 *	@param	-O&I - unsigned int * pLen      数据长度
 *	@return IVMS_DECLARE int                0表示成功，否则失败
 */
int URLOPT_Del(char *szUrl, unsigned char *pData, unsigned int *pLen, unsigned int nTimeOut=5);


/** @fn		int URLOPT_Post_With_Params_String(char *szUrl, unsigned char *pInData, unsigned int nInLen, std::string &strOutData, unsigned int *pOutLen, unsigned int nTimeOut)
 *  @brief	Post 操作
 *	@param	-I	 - char * szUrl             Url
 *	@param	-I	 - unsigned char * pInData  传入数据
 *	@param	-I	 - unsigned int nInLen      长度
 *	@param	-O	 - std::string &strOutData 传出数据
 *	@param	-I&O - unsigned int * pOutLen   长度
 *	@param	-I   - unsigned int nTimeOut    超时时间, 未传则默认5s
 *	@return int                             0表示成功，否则失败
 */
int URLOPT_Post_With_Params_String(char *szUrl, const unsigned char *pInData, unsigned int nInLen,std::string &strOutData, unsigned int &pOutLen,  URLOPT_ADDITION_PARAMS *pstruParams,unsigned int nTimeOut);

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
int URLOPT_Get_With_Params_String(char *szUrl, std::string &strOutData, unsigned int &pLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut);




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
int URLOPT_Post_With_Params(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char *pOutData, unsigned int *pOutLen,  URLOPT_ADDITION_PARAMS *pstruParams,unsigned int nTimeOut);

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
int URLOPT_Get_With_Params(char *szUrl, unsigned char *pData, unsigned int *pLen, URLOPT_ADDITION_PARAMS *pstruParams, unsigned int nTimeOut=5);

HPR_INT32 URLOPT_GetHttp (const char *szUrl, HPR_INT32 nExcuteTimeout, FILE *fileFd, unsigned long MaxLen, unsigned long *pLen);

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
HPR_VOID URLEncodeString(const char *szurl, int len, std::string & strEncodeUrl);

//int URLOPT_Post_malloc_result(char *szUrl, unsigned char *pInData, unsigned int nInLen,unsigned char **pOutData, unsigned int *pOutLen, unsigned int nTimeOut);

#endif

