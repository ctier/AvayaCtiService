/***********************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/* abstract syntax: sdb_asn_tbl */
/* last module in input: SDB-control-services */
/* created: Tue Jul 15 12:34:26 1997 */
/* associated control file: sdbdefs.c */

#ifndef SDBDEFS_H
#define SDBDEFS_H

#include "tsplatfm.h"


#define          SDB_OPEN_CONNECTION 1
#define          SDB_OPEN_CONN_CONF 2
#define          SDB_CLOSE_CONNECTION 3
#define          SDB_CLOSE_CONN_CONF 4
#define          SDB_INSERT_OBJECT 5
#define          SDB_INSERT_OBJECT_CONF 6
#define          SDB_INSERT_ATTRIBUTE 7
#define          SDB_INSERT_ATTRIBUTE_CONF 8
#define          SDB_DELETE_OBJECT 9
#define          SDB_DELETE_OBJECT_CONF 10
#define          SDB_DELETE_ATTRIBUTE 11
#define          SDB_DELETE_ATTRIBUTE_CONF 12
#define          SDB_SELECT_OBJECT 13
#define          SDB_SELECT_OBJECT_CONF 14
#define          SDB_OPEN_CURSOR 15
#define          SDB_OPEN_CURSOR_CONF 16
#define          SDB_FETCH_CURSOR 17
#define          SDB_FETCH_CURSOR_CONF 18
#define          SDB_CLOSE_CURSOR 19
#define          SDB_CLOSE_CURSOR_CONF 20
#define          SDB_MODIFY_OBJECT 21
#define          SDB_MODIFY_OBJECT_CONF 22
#define          SDB_START_TRANS 23
#define          SDB_START_TRANS_CONF 24
#define          SDB_COMMIT_TRANS 25
#define          SDB_COMMIT_TRANS_CONF 26
#define          SDB_ROLLBACK_TRANS 27
#define          SDB_ROLLBACK_TRANS_CONF 28
#define          SDB_BACKUP_DATA_BASE 29
#define          SDB_BACKUP_DATA_BASE_CONF 30
#define          SDB_UPDATE_DATA_BASE 31
#define          SDB_UPDATE_DATA_BASE_CONF 32
#define          SDB_CREATE_TEMPLATE 33
#define          SDB_CREATE_TEMPLATE_CONF 34
#define          SDB_QUERY_VERSIONS 35
#define          SDB_QUERY_VERSIONS_CONF 36
#define          SDB_QUERY_FILES 37
#define          SDB_QUERY_FILES_CONF 38
#define          SDB_QUERY_ATTRIBUTES 39
#define          SDB_QUERY_ATTRIBUTES_CONF 40
#define          SDB_QUERY_STATUS 41
#define          SDB_QUERY_STATUS_CONF 42
#define          SDB_UNIVERSAL_FAILURE_CONF 43
#define          SDB_UNIVERSAL_FAILURE 44
#define          SDB_SELECT_KEY 45
#define          SDB_SELECT_KEY_CONF 46
#define          SDB_CONVERT_DATA_BASE 47
#define          SDB_CONVERT_DATA_BASE_CONF 48
#define          SDB_BACKUP_NDS_DATA_BASE 49
#define          SDB_BACKUP_NDS_DATA_BASE_CONF 50
#define          SDB_UPDATE_NDS_DATA_BASE 51
#define          SDB_UPDATE_NDS_DATA_BASE_CONF 52
#define          SDB_SET_SDB_LOG_OPTIONS 53
#define          SDB_SET_SDB_LOG_OPTIONS_CONF 54
#define          SDB_GET_SDB_LOG_OPTIONS 55
#define          SDB_GET_SDB_LOG_OPTIONS_CONF 56
#define          SDB_GET_CONNECTIONS 57
#define          SDB_GET_CONNECTIONS_CONF 58
#define          SDB_GET_ABOUT_INFO 59
#define          SDB_GET_ABOUT_CONF 60
#define          SDB_GET_ADMIN_INFO 61
#define          SDB_GET_ADMIN_INFO_CONF 62
#define          SDB_SET_ADMIN_INFO 63
#define          SDB_SET_ADMIN_INFO_CONF 64
#define          SDB_GET_TCP_INFO 65
#define          SDB_GET_TCP_INFO_CONF 66
#define          SDB_SET_TCP_INFO 67
#define          SDB_SET_TCP_INFO_CONF 68

