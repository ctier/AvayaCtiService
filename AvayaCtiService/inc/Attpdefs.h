/************************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/************************************************************/
/* abstract syntax: att_asn_tbl */
/* last module in input: ATT-private-identifiers */
/* created: Mon Jul  2 11:18:01 2001 */
/* associated control file: attpdefs.c */

#ifndef ATTPDEFS_H
#define ATTPDEFS_H

#include "cstadefs.h"


#define          ATTV5_CLEAR_CONNECTION 1
#define			FIRST_PRIV_TYPE  ATTV5_CLEAR_CONNECTION
#define          ATTV5_CONSULTATION_CALL 2
#define          ATTV5_MAKE_CALL 3
#define          ATTV5_DIRECT_AGENT_CALL 4
#define          ATTV5_MAKE_PREDICTIVE_CALL 5
#define          ATTV5_SUPERVISOR_ASSIST_CALL 6
#define          ATTV5_RECONNECT_CALL 7
#define          ATTV4_SENDDTMF_TONE 8
#define          ATT_SENDDTMF_TONE_CONF 9
#define          ATTV4_SET_AGENT_STATE 10
#define          ATT_QUERY_ACD_SPLIT 11
#define          ATT_QUERY_ACD_SPLIT_CONF 12
#define          ATT_QUERY_AGENT_LOGIN 13
#define          ATT_QUERY_AGENT_LOGIN_CONF 14
#define          ATT_QUERY_AGENT_LOGIN_RESP 15
#define          ATT_QUERY_AGENT_STATE 16
#define          ATTV4_QUERY_AGENT_STATE_CONF 17
#define          ATT_QUERY_CALL_CLASSIFIER 18
#define          ATT_QUERY_CALL_CLASSIFIER_CONF 19
#define          ATTV4_QUERY_DEVICE_INFO_CONF 20
#define          ATT_QUERY_MWI_CONF 21
#define          ATT_QUERY_STATION_STATUS 22
#define          ATT_QUERY_STATION_STATUS_CONF 23
#define          ATT_QUERY_TOD 24
#define          ATT_QUERY_TOD_CONF 25
#define          ATT_QUERY_TG 26
#define          ATT_QUERY_TG_CONF 27
#define          ATTV4_SNAPSHOT_DEVICE_CONF 28
#define          ATTV4_MONITOR_FILTER 29
#define          ATTV4_MONITOR_CONF 30
#define          ATT_MONITOR_STOP_ON_CALL 31
#define          ATT_MONITOR_STOP_ON_CALL_CONF 32
#define          ATTV4_MONITOR_CALL_CONF 33
#define          ATT_CALL_CLEARED 34
#define          ATTV3_CONFERENCED 35
#define          ATTV5_CONNECTION_CLEARED 36
#define          ATTV3_DELIVERED 37
#define          ATT_ENTERED_DIGITS 38
#define          ATTV3_ESTABLISHED 39
#define          ATTV4_NETWORK_REACHED 40
#define          ATTV3_TRANSFERRED 41
#define          ATTV4_ROUTE_REQUEST 42
#define          ATTV5_ROUTE_SELECT 43
#define          ATT_ROUTE_USED 44
#define          ATT_SYS_STAT 45
#define          ATTV3_LINK_STATUS 46
#define          ATTV5_ORIGINATED 47
#define          ATT_LOGGED_ON 48
#define          ATT_QUERY_DEVICE_NAME 49
#define          ATTV4_QUERY_DEVICE_NAME_CONF 50
#define          ATT_QUERY_AGENT_MEASUREMENTS 51
#define          ATT_QUERY_AGENT_MEASUREMENTS_CONF 52
#define          ATT_QUERY_SPLIT_SKILL_MEASUREMENTS 53
#define          ATT_QUERY_SPLIT_SKILL_MEASUREMENTS_CONF 54
#define          ATT_QUERY_TRUNK_GROUP_MEASUREMENTS 55
#define          ATT_QUERY_TRUNK_GROUP_MEASUREMENTS_CONF 56
#define          ATT_QUERY_VDN_MEASUREMENTS 57
#define          ATT_QUERY_VDN_MEASUREMENTS_CONF 58
#define          ATTV4_CONFERENCED 59
#define          ATTV4_DELIVERED 60
#define          ATTV4_ESTABLISHED 61
#define          ATTV4_TRANSFERRED 62
#define          ATTV4_LINK_STATUS 63
#define          ATTV4_GETAPI_CAPS_CONF 64
#define          ATT_SINGLE_STEP_CONFERENCE_CALL 65
#define          ATT_SINGLE_STEP_CONFERENCE_CALL_CONF 66
#define          ATT_SELECTIVE_LISTENING_HOLD 67
#define          ATT_SELECTIVE_LISTENING_HOLD_CONF 68
#define          ATT_SELECTIVE_LISTENING_RETRIEVE 69
#define          ATT_SELECTIVE_LISTENING_RETRIEVE_CONF 70
#define          ATT_SENDDTMF_TONE 71
#define          ATT_SNAPSHOT_DEVICE_CONF 72
#define          ATT_LINK_STATUS 73
#define          ATT_SET_BILL_RATE 74
#define          ATT_SET_BILL_RATE_CONF 75
#define          ATT_QUERY_UCID 76
#define          ATT_QUERY_UCID_CONF 77
#define          ATTV5_CONFERENCED 78
#define          ATT_LOGGED_OFF 79
#define          ATTV5_DELIVERED 80
#define          ATTV5_ESTABLISHED 81
#define          ATTV5_TRANSFERRED 82
#define          ATTV5_ROUTE_REQUEST 83
#define          ATT_CONSULTATION_CALL_CONF 84
#define          ATT_MAKE_CALL_CONF 85
#define          ATT_MAKE_PREDICTIVE_CALL_CONF 86
#define          ATTV5_SET_AGENT_STATE 87
#define          ATTV5_QUERY_AGENT_STATE_CONF 88
#define          ATT_QUERY_DEVICE_NAME_CONF 89
#define          ATT_CONFERENCE_CALL_CONF 90
#define          ATT_TRANSFER_CALL_CONF 91
#define          ATT_MONITOR_FILTER 92
#define          ATT_MONITOR_CONF 93
#define          ATT_MONITOR_CALL_CONF 94
#define          ATT_SERVICE_INITIATED 95
#define          ATT_CHARGE_ADVICE 96
#define          ATT_GETAPI_CAPS_CONF 97
#define          ATT_QUERY_DEVICE_INFO_CONF 98
#define          ATT_SET_ADVICE_OF_CHARGE 99
#define          ATT_SET_ADVICE_OF_CHARGE_CONF 100
#define          ATT_NETWORK_REACHED 101
#define          ATT_SET_AGENT_STATE 102
#define          ATT_SET_AGENT_STATE_CONF 103
#define          ATT_QUERY_AGENT_STATE_CONF 104
#define          ATT_ROUTE_REQUEST 105
#define          ATT_TRANSFERRED 106
#define          ATT_CONFERENCED 107
#define          ATT_CLEAR_CONNECTION 108
#define          ATT_CONSULTATION_CALL 109
#define          ATT_MAKE_CALL 110
#define          ATT_DIRECT_AGENT_CALL 111
#define          ATT_MAKE_PREDICTIVE_CALL 112
#define          ATT_SUPERVISOR_ASSIST_CALL 113
#define          ATT_RECONNECT_CALL 114
#define          ATT_CONNECTION_CLEARED 115
#define          ATT_ROUTE_SELECT 116
#define          ATT_DELIVERED 117
#define          ATT_ESTABLISHED 118
#define          ATT_ORIGINATED 119
#define	LAST_PRIV_TYPE  ATT_ORIGINATED // Please keep this up to data when private types are added

