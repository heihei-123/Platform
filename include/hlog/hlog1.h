/** @file   hlog1.h
 *  @note   HangZhou Hikvision System Technology Co., Ltd. All Right Reserved.
 *  @brief  ���ǿ�ɽӿ�
 *
 *  @note   create file
 *  @author wangjingyf@hikvision.com
 *  @date   2012/09/05 15:30:44
 *
 *  @change liutianmin@hikvision.com.cn
            ���������߷�����V2����
 *
 */
#ifndef __HLOG1_H__
#define __HLOG1_H__

#include "hlogconfig.h"
#include "string.h"
#ifdef _DEBUG
#include <stdio.h>
#include <stdarg.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (HLOG_API *HLOG_CB)(HLOG_LEVEL level, const char* message);

    /** @fn int hlog_init(const char* name, char async = false)
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_init(const char* name, char async);
#endif

    /** @fn int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false)
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
#ifdef __cplusplus
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async = false);
#else
    HLOG_DECLARE int HLOG_API hlog_ocx_init(const char* name, const char* path, char async);
#endif

    /** @fn int hlog_fini()
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_fini();

    /** @fn int hlog_set_callback(HLOG_CB callback)
     *  @brief ������־�Ļص�����
     *  @param[in] callback ���ڴ�����־��Ϣ�Ļص�����
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_set_callback(HLOG_CB callback);

    /** @fn int hlog_level(HLOG_LEVEL level)
     *  @brief ���ݾɽӿ�, ��ִ���κβ���
     *  @return HLOG_OK
     */
    HLOG_DECLARE int HLOG_API hlog_level(HLOG_LEVEL level);

    /** @fn int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...)
     *  @brief д��־��ʽ������
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] format ��־��ʽ���ַ���, ��ӿɱ����
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_format�����hlog_set_callback����Ļص�����
     *  @warning ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
     *  @sa hlog_format_ex
     */
    HLOG_DECLARE int HLOG_API hlog_format(HLOG_LEVEL level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn int HLOG_API hlog_format(int level, const char* module, const char* format, ...)
     *
     *  @brief д��־��ʽ������, ���ܺ�hlog_format��ͬ��ֻ�ǽӿڲ����������ͨ��
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] format ��־��ʽ���ַ���, ��ӿɱ����
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_format�����hlog_set_callback����Ļص�����
     *  @warning ʹ���߱��뱣֤����ĸ�ʽ���ַ����Ϳɱ������ƥ��
     *  @sa hlog_format
     */
    HLOG_DECLARE int HLOG_API hlog_format_ex(int level, const char* module, const char* format, ...) LOG_CHECK_FMT(3, 4);

    /** @fn int hlog_message(HLOG_LEVEL level, const char* module, const char* message)
     *  @brief д��־�ַ���
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] message ��־�ַ���
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @note hlog_message�������hlog_set_callback����Ļص�����
     *  @warning ��ʹ�øýӿ�ʱ, ��Ӧ��message��Я��%n�ȸ�ʽ��������ַ�,
     *           ��������б����ķ���, �������ȷ�����������, ��ô��ʹ��
     *           hlog_message_ex�ӿ�
     *  @sa hlog_message_ex
     */
    HLOG_DECLARE int HLOG_API hlog_message(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn int hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message)
     *  @brief д��־�ַ���
     *  @param[in] level ��־����
     *  @param[in] module ��־ģ��
     *  @param[in] message ��־�ַ���
     *  @return HLOG_OK, �ɹ�; ����, ʧ��
     *  @sa hlog_message
     */
    HLOG_DECLARE int HLOG_API hlog_message_ex(HLOG_LEVEL level, const char* module, const char* message);

    /** @fn void HLOG_API hlog_set_configfile_name(const char* config_file_name)
     *  @brief ����̹���һ�������ļ�ʱ�������־�ļ���������, Ϊ�˹����һ����,
     *         �ؼ��ϴ˽ӿ�, ������������ӿ�, �������һ������, �������һ����
     *         ���ļ�
     *  @param[in] config_file_name �����ļ���
     */
    HLOG_DECLARE void HLOG_API hlog_set_configfile_name(const char* config_file_name);

    /** @fn void HLOG_API hlog_set_immediate_flush(int immediate_flush);
     *
     *  @brief      �����Ƿ�����ˢд��־���ļ����ӿ�Ԥ������δʵ�֣�
     *  @param[in]  immediate_flush, �Ƿ�����ˢд��־���ļ�, 0-false, else-true
     *  @warning    �������־�����ļ�����������־���������������˳�ʱ�αȽϹ�ע
     *              ��־�ļ�ʱ�ԣ���ô���Կ���ʹ�øýӿڿ��ƽ��̻ص�����д��־��
     *              ״̬
     *  @sa         hlog_flush_and_finalize
     */
    HLOG_DECLARE void HLOG_API hlog_set_immediate_flush(int immediate_flush);

    /** @fn void HLOG_API hlog_flush_and_finalize();
     *
     *  @brief      ˢд������������־������ʼ����־��
     *  @warning    �������־�����ļ�����������־����������ô�����ڳ����˳�ǰ
     *              ���øýӿڽ�����������־ˢд����־�ļ���
     *  @sa         hlog_set_immediate_flush
     */
    HLOG_DECLARE void HLOG_API hlog_flush_and_finalize();

