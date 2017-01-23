#ifndef _I_GT_PUSH_H_
#define _I_GT_PUSH_H_

/***************************�汾�޸���־***************************
* ==========V1.0.1, chenjb, 2014-07-28==========
* 1. ȥ��pushMessageToListB�ӿڣ�pushMessageToListA����ΪpushMessageToList
* 2. pushMessageToList���ӷ����������鹦��
*
* ==========V1.0.2, chenjb, 2015-01-14==========
* 1. curl bug�޸ģ�http://blog.chinaunix.net/uid-20761674-id-3391182.html
*/

#ifdef __cplusplus
extern "C" {
#endif

#if defined(WIN32) || defined(_WIN32)
#	define STDCALL _stdcall
#	if defined(GTPUSHSDK_EXPORTS)
#		define DLL_EXTERN  __declspec(dllexport)
#	else
#		define DLL_EXTERN  __declspec(dllimport)
#	endif
#else
#	define DLL_EXTERN
#	define STDCALL
#endif

// ���÷��ؽ���ṹ�壺SUCCESS(�ɹ�)/FAILED(ʧ��)
typedef enum result_t {
    SUCCESS = 0,
    FAILED = 1,
	ERR_ENCODE = 2
} Result;

// ���������ֵ�Խṹ��
typedef struct entry_t {
    char key[100];
    char value[1024];
} Entry;

// ���ͽ���ṹ��
typedef struct i_push_result_t {
    int size; // ����д��ڶ��ٸ�Entry
    Entry entry[10];
} IPushResult;

// ��ѯ����ṹ��
typedef struct i_query_result_t {
	char result[255];//�ɹ���־
    int size; // ����д��ڶ��ٸ�Entry
    Entry data[20];
} IQueryResult;

typedef struct _CustomMsg{
	int size;
	Entry* map;
}CustomMsg;

// ������Ϣ�ṹ��
typedef struct message_t {
    int isOffline;
    long offlineExpireTime;
    int priority;
	int pushNetWorkType;
} Message;

// ������Ϣ�ṹ��
typedef struct single_message_t {
    Message msg;
} SingleMessage;

// CID�б���Ϣ�ṹ��
typedef struct list_message_t {
    Message msg;
} ListMessage;

// Ӧ����Ϣ�ṹ��
typedef struct app_message_t {
    Message msg;
    char **appIdList;
    int appIdListSize;
    char **phoneTypeList;
    int phoneTypeListSize;
    char **provinceList;
    int provinceListSize;
    char **tagList;
    int tagListSize;
	int speed;
} AppMessage;

// ����Ŀ��ṹ��
typedef struct target_t {
    char *appId;
    char *clientId;
	char *alias;
} Target;

// ģ������ö��
typedef enum template_type_t {
    Transmission, PopupTransmission, NotyPopLoad, Notification, Link, APN
} TemplateType;

// ����ö��
typedef enum _OFF_ON {
    GT_ON = 0, GT_OFF = 1
} off_on;

typedef struct _LISTITEM{
	char item[255];
}ListItem;
typedef struct _LISTINFO{
	int size;
	ListItem* item;
}ListInfo;

// Ӧ����IOS�ֻ�
typedef struct push_info_t {
	int badge;
	char* sound;
	int contentAvailable;
	char* category;
	char* title;
	char* body;
	char* titleLocKey;
	ListInfo titleLocArgs;
	char* actionLocKey;
	char* locKey;
	ListInfo locArgs;
	char* launchImage;
	CustomMsg cmsg;
} PushInfo;

// ����ģ��ṹ��
typedef struct template_t {
    char *appId;
    char *appKey;
    PushInfo pushInfo;
	char* duration_start;
	char* duration_end;
} Template;

// apn����
typedef struct APNTemplate_template_t{
	Template t;
}APNTemplate;

// ͸��ģ��ṹ��
typedef struct transmission_template_t {
    Template t;
    int transmissionType;
    char *transmissionContent;
} TransmissionTemplate;

// ����͸��ģ��ṹ��
typedef struct popup_transmission_template_t {
    Template t;
    int transmissionType;
    char *transmissionContent;
    char *title;
    char *text;
    char *img;
    char *confirmButtonText;
    char *cancelButtonText;
} PopupTransmissionTemplate;

// ֪ͨ��������ģ��ṹ��
typedef struct noty_pop_load_template_t {
    Template t;
    char *notyIcon;
    char *logoUrl;
    char *notyTitle;
    char *notyContent;
    off_on isCleared;
    off_on isBelled;
    off_on isVibrationed;
    char *popTitle;
    char *popContent;
    char *popImage;
    char *popButton1;
    char *popButton2;
    char *loadIcon;
    char *loadTitle;
    char *loadUrl;
    int isAutoInstall;
    int isActived;
    char *androidMark;
    char *symbianMark;
    char *iphoneMark;
} NotyPopLoadTemplate;

// ֪ͨģ��ṹ��
typedef struct notification_template_t {
    Template t;
    int transmissionType;
    char *transmissionContent;
    char *text;
    char *title;
    char *logo;
    char *logoUrl;
	off_on isRing;
    off_on isVibrate;
	off_on isClearable;
} NotificationTemplate;

// ����ģ��ṹ��
typedef struct link_template_t {
    Template t;
    char *text;
    char *title;
    char *logo;
    char *logoUrl;
	char *url;
    off_on isRing;
    off_on isVibrate;
	off_on isClearable;
} LinkTemplate;

// ���ͽ������
typedef struct push_detail_t {
	char cid[33]; // ��Ӧ��CID
	char ret[51]; // ��������
} PushDetail;


// ���ܣ����ͳ�ʼ������������ǰ��ʼ��һ�μ���
// ������
//		host ���Ʒ�����URL [in]
//		appKey ��������Ӧ�õ�appKey [in]
//		masterSecret ��������Ӧ�õ�masterSecret [in]
//		testUTF8 �������нӿڱ��봫���ַ�����ΪUTF��8���룬�������ڲ����Ƿ���UTF��8���룬�̶���д"����"���� [in]
// ���أ�Resultö��, SUCCESS��FAILED��ERR_ENCODE���������ʧ�ܣ�
DLL_EXTERN Result STDCALL pushInit(char *host, char *appKey, char *masterSecret, const char *testUTF8);

// ���ܣ���ʼ�����Ʒ�������Ȩ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
// ���أ�Resultö��, SUCCESS��FAILED
DLL_EXTERN Result STDCALL pushConnect(char *appKey);

// ���ܣ��رո��Ʒ�������Ȩ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
// ���أ�Resultö��, SUCCESS��FAILED
DLL_EXTERN Result STDCALL pushClose(char *appKey);

// ���ܣ����͵�����Ϣ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData ������Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		target ����Ŀ��ṹ��ָ�� [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushMessageToSingle(char *appKey, SingleMessage *msgData, void *templateData, TemplateType templateType, Target *target);

// ���ܣ����͵�����Ϣ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData ������Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		target ����Ŀ��ṹ��ָ�� [in]
//		requestId �������Է��� [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushMessageToSingleByReqId(char *appKey, SingleMessage *msgData, void *templateData, TemplateType templateType, Target *target, const char *requestId);

// ���ܣ����͵�����Ϣ��ios�豸
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData ������Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		appId Ӧ��ʶ��� [in]
//		deviceToken ios�豸���� [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushAPNMessageToSingle(char *appKey, void *templateData, const char *appId, const char *deviceToken);



// ���ܣ���ȡcontentId for ios����
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData CID�б���Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		contentId ���ڷ���contentId��ָ�� [out]
//		size �ɴ��contentId�Ĵ�С [in]
// ���أ�Resultö��, SUCCESS��FAILED
// ע�⣺���sizeС�ڷ��ص�ID���򷵻�FAILED
DLL_EXTERN Result STDCALL getAPNContentId(char *appKey, void *templateData, char *contentId, int size);


// ���ܣ�������Ϣ��tokenlist�豸
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		deviceTokenList ios�豸�����嵥 [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushAPNMessageToList(const char *appKey, const char *appId, ListInfo* deviceTokenList, const char* contentId);

// ���ܣ���ȡcontentId������pushMessageToListA�ӿ�
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData CID�б���Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		contentId ���ڷ���contentId��ָ�� [out]
//		size �ɴ��contentId�Ĵ�С [in]
//		groupName ��ʶ����
// ���أ�Resultö��, SUCCESS��FAILED
// ע�⣺���sizeС�ڷ��ص�ID���򷵻�FAILED
DLL_EXTERN Result STDCALL getContentIdByGroup(char *appKey, ListMessage *msgData, void *templateData, TemplateType templateType, char *contentId, int size, const char* groupName);

// ���ܣ���ȡcontentId������pushMessageToListA�ӿ�
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData CID�б���Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		contentId ���ڷ���contentId��ָ�� [out]
//		size �ɴ��contentId�Ĵ�С [in]
// ���أ�Resultö��, SUCCESS��FAILED
// ע�⣺���sizeС�ڷ��ص�ID���򷵻�FAILED
DLL_EXTERN Result STDCALL getContentId(char *appKey, ListMessage *msgData, void *templateData, TemplateType templateType, char *contentId, int size);

// ���ܣ�ȡ��contentId
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		contentId ��Ҫȡ����contentId [in]
// ���أ�Resultö��, SUCCESS��FAILED
DLL_EXTERN Result STDCALL cancelContentId(char *appKey, char *contentId);

// ���ܣ�����CID�б�
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		contentId ��getContentId���ص�contentId [in]
//		targetList ��Ҫ���͵�Ŀ���б� [in]
//		targetSize Ŀ���б����ж��ٸ�Targe������ÿ��50 [in]
//		details �����������ݣ�����Ҫ�������дNULL��������ҪԤ�ȷ����㹻�ڴ�(����ҪtargetSize��PushDetail) [in]
// ���أ�Resultö��, SUCCESS��FAILED
DLL_EXTERN IPushResult STDCALL pushMessageToList(char *appKey, char *contentId, Target *targetList, int targetSize, PushDetail *details);

// ���ܣ�����Ӧ����Ϣ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData Ӧ����Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushMessageToApp(char *appKey, AppMessage *msgData, void *templateData, TemplateType templateType);

// ���ܣ�����Ӧ����Ϣ
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		msgData Ӧ����Ϣ�ṹ��ָ�� [in]
//		templateData ģ��ṹ��ָ�� [in]
//		templateType ģ������ [in]
//		groupName	���� [in]
// ���أ����ͽ������
DLL_EXTERN IPushResult STDCALL pushMessageToAppByGroupName(char *appKey, AppMessage *msgData, void *templateData, TemplateType templateType, const char* groupName);

// ���ܣ�ֹͣ����ĳ������
// ������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		contentId ��Ҫֹͣ���͵�contentId [in]
// ���أ�Resultö��, SUCCESS��FAILED
DLL_EXTERN Result STDCALL pushStop(char *appKey, char *contentId);

// ���ܣ���ȡ��ǰSDK�汾��
// ��������
// ���أ��汾���ַ���
DLL_EXTERN const char * STDCALL getPushSdkVersion();


//���ܣ���õ������ͽ��
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		date ��ѯ���� ��20150526 [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IQueryResult STDCALL  queryAppPushDataByDate(const char *appKey, const char* appId, const char* date);

//���ܣ���õ����û�����
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		date ��ѯ���� ��20150526 [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IQueryResult STDCALL  queryAppUserDataByDate(const char *appKey, const char* appId, const char* date);


//���ܣ���������Ż�õ�������
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		taskId ����� [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  getPushResult(const char *appKey, const char* taskId);


//���ܣ�����cid�󶨱���
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		alias �û����� [in]
//		cid �����û���ʶid [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  bindAlias(const char *appKey, const char* appId, const char* alias, const char* cid);

//���ܣ����cid�󶨱���
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		target ������cid��Ӧ�б� [in]
//		num	   target�б��С [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  bindAliasList(const char *appKey, const char* appId, Target *target, int num);


//���ܣ�������ȡcid
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		alias  Ҫ��ѯ�ı��� [in]
//		list   ��ñ����󶨵�cid�б� [out]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  queryClientId(const char *appKey, const char* appId, const char *alias, char** list);

//���ܣ��ͷ���Դ
//������
//		list ��queryClientId���ص�cid�б�
//���أ��Ƿ���óɹ�
DLL_EXTERN Result STDCALL  releaseMem(char* list);

//���ܣ�ͨ��cid��ȡ����
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		cid	   Ҫ��ѯ��cid [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  queryAlias(const char *appKey,const char *appId, const char *cid);

//���ܣ�����cid�ͱ������
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		alias  Ҫ���ı��� [in]
//		cid	   Ҫ��������cid [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  unBindAlias(const char *appKey,const char *appId, const char *alias, const char* cid);

//���ܣ�����������cid
//������
//		appKey ����pushInitʱAPP��Ӧ��appKey [in]
//		appId Ӧ��ʶ��� [in]
//		alias Ҫ���ı���(����Ӧ������cid) [in]
//���أ��Ƿ���óɹ�
DLL_EXTERN IPushResult STDCALL  unBindAliasAll(const char *appKey,const char *appId, const char *alias);
#ifdef __cplusplus
}
#endif

#endif