#define EXPOSED_PRIV_TYPE LAST_PRIV_TYPE

typedef enum ATTUUIProtocolType_t {
    UUI_NONE = -1,
    UUI_USER_SPECIFIC = 0,
    UUI_IA5_ASCII = 4
} ATTUUIProtocolType_t;

typedef struct ATTV5UserToUserInfo_t {
    ATTUUIProtocolType_t type;
    struct {
        short           length;
        unsigned char   value[33];
    } data;
} ATTV5UserToUserInfo_t;

typedef enum ATTInterflow_t {
    LAI_NO_INTERFLOW = -1,
    LAI_ALL_INTERFLOW = 0,
    LAI_THRESHOLD_INTERFLOW = 1,
    LAI_VECTORING_INTERFLOW = 2
} ATTInterflow_t;

typedef enum ATTPriority_t {
    LAI_NOT_IN_QUEUE = 0,
    LAI_LOW = 1,
    LAI_MEDIUM = 2,
    LAI_HIGH = 3,
    LAI_TOP = 4
} ATTPriority_t;


typedef struct ATTV4LookaheadInfo_t {
    ATTInterflow_t  type;
    ATTPriority_t   priority;
    short           hours;
    short           minutes;
    short           seconds;
    DeviceID_t      sourceVDN;
} ATTV4LookaheadInfo_t;

typedef enum ATTUserEnteredCodeType_t {
    UE_NONE = -1,
    UE_ANY = 0,
    UE_LOGIN_DIGITS = 2,
    UE_CALL_PROMPTER = 5,
    UE_DATA_BASE_PROVIDED = 17,
    UE_TONE_DETECTOR = 32
} ATTUserEnteredCodeType_t;

typedef enum ATTUserEnteredCodeIndicator_t {
    UE_COLLECT = 0,
    UE_ENTERED = 1
} ATTUserEnteredCodeIndicator_t;

typedef struct ATTUserEnteredCode_t {
    ATTUserEnteredCodeType_t type;
    ATTUserEnteredCodeIndicator_t indicator;
    char            data[25];
    DeviceID_t      collectVDN;
} ATTUserEnteredCode_t;


typedef struct ATTV4ConnIDList_t {
    short           count;
    ConnectionID_t  party[5];
} ATTV4ConnIDList_t;

typedef enum ATTProgressLocation_t {
    PL_NONE = -1,
    PL_USER = 0,
    PL_PUB_LOCAL = 1,
    PL_PUB_REMOTE = 4,
    PL_PRIV_REMOTE = 5
} ATTProgressLocation_t;

typedef enum ATTProgressDescription_t {
    PD_NONE = -1,
    PD_CALL_OFF_ISDN = 1,
    PD_DEST_NOT_ISDN = 2,
    PD_ORIG_NOT_ISDN = 3,
    PD_CALL_ON_ISDN = 4,
    PD_INBAND = 8
} ATTProgressDescription_t;

typedef enum ATTWorkMode_t {
    WM_NONE = -1,
    WM_AUX_WORK = 1,
    WM_AFTCAL_WK = 2,
    WM_AUTO_IN = 3,
    WM_MANUAL_IN = 4
} ATTWorkMode_t;

typedef enum ATTTalkState_t {
    TS_ON_CALL = 0,
    TS_IDLE = 1
} ATTTalkState_t;

typedef enum ATTExtensionClass_t {
    EC_VDN = 0,
    EC_ACD_SPLIT = 1,
    EC_ANNOUNCEMENT = 2,
    EC_DATA = 4,
    EC_ANALOG = 5,
    EC_PROPRIETARY = 6,
    EC_BRI = 7,
    EC_CTI = 8,
    EC_LOGICAL_AGENT = 9,
    EC_OTHER = 10
} ATTExtensionClass_t;

typedef enum ATTAnswerTreat_t {
    AT_NO_TREATMENT = 0,
    AT_NONE = 1,
    AT_DROP = 2,
    AT_CONNECT = 3
} ATTAnswerTreat_t;

typedef unsigned char   ATTMwiApplication_t;
#define                     AT_MCS 0x01
#define                     AT_VOICE 0x02
#define                     AT_PROPMGT 0x04
#define                     AT_LWC 0x08
#define                     AT_CTI 0x10

typedef unsigned char   ATTV4PrivateFilter_t;
#define                     ATT_V4_ENTERED_DIGITS_FILTER 0x80





typedef struct ATTV4SnapshotCall_t {
    short           count;
    CSTASnapshotCallResponseInfo_t info[6];
} ATTV4SnapshotCall_t;

