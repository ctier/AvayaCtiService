/***********************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/* abstract syntax: csta_asn_tbl */
/* last module in input: CSTA-route-end-request-invoke */
/* created: Fri Aug  1 10:51:26 1997 */
/* associated control file: cstadefs.c */

#ifndef CSTADEFS_H
#define CSTADEFS_H

#include "tsplatfm.h"


#define          CSTA_ALTERNATE_CALL 1
#define          CSTA_ALTERNATE_CALL_CONF 2
#define          CSTA_ANSWER_CALL 3
#define          CSTA_ANSWER_CALL_CONF 4
#define          CSTA_CALL_COMPLETION 5
#define          CSTA_CALL_COMPLETION_CONF 6
#define          CSTA_CLEAR_CALL 7
#define          CSTA_CLEAR_CALL_CONF 8
#define          CSTA_CLEAR_CONNECTION 9
#define          CSTA_CLEAR_CONNECTION_CONF 10
#define          CSTA_CONFERENCE_CALL 11
#define          CSTA_CONFERENCE_CALL_CONF 12
#define          CSTA_CONSULTATION_CALL 13
#define          CSTA_CONSULTATION_CALL_CONF 14
#define          CSTA_DEFLECT_CALL 15
#define          CSTA_DEFLECT_CALL_CONF 16
#define          CSTA_PICKUP_CALL 17
#define          CSTA_PICKUP_CALL_CONF 18
#define          CSTA_GROUP_PICKUP_CALL 19
#define          CSTA_GROUP_PICKUP_CALL_CONF 20
#define          CSTA_HOLD_CALL 21
#define          CSTA_HOLD_CALL_CONF 22
#define          CSTA_MAKE_CALL 23
#define          CSTA_MAKE_CALL_CONF 24
#define          CSTA_MAKE_PREDICTIVE_CALL 25
#define          CSTA_MAKE_PREDICTIVE_CALL_CONF 26
#define          CSTA_QUERY_MWI 27
#define          CSTA_QUERY_MWI_CONF 28
#define          CSTA_QUERY_DND 29
#define          CSTA_QUERY_DND_CONF 30
#define          CSTA_QUERY_FWD 31
#define          CSTA_QUERY_FWD_CONF 32
#define          CSTA_QUERY_AGENT_STATE 33
#define          CSTA_QUERY_AGENT_STATE_CONF 34
#define          CSTA_QUERY_LAST_NUMBER 35
#define          CSTA_QUERY_LAST_NUMBER_CONF 36
#define          CSTA_QUERY_DEVICE_INFO 37
#define          CSTA_QUERY_DEVICE_INFO_CONF 38
#define          CSTA_RECONNECT_CALL 39
#define          CSTA_RECONNECT_CALL_CONF 40
#define          CSTA_RETRIEVE_CALL 41
#define          CSTA_RETRIEVE_CALL_CONF 42
#define          CSTA_SET_MWI 43
#define          CSTA_SET_MWI_CONF 44
#define          CSTA_SET_DND 45
#define          CSTA_SET_DND_CONF 46
#define          CSTA_SET_FWD 47
#define          CSTA_SET_FWD_CONF 48
#define          CSTA_SET_AGENT_STATE 49
#define          CSTA_SET_AGENT_STATE_CONF 50
#define          CSTA_TRANSFER_CALL 51
#define          CSTA_TRANSFER_CALL_CONF 52
#define          CSTA_UNIVERSAL_FAILURE_CONF 53
#define          CSTA_CALL_CLEARED 54
#define          CSTA_CONFERENCED 55
#define          CSTA_CONNECTION_CLEARED 56
#define          CSTA_DELIVERED 57
#define          CSTA_DIVERTED 58
#define          CSTA_ESTABLISHED 59
#define          CSTA_FAILED 60
#define          CSTA_HELD 61
#define          CSTA_NETWORK_REACHED 62
#define          CSTA_ORIGINATED 63
#define          CSTA_QUEUED 64
#define          CSTA_RETRIEVED 65
#define          CSTA_SERVICE_INITIATED 66
#define          CSTA_TRANSFERRED 67
#define          CSTA_CALL_INFORMATION 68
#define          CSTA_DO_NOT_DISTURB 69
#define          CSTA_FORWARDING 70
#define          CSTA_MESSAGE_WAITING 71
#define          CSTA_LOGGED_ON 72
#define          CSTA_LOGGED_OFF 73
#define          CSTA_NOT_READY 74
#define          CSTA_READY 75
#define          CSTA_WORK_NOT_READY 76
#define          CSTA_WORK_READY 77
#define          CSTA_ROUTE_REGISTER_REQ 78
#define          CSTA_ROUTE_REGISTER_REQ_CONF 79
#define          CSTA_ROUTE_REGISTER_CANCEL 80
#define          CSTA_ROUTE_REGISTER_CANCEL_CONF 81
#define          CSTA_ROUTE_REGISTER_ABORT 82
#define          CSTA_ROUTE_REQUEST 83
#define          CSTA_ROUTE_SELECT_REQUEST 84
#define          CSTA_RE_ROUTE_REQUEST 85
#define          CSTA_ROUTE_USED 86
#define          CSTA_ROUTE_END 87
#define          CSTA_ROUTE_END_REQUEST 88
#define          CSTA_ESCAPE_SVC 89
#define          CSTA_ESCAPE_SVC_CONF 90
#define          CSTA_ESCAPE_SVC_REQ 91
#define          CSTA_ESCAPE_SVC_REQ_CONF 92
#define          CSTA_PRIVATE 93
#define          CSTA_PRIVATE_STATUS 94
#define          CSTA_SEND_PRIVATE 95
#define          CSTA_BACK_IN_SERVICE 96
#define          CSTA_OUT_OF_SERVICE 97
#define          CSTA_REQ_SYS_STAT 98
#define          CSTA_SYS_STAT_REQ_CONF 99
#define          CSTA_SYS_STAT_START 100
#define          CSTA_SYS_STAT_START_CONF 101
#define          CSTA_SYS_STAT_STOP 102
#define          CSTA_SYS_STAT_STOP_CONF 103
#define          CSTA_CHANGE_SYS_STAT_FILTER 104
#define          CSTA_CHANGE_SYS_STAT_FILTER_CONF 105
#define          CSTA_SYS_STAT 106
#define          CSTA_SYS_STAT_ENDED 107
#define          CSTA_SYS_STAT_REQ 108
#define          CSTA_REQ_SYS_STAT_CONF 109
#define          CSTA_SYS_STAT_EVENT_SEND 110
#define          CSTA_MONITOR_DEVICE 111
#define          CSTA_MONITOR_CALL 112
#define          CSTA_MONITOR_CALLS_VIA_DEVICE 113
#define          CSTA_MONITOR_CONF 114
#define          CSTA_CHANGE_MONITOR_FILTER 115
#define          CSTA_CHANGE_MONITOR_FILTER_CONF 116
#define          CSTA_MONITOR_STOP 117
#define          CSTA_MONITOR_STOP_CONF 118
#define          CSTA_MONITOR_ENDED 119
#define          CSTA_SNAPSHOT_CALL 120
#define          CSTA_SNAPSHOT_CALL_CONF 121
#define          CSTA_SNAPSHOT_DEVICE 122
#define          CSTA_SNAPSHOT_DEVICE_CONF 123
#define          CSTA_GETAPI_CAPS 124
#define          CSTA_GETAPI_CAPS_CONF 125
#define          CSTA_GET_DEVICE_LIST 126
#define          CSTA_GET_DEVICE_LIST_CONF 127
#define          CSTA_QUERY_CALL_MONITOR 128
#define          CSTA_QUERY_CALL_MONITOR_CONF 129
#define          CSTA_ROUTE_REQUEST_EXT 130
#define          CSTA_ROUTE_USED_EXT 131
#define          CSTA_ROUTE_SELECT_INV_REQUEST 132
#define          CSTA_ROUTE_END_INV_REQUEST 133