typedef char            SDBContext_t[512];

typedef char            SDBVersion_t[22];

typedef char            SDBBtrvVersion_t[8];

typedef enum SDBIPNameFormat_t {
    SDB_IP_HOST_NAME = 1,
    SDB_IP_ADDRESS = 2
} SDBIPNameFormat_t;

typedef unsigned long   SDBFileType_t;
#define                     SDB_ORG 0x40000000
#define                     SDB_ORGUNIT 0x20000000
#define                     SDB_SIMPLE 0x10000000
#define                     SDB_USER 0x00000001
#define                     SDB_WORKTOP 0x00000002
#define                     SDB_DEVICE 0x00000004
#define                     SDB_DLIST 0x00000008
#define                     SDB_TLINK 0x00000010
#define                     SDB_TLIST 0x00000020
#define                     SDB_OAMLIST 0x00000040
#define                     SDB_TSERV 0x00000080
#define                     SDB_DLIST_INDEX 0x00000100
#define                     SDB_TLIST_INDEX 0x00000200
#define                     SDB_OAMLIST_INDEX 0x00000400
#define                     SDB_INDEX 0x00000800

typedef enum SDBAttributeID_t {
    NULL_ATTR = 0,
    LOGIN = 100,
    USER_NAME = 101,
    USER_WKTP = 102,
    DEV_DEV_LIST = 103,
    CALL_DEV_LIST = 104,
    CALL_CALL = 105,
    CALL_CTL_LIST = 106,
    ROUTING_LIST = 107,
    OAM_LIST = 108,
    SUPER_ADMIN_USER = 109,
    ACL_USER = 110,
    WKTP_NAME = 200,
    WKTP_DEVICE = 201,
    IPX_LAN_ADDR = 202,
    IP_LAN_ADDR = 203,
    IP_NAME = 204,
    WKTP_DLIST = 205,
    ACL_WKTP = 206,
    WKTP_INDEX = 207,
    DEVICE_ID = 300,
    DB_DEVICE_TYPE = 301,
    DEVICE_TLIST = 302,
    LOCATION = 303,
    TELEPHONE_NO = 304,
    ACL_DEVICE = 305,
    DEVICE_INDEX = 306,
    DLIST_NAME = 400,
    EXCEPT_LIST = 401,
    DLIST_DEVICE = 402,
    ACL_DLIST = 403,
    DLIST_INDEX = 404,
    DLST_INDX = 490,
    DEV_INDX = 491,
    DLST_COMB = 492,
    TLINK_NAME = 500,
    SERVICE_TYPE = 510,
    TLINK_INDEX = 526,
    TLIST_NAME = 600,
    TLIST_LINKNM = 601,
    ACL_TLIST = 602,
    TLIST_INDEX = 603,
    TLST_INDX = 690,
    TLNK_INDX = 691,
    TLIST_COMB = 692,
    OAMLIST_NAME = 700,
    OAMLIST_LINKNM = 701,
    ACL_OAMLIST = 702,
    OAMLIST_INDEX = 703,
    OAMLST_INDX = 790,
    OAMLNK_INDX = 791,
    OAMLIST_COMB = 792,
    ORG_NAME = 900,
    ACL_ORG = 901,
    ORGUNIT_NAME = 910,
    ACL_ORGUNIT = 911
} SDBAttributeID_t;

typedef char            SDBFileName_t[22];

typedef SDBFileName_t   SDBFlatFileName_t;

typedef SDBFileName_t   SDBSimpleFileName_t;

typedef SDBFileName_t   SDBErrorFileName_t;

typedef short           SDBConnectionID_t;

typedef short           SDBAttrDataLength_t;

typedef char            SDBComments_t[256];

typedef char            SDBLogPath_t[256];

typedef char            SDBAttributeName_t[22];

typedef char            SDBLoginName_t[49];

typedef short           SDBBufferSize_t;

typedef short           SDBConnectCount_t;