typedef enum ATTLocalCallState_t {
    ATT_CS_INITIATED = 1,
    ATT_CS_ALERTING = 2,
    ATT_CS_CONNECTED = 3,
    ATT_CS_HELD = 4,
    ATT_CS_BRIDGED = 5,
    ATT_CS_OTHER = 6
} ATTLocalCallState_t;

typedef struct ATTSnapshotDevice_t {
    ConnectionID_t  call;
    ATTLocalCallState_t state;
} ATTSnapshotDevice_t;

typedef enum ATTCollectCodeType_t {
    UC_NONE = 0,
    UC_TONE_DETECTOR = 32
} ATTCollectCodeType_t;

typedef enum ATTProvidedCodeType_t {
    UP_NONE = 0,
    UP_DATA_BASE_PROVIDED = 17
} ATTProvidedCodeType_t;

typedef struct ATTUserProvidedCode_t {
    ATTProvidedCodeType_t type;
    char            data[25];
} ATTUserProvidedCode_t;

typedef enum ATTSpecificEvent_t {
    SE_ANSWER = 11,
    SE_DISCONNECT = 4
} ATTSpecificEvent_t;

typedef struct ATTUserCollectCode_t {
    ATTCollectCodeType_t type;
    short           digitsToBeCollected;
    short           timeout;
    ConnectionID_t  collectParty;
    ATTSpecificEvent_t specificEvent;
} ATTUserCollectCode_t;

typedef enum ATTDropResource_t {
    DR_NONE = -1,
    DR_CALL_CLASSIFIER = 0,
    DR_TONE_GENERATOR = 1
} ATTDropResource_t;