typedef enum CSTAUniversalFailure_t {
    GENERIC_UNSPECIFIED = 0,
    GENERIC_OPERATION = 1,
    REQUEST_INCOMPATIBLE_WITH_OBJECT = 2,
    VALUE_OUT_OF_RANGE = 3,
    OBJECT_NOT_KNOWN = 4,
    INVALID_CALLING_DEVICE = 5,
    INVALID_CALLED_DEVICE = 6,
    INVALID_FORWARDING_DESTINATION = 7,
    PRIVILEGE_VIOLATION_ON_SPECIFIED_DEVICE = 8,
    PRIVILEGE_VIOLATION_ON_CALLED_DEVICE = 9,
    PRIVILEGE_VIOLATION_ON_CALLING_DEVICE = 10,
    INVALID_CSTA_CALL_IDENTIFIER = 11,
    INVALID_CSTA_DEVICE_IDENTIFIER = 12,
    INVALID_CSTA_CONNECTION_IDENTIFIER = 13,
    INVALID_DESTINATION = 14,
    INVALID_FEATURE = 15,
    INVALID_ALLOCATION_STATE = 16,
    INVALID_CROSS_REF_ID = 17,
    INVALID_OBJECT_TYPE = 18,
    SECURITY_VIOLATION = 19,
    GENERIC_STATE_INCOMPATIBILITY = 21,
    INVALID_OBJECT_STATE = 22,
    INVALID_CONNECTION_ID_FOR_ACTIVE_CALL = 23,
    NO_ACTIVE_CALL = 24,
    NO_HELD_CALL = 25,
    NO_CALL_TO_CLEAR = 26,
    NO_CONNECTION_TO_CLEAR = 27,
    NO_CALL_TO_ANSWER = 28,
    NO_CALL_TO_COMPLETE = 29,
    GENERIC_SYSTEM_RESOURCE_AVAILABILITY = 31,
    SERVICE_BUSY = 32,
    RESOURCE_BUSY = 33,
    RESOURCE_OUT_OF_SERVICE = 34,
    NETWORK_BUSY = 35,
    NETWORK_OUT_OF_SERVICE = 36,
    OVERALL_MONITOR_LIMIT_EXCEEDED = 37,
    CONFERENCE_MEMBER_LIMIT_EXCEEDED = 38,
    GENERIC_SUBSCRIBED_RESOURCE_AVAILABILITY = 41,
    OBJECT_MONITOR_LIMIT_EXCEEDED = 42,
    EXTERNAL_TRUNK_LIMIT_EXCEEDED = 43,
    OUTSTANDING_REQUEST_LIMIT_EXCEEDED = 44,
    GENERIC_PERFORMANCE_MANAGEMENT = 51,
    PERFORMANCE_LIMIT_EXCEEDED = 52,
    UNSPECIFIED_SECURITY_ERROR = 60,
    SEQUENCE_NUMBER_VIOLATED = 61,
    TIME_STAMP_VIOLATED = 62,
    PAC_VIOLATED = 63,
    SEAL_VIOLATED = 64,
    GENERIC_UNSPECIFIED_REJECTION = 70,
    GENERIC_OPERATION_REJECTION = 71,
    DUPLICATE_INVOCATION_REJECTION = 72,
    UNRECOGNIZED_OPERATION_REJECTION = 73,
    MISTYPED_ARGUMENT_REJECTION = 74,
    RESOURCE_LIMITATION_REJECTION = 75,
    ACS_HANDLE_TERMINATION_REJECTION = 76,
    SERVICE_TERMINATION_REJECTION = 77,
    REQUEST_TIMEOUT_REJECTION = 78,
    REQUESTS_ON_DEVICE_EXCEEDED_REJECTION = 79,
    UNRECOGNIZED_APDU_REJECTION = 80,
    MISTYPED_APDU_REJECTION = 81,
    BADLY_STRUCTURED_APDU_REJECTION = 82,
    INITIATOR_RELEASING_REJECTION = 83,
    UNRECOGNIZED_LINKEDID_REJECTION = 84,
    LINKED_RESPONSE_UNEXPECTED_REJECTION = 85,
    UNEXPECTED_CHILD_OPERATION_REJECTION = 86,
    MISTYPED_RESULT_REJECTION = 87,
    UNRECOGNIZED_ERROR_REJECTION = 88,
    UNEXPECTED_ERROR_REJECTION = 89,
    MISTYPED_PARAMETER_REJECTION = 90,
    NON_STANDARD = 100
} CSTAUniversalFailure_t;