typedef short           SDBFileReadCount_t;

typedef _Int             SDBMemoryUsed_t;

typedef short           SDBReturnedCount_t;

typedef unsigned char   SDBDriverType_t;
#define                     SDB_BTRIEVE 0x40
#define                     SDB_NDS 0x20

typedef enum SDBRetrievalStatus_t {
    SDB_RET_SUCCESS = 0,
    SDB_RET_MORE_DATA = 1,
    SDB_RET_END_OF_FILE = 2
} SDBRetrievalStatus_t;

typedef enum SDBDriverState_t {
    SDB_NORMAL = 1,
    SDB_INITIALIZED = 2,
    SDB_INCONSISTENT = 3,
    SDB_UNINITIALIZED = 4,
    SDB_OLD_DATABASE = 5,
    SDB_SICK_DB_ENGINE = 6,
    SDB_UNLOADING = 7
} SDBDriverState_t;

typedef enum SDBAttrDataType_t {
    SDB_SHORT = 100,
    SDB_LONG = 200,
    SDB_STR = 300,
    SDB_BOOL = 400,
    SDB_STR_DN = 500,
    SDB_IPX = 600,
    SDB_IP = 700,
    SDB_ACL = 800,
    SDB_PHONE = 900
} SDBAttrDataType_t;

typedef short           SDBBulkAddIgnore_t;

typedef short           SDBMultiValOpt_t;

typedef short           SDBPrimaryKeyOpt_t;

typedef short           SDBQueryFlg_t;

typedef char            FAR *SDBAttrVariable_t;

typedef struct SDBAttrHdr_t {
    SDBAttributeID_t attrID;
    SDBAttrVariable_t attrDesc;
} SDBAttrHdr_t;

typedef struct SDBAttributeList_t {
    _Int             count;
    SDBAttrHdr_t    FAR *sdbAttrHdr;
} SDBAttributeList_t;

typedef SDBAttributeList_t SDBKeyList_t;

typedef struct SDBSelectAttrList_t {
    _Int             count;
    int             FAR *value;
} SDBSelectAttrList_t;

typedef struct SDBFileHdr_t {
    SDBFileType_t   fileType;
    SDBFileName_t   fileName;
} SDBFileHdr_t;

typedef struct SDBFileList_t {
    _Int             count;
    SDBFileHdr_t    FAR *sdbFileHdr;
} SDBFileList_t;

typedef struct SDBQryAttr_t {
    SDBAttributeID_t attrID;
    SDBAttributeName_t attrName;
    SDBAttributeID_t rootID;
    SDBAttrDataLength_t dataLen;
    SDBAttrDataType_t dataType;
    SDBPrimaryKeyOpt_t primaryKey;
    SDBMultiValOpt_t multiVal;
    SDBBulkAddIgnore_t baIgnore;
    SDBQueryFlg_t   flag1;
    SDBQueryFlg_t   flag2;
} SDBQryAttr_t;

typedef struct SDBQryAttrList_t {
    _Int             count;
    SDBQryAttr_t    FAR *sdbQryAttr;
} SDBQryAttrList_t;

typedef enum SDBSelectOpcodes_t {
    SDB_GET_ALL = 1,
    SDB_GET_EQUAL = 2,
    SDB_EXT_GET_EQUAL = 3,
    SDB_GET_GROUP = 4,
    SDB_EXT_GET_GROUP = 5
} SDBSelectOpcodes_t;