typedef struct ATTV5ClearConnection_t {
    ATTDropResource_t dropResource;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ClearConnection_t;

typedef struct ATTV5ConsultationCall_t {
    DeviceID_t      destRoute;
    Boolean         priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ConsultationCall_t;

typedef struct ATTV5MakeCall_t {
    DeviceID_t      destRoute;
    Boolean         priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5MakeCall_t;

typedef struct ATTV5DirectAgentCall_t {
    DeviceID_t      split;
    Boolean         priorityCalling;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5DirectAgentCall_t;

typedef struct ATTV5MakePredictiveCall_t {
    Boolean         priorityCalling;
    short           maxRings;
    ATTAnswerTreat_t answerTreat;
    DeviceID_t      destRoute;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5MakePredictiveCall_t;

typedef struct ATTV5SupervisorAssistCall_t {
    DeviceID_t      split;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5SupervisorAssistCall_t;

typedef struct ATTV5ReconnectCall_t {
    ATTDropResource_t dropResource;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ReconnectCall_t;

typedef struct ATTV4SendDTMFTone_t {
    ConnectionID_t  sender;
    ATTV4ConnIDList_t receivers;
    char            tones[33];
    short           toneDuration;
    short           pauseDuration;
} ATTV4SendDTMFTone_t;

typedef struct ATTSendDTMFToneConfEvent_t {
    Nulltype        null;
} ATTSendDTMFToneConfEvent_t;

typedef struct ATTV4SetAgentState_t {
    ATTWorkMode_t   workMode;
} ATTV4SetAgentState_t;

typedef struct ATTQueryAcdSplit_t {
    DeviceID_t      device;
} ATTQueryAcdSplit_t;

typedef struct ATTQueryAcdSplitConfEvent_t {
    short           availableAgents;
    short           callsInQueue;
    short           agentsLoggedIn;
} ATTQueryAcdSplitConfEvent_t;

typedef struct ATTQueryAgentLogin_t {
    DeviceID_t      device;
} ATTQueryAgentLogin_t;

typedef long            ATTPrivEventCrossRefID_t;

typedef struct ATTQueryAgentLoginConfEvent_t {
    ATTPrivEventCrossRefID_t privEventCrossRefID;
} ATTQueryAgentLoginConfEvent_t;

typedef struct ATTQueryAgentLoginResp_t {
    ATTPrivEventCrossRefID_t privEventCrossRefID;
    struct {
        short           count;
        DeviceID_t      device[10];
    } list;
} ATTQueryAgentLoginResp_t;

typedef struct ATTQueryAgentState_t {
    DeviceID_t      split;
} ATTQueryAgentState_t;

typedef struct ATTV4QueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
} ATTV4QueryAgentStateConfEvent_t;

typedef struct ATTQueryCallClassifier_t {
    Nulltype        null;
} ATTQueryCallClassifier_t;

typedef struct ATTQueryCallClassifierConfEvent_t {
    short           numAvailPorts;
    short           numInUsePorts;
} ATTQueryCallClassifierConfEvent_t;

typedef struct ATTV4QueryDeviceInfoConfEvent_t {
    ATTExtensionClass_t extensionClass;
} ATTV4QueryDeviceInfoConfEvent_t;

typedef struct ATTQueryMwiConfEvent_t {
    ATTMwiApplication_t applicationType;
} ATTQueryMwiConfEvent_t;

typedef struct ATTQueryStationStatus_t {
    DeviceID_t      device;
} ATTQueryStationStatus_t;

typedef struct ATTQueryStationStatusConfEvent_t {
    Boolean         stationStatus;
} ATTQueryStationStatusConfEvent_t;

typedef struct ATTQueryTod_t {
    Nulltype        null;
} ATTQueryTod_t;

typedef struct ATTQueryTodConfEvent_t {
    short           year;
    short           month;
    short           day;
    short           hour;
    short           minute;
    short           second;
} ATTQueryTodConfEvent_t;

typedef struct ATTQueryTg_t {
    DeviceID_t      device;
} ATTQueryTg_t;

typedef struct ATTQueryTgConfEvent_t {
    short           idleTrunks;
    short           usedTrunks;
} ATTQueryTgConfEvent_t;

typedef struct ATTV4SnapshotDeviceConfEvent_t {
    short           count;
    ATTSnapshotDevice_t snapshotDevice[6];
} ATTV4SnapshotDeviceConfEvent_t;

typedef struct ATTV4MonitorFilter_t {
    ATTV4PrivateFilter_t privateFilter;
} ATTV4MonitorFilter_t;

typedef struct ATTV4MonitorConfEvent_t {
    ATTV4PrivateFilter_t usedFilter;
} ATTV4MonitorConfEvent_t;


typedef struct ATTMonitorStopOnCall_t {
    CSTAMonitorCrossRefID_t monitorCrossRefID;
    ConnectionID_t  call;
} ATTMonitorStopOnCall_t;

typedef struct ATTMonitorStopOnCallConfEvent_t {
    Nulltype        null;
} ATTMonitorStopOnCallConfEvent_t;

typedef struct ATTV4MonitorCallConfEvent_t {
    ATTV4PrivateFilter_t usedFilter;
    ATTV4SnapshotCall_t snapshotCall;
} ATTV4MonitorCallConfEvent_t;

typedef enum ATTReasonCode_t {
    AR_NONE = 0,
    AR_ANSWER_NORMAL = 1,
    AR_ANSWER_TIMED = 2,
    AR_ANSWER_VOICE_ENERGY = 3,
    AR_ANSWER_MACHINE_DETECTED = 4,
    AR_SIT_REORDER = 5,
    AR_SIT_NO_CIRCUIT = 6,
    AR_SIT_INTERCEPT = 7,
    AR_SIT_VACANT_CODE = 8,
    AR_SIT_INEFFECTIVE_OTHER = 9,
    AR_SIT_UNKNOWN = 10,
    AR_IN_QUEUE = 11,
    AR_SERVICE_OBSERVER = 12
} ATTReasonCode_t;

typedef enum ATTReasonForCallInfo_t {
    OR_NONE = 0,
    OR_CONSULTATION = 1,
    OR_CONFERENCED = 2,
    OR_TRANSFERRED = 3,
    OR_NEW_CALL = 4
} ATTReasonForCallInfo_t;


typedef struct ATTV4OriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV4OriginalCallInfo_t;

typedef struct ATTCallClearedEvent_t {
    ATTReasonCode_t reason;
} ATTCallClearedEvent_t;

typedef struct ATTV3ConferencedEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3ConferencedEvent_t;

typedef struct ATTV5ConnectionClearedEvent_t {
    ATTV5UserToUserInfo_t userInfo;
} ATTV5ConnectionClearedEvent_t;

typedef enum ATTDeliveredType_t {
    DELIVERED_TO_ACD = 1,
    DELIVERED_TO_STATION = 2,
    DELIVERED_OTHER = 3
} ATTDeliveredType_t;

typedef struct ATTV3DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3DeliveredEvent_t;


typedef struct ATTEnteredDigitsEvent_t {
    ConnectionID_t  connection;
    char            digits[25];
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} ATTEnteredDigitsEvent_t;

typedef struct ATTV3EstablishedEvent_t {
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3EstablishedEvent_t;

typedef struct ATTV4NetworkReachedEvent_t {
    ATTProgressLocation_t progressLocation;
    ATTProgressDescription_t progressDescription;
} ATTV4NetworkReachedEvent_t;

typedef struct ATTV3TransferredEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
} ATTV3TransferredEvent_t;

typedef struct ATTV4RouteRequestEvent_t {
    DeviceID_t      trunk;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV4RouteRequestEvent_t;

typedef struct ATTV5RouteSelect_t {
    DeviceID_t      callingDevice;
    DeviceID_t      directAgentCallSplit;
    Boolean         priorityCalling;
    DeviceID_t      destRoute;
    ATTUserCollectCode_t collectCode;
    ATTUserProvidedCode_t userProvidedCode;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5RouteSelect_t;

typedef struct ATTRouteUsedEvent_t {
    DeviceID_t      destRoute;
} ATTRouteUsedEvent_t;

typedef struct ATTSysStat_t {
    Boolean         linkStatusReq;
} ATTSysStat_t;

typedef enum ATTLinkState_t {
    LS_LINK_UNAVAIL = 0,
    LS_LINK_UP = 1,
    LS_LINK_DOWN = 2
} ATTLinkState_t;

typedef struct ATTLinkStatus_t {
    short           linkID;
    ATTLinkState_t  linkState;
} ATTLinkStatus_t;

typedef struct ATTV3LinkStatusEvent_t {
    short           count;
    ATTLinkStatus_t linkStatus[4];
} ATTV3LinkStatusEvent_t;

typedef struct ATTV5OriginatedEvent_t {
    DeviceID_t      logicalAgent;
    ATTV5UserToUserInfo_t userInfo;
} ATTV5OriginatedEvent_t;

typedef struct ATTLoggedOnEvent_t {
    ATTWorkMode_t   workMode;
} ATTLoggedOnEvent_t;

typedef enum ATTDeviceType_t {
    ATT_DT_ACD_SPLIT = 1,
    ATT_DT_ANNOUNCEMENT = 2,
    ATT_DT_DATA = 3,
    ATT_DT_LOGICAL_AGENT = 4,
    ATT_DT_STATION = 5,
    ATT_DT_TRUNK_ACCESS_CODE = 6,
    ATT_DT_VDN = 7
} ATTDeviceType_t;

typedef struct ATTQueryDeviceName_t {
    DeviceID_t      device;
} ATTQueryDeviceName_t;

typedef struct ATTV4QueryDeviceNameConfEvent_t {
    ATTDeviceType_t deviceType;
    DeviceID_t      device;
    char            name[16];
} ATTV4QueryDeviceNameConfEvent_t;

typedef enum ATTAgentTypeID_t {
    EXTENSION_ID = 0,
    LOGICAL_ID = 1
} ATTAgentTypeID_t;

typedef enum ATTSplitSkill_t {
    SPLIT_SKILL_NONE = -1,
    SPLIT_SKILL_ALL = 0,
    SPLIT_SKILL1 = 1,
    SPLIT_SKILL2 = 2,
    SPLIT_SKILL3 = 3,
    SPLIT_SKILL4 = 4
} ATTSplitSkill_t;

typedef short           ATTInterval_t;
#define                     intvCurrent -1
#define                     intvDay -2
#define                     intvLast -3

typedef struct ATTAgentMeasurements_t {
    long            acdCalls;
    char            extension[6];
    char            name[16];
    unsigned char   state;
    long            avgACDTalkTime;
    long            avgExtensionTime;
    long            callRate;
    short           elapsedTime;
    long            extensionCalls;
    long            extensionIncomingCalls;
    long            extensionOutgoingCalls;
    long            shiftACDCalls;
    long            shiftAvgACDTalkTime;
    short           splitAcceptableSvcLevel;
    long            splitACDCalls;
    long            splitAfterCallSessions;
    short           splitAgentsAvailable;
    short           splitAgentsInAfterCall;
    short           splitAgentsInAux;
    short           splitAgentsInOther;
    short           splitAgentsOnACDCalls;
    short           splitAgentsOnExtCalls;
    short           splitAgentsStaffed;
    long            splitAvgACDTalkTime;
    long            splitAvgAfterCallTime;
    short           splitAvgSpeedOfAnswer;
    short           splitAvgTimeToAbandon;
    long            splitCallRate;
    long            splitCallsAbandoned;
    long            splitCallsFlowedIn;
    long            splitCallsFlowedOut;
    short           splitCallsWaiting;
    char            splitName[16];
    short           splitNumber;
    char            splitExtension[6];
    char            splitObjective[6];
    short           splitOldestCallWaiting;
    unsigned char   splitPercentInSvcLevel;
    long            splitTotalACDTalkTime;
    long            splitTotalAfterCallTime;
    long            splitTotalAuxTime;
    long            timeAgentEnteredState;
    long            totalACDTalkTime;
    long            totalAfterCallTime;
    long            totalAuxTime;
    long            totalAvailableTime;
    long            totalHoldTime;
    long            totalStaffedTime;
    long            totalACDCallTime;
    long            avgACDCallTime;
} ATTAgentMeasurements_t;

typedef struct ATTSplitSkillMeasurements_t {
    short           acceptableSvcLevel;
    long            acdCalls;
    long            afterCallSessions;
    short           agentsAvailable;
    short           agentsInAfterCall;
    short           agentsInAux;
    short           agentsInOther;
    short           onACDCalls;
    short           agentsOnExtensionCalls;
    short           agentsStaffed;
    long            avgACDTalkTime;
    long            afterCallTime;
    short           avgSpeedOfAnswer;
    short           avgTimeToAbandon;
    long            callRate;
    long            callsAbandoned;
    long            callsFlowedIn;
    long            callsFlowedOut;
    short           callsWaiting;
    short           oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    char            name[16];
    char            extension[6];
    short           number;
    char            objective[6];
    long            totalAfterCallTime;
    long            totalAuxTime;
    long            totalACDTalkTime;
} ATTSplitSkillMeasurements_t;

typedef struct ATTTrunkGroupMeasurements_t {
    long            avgIncomingCallTime;
    long            avgOutgoingCallTime;
    long            incomingAbandonedCalls;
    long            incomingCalls;
    long            incomingUsage;
    short           numberOfTrunks;
    long            outgoingCalls;
    long            outgoingCompletedCalls;
    long            outgoingUsage;
    unsigned char   percentAllTrunksBusy;
    unsigned char   percentTrunksMaintBusy;
    char            trunkGroupName[16];
    short           trunkGroupNumber;
    short           trunksInUse;
    short           trunksMaintBusy;
} ATTTrunkGroupMeasurements_t;

typedef struct ATTVdnMeasurements_t {
    short           acceptableSvcLevel;
    long            acdCalls;
    long            avgACDTalkTime;
    short           avgSpeedOfAnswer;
    short           avgTimeToAbandon;
    long            callsAbandoned;
    long            callsFlowedOut;
    long            callsForcedBusyDisc;
    long            callsOffered;
    short           callsWaiting;
    long            callsNonACD;
    short           oldestCallWaiting;
    unsigned char   percentInSvcLevel;
    long            totalACDTalkTime;
    char            extension[6];
    char            name[16];
} ATTVdnMeasurements_t;

typedef struct ATTAgentMeasurementsPresent_t {
    Boolean         allMeasurements;
    Boolean         acdCalls;
    Boolean         extension;
    Boolean         name;
    Boolean         state;
    Boolean         avgACDTalkTime;
    Boolean         avgExtensionTime;
    Boolean         callRate;
    Boolean         elapsedTime;
    Boolean         extensionCalls;
    Boolean         extensionIncomingCalls;
    Boolean         extensionOutgoingCalls;
    Boolean         shiftACDCalls;
    Boolean         shiftAvgACDTalkTime;
    Boolean         splitAcceptableSvcLevel;
    Boolean         splitACDCalls;
    Boolean         splitAfterCallSessions;
    Boolean         splitAgentsAvailable;
    Boolean         splitAgentsInAfterCall;
    Boolean         splitAgentsInAux;
    Boolean         splitAgentsInOther;
    Boolean         splitAgentsOnACDCalls;
    Boolean         splitAgentsOnExtCalls;
    Boolean         splitAgentsStaffed;
    Boolean         splitAvgACDTalkTime;
    Boolean         splitAvgAfterCallTime;
    Boolean         splitAvgSpeedOfAnswer;
    Boolean         splitAvgTimeToAbandon;
    Boolean         splitCallRate;
    Boolean         splitCallsAbandoned;
    Boolean         splitCallsFlowedIn;
    Boolean         splitCallsFlowedOut;
    Boolean         splitCallsWaiting;
    Boolean         splitName;
    Boolean         splitNumber;
    Boolean         splitExtension;
    Boolean         splitObjective;
    Boolean         splitOldestCallWaiting;
    Boolean         splitPercentInSvcLevel;
    Boolean         splitTotalACDTalkTime;
    Boolean         splitTotalAfterCallTime;
    Boolean         splitTotalAuxTime;
    Boolean         timeAgentEnteredState;
    Boolean         totalACDTalkTime;
    Boolean         totalAfterCallTime;
    Boolean         totalAuxTime;
    Boolean         totalAvailableTime;
    Boolean         totalHoldTime;
    Boolean         totalStaffedTime;
    Boolean         totalACDCallTime;
    Boolean         avgACDCallTime;
} ATTAgentMeasurementsPresent_t;

typedef struct ATTSplitSkillMeasurementsPresent_t {
    Boolean         allMeasurements;
    Boolean         acceptableSvcLevel;
    Boolean         acdCalls;
    Boolean         afterCallSessions;
    Boolean         agentsAvailable;
    Boolean         agentsInAfterCall;
    Boolean         agentsInAux;
    Boolean         agentsInOther;
    Boolean         onACDCalls;
    Boolean         agentsOnExtensionCalls;
    Boolean         agentsStaffed;
    Boolean         avgACDTalkTime;
    Boolean         afterCallTime;
    Boolean         avgSpeedOfAnswer;
    Boolean         avgTimeToAbandon;
    Boolean         callRate;
    Boolean         callsAbandoned;
    Boolean         callsFlowedIn;
    Boolean         callsFlowedOut;
    Boolean         callsWaiting;
    Boolean         oldestCallWaiting;
    Boolean         percentInSvcLevel;
    Boolean         name;
    Boolean         extension;
    Boolean         number;
    Boolean         objective;
    Boolean         totalAfterCallTime;
    Boolean         totalAuxTime;
    Boolean         totalACDTalkTime;
} ATTSplitSkillMeasurementsPresent_t;

typedef struct ATTTrunkGroupMeasurementsPresent_t {
    Boolean         allMeasurements;
    Boolean         avgIncomingCallTime;
    Boolean         avgOutgoingCallTime;
    Boolean         incomingAbandonedCalls;
    Boolean         incomingCalls;
    Boolean         incomingUsage;
    Boolean         numberOfTrunks;
    Boolean         outgoingCalls;
    Boolean         outgoingCompletedCalls;
    Boolean         outgoingUsage;
    Boolean         percentAllTrunksBusy;
    Boolean         percentTrunksMaintBusy;
    Boolean         trunkGroupName;
    Boolean         trunkGroupNumber;
    Boolean         trunksInUse;
    Boolean         trunksMaintBusy;
} ATTTrunkGroupMeasurementsPresent_t;

typedef struct ATTVdnMeasurementsPresent_t {
    Boolean         allMeasurements;
    Boolean         acceptableSvcLevel;
    Boolean         acdCalls;
    Boolean         avgACDTalkTime;
    Boolean         avgSpeedOfAnswer;
    Boolean         avgTimeToAbandon;
    Boolean         callsAbandoned;
    Boolean         callsFlowedOut;
    Boolean         callsForcedBusyDisc;
    Boolean         callsOffered;
    Boolean         callsWaiting;
    Boolean         callsNonACD;
    Boolean         oldestCallWaiting;
    Boolean         percentInSvcLevel;
    Boolean         totalACDTalkTime;
    Boolean         extension;
    Boolean         name;
} ATTVdnMeasurementsPresent_t;

typedef struct ATTQueryAgentMeasurements_t {
    DeviceID_t      agentID;
    ATTAgentTypeID_t typeID;
    ATTSplitSkill_t splitSkill;
    ATTAgentMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryAgentMeasurements_t;

typedef struct ATTQueryAgentMeasurementsConfEvent_t {
    ATTAgentMeasurementsPresent_t returnedItems;
    ATTAgentMeasurements_t values;
} ATTQueryAgentMeasurementsConfEvent_t;

typedef struct ATTQuerySplitSkillMeasurements_t {
    DeviceID_t      device;
    ATTSplitSkillMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQuerySplitSkillMeasurements_t;

typedef struct ATTQuerySplitSkillMeasurementsConfEvent_t {
    ATTSplitSkillMeasurementsPresent_t returnedItems;
    ATTSplitSkillMeasurements_t values;
} ATTQuerySplitSkillMeasurementsConfEvent_t;

typedef struct ATTQueryTrunkGroupMeasurements_t {
    DeviceID_t      device;
    ATTTrunkGroupMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryTrunkGroupMeasurements_t;

typedef struct ATTQueryTrunkGroupMeasurementsConfEvent_t {
    ATTTrunkGroupMeasurementsPresent_t returnedItems;
    ATTTrunkGroupMeasurements_t values;
} ATTQueryTrunkGroupMeasurementsConfEvent_t;

typedef struct ATTQueryVdnMeasurements_t {
    DeviceID_t      device;
    ATTVdnMeasurementsPresent_t requestItems;
    ATTInterval_t   interval;
} ATTQueryVdnMeasurements_t;

typedef struct ATTQueryVdnMeasurementsConfEvent_t {
    ATTVdnMeasurementsPresent_t returnedItems;
    ATTVdnMeasurements_t values;
} ATTQueryVdnMeasurementsConfEvent_t;

typedef struct ATTV4ConferencedEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4ConferencedEvent_t;

typedef struct ATTV4DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4DeliveredEvent_t;

typedef struct ATTV4EstablishedEvent_t {
    DeviceID_t      trunk;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTV4LookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4EstablishedEvent_t;

typedef struct ATTV4TransferredEvent_t {
    ATTV4OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
} ATTV4TransferredEvent_t;

typedef struct ATTV4LinkStatusEvent_t {
    short           count;
    ATTLinkStatus_t linkStatus[8];
} ATTV4LinkStatusEvent_t;

typedef struct ATTV4GetAPICapsConfEvent_t {
    char            switchVersion[16];
    Boolean         sendDTMFTone;
    Boolean         enteredDigitsEvent;
    Boolean         queryDeviceName;
    Boolean         queryAgentMeas;
    Boolean         querySplitSkillMeas;
    Boolean         queryTrunkGroupMeas;
    Boolean         queryVdnMeas;
    Boolean         reserved1;
    Boolean         reserved2;
} ATTV4GetAPICapsConfEvent_t;

typedef enum ATTParticipationType_t {
    PT_ACTIVE = 1,
    PT_SILENT = 0
} ATTParticipationType_t;

typedef char            ATTUCID_t[64];

typedef struct ATTSingleStepConferenceCall_t {
    ConnectionID_t  activeCall;
    DeviceID_t      deviceToBeJoin;
    ATTParticipationType_t participationType;
    Boolean         alertDestination;
} ATTSingleStepConferenceCall_t;

typedef struct ATTSingleStepConferenceCallConfEvent_t {
    ConnectionID_t  newCall;
    ConnectionList_t connList;
    ATTUCID_t       ucid;
} ATTSingleStepConferenceCallConfEvent_t;

typedef struct ATTSelectiveListeningHold_t {
    ConnectionID_t  subjectConnection;
    Boolean         allParties;
    ConnectionID_t  selectedParty;
} ATTSelectiveListeningHold_t;

typedef struct ATTSelectiveListeningHoldConfEvent_t {
    Nulltype        null;
} ATTSelectiveListeningHoldConfEvent_t;

typedef struct ATTSelectiveListeningRetrieve_t {
    ConnectionID_t  subjectConnection;
    Boolean         allParties;
    ConnectionID_t  selectedParty;
} ATTSelectiveListeningRetrieve_t;

typedef struct ATTSelectiveListeningRetrieveConfEvent_t {
    Nulltype        null;
} ATTSelectiveListeningRetrieveConfEvent_t;

typedef struct ATTUnicodeDeviceID_t {
    short           count;
    unsigned short           value[64];
} ATTUnicodeDeviceID_t;

typedef struct ATTLookaheadInfo_t {
    ATTInterflow_t  type;
    ATTPriority_t   priority;
    short           hours;
    short           minutes;
    short           seconds;
    DeviceID_t      sourceVDN;
    ATTUnicodeDeviceID_t uSourceVDN;
} ATTLookaheadInfo_t;

typedef struct ATTCallOriginatorInfo_t {
    Boolean         hasInfo;
    short           callOriginatorType;
} ATTCallOriginatorInfo_t;

typedef struct ATTV5OriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTV5OriginalCallInfo_t;

typedef struct ATTConnIDList_t {
    _Int             count;
    ConnectionID_t  FAR *pParty;
} ATTConnIDList_t;

typedef struct ATTSendDTMFTone_t {
    ConnectionID_t  sender;
    ATTConnIDList_t receivers;
    char            tones[33];
    short           toneDuration;
    short           pauseDuration;
} ATTSendDTMFTone_t;

typedef struct ATTSnapshotDeviceConfEvent_t {
    _Int             count;
    ATTSnapshotDevice_t FAR *pSnapshotDevice;
} ATTSnapshotDeviceConfEvent_t;

typedef struct ATTLinkStatusEvent_t {
    _Int             count;
    ATTLinkStatus_t FAR *pLinkStatus;
} ATTLinkStatusEvent_t;

typedef enum ATTBillType_t {
    BT_NEW_RATE = 16,
    BT_FLAT_RATE = 17,
    BT_PREMIUM_CHARGE = 18,
    BT_PREMIUM_CREDIT = 19,
    BT_FREE_CALL = 24
} ATTBillType_t;

typedef struct ATTSetBillRate_t {
    ConnectionID_t  call;
    ATTBillType_t   billType;
    float           billRate;
} ATTSetBillRate_t;

typedef struct ATTSetBillRateConfEvent_t {
    Nulltype        null;
} ATTSetBillRateConfEvent_t;

typedef struct ATTQueryUcid_t {
    ConnectionID_t  call;
} ATTQueryUcid_t;

typedef struct ATTQueryUcidConfEvent_t {
    ATTUCID_t       ucid;
} ATTQueryUcidConfEvent_t;

typedef struct ATTV5ConferencedEvent_t {
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
} ATTV5ConferencedEvent_t;

typedef struct ATTLoggedOffEvent_t {
    long            reasonCode;
} ATTLoggedOffEvent_t;

typedef struct ATTV5DeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTV5DeliveredEvent_t;

typedef struct ATTV5EstablishedEvent_t {
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTV5EstablishedEvent_t;

typedef struct ATTV5TransferredEvent_t {
    ATTV5OriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
} ATTV5TransferredEvent_t;

typedef struct ATTV5RouteRequestEvent_t {
    DeviceID_t      trunkGroup;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTV5UserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTV5RouteRequestEvent_t;

typedef unsigned char   ATTPrivateFilter_t;
#define                     ATT_ENTERED_DIGITS_FILTER 0x80
#define                     ATT_CHARGE_ADVICE_FILTER 0x40

typedef struct ATTConsultationCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTConsultationCallConfEvent_t;

typedef struct ATTMakeCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTMakeCallConfEvent_t;

typedef struct ATTMakePredictiveCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTMakePredictiveCallConfEvent_t;

typedef struct ATTV5SetAgentState_t {
    ATTWorkMode_t   workMode;
    long            reasonCode;
} ATTV5SetAgentState_t;

typedef struct ATTV5QueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
    long            reasonCode;
} ATTV5QueryAgentStateConfEvent_t;

typedef struct ATTQueryDeviceNameConfEvent_t {
    ATTDeviceType_t deviceType;
    DeviceID_t      device;
    DeviceID_t      name;
    ATTUnicodeDeviceID_t uname;
} ATTQueryDeviceNameConfEvent_t;

typedef struct ATTConferenceCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTConferenceCallConfEvent_t;

typedef struct ATTTransferCallConfEvent_t {
    ATTUCID_t       ucid;
} ATTTransferCallConfEvent_t;

typedef struct ATTMonitorFilter_t {
    ATTPrivateFilter_t privateFilter;
} ATTMonitorFilter_t;

typedef struct ATTMonitorConfEvent_t {
    ATTPrivateFilter_t usedFilter;
} ATTMonitorConfEvent_t;

typedef struct ATTSnapshotCall_t {
    _Int             count;
    CSTASnapshotCallResponseInfo_t FAR *pInfo;
} ATTSnapshotCall_t;

typedef struct ATTMonitorCallConfEvent_t {
    ATTPrivateFilter_t usedFilter;
    ATTSnapshotCall_t snapshotCall;
} ATTMonitorCallConfEvent_t;

typedef struct ATTServiceInitiatedEvent_t {
    ATTUCID_t       ucid;
} ATTServiceInitiatedEvent_t;

typedef enum ATTChargeType_t {
    CT_INTERMEDIATE_CHARGE = 1,
    CT_FINAL_CHARGE = 2,
    CT_SPLIT_CHARGE = 3
} ATTChargeType_t;

typedef enum ATTChargeError_t {
    CE_NONE = 0,
    CE_NO_FINAL_CHARGE = 1,
    CE_LESS_FINAL_CHARGE = 2,
    CE_CHARGE_TOO_LARGE = 3,
    CE_NETWORK_BUSY = 4
} ATTChargeError_t;

typedef struct ATTChargeAdviceEvent_t {
    ConnectionID_t  connection;
    DeviceID_t      calledDevice;
    DeviceID_t      chargingDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTChargeType_t chargeType;
    long            charge;
    ATTChargeError_t error;
} ATTChargeAdviceEvent_t;

typedef struct ATTGetAPICapsConfEvent_t {
    char            switchVersion[16];
    Boolean         sendDTMFTone;
    Boolean         enteredDigitsEvent;
    Boolean         queryDeviceName;
    Boolean         queryAgentMeas;
    Boolean         querySplitSkillMeas;
    Boolean         queryTrunkGroupMeas;
    Boolean         queryVdnMeas;
    Boolean         singleStepConference;
    Boolean         selectiveListeningHold;
    Boolean         selectiveListeningRetrieve;
    Boolean         setBillingRate;
    Boolean         queryUCID;
    Boolean         chargeAdviceEvent;
    Boolean         reserved1;
    Boolean         reserved2;
} ATTGetAPICapsConfEvent_t;

typedef struct ATTQueryDeviceInfoConfEvent_t {
    ATTExtensionClass_t extensionClass;
    ATTExtensionClass_t associatedClass;
    DeviceID_t      associatedDevice;
} ATTQueryDeviceInfoConfEvent_t;

typedef struct ATTSetAdviceOfCharge_t {
    Boolean         featureFlag;
} ATTSetAdviceOfCharge_t;

typedef struct ATTSetAdviceOfChargeConfEvent_t {
    Nulltype        null;
} ATTSetAdviceOfChargeConfEvent_t;

typedef struct ATTNetworkReachedEvent_t {
    ATTProgressLocation_t progressLocation;
    ATTProgressDescription_t progressDescription;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
} ATTNetworkReachedEvent_t;

typedef struct ATTSetAgentState_t {
    ATTWorkMode_t   workMode;
    long            reasonCode;
    Boolean         enablePending;
} ATTSetAgentState_t;

typedef struct ATTSetAgentStateConfEvent_t {
    Boolean         isPending;
} ATTSetAgentStateConfEvent_t;

typedef struct ATTQueryAgentStateConfEvent_t {
    ATTWorkMode_t   workMode;
    ATTTalkState_t  talkState;
    long            reasonCode;
    ATTWorkMode_t   pendingWorkMode;
    long            pendingReasonCode;
} ATTQueryAgentStateConfEvent_t;

typedef struct ATTUserToUserInfo_t {
    ATTUUIProtocolType_t type;
    struct {
        short           length;
        unsigned char   value[129];
    } data;
} ATTUserToUserInfo_t;

typedef struct ATTRouteRequestEvent_t {
    DeviceID_t      trunkGroup;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
    DeviceID_t      trunkMember;
} ATTRouteRequestEvent_t;

typedef struct ATTOriginalCallInfo_t {
    ATTReasonForCallInfo_t reason;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTOriginalCallInfo_t;

typedef struct ATTTrunkInfo_t {
    ConnectionID_t  connection;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
} ATTTrunkInfo_t;

#define MAX_TRUNKS 5

typedef struct ATTTrunkList_t {
    short           count;
    ATTTrunkInfo_t  trunks[MAX_TRUNKS];
} ATTTrunkList_t;

typedef struct ATTTransferredEvent_t {
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
} ATTTransferredEvent_t;

typedef struct ATTConferencedEvent_t {
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTTrunkList_t  trunkList;
} ATTConferencedEvent_t;

typedef struct ATTClearConnection_t {
    ATTDropResource_t dropResource;
    ATTUserToUserInfo_t userInfo;
} ATTClearConnection_t;

typedef struct ATTConsultationCall_t {
    DeviceID_t      destRoute;
    Boolean         priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTConsultationCall_t;

typedef struct ATTMakeCall_t {
    DeviceID_t      destRoute;
    Boolean         priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTMakeCall_t;

typedef struct ATTDirectAgentCall_t {
    DeviceID_t      split;
    Boolean         priorityCalling;
    ATTUserToUserInfo_t userInfo;
} ATTDirectAgentCall_t;

typedef struct ATTMakePredictiveCall_t {
    Boolean         priorityCalling;
    short           maxRings;
    ATTAnswerTreat_t answerTreat;
    DeviceID_t      destRoute;
    ATTUserToUserInfo_t userInfo;
} ATTMakePredictiveCall_t;

typedef struct ATTSupervisorAssistCall_t {
    DeviceID_t      split;
    ATTUserToUserInfo_t userInfo;
} ATTSupervisorAssistCall_t;

typedef struct ATTReconnectCall_t {
    ATTDropResource_t dropResource;
    ATTUserToUserInfo_t userInfo;
} ATTReconnectCall_t;

typedef struct ATTConnectionClearedEvent_t {
    ATTUserToUserInfo_t userInfo;
} ATTConnectionClearedEvent_t;

typedef struct ATTRouteSelect_t {
    DeviceID_t      callingDevice;
    DeviceID_t      directAgentCallSplit;
    Boolean         priorityCalling;
    DeviceID_t      destRoute;
    ATTUserCollectCode_t collectCode;
    ATTUserProvidedCode_t userProvidedCode;
    ATTUserToUserInfo_t userInfo;
} ATTRouteSelect_t;

typedef struct ATTDeliveredEvent_t {
    ATTDeliveredType_t deliveredType;
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTDeliveredEvent_t;

typedef struct ATTEstablishedEvent_t {
    DeviceID_t      trunkGroup;
    DeviceID_t      trunkMember;
    DeviceID_t      split;
    ATTLookaheadInfo_t lookaheadInfo;
    ATTUserEnteredCode_t userEnteredCode;
    ATTUserToUserInfo_t userInfo;
    ATTReasonCode_t reason;
    ATTOriginalCallInfo_t originalCallInfo;
    CalledDeviceID_t distributingDevice;
    ATTUCID_t       ucid;
    ATTCallOriginatorInfo_t callOriginatorInfo;
    Boolean         flexibleBilling;
} ATTEstablishedEvent_t;

typedef struct ATTOriginatedEvent_t {
    DeviceID_t      logicalAgent;
    ATTUserToUserInfo_t userInfo;
} ATTOriginatedEvent_t;





extern void FAR *att_asn_tbl;    /* encoder-decoder control table */

#endif