typedef enum CSTAEventCause_t {
    EC_NONE = -1,
    EC_ACTIVE_MONITOR = 1,
    EC_ALTERNATE = 2,
    EC_BUSY = 3,
    EC_CALL_BACK = 4,
    EC_CALL_CANCELLED = 5,
    EC_CALL_FORWARD_ALWAYS = 6,
    EC_CALL_FORWARD_BUSY = 7,
    EC_CALL_FORWARD_NO_ANSWER = 8,
    EC_CALL_FORWARD = 9,
    EC_CALL_NOT_ANSWERED = 10,
    EC_CALL_PICKUP = 11,
    EC_CAMP_ON = 12,
    EC_DEST_NOT_OBTAINABLE = 13,
    EC_DO_NOT_DISTURB = 14,
    EC_INCOMPATIBLE_DESTINATION = 15,
    EC_INVALID_ACCOUNT_CODE = 16,
    EC_KEY_CONFERENCE = 17,
    EC_LOCKOUT = 18,
    EC_MAINTENANCE = 19,
    EC_NETWORK_CONGESTION = 20,
    EC_NETWORK_NOT_OBTAINABLE = 21,
    EC_NEW_CALL = 22,
    EC_NO_AVAILABLE_AGENTS = 23,
    EC_OVERRIDE = 24,
    EC_PARK = 25,
    EC_OVERFLOW = 26,
    EC_RECALL = 27,
    EC_REDIRECTED = 28,
    EC_REORDER_TONE = 29,
    EC_RESOURCES_NOT_AVAILABLE = 30,
    EC_SILENT_MONITOR = 31,
    EC_TRANSFER = 32,
    EC_TRUNKS_BUSY = 33,
    EC_VOICE_UNIT_INITIATOR = 34,
    EC_NETWORKSIGNAL = 46,
    EC_ALERTTIMEEXPIRED = 60,
    EC_DESTOUTOFORDER = 65,
    EC_NOTSUPPORTEDBEARERSERVICE = 80,
	EC_UNASSIGNED_NUMBER = 81,
	EC_INCOMPATIBLE_BEARER_SERVICE = 87
} CSTAEventCause_t;

typedef char            DeviceID_t[64];

typedef enum DeviceIDType_t {
    DEVICE_IDENTIFIER = 0,
    IMPLICIT_PUBLIC = 20,
    EXPLICIT_PUBLIC_UNKNOWN = 30,
    EXPLICIT_PUBLIC_INTERNATIONAL = 31,
    EXPLICIT_PUBLIC_NATIONAL = 32,
    EXPLICIT_PUBLIC_NETWORK_SPECIFIC = 33,
    EXPLICIT_PUBLIC_SUBSCRIBER = 34,
    EXPLICIT_PUBLIC_ABBREVIATED = 35,
    IMPLICIT_PRIVATE = 40,
    EXPLICIT_PRIVATE_UNKNOWN = 50,
    EXPLICIT_PRIVATE_LEVEL3_REGIONAL_NUMBER = 51,
    EXPLICIT_PRIVATE_LEVEL2_REGIONAL_NUMBER = 52,
    EXPLICIT_PRIVATE_LEVEL1_REGIONAL_NUMBER = 53,
    EXPLICIT_PRIVATE_PTN_SPECIFIC_NUMBER = 54,
    EXPLICIT_PRIVATE_LOCAL_NUMBER = 55,
    EXPLICIT_PRIVATE_ABBREVIATED = 56,
    OTHER_PLAN = 60,
    TRUNK_IDENTIFIER = 70,
    TRUNK_GROUP_IDENTIFIER = 71
} DeviceIDType_t;

typedef enum DeviceIDStatus_t {
    ID_PROVIDED = 0,
    ID_NOT_KNOWN = 1,
    ID_NOT_REQUIRED = 2
} DeviceIDStatus_t;

typedef struct ExtendedDeviceID_t {
    DeviceID_t      deviceID;
    DeviceIDType_t  deviceIDType;
    DeviceIDStatus_t deviceIDStatus;
} ExtendedDeviceID_t;

typedef ExtendedDeviceID_t CallingDeviceID_t;

typedef ExtendedDeviceID_t CalledDeviceID_t;

typedef ExtendedDeviceID_t SubjectDeviceID_t;

typedef ExtendedDeviceID_t RedirectionDeviceID_t;

typedef enum ConnectionID_Device_t {
    STATIC_ID = 0,
    DYNAMIC_ID = 1
} ConnectionID_Device_t;

typedef struct ConnectionID_t {
    long            callID;
    DeviceID_t      deviceID;
    ConnectionID_Device_t devIDType;
} ConnectionID_t;

typedef struct Connection_t {
    ConnectionID_t  party;
    SubjectDeviceID_t staticDevice;
} Connection_t;

typedef struct ConnectionList_t {
    _Int             count;
    Connection_t    FAR *connection;
} ConnectionList_t;

typedef enum LocalConnectionState_t {
    CS_NONE = -1,
    CS_NULL = 0,
    CS_INITIATE = 1,
    CS_ALERTING = 2,
    CS_CONNECT = 3,
    CS_HOLD = 4,
    CS_QUEUED = 5,
    CS_FAIL = 6
} LocalConnectionState_t;

typedef long            CSTAMonitorCrossRefID_t;

typedef unsigned short  CSTACallFilter_t;
#define                     CF_CALL_CLEARED 0x8000
#define                     CF_CONFERENCED 0x4000
#define                     CF_CONNECTION_CLEARED 0x2000
#define                     CF_DELIVERED 0x1000
#define                     CF_DIVERTED 0x0800
#define                     CF_ESTABLISHED 0x0400
#define                     CF_FAILED 0x0200
#define                     CF_HELD 0x0100
#define                     CF_NETWORK_REACHED 0x0080
#define                     CF_ORIGINATED 0x0040
#define                     CF_QUEUED 0x0020
#define                     CF_RETRIEVED 0x0010
#define                     CF_SERVICE_INITIATED 0x0008
#define                     CF_TRANSFERRED 0x0004