typedef enum SDBFailureCodes_t {
    SDB_CORRUPT_DICTNRY = 501,
    SDB_BAD_INDEX_FILE = 502,
    SDB_MISSING_DICTIONARY = 503,
    SDB_INVALID_STATE = 504,
    SDB_INVALID_ATTRIBUTE_TYPE = 505,
    SDB_TOO_MANY_ATTRIBUTES = 506,
    SDB_INVALID_FILE_TYPE = 507,
    SDB_ATTR_NOT_IN_FILE = 508,
    SDB_INVALID_COMMAND = 509,
    SDB_RECORD_NOT_FOUND = 510,
    SDB_DATABASE_ERROR = 511,
    SDB_INCONSISTENT_DATABASE = 512,
    SDB_INTERNAL_ERR = 513,
    SDB_CONNECTION_TABLE_FULL = 514,
    SDB_INVALID_CONNECTION_ID = 515,
    SDB_CONNECTION_NOT_ACTIVE = 516,
    SDB_INVALID_CONTEXT = 517,
    SDB_LOGIN_TABLE_FULL = 518,
    SDB_FAILED_LOGIN = 519,
    SDB_NO_PERMISSIONS = 520,
    SDB_INVALID_DATA = 521,
    SDB_MISSING_PRIMARY_KEY = 522,
    SDB_MANDATORY_ATTRIBUTE_MISSING = 523,
    SDB_INVALID_PRIMARY_KEY = 524,
    SDB_INVALID_KEY = 525,
    SDB_DUPLICATE_KEY = 526,
    SDB_MULTI_VAL_ATTR = 527,
    SDB_NOT_MULTI_VALUED = 528,
    SDB_INVALID_LIST_FILE = 529,
    SDB_CURSOR_NOT_ACTIVE = 530,
    SDB_CURSOR_SELECTION_NOT_SET = 531,
    SDB_INVALID_CURSOR_OP = 532,
    SDB_CURSOR_ALREADY_ACTIVE = 533,
    SDB_CURSOR_ACTIVE = 534,
    SDB_OBJECT_NOT_ACCESSED = 535,
    SDB_CONTENTION = 536,
    SDB_NO_MORE_DISK_SPACE = 537,
    SDB_NO_MEMORY = 538,
    SDB_MAX_OPEN_FILES_EXCEEDED = 539,
    SDB_NO_ACTIVE_TRANSACTION = 540,
    SDB_TRANSACTION_ALREADY_ACTIVE = 541,
    SDB_TRANSACTION_ERROR = 542,
    SDB_TRANSACTION_ABORTED = 543,
    SDB_INVALID_OPCODE = 544,
    SDB_INVALID_RTN_CNT = 545,
    SDB_BUF_TOO_SMALL = 546,
    SDB_KEY_SPECIFICATION = 547,
    SDB_ATTR_OVER_MAX = 548,
    SDB_ATTR_UNDER_MIN = 549,
    SDB_DATA_TOO_LARGE = 550,
    SDB_DOT_IN_KEY = 551,
    SDB_WRITE_FAILED = 552,
    SDB_READ_FAILURE = 553,
    SDB_FILE_NOT_PRESENT = 554,
    SDB_NO_INFORM1_LINE = 555,
    SDB_INVALID_ATTR_LIST = 556,
    SDB_INVALID_KEY_LIST = 557,
    SDB_INVALID_SELECT_LIST = 558,
    SDB_FOREIGN_KEY = 559,
    SDB_OLD_DICTIONARY_FAILURE = 560,
    SDB_UPGRADE_ERR = 561,
    SDB_FILE_ALREADY_EXISTS = 562,
    SDB_OPEN_SDB_LOG_FAILED = 563,
    SDB_WRITE_SDB_LOG_FAILED = 564,
    SDB_FILE_OPEN_FAILURE = 565,
    SDB_QUERY_VERS_FAILED = 566,
    SDB_BA_BACKUP_FAILED = 567,
    SDB_SIMPLE_UPDATE_FAILED = 568,
    SDB_QRY_FILES_FAILED = 569,
    SDB_QRY_ATTR_FAILED = 570,
    SDB_INVALID_INPUT_LINE = 571,
    SDB_CREATE_TMPLT_FAILED = 572,
    SDB_FLAT_UPDATE_FAILED = 573,
    SDB_CANT_MODIFY_MVATTR = 574,
    SDB_DUPLICATE_FILE_NAMES = 575,
    SDB_INVALID_VENDOR_LEN = 576,
    SDB_INVALID_SERVICE_LEN = 577,
    SDB_INVALID_SRV_TYPE = 578,
    SDB_INVALID_SRV_NAME_LEN = 579,
    SDB_ALLOC_RESOURCE_ERR = 580,
    SDB_INIT_TSRV_PASSWD_ERR = 581,
    SDB_GET_TSRV_DEFAULT_ERR = 582,
    SDB_TSRV_LOADED = 583,
    SDB_SCHEMA_CHANGE_ERR = 584,
    SDB_MUST_BE_CSTA = 585,
    SDB_INVALID_FILE_NM = 586,
    SDB_INVALID_FILE_FORMAT = 587,
    SDB_LAST_ADMIN_USER = 588,
    SDB_MIXED_VERSION_NUMBERS = 589,
    SDB_LAST_ERR = 599
} SDBFailureCodes_t;