#ifdef __cplusplus
}
#endif

#define LOG_INIT(fmt)                   hlog_init(fmt)

#define LOG_FINI()                      hlog_fini()

// ���Ǽ����ԣ�������log_printf_def��log_printf_dst
#if (defined _WIN32 || defined _WIN64)
#define log_printf_def(level, format, ...)      hlog_format(level, "", format, ##__VA_ARGS__)
#else
#define log_printf_def(level, format, args...)  hlog_format(level, "", format, ##args)
#endif
#define log_printf_dst hlog_format

// for NetConn module
#if (defined _WIN32 || defined _WIN64)
#define VCAENGINE_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#define VCAENGINE_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#define VCAENGINE_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#ifdef _DEBUG
#define VCAENGINE_DEBUG(fmt, ...)         printf(fmt,__VA_ARGS__); printf("\n"); hlog_format(HLOG_LEVEL_DEBUG, "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#else
#define VCAENGINE_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#endif
#define VCAENGINE_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#else
#define VCAENGINE_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define VCAENGINE_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define VCAENGINE_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define VCAENGINE_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define VCAENGINE_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)

#define VCAENGINE_RESULTCHECK_INFO(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "ResultCheck", "<%s>|<%d>\t<>," fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#endif

// for crashbacktrace
#if (defined _WIN32 || defined _WIN64)
#define CRASHBT_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#define CRASHBT_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#define CRASHBT_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#define CRASHBT_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#define CRASHBT_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##__VA_ARGS__)
#else
#define CRASHBT_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##args)
#define CRASHBT_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##args)
#define CRASHBT_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##args)
#define CRASHBT_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##args)
#define CRASHBT_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "CRASHBT", "[%-4d]%s " fmt"\r", __LINE__, ":", ##args)
#endif

// important info
#if (defined _WIN32 || defined _WIN64)
#define SYS_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "SYS", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#define SYS_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "SYS", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#define SYS_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "SYS", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#ifdef _DEBUG
#define SYS_DEBUG(fmt, ...)         printf(fmt,__VA_ARGS__); printf("\n"); hlog_format(HLOG_LEVEL_DEBUG, "VcaEngine", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#else
#define SYS_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "SYS", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#endif
#define SYS_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "SYS", "< [%4d] - > " fmt,  /*strrchr(__FILE__,'\\')+1,*/ __LINE__, /*__FUNCTION__,*/ ##__VA_ARGS__)
#else
#define SYS_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "SYS", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args);hlog_format(HLOG_LEVEL_ERROR, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define SYS_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "SYS", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args);hlog_format(HLOG_LEVEL_WARN,  "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define SYS_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "SYS", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args);hlog_format(HLOG_LEVEL_INFO,  "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define SYS_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "SYS", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args);hlog_format(HLOG_LEVEL_DEBUG, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#define SYS_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "SYS", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args);hlog_format(HLOG_LEVEL_TRACE, "VcaEngine", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)
#endif

// for KAFKA
#if (defined _WIN32 || defined _WIN64)
#define KAFKA_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define KAFKA_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define KAFKA_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define KAFKA_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define KAFKA_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define KAFKA_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define KAFKA_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define KAFKA_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define KAFKA_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define KAFKA_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "KAFKA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif

// for FACELIST
#if (defined _WIN32 || defined _WIN64)
#define FACELIST_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define FACELIST_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define FACELIST_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define FACELIST_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define FACELIST_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define FACELIST_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define FACELIST_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define FACELIST_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define FACELIST_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define FACELIST_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "FACELIST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define VCATASK_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define VCATASK_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define VCATASK_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define VCATASK_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define VCATASK_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define VCATASK_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define VCATASK_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define VCATASK_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define VCATASK_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define VCATASK_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "VcaTask", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define HPCENGINE_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define HPCENGINE_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define HPCENGINE_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define HPCENGINE_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define HPCENGINE_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define HPCENGINE_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define HPCENGINE_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define HPCENGINE_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define HPCENGINE_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define HPCENGINE_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "HpcEngine", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif


#define STDOUTPUT_INFO(fmt, args...)   hlog_format(HLOG_LEVEL_INFO,  "STDOUTPUT", fmt, ##args)

#define ENGINEDEMO_INFO(fmt, args...)   hlog_format(HLOG_LEVEL_INFO,  "EngineDemo", "<%s>|<%d> " fmt "\r", strrchr(__FILE__,'/')+1, __LINE__, /*__FUNCTION__,*/ ##args)

// for Algorithm
#if (defined _WIN32 || defined _WIN64)
#define ALGRITHM_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define ALGRITHM_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define ALGRITHM_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define ALGRITHM_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define ALGRITHM_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define ALGRITHM_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define ALGRITHM_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define ALGRITHM_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define ALGRITHM_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define ALGRITHM_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "ALGRITHM", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif


#if (defined _WIN32 || defined _WIN64)
#define NODESTA_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define NODESTA_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define NODESTA_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define NODESTA_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define NODESTA_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define NODESTA_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define NODESTA_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define NODESTA_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define NODESTA_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define NODESTA_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "NODESTA", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif
#if (defined _WIN32 || defined _WIN64)
#define DESTSTAT_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DESTSTAT_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DESTSTAT_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DESTSTAT_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DESTSTAT_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define DESTSTAT_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DESTSTAT_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DESTSTAT_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DESTSTAT_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DESTSTAT_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "DESTSTAT", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif
#if (defined _WIN32 || defined _WIN64)
#define PROTOCOL_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define PROTOCOL_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define PROTOCOL_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define PROTOCOL_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define PROTOCOL_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define PROTOCOL_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define PROTOCOL_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define PROTOCOL_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define PROTOCOL_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define PROTOCOL_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "PROTOCOL", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif
#if (defined _WIN32 || defined _WIN64)
#define TASK_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TASK_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TASK_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TASK_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TASK_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define TASK_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TASK_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TASK_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TASK_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TASK_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "TASK", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif
#if (defined _WIN32 || defined _WIN64)
#define TEST_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TEST_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TEST_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TEST_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define TEST_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define TEST_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TEST_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TEST_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TEST_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define TEST_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "TEST", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif

#if (defined _WIN32 || defined _WIN64)
#define DEMO_ERROR(fmt, ...)         hlog_format(HLOG_LEVEL_ERROR, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DEMO_WARN(fmt, ...)          hlog_format(HLOG_LEVEL_WARN,  "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DEMO_INFO(fmt, ...)          hlog_format(HLOG_LEVEL_INFO,  "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DEMO_DEBUG(fmt, ...)         hlog_format(HLOG_LEVEL_DEBUG, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#define DEMO_TRACE(fmt, ...)         hlog_format(HLOG_LEVEL_TRACE, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##__VA_ARGS__)
#else
#define DEMO_ERROR(fmt, args...)     hlog_format(HLOG_LEVEL_ERROR, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DEMO_WARN(fmt, args...)      hlog_format(HLOG_LEVEL_WARN,  "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DEMO_INFO(fmt, args...)      hlog_format(HLOG_LEVEL_INFO,  "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DEMO_DEBUG(fmt, args...)     hlog_format(HLOG_LEVEL_DEBUG, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#define DEMO_TRACE(fmt, args...)     hlog_format(HLOG_LEVEL_TRACE, "DEMO", "<%s>[%-4d]<%s>%s " fmt"\r",strrchr(__FILE__,'/') + 1, __LINE__, __FUNCTION__, ":", ##args)
#endif

#ifdef _WIN32
#pragma comment (lib, "hlog.lib")
#endif ///< windows

#endif