typedef unsigned char   CSTAFeatureFilter_t;
#define                     FF_CALL_INFORMATION 0x80
#define                     FF_DO_NOT_DISTURB 0x40
#define                     FF_FORWARDING 0x20
#define                     FF_MESSAGE_WAITING 0x10

typedef unsigned char   CSTAAgentFilter_t;
#define                     AF_LOGGED_ON 0x80
#define                     AF_LOGGED_OFF 0x40
#define                     AF_NOT_READY 0x20
#define                     AF_READY 0x10
#define                     AF_WORK_NOT_READY 0x08
#define                     AF_WORK_READY 0x04

typedef unsigned char   CSTAMaintenanceFilter_t;
#define                     MF_BACK_IN_SERVICE 0x80
#define                     MF_OUT_OF_SERVICE 0x40

typedef struct CSTAMonitorFilter_t {
    CSTACallFilter_t call;
    CSTAFeatureFilter_t feature;
    CSTAAgentFilter_t agent;
    CSTAMaintenanceFilter_t maintenance;
    long            privateFilter;
} CSTAMonitorFilter_t;

typedef struct CSTACallState_t {
    _Int             count;
    LocalConnectionState_t FAR *state;
} CSTACallState_t;

typedef struct CSTASnapshotDeviceResponseInfo_t {
    ConnectionID_t  callIdentifier;
    CSTACallState_t localCallState;
} CSTASnapshotDeviceResponseInfo_t;

typedef struct CSTASnapshotDeviceData_t {
    _Int             count;
    CSTASnapshotDeviceResponseInfo_t FAR *info;
} CSTASnapshotDeviceData_t;

typedef struct CSTASnapshotCallResponseInfo_t {
    SubjectDeviceID_t deviceOnCall;
    ConnectionID_t  callIdentifier;
    LocalConnectionState_t localConnectionState;
} CSTASnapshotCallResponseInfo_t;

typedef struct CSTASnapshotCallData_t {
    _Int             count;
    CSTASnapshotCallResponseInfo_t FAR *info;
} CSTASnapshotCallData_t;

typedef char            AccountInfo_t[32];

typedef char            AgentID_t[32];

typedef DeviceID_t      AgentGroup_t;

typedef char            AgentPassword_t[32];

typedef char            AuthCode_t[32];

typedef enum ForwardingType_t {
    FWD_IMMEDIATE = 0,
    FWD_BUSY = 1,
    FWD_NO_ANS = 2,
    FWD_BUSY_INT = 3,
    FWD_BUSY_EXT = 4,
    FWD_NO_ANS_INT = 5,
    FWD_NO_ANS_EXT = 6
} ForwardingType_t;

typedef struct ForwardingInfo_t {
    ForwardingType_t forwardingType;
    Boolean         forwardingOn;
    DeviceID_t      forwardDN;
} ForwardingInfo_t;

typedef struct ListForwardParameters_t {
    short           count;
    ForwardingInfo_t param[7];
} ListForwardParameters_t;

typedef enum SelectValue_t {
    SV_NORMAL = 0,
    SV_LEAST_COST = 1,
    SV_EMERGENCY = 2,
    SV_ACD = 3,
    SV_USER_DEFINED = 4
} SelectValue_t;

typedef struct SetUpValues_t {
    _Int             length;
    unsigned char   FAR *value;
} SetUpValues_t;

typedef short           RetryValue_t;
#define                     noListAvailable -1
#define                     noCountAvailable -2

typedef long            RoutingCrossRefID_t;

typedef long            RouteRegisterReqID_t;

typedef struct CSTAAlternateCall_t {
    ConnectionID_t  activeCall;
    ConnectionID_t  otherCall;
} CSTAAlternateCall_t;

typedef struct CSTAAlternateCallConfEvent_t {
    Nulltype        null;
} CSTAAlternateCallConfEvent_t;

typedef struct CSTAAnswerCall_t {
    ConnectionID_t  alertingCall;
} CSTAAnswerCall_t;

typedef struct CSTAAnswerCallConfEvent_t {
    Nulltype        null;
} CSTAAnswerCallConfEvent_t;

typedef enum Feature_t {
    FT_CAMP_ON = 0,
    FT_CALL_BACK = 1,
    FT_INTRUDE = 2
} Feature_t;

typedef struct CSTACallCompletion_t {
    Feature_t       feature;
    ConnectionID_t  call;
} CSTACallCompletion_t;

typedef struct CSTACallCompletionConfEvent_t {
    Nulltype        null;
} CSTACallCompletionConfEvent_t;

typedef struct CSTAClearCall_t {
    ConnectionID_t  call;
} CSTAClearCall_t;

typedef struct CSTAClearCallConfEvent_t {
    Nulltype        null;
} CSTAClearCallConfEvent_t;

typedef struct CSTAClearConnection_t {
    ConnectionID_t  call;
} CSTAClearConnection_t;

typedef struct CSTAClearConnectionConfEvent_t {
    Nulltype        null;
} CSTAClearConnectionConfEvent_t;

typedef struct CSTAConferenceCall_t {
    ConnectionID_t  heldCall;
    ConnectionID_t  activeCall;
} CSTAConferenceCall_t;

typedef struct CSTAConferenceCallConfEvent_t {
    ConnectionID_t  newCall;
    ConnectionList_t connList;
} CSTAConferenceCallConfEvent_t;

typedef struct CSTAConsultationCall_t {
    ConnectionID_t  activeCall;
    DeviceID_t      calledDevice;
} CSTAConsultationCall_t;

typedef struct CSTAConsultationCallConfEvent_t {
    ConnectionID_t  newCall;
} CSTAConsultationCallConfEvent_t;

typedef struct CSTADeflectCall_t {
    ConnectionID_t  deflectCall;
    DeviceID_t      calledDevice;
} CSTADeflectCall_t;

typedef struct CSTADeflectCallConfEvent_t {
    Nulltype        null;
} CSTADeflectCallConfEvent_t;