typedef unsigned char   SDBOptions_t;
#define                     SDB_NON_FATAL 0x40
#define                     SDB_OVERWRITE 0x20
#define                     SDB_CONVERT_SIMPLE 0x10
#define                     SDB_CONVERT_FLAT 0x08

typedef unsigned char   SDBConvertOptions_t;
#define                     BTRV_TO_NDS 0x40
#define                     BTRV_TO_UNIX 0x20

typedef struct SDBOpenConnection_t {
    SDBContext_t    context;
    SDBLoginName_t  login;
} SDBOpenConnection_t;

typedef struct SDBOpenConnConfEvent_t {
    SDBConnectionID_t connID;
    SDBContext_t    context;
} SDBOpenConnConfEvent_t;

typedef struct SDBCloseConnection_t {
    SDBConnectionID_t connID;
} SDBCloseConnection_t;

typedef struct SDBCloseConnConfEvent_t {
    Nulltype        null;
} SDBCloseConnConfEvent_t;

typedef struct SDBInsertObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *attrList;
} SDBInsertObject_t;

typedef struct SDBInsertObjectConfEvent_t {
    Nulltype        null;
} SDBInsertObjectConfEvent_t;

typedef struct SDBInsertAttribute_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *keyList;
    struct SDBAttributeList_t FAR *attrList;
} SDBInsertAttribute_t;

typedef struct SDBInsertAttributeConfEvent_t {
    Nulltype        null;
} SDBInsertAttributeConfEvent_t;

typedef struct SDBDeleteObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *keyList;
} SDBDeleteObject_t;

typedef struct SDBDeleteObjectConfEvent_t {
    Nulltype        null;
} SDBDeleteObjectConfEvent_t;

typedef struct SDBDeleteAttribute_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *keyList;
    struct SDBAttributeList_t FAR *attrList;
} SDBDeleteAttribute_t;

typedef struct SDBDeleteAttributeConfEvent_t {
    Nulltype        null;
} SDBDeleteAttributeConfEvent_t;

typedef struct SDBSelectObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *keyList;
    SDBSelectOpcodes_t opcode;
    struct SDBSelectAttrList_t FAR *attrList;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBSelectObject_t;

typedef struct SDBSelectObjectConfEvent_t {
    struct SDBAttributeList_t FAR *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBSelectObjectConfEvent_t;

typedef struct SDBOpenCursor_t {
    SDBConnectionID_t connID;
} SDBOpenCursor_t;

typedef struct SDBOpenCursorConfEvent_t {
    Nulltype        null;
} SDBOpenCursorConfEvent_t;

typedef struct SDBFetchCursor_t {
    SDBConnectionID_t connID;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBFetchCursor_t;

typedef struct SDBFetchCursorConfEvent_t {
    struct SDBAttributeList_t FAR *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBFetchCursorConfEvent_t;

typedef struct SDBCloseCursor_t {
    SDBConnectionID_t connID;
} SDBCloseCursor_t;

typedef struct SDBCloseCursorConfEvent_t {
    Nulltype        null;
} SDBCloseCursorConfEvent_t;

typedef struct SDBModifyObject_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    struct SDBAttributeList_t FAR *keyList;
    struct SDBAttributeList_t FAR *attrList;
} SDBModifyObject_t;

typedef struct SDBModifyObjectConfEvent_t {
    Nulltype        null;
} SDBModifyObjectConfEvent_t;

typedef struct SDBStartTrans_t {
    SDBConnectionID_t connID;
} SDBStartTrans_t;

typedef struct SDBStartTransConfEvent_t {
    Nulltype        null;
} SDBStartTransConfEvent_t;

typedef struct SDBCommitTrans_t {
    SDBConnectionID_t connID;
} SDBCommitTrans_t;

typedef struct SDBCommitTransConfEvent_t {
    Nulltype        null;
} SDBCommitTransConfEvent_t;

typedef struct SDBRollbackTrans_t {
    SDBConnectionID_t connID;
} SDBRollbackTrans_t;

typedef struct SDBRollbackTransConfEvent_t {
    Nulltype        null;
} SDBRollbackTransConfEvent_t;

typedef struct SDBBackupDataBase_t {
    SDBFileName_t   fileNm;
    SDBComments_t   comments;
} SDBBackupDataBase_t;

typedef struct SDBBackupDataBaseConfEvent_t {
    Nulltype        null;
} SDBBackupDataBaseConfEvent_t;

typedef struct SDBUpdateDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
    SDBErrorFileName_t errorFile;
    SDBOptions_t    options;
} SDBUpdateDataBase_t;

typedef struct SDBUpdateDataBaseConfEvent_t {
    Nulltype        null;
} SDBUpdateDataBaseConfEvent_t;

typedef struct SDBCreateTemplate_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
} SDBCreateTemplate_t;