typedef struct CSTAPickupCall_t {
    ConnectionID_t  deflectCall;
    DeviceID_t      calledDevice;
} CSTAPickupCall_t;

typedef struct CSTAPickupCallConfEvent_t {
    Nulltype        null;
} CSTAPickupCallConfEvent_t;

typedef struct CSTAGroupPickupCall_t {
    ConnectionID_t  deflectCall;
    DeviceID_t      pickupDevice;
} CSTAGroupPickupCall_t;

typedef struct CSTAGroupPickupCallConfEvent_t {
    Nulltype        null;
} CSTAGroupPickupCallConfEvent_t;

typedef struct CSTAHoldCall_t {
    ConnectionID_t  activeCall;
    Boolean         reservation;
} CSTAHoldCall_t;

typedef struct CSTAHoldCallConfEvent_t {
    Nulltype        null;
} CSTAHoldCallConfEvent_t;

typedef struct CSTAMakeCall_t {
    DeviceID_t      callingDevice;
    DeviceID_t      calledDevice;
} CSTAMakeCall_t;

typedef struct CSTAMakeCallConfEvent_t {
    ConnectionID_t  newCall;
} CSTAMakeCallConfEvent_t;

typedef enum AllocationState_t {
    AS_CALL_DELIVERED = 0,
    AS_CALL_ESTABLISHED = 1
} AllocationState_t;

typedef struct CSTAMakePredictiveCall_t {
    DeviceID_t      callingDevice;
    DeviceID_t      calledDevice;
    AllocationState_t allocationState;
} CSTAMakePredictiveCall_t;

typedef struct CSTAMakePredictiveCallConfEvent_t {
    ConnectionID_t  newCall;
} CSTAMakePredictiveCallConfEvent_t;

typedef struct CSTAQueryMwi_t {
    DeviceID_t      device;
} CSTAQueryMwi_t;

typedef struct CSTAQueryMwiConfEvent_t {
    Boolean         messages;
} CSTAQueryMwiConfEvent_t;

typedef struct CSTAQueryDnd_t {
    DeviceID_t      device;
} CSTAQueryDnd_t;

typedef struct CSTAQueryDndConfEvent_t {
    Boolean         doNotDisturb;
} CSTAQueryDndConfEvent_t;

typedef struct CSTAQueryFwd_t {
    DeviceID_t      device;
} CSTAQueryFwd_t;

typedef struct CSTAQueryFwdConfEvent_t {
    ListForwardParameters_t forward;
} CSTAQueryFwdConfEvent_t;

typedef struct CSTAQueryAgentState_t {
    DeviceID_t      device;
} CSTAQueryAgentState_t;

typedef enum AgentState_t {
    AG_NOT_READY = 0,
    AG_NULL = 1,
    AG_READY = 2,
    AG_WORK_NOT_READY = 3,
    AG_WORK_READY = 4
} AgentState_t;

typedef struct CSTAQueryAgentStateConfEvent_t {
    AgentState_t    agentState;
} CSTAQueryAgentStateConfEvent_t;

typedef struct CSTAQueryLastNumber_t {
    DeviceID_t      device;
} CSTAQueryLastNumber_t;

typedef struct CSTAQueryLastNumberConfEvent_t {
    DeviceID_t      lastNumber;
} CSTAQueryLastNumberConfEvent_t;

typedef struct CSTAQueryDeviceInfo_t {
    DeviceID_t      device;
} CSTAQueryDeviceInfo_t;

typedef enum DeviceType_t {
    DT_STATION = 0,
    DT_LINE = 1,
    DT_BUTTON = 2,
    DT_ACD = 3,
    DT_TRUNK = 4,
    DT_OPERATOR = 5,
    DT_STATION_GROUP = 16,
    DT_LINE_GROUP = 17,
    DT_BUTTON_GROUP = 18,
    DT_ACD_GROUP = 19,
    DT_TRUNK_GROUP = 20,
    DT_OPERATOR_GROUP = 21,
    DT_OTHER = 255
} DeviceType_t;

typedef unsigned char   DeviceClass_t;
#define                     DC_VOICE 0x80
#define                     DC_DATA 0x40
#define                     DC_IMAGE 0x20
#define                     DC_OTHER 0x10

typedef struct CSTAQueryDeviceInfoConfEvent_t {
    DeviceID_t      device;
    DeviceType_t    deviceType;
    DeviceClass_t   deviceClass;
} CSTAQueryDeviceInfoConfEvent_t;

typedef struct CSTAReconnectCall_t {
    ConnectionID_t  activeCall;
    ConnectionID_t  heldCall;
} CSTAReconnectCall_t;

typedef struct CSTAReconnectCallConfEvent_t {
    Nulltype        null;
} CSTAReconnectCallConfEvent_t;

typedef struct CSTARetrieveCall_t {
    ConnectionID_t  heldCall;
} CSTARetrieveCall_t;

typedef struct CSTARetrieveCallConfEvent_t {
    Nulltype        null;
} CSTARetrieveCallConfEvent_t;

typedef struct CSTASetMwi_t {
    DeviceID_t      device;
    Boolean         messages;
} CSTASetMwi_t;

typedef struct CSTASetMwiConfEvent_t {
    Nulltype        null;
} CSTASetMwiConfEvent_t;

typedef struct CSTASetDnd_t {
    DeviceID_t      device;
    Boolean         doNotDisturb;
} CSTASetDnd_t;

typedef struct CSTASetDndConfEvent_t {
    Nulltype        null;
} CSTASetDndConfEvent_t;

typedef struct CSTASetFwd_t {
    DeviceID_t      device;
    ForwardingInfo_t forward;
} CSTASetFwd_t;

typedef struct CSTASetFwdConfEvent_t {
    Nulltype        null;
} CSTASetFwdConfEvent_t;

typedef enum AgentMode_t {
    AM_LOG_IN = 0,
    AM_LOG_OUT = 1,
    AM_NOT_READY = 2,
    AM_READY = 3,
    AM_WORK_NOT_READY = 4,
    AM_WORK_READY = 5
} AgentMode_t;

typedef struct CSTASetAgentState_t {
    DeviceID_t      device;
    AgentMode_t     agentMode;
    AgentID_t       agentID;
    AgentGroup_t    agentGroup;
    AgentPassword_t agentPassword;
} CSTASetAgentState_t;

typedef struct CSTASetAgentStateConfEvent_t {
    Nulltype        null;
} CSTASetAgentStateConfEvent_t;

typedef struct CSTATransferCall_t {
    ConnectionID_t  heldCall;
    ConnectionID_t  activeCall;
} CSTATransferCall_t;

typedef struct CSTATransferCallConfEvent_t {
    ConnectionID_t  newCall;
    ConnectionList_t connList;
} CSTATransferCallConfEvent_t;

typedef struct CSTAUniversalFailureConfEvent_t {
    CSTAUniversalFailure_t error;
} CSTAUniversalFailureConfEvent_t;

typedef struct CSTACallClearedEvent_t {
    ConnectionID_t  clearedCall;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTACallClearedEvent_t;

typedef struct CSTAConferencedEvent_t {
    ConnectionID_t  primaryOldCall;
    ConnectionID_t  secondaryOldCall;
    SubjectDeviceID_t confController;
    SubjectDeviceID_t addedParty;
    ConnectionList_t conferenceConnections;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAConferencedEvent_t;

typedef struct CSTAConnectionClearedEvent_t {
    ConnectionID_t  droppedConnection;
    SubjectDeviceID_t releasingDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAConnectionClearedEvent_t;

typedef struct CSTADeliveredEvent_t {
    ConnectionID_t  connection;
    SubjectDeviceID_t alertingDevice;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    RedirectionDeviceID_t lastRedirectionDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTADeliveredEvent_t;

typedef struct CSTADivertedEvent_t {
    ConnectionID_t  connection;
    SubjectDeviceID_t divertingDevice;
    CalledDeviceID_t newDestination;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTADivertedEvent_t;

typedef struct CSTAEstablishedEvent_t {
    ConnectionID_t  establishedConnection;
    SubjectDeviceID_t answeringDevice;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    RedirectionDeviceID_t lastRedirectionDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAEstablishedEvent_t;

typedef struct CSTAFailedEvent_t {
    ConnectionID_t  failedConnection;
    SubjectDeviceID_t failingDevice;
    CalledDeviceID_t calledDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAFailedEvent_t;

typedef struct CSTAHeldEvent_t {
    ConnectionID_t  heldConnection;
    SubjectDeviceID_t holdingDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAHeldEvent_t;

typedef struct CSTANetworkReachedEvent_t {
    ConnectionID_t  connection;
    SubjectDeviceID_t trunkUsed;
    CalledDeviceID_t calledDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTANetworkReachedEvent_t;

typedef struct CSTAOriginatedEvent_t {
    ConnectionID_t  originatedConnection;
    SubjectDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAOriginatedEvent_t;

typedef struct CSTAQueuedEvent_t {
    ConnectionID_t  queuedConnection;
    SubjectDeviceID_t queue;
    CallingDeviceID_t callingDevice;
    CalledDeviceID_t calledDevice;
    RedirectionDeviceID_t lastRedirectionDevice;
    short           numberQueued;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAQueuedEvent_t;

typedef struct CSTARetrievedEvent_t {
    ConnectionID_t  retrievedConnection;
    SubjectDeviceID_t retrievingDevice;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTARetrievedEvent_t;

typedef struct CSTAServiceInitiatedEvent_t {
    ConnectionID_t  initiatedConnection;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTAServiceInitiatedEvent_t;

typedef struct CSTATransferredEvent_t {
    ConnectionID_t  primaryOldCall;
    ConnectionID_t  secondaryOldCall;
    SubjectDeviceID_t transferringDevice;
    SubjectDeviceID_t transferredDevice;
    ConnectionList_t transferredConnections;
    LocalConnectionState_t localConnectionInfo;
    CSTAEventCause_t cause;
} CSTATransferredEvent_t;

typedef struct CSTACallInformationEvent_t {
    ConnectionID_t  connection;
    SubjectDeviceID_t device;
    AccountInfo_t   accountInfo;
    AuthCode_t      authorisationCode;
} CSTACallInformationEvent_t;

typedef struct CSTADoNotDisturbEvent_t {
    SubjectDeviceID_t device;
    Boolean         doNotDisturbOn;
} CSTADoNotDisturbEvent_t;

typedef struct CSTAForwardingEvent_t {
    SubjectDeviceID_t device;
    ForwardingInfo_t forwardingInformation;
} CSTAForwardingEvent_t;

typedef struct CSTAMessageWaitingEvent_t {
    CalledDeviceID_t deviceForMessage;
    SubjectDeviceID_t invokingDevice;
    Boolean         messageWaitingOn;
} CSTAMessageWaitingEvent_t;

typedef struct CSTALoggedOnEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
    AgentGroup_t    agentGroup;
    AgentPassword_t password;
} CSTALoggedOnEvent_t;

typedef struct CSTALoggedOffEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
    AgentGroup_t    agentGroup;
} CSTALoggedOffEvent_t;

typedef struct CSTANotReadyEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
} CSTANotReadyEvent_t;

typedef struct CSTAReadyEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
} CSTAReadyEvent_t;

typedef struct CSTAWorkNotReadyEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
} CSTAWorkNotReadyEvent_t;

typedef struct CSTAWorkReadyEvent_t {
    SubjectDeviceID_t agentDevice;
    AgentID_t       agentID;
} CSTAWorkReadyEvent_t;

typedef struct CSTARouteRegisterReq_t {
    DeviceID_t      routingDevice;
} CSTARouteRegisterReq_t;

typedef struct CSTARouteRegisterReqConfEvent_t {
    RouteRegisterReqID_t registerReqID;
} CSTARouteRegisterReqConfEvent_t;

typedef struct CSTARouteRegisterCancel_t {
    RouteRegisterReqID_t routeRegisterReqID;
} CSTARouteRegisterCancel_t;

typedef struct CSTARouteRegisterCancelConfEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
} CSTARouteRegisterCancelConfEvent_t;

typedef struct CSTARouteRegisterAbortEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
} CSTARouteRegisterAbortEvent_t;

typedef struct CSTARouteRequestEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    DeviceID_t      currentRoute;
    DeviceID_t      callingDevice;
    ConnectionID_t  routedCall;
    SelectValue_t   routedSelAlgorithm;
    Boolean         priority;
    SetUpValues_t   setupInformation;
} CSTARouteRequestEvent_t;

typedef struct CSTARouteSelectRequest_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    DeviceID_t      routeSelected;
    RetryValue_t    remainRetry;
    SetUpValues_t   setupInformation;
    Boolean         routeUsedReq;
} CSTARouteSelectRequest_t;

typedef struct CSTAReRouteRequest_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
} CSTAReRouteRequest_t;

typedef struct CSTARouteUsedEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    DeviceID_t      routeUsed;
    DeviceID_t      callingDevice;
    Boolean         domain;
} CSTARouteUsedEvent_t;

typedef struct CSTARouteEndEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    CSTAUniversalFailure_t errorValue;
} CSTARouteEndEvent_t;

typedef struct CSTARouteEndRequest_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    CSTAUniversalFailure_t errorValue;
} CSTARouteEndRequest_t;