typedef struct SDBCreateTemplateConfEvent_t {
    Nulltype        null;
} SDBCreateTemplateConfEvent_t;

typedef struct SDBQueryVersions_t {
    Nulltype        null;
} SDBQueryVersions_t;

typedef struct SDBQueryVersionsConfEvent_t {
    SDBVersion_t    dataDictionaryVersion;
    SDBVersion_t    oldDictionaryVersion;
    SDBVersion_t    overallVersion;
    SDBVersion_t    userVersion;
    SDBVersion_t    worktopVersion;
    SDBVersion_t    deviceVersion;
    SDBVersion_t    dlistVersion;
    SDBVersion_t    tlinkVersion;
    SDBVersion_t    tlistVersion;
    SDBVersion_t    oamlistVersion;
    SDBVersion_t    tservVersion;
    SDBDriverType_t driverType;
    SDBVersion_t    driverVersion;
    SDBVersion_t    tsrvnlmVersion;
    SDBDriverState_t driverState;
    SDBBtrvVersion_t btrvVersion;
} SDBQueryVersionsConfEvent_t;

typedef struct SDBQueryFiles_t {
    SDBBufferSize_t bufSize;
} SDBQueryFiles_t;

typedef struct SDBQueryFilesConfEvent_t {
    struct SDBFileList_t FAR *fileList;
} SDBQueryFilesConfEvent_t;

typedef struct SDBQueryAttributes_t {
    SDBFileType_t   fileType;
    SDBBufferSize_t bufSize;
    SDBReturnedCount_t retrnCnt;
} SDBQueryAttributes_t;

typedef struct SDBQueryAttributesConfEvent_t {
    struct SDBQryAttrList_t FAR *attrList;
    SDBReturnedCount_t retrnCnt;
    SDBRetrievalStatus_t status;
} SDBQueryAttributesConfEvent_t;

typedef struct SDBFileReadList_t {
    _Int             count;
    SDBFileReadCount_t FAR *sdbFileRd;
} SDBFileReadList_t;

typedef struct SDBQueryStatus_t {
    Nulltype        null;
} SDBQueryStatus_t;

typedef struct SDBQueryStatusConfEvent_t {
    SDBConnectCount_t sdbConns;
    SDBMemoryUsed_t memUsed;
    SDBFileReadList_t fileRd;
} SDBQueryStatusConfEvent_t;

typedef struct SDBUniversalFailureConfEvent_t {
    SDBFailureCodes_t error;
    SDBAttributeID_t attrID;
} SDBUniversalFailureConfEvent_t;

typedef struct SDBUniversalFailureEvent_t {
    SDBFailureCodes_t error;
} SDBUniversalFailureEvent_t;

typedef struct SDBSelectKey_t {
    SDBConnectionID_t connID;
    SDBFileType_t   fileType;
    SDBAttributeID_t key;
    SDBAttrHdr_t    filter;
    SDBBufferSize_t bufSize;
} SDBSelectKey_t;

typedef struct SDBSelectKeyConfEvent_t {
    SDBRetrievalStatus_t status;
    struct {
        short           length;
        unsigned char   FAR *value;
    } keyList;
} SDBSelectKeyConfEvent_t;