typedef struct CSTAEscapeSvc_t {
    Nulltype        null;
} CSTAEscapeSvc_t;

typedef struct CSTAEscapeSvcConfEvent_t {
    Nulltype        null;
} CSTAEscapeSvcConfEvent_t;

typedef struct CSTAEscapeSvcReqEvent_t {
    Nulltype        null;
} CSTAEscapeSvcReqEvent_t;

typedef struct CSTAEscapeSvcReqConf_t {
    CSTAUniversalFailure_t errorValue;
} CSTAEscapeSvcReqConf_t;

typedef struct CSTAPrivateEvent_t {
    Nulltype        null;
} CSTAPrivateEvent_t;

typedef struct CSTAPrivateStatusEvent_t {
    Nulltype        null;
} CSTAPrivateStatusEvent_t;

typedef struct CSTASendPrivateEvent_t {
    Nulltype        null;
} CSTASendPrivateEvent_t;

typedef struct CSTABackInServiceEvent_t {
    DeviceID_t      device;
    CSTAEventCause_t cause;
} CSTABackInServiceEvent_t;

typedef struct CSTAOutOfServiceEvent_t {
    DeviceID_t      device;
    CSTAEventCause_t cause;
} CSTAOutOfServiceEvent_t;

typedef enum SystemStatus_t {
    SS_INITIALIZING = 0,
    SS_ENABLED = 1,
    SS_NORMAL = 2,
    SS_MESSAGES_LOST = 3,
    SS_DISABLED = 4,
    SS_OVERLOAD_IMMINENT = 5,
    SS_OVERLOAD_REACHED = 6,
    SS_OVERLOAD_RELIEVED = 7
} SystemStatus_t;

typedef unsigned char   SystemStatusFilter_t;
#define                     SF_INITIALIZING 0x80
#define                     SF_ENABLED 0x40
#define                     SF_NORMAL 0x20
#define                     SF_MESSAGES_LOST 0x10
#define                     SF_DISABLED 0x08
#define                     SF_OVERLOAD_IMMINENT 0x04
#define                     SF_OVERLOAD_REACHED 0x02
#define                     SF_OVERLOAD_RELIEVED 0x01

typedef struct CSTAReqSysStat_t {
    Nulltype        null;
} CSTAReqSysStat_t;

typedef struct CSTASysStatReqConfEvent_t {
    SystemStatus_t  systemStatus;
} CSTASysStatReqConfEvent_t;

typedef struct CSTASysStatStart_t {
    SystemStatusFilter_t statusFilter;
} CSTASysStatStart_t;

typedef struct CSTASysStatStartConfEvent_t {
    SystemStatusFilter_t statusFilter;
} CSTASysStatStartConfEvent_t;

typedef struct CSTASysStatStop_t {
    Nulltype        null;
} CSTASysStatStop_t;

typedef struct CSTASysStatStopConfEvent_t {
    Nulltype        null;
} CSTASysStatStopConfEvent_t;

typedef struct CSTAChangeSysStatFilter_t {
    SystemStatusFilter_t statusFilter;
} CSTAChangeSysStatFilter_t;

typedef struct CSTAChangeSysStatFilterConfEvent_t {
    SystemStatusFilter_t statusFilterSelected;
    SystemStatusFilter_t statusFilterActive;
} CSTAChangeSysStatFilterConfEvent_t;

typedef struct CSTASysStatEvent_t {
    SystemStatus_t  systemStatus;
} CSTASysStatEvent_t;

typedef struct CSTASysStatEndedEvent_t {
    Nulltype        null;
} CSTASysStatEndedEvent_t;

typedef struct CSTASysStatReqEvent_t {
    Nulltype        null;
} CSTASysStatReqEvent_t;

typedef struct CSTAReqSysStatConf_t {
    SystemStatus_t  systemStatus;
} CSTAReqSysStatConf_t;

typedef struct CSTASysStatEventSend_t {
    SystemStatus_t  systemStatus;
} CSTASysStatEventSend_t;

typedef struct CSTAMonitorDevice_t {
    DeviceID_t      deviceID;
    CSTAMonitorFilter_t monitorFilter;
} CSTAMonitorDevice_t;

typedef struct CSTAMonitorCall_t {
    ConnectionID_t  call;
    CSTAMonitorFilter_t monitorFilter;
} CSTAMonitorCall_t;

typedef struct CSTAMonitorCallsViaDevice_t {
    DeviceID_t      deviceID;
    CSTAMonitorFilter_t monitorFilter;
} CSTAMonitorCallsViaDevice_t;

typedef struct CSTAMonitorConfEvent_t {
    CSTAMonitorCrossRefID_t monitorCrossRefID;
    CSTAMonitorFilter_t monitorFilter;
} CSTAMonitorConfEvent_t;

typedef struct CSTAChangeMonitorFilter_t {
    CSTAMonitorCrossRefID_t monitorCrossRefID;
    CSTAMonitorFilter_t monitorFilter;
} CSTAChangeMonitorFilter_t;