typedef struct SDBConvertDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBFlatFileName_t finalFile;
    SDBErrorFileName_t errorFile;
    SDBConvertOptions_t options;
    SDBContext_t    context;
} SDBConvertDataBase_t;

typedef struct SDBConvertDataBaseConfEvent_t {
    Nulltype        null;
} SDBConvertDataBaseConfEvent_t;

typedef struct SDBBackupNdsDataBase_t {
    SDBFileName_t   fileNm;
    SDBComments_t   comments;
    SDBContext_t    context;
} SDBBackupNdsDataBase_t;

typedef struct SDBBackupNdsDataBaseConfEvent_t {
    Nulltype        null;
} SDBBackupNdsDataBaseConfEvent_t;

typedef struct SDBUpdateNdsDataBase_t {
    SDBFlatFileName_t flatFile;
    SDBSimpleFileName_t simpleFile;
    SDBErrorFileName_t errorFile;
    SDBOptions_t    options;
    SDBContext_t    context;
} SDBUpdateNdsDataBase_t;

typedef struct SDBUpdateNdsDataBaseConfEvent_t {
    Nulltype        null;
} SDBUpdateNdsDataBaseConfEvent_t;

typedef struct SDBSetSdbLogOptions_t {
    Boolean         logSdbChanges;
    SDBLogPath_t    logPath;
    long            sdbLogSize;
} SDBSetSdbLogOptions_t;

typedef struct SDBSetSdbLogOptionsConfEvent_t {
    Nulltype        null;
} SDBSetSdbLogOptionsConfEvent_t;

typedef struct SDBGetSdbLogOptions_t {
    Nulltype        null;
} SDBGetSdbLogOptions_t;

typedef struct SDBGetSdbLogOptionsConfEvent_t {
    Boolean         logSdbChanges;
    SDBLogPath_t    logPath;
    long            sdbLogSize;
} SDBGetSdbLogOptionsConfEvent_t;

typedef struct SDBGetConnections_t {
    Nulltype        null;
} SDBGetConnections_t;

typedef struct SDBGetConnectionsConfEvent_t {
    long            sdbConns;
} SDBGetConnectionsConfEvent_t;

typedef char            SDBAboutString[41];

typedef struct SDBGetAboutInfo_t {
    Nulltype        null;
} SDBGetAboutInfo_t;

typedef struct SDBGetAbout_t {
    SDBVersion_t    aboutVer;
    SDBAboutString  aboutString;
} SDBGetAbout_t;

typedef struct SDBGetAboutList_t {
    _Int             count;
    SDBGetAbout_t   FAR *aboutList;
} SDBGetAboutList_t;

typedef struct SDBGetAboutConfEvent_t {
    long            numLeft;
    SDBGetAboutList_t aboutInfo;
} SDBGetAboutConfEvent_t;

typedef struct SDBGetAdminInfo_t {
    Nulltype        null;
} SDBGetAdminInfo_t;

typedef struct SDBGetAdminInfoConfEvent_t {
    Boolean         workStation;
    Boolean         autoAdmin;
} SDBGetAdminInfoConfEvent_t;

typedef struct SDBSetAdminInfo_t {
    Boolean         workStation;
    Boolean         autoAdmin;
} SDBSetAdminInfo_t;

typedef struct SDBSetAdminInfoConfEvent_t {
    Nulltype        null;
} SDBSetAdminInfoConfEvent_t;

typedef struct SDBGetTcpInfo_t {
    Nulltype        null;
} SDBGetTcpInfo_t;

typedef struct SDBGetTcpInfoConfEvent_t {
    SDBIPNameFormat_t tcpNameFormat;
} SDBGetTcpInfoConfEvent_t;

typedef struct SDBSetTcpInfo_t {
    SDBIPNameFormat_t tcpNameFormat;
} SDBSetTcpInfo_t;

typedef struct SDBSetTcpInfoConfEvent_t {
    Nulltype        null;
} SDBSetTcpInfoConfEvent_t;


extern void FAR *sdb_asn_tbl;    /* encoder-decoder control table */

#endif