typedef struct CSTAChangeMonitorFilterConfEvent_t {
    CSTAMonitorFilter_t monitorFilter;
} CSTAChangeMonitorFilterConfEvent_t;

typedef struct CSTAMonitorStop_t {
    CSTAMonitorCrossRefID_t monitorCrossRefID;
} CSTAMonitorStop_t;

typedef struct CSTAMonitorStopConfEvent_t {
    Nulltype        null;
} CSTAMonitorStopConfEvent_t;

typedef struct CSTAMonitorEndedEvent_t {
    CSTAEventCause_t cause;
} CSTAMonitorEndedEvent_t;

typedef struct CSTASnapshotCall_t {
    ConnectionID_t  snapshotObject;
} CSTASnapshotCall_t;

typedef struct CSTASnapshotCallConfEvent_t {
    CSTASnapshotCallData_t snapshotData;
} CSTASnapshotCallConfEvent_t;

typedef struct CSTASnapshotDevice_t {
    DeviceID_t      snapshotObject;
} CSTASnapshotDevice_t;

typedef struct CSTASnapshotDeviceConfEvent_t {
    CSTASnapshotDeviceData_t snapshotData;
} CSTASnapshotDeviceConfEvent_t;

typedef struct CSTAGetAPICaps_t {
    Nulltype        null;
} CSTAGetAPICaps_t;

typedef struct CSTAGetAPICapsConfEvent_t {
    short           alternateCall;
    short           answerCall;
    short           callCompletion;
    short           clearCall;
    short           clearConnection;
    short           conferenceCall;
    short           consultationCall;
    short           deflectCall;
    short           pickupCall;
    short           groupPickupCall;
    short           holdCall;
    short           makeCall;
    short           makePredictiveCall;
    short           queryMwi;
    short           queryDnd;
    short           queryFwd;
    short           queryAgentState;
    short           queryLastNumber;
    short           queryDeviceInfo;
    short           reconnectCall;
    short           retrieveCall;
    short           setMwi;
    short           setDnd;
    short           setFwd;
    short           setAgentState;
    short           transferCall;
    short           eventReport;
    short           callClearedEvent;
    short           conferencedEvent;
    short           connectionClearedEvent;
    short           deliveredEvent;
    short           divertedEvent;
    short           establishedEvent;
    short           failedEvent;
    short           heldEvent;
    short           networkReachedEvent;
    short           originatedEvent;
    short           queuedEvent;
    short           retrievedEvent;
    short           serviceInitiatedEvent;
    short           transferredEvent;
    short           callInformationEvent;
    short           doNotDisturbEvent;
    short           forwardingEvent;
    short           messageWaitingEvent;
    short           loggedOnEvent;
    short           loggedOffEvent;
    short           notReadyEvent;
    short           readyEvent;
    short           workNotReadyEvent;
    short           workReadyEvent;
    short           backInServiceEvent;
    short           outOfServiceEvent;
    short           privateEvent;
    short           routeRequestEvent;
    short           reRoute;
    short           routeSelect;
    short           routeUsedEvent;
    short           routeEndEvent;
    short           monitorDevice;
    short           monitorCall;
    short           monitorCallsViaDevice;
    short           changeMonitorFilter;
    short           monitorStop;
    short           monitorEnded;
    short           snapshotDeviceReq;
    short           snapshotCallReq;
    short           escapeService;
    short           privateStatusEvent;
    short           escapeServiceEvent;
    short           escapeServiceConf;
    short           sendPrivateEvent;
    short           sysStatReq;
    short           sysStatStart;
    short           sysStatStop;
    short           changeSysStatFilter;
    short           sysStatReqEvent;
    short           sysStatReqConf;
    short           sysStatEvent;
} CSTAGetAPICapsConfEvent_t;

typedef enum CSTALevel_t {
    CSTA_HOME_WORK_TOP = 1,
    CSTA_AWAY_WORK_TOP = 2,
    CSTA_DEVICE_DEVICE_MONITOR = 3,
    CSTA_CALL_DEVICE_MONITOR = 4,
    CSTA_CALL_CONTROL = 5,
    CSTA_ROUTING = 6,
    CSTA_CALL_CALL_MONITOR = 7
} CSTALevel_t;

typedef enum SDBLevel_t {
    NO_SDB_CHECKING = -1,
    ACS_ONLY = 1,
    ACS_AND_CSTA_CHECKING = 0
} SDBLevel_t;

typedef struct CSTAGetDeviceList_t {
    long            index;
    CSTALevel_t     level;
} CSTAGetDeviceList_t;

typedef struct DeviceList_t {
    short           count;
    DeviceID_t      device[20];
} DeviceList_t;

typedef struct CSTAGetDeviceListConfEvent_t {
    SDBLevel_t      driverSdbLevel;
    CSTALevel_t     level;
    long            index;
    DeviceList_t    devList;
} CSTAGetDeviceListConfEvent_t;

typedef struct CSTAQueryCallMonitor_t {
    Nulltype        null;
} CSTAQueryCallMonitor_t;

typedef struct CSTAQueryCallMonitorConfEvent_t {
    Boolean         callMonitor;
} CSTAQueryCallMonitorConfEvent_t;

typedef struct CSTARouteRequestExtEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    CalledDeviceID_t currentRoute;
    CallingDeviceID_t callingDevice;
    ConnectionID_t  routedCall;
    SelectValue_t   routedSelAlgorithm;
    Boolean         priority;
    SetUpValues_t   setupInformation;
} CSTARouteRequestExtEvent_t;

typedef struct CSTARouteUsedExtEvent_t {
    RouteRegisterReqID_t routeRegisterReqID;
    RoutingCrossRefID_t routingCrossRefID;
    CalledDeviceID_t routeUsed;
    CallingDeviceID_t callingDevice;
    Boolean         domain;
} CSTARouteUsedExtEvent_t;

typedef CSTARouteSelectRequest_t CSTARouteSelectInvRequest_t;

typedef CSTARouteEndRequest_t CSTARouteEndInvRequest_t;


extern void FAR *csta_asn_tbl;    /* encoder-decoder control table */

#endif
