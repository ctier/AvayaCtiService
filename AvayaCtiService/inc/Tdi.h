/***********************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/*
 *  tdi.h    Tserver-Driver Interface
 *
 *  Header File Dependencies
 *      acs.h
 *      csta.h
 *
 *  When compiling for the Windows NT platform define _WINNT_NTS_.
 *
 *  When compiling for the NetWare platform define _NETWARE_NTS_.
 *
 *  If neither of these are defined an error will occur during the compile.
 */

#ifndef TDI__H
#define TDI__H


#ifdef _WINNT_NTS_
	#ifdef WATCOMC
		#define	TDILIBAPI	__export
	#else
		#if !defined(_TDILIB_)
			#define TDILIBAPI __declspec(dllimport)
		#else
			#define TDILIBAPI __declspec(dllexport)
		#endif
	#endif
#elif defined ( _NETWARE_NTS_ )
	#define TDILIBAPI extern 
#else
	Must define platform (_WINNT_NTS_ or _NETWARE_NTS_)
#endif
	


     /*
      * DEFINES
      */

#define TSDI_VERSION		"1.1"		/* Tserver Driver Interface version 1 */
#define TSDI_VERSION_2		"2.1"		/* Tserver Driver Interface version 2 */

#define TDI_SUCCESS             1       /* TDI Function call completed OK */

#define TDI_MAX_SERVICE_NAME    14      /* Max length of the service name */
#define TDI_MAX_DRIVER_NAME     10      /* Max length of the driver name  */
#define TDI_MAX_VENDOR_NAME     8       /* Max length of the vendor name  */
#define TDI_MAX_SERVICE_TYPE    15      /* Max length of the service type */

#define TDI_MAX_REGISTRATIONS   16      /* Max driver registerations per
					 					 * Tserver */
#define TDI_MAX_NAME_SPACE      48      /* Max size of char arrays stored by
					 					 * TDI */
#define TDI_MAX_VERSION_STRING	24		/* Max length of version string */
#define TDI_MAX_TSDI_VER	 	5		/* Max length of tsdi version string */
#define TDI_MAX_BUFFER_SIZE     (4096-16) /* Max size of buffers sent across
					   					   * the TDI */


/* TDI Default buffer descriptor values */

#define TDI_MAX_BYTES_ALLOCATED 0x180000 	/* Default max bytes allocated per
					  						 * driver: 1 meg  */
#define TDI_MIN_BYTES_ALLOCATED 0x10000 	/* Default min bytes allocated per
					  						 * driver: 1 meg  */
#define TDI_BUFFER_HI_WATER_MARK (TDI_MAX_BYTES_ALLOCATED * 80 / 100)  /* Default high water mark for
																		* allocated buffers */
					 						 

/* TDI Buffer allocation condition flags */

#define TDI_EXCEED_HIWATER_MARK 0x01    /* Buffers allocated exceed high water
					 					 * mark */
#define TDI_EXCEED_MAX_BYTES    0x02    /* Buffers allocated exceed max bytes
					 					 * allowed */ 

/* TDI Security Checks per client request 
 * All levels of security verify that the
 * client has a valid login and password
 */

#define TDI_CSTA_SECURITY       0       /* Security check per client req. */
#define TDI_LOGIN_SECURITY      1       /* Security check on login */
#define TDI_NO_SECURITY         -1      /* No security checks */


/* TDI Message Priority Class */

#define TDI_NORMAL_MESSAGE      0x0     /* Send message normal class */
#define TDI_PRIORITY_MESSAGE    0x1     /* Send message priority class */

/* TDI CSTA Protocol Versions */
#define TDI_CSTA_VERSION_1	0x1			/* TSAPI CSTA protocol version 1 */
#define TDI_CSTA_VERSION_2	0x2			/* TSAPI CSTA protocol version 2 */
#define TDI_CSTA_VERSION_3	0x4			/* TSAPI CSTA protocol version 3 */

/* TDI OAM Protocol Version */
#define TDI_OAM_VERSION_1	0x1			/* TSAPI OAM protocol version 1 */

/* TDI Simulator Protocol Versions */
#define TDI_SIM_VERSION_1	0x1			/* Simulator protocol version 1 */
#define TDI_SIM_VERSION_2	0x2			/* Simulator protocol version 2 */
#define TDI_SIM_VERSION_3	0x4			/* Simulator protocol version 2 */

/* TDI Name Server Protocol Versions */
#define TDI_NMSRV_VERSION_1	0x1	/* Tserver NS protocol version 1 */

/* TDI Tserver OAM Protocol Versions */
#define TDI_TSRVOAM_VERSION_1	0x01	/* Tserver OAM protocol version 1 */
#define TDI_TSRVOAM_VERSION_2	0x02	/* Tserver OAM protocol version 2 */
#define TDI_TSRVOAM_VERSION_3	0x04	/* Tserver OAM protocol version 3 */
#define TDI_TSRVOAM_VERSION_4	0x08	/* Tserver OAM protocol version 4 */
#define TDI_TSRVOAM_VERSION_5	0x10	/* Tserver OAM protocol version 5 */

/* TDI Tserver Maintenance Protocol Versions */
#define TDI_TSRVMAINT_VERSION_4 0x8	/* Tserver Maintenance protocol version 4 */

/* TDI Tserver SDB Admin Protocol Versions */
#define TDI_SDBADMIN_VERSION_4 0x8  /* Tserver SDB Admin protocol versions 4 */
#define TDI_SDBADMIN_VERSION_5 0x10 /* Tserver SDB Admin protocol versions 5 */

/* TDI CSTA Server OAM Protocol Versions */
#define TDI_CSRVOAM_VERSION_1	0x1	/* Cserver OAM protocol version 1 */

/* TDI Error Codes  */

#define TDI_ERR_ESYS            -1      /* System Error occurred */
#define TDI_ERR_BAD_DRVRID      -2      /* Unregistered driverID */
#define TDI_ERR_DUP_DRVR        -3      /* Service name already registered */
#define TDI_ERR_NO_MEM          -4      /* Unable to allocate memory */
#define TDI_ERR_MAX_DRVR        -5      /* Max  number of drivers exceeded */
#define TDI_ERR_EINVAL          -6      /* Invalid parameter to TDI call */
#define TDI_ERR_NO_BUFFERS      -7      /* No  buffers available to allocate */
#define TDI_ERR_BADLENGTH       -8      /* Requested length > max buf size */
#define TDI_ERR_BAD_BUF         -9      /* Buffer supplied is invalid */
#define	TDI_ERR_NOT_YOUR_BUFFER	-10	/* trying to free someone else's buf */
#define TDI_ERR_DRVR_UNREGISTERED -11   /* The Driver unregistered */
#define TDI_ERR_BAD_VERSION 	-12   	/* Bad version # to registration */
#define TDI_ERR_BAD_SECURITY 	-13   	/* Bad drvr security to registration */
#define TDI_ERR_BAD_SRVC_NAME 	-14   	/* Bad service name to registration */
#define TDI_ERR_BAD_VENDOR_NAME	-15   	/* Bad vendor name to registration */
#define TDI_ERR_BAD_DRVR_NAME 	-16   	/* Bad driver name to registration */
#define TDI_ERR_BAD_SESSIONID 	-17   	/* Bad session ID */
#define TDI_ERR_BAD_INVOKEID 	-18   	/* Bad invoke ID */
#define TDI_ERR_BAD_SEM 		-19   	/* Bad semaphore from on WaitLocal*/
#define TDI_ERR_BAD_PROTOCOL	-20	/* Bad protocol to registration */
#define TDI_ERR_BAD_SRVC_TYPE	-21	/* Bad service type */
#define TDI_ERR_TRAFFIC_OFF		-22	/* Traffic Measurments is disabled */
#define TDI_ERR_NOT_REGISTERED	-23	/* Not registered for Traffic */

/* Traffic Measurements Report Type */
#define	TDI_PBX_DRIVER		0

/* Traffic Measurments Statistic Types */
#define	TDI_RECEIVED_MESSAGE	1
#define	TDI_SENT_MESSAGE		2
#define	TDI_REJECTED_MESSAGE	3

/* Traffic Measurements Callback Function Parameter */
#define	TDI_TRAFFIC_ENABLED		4
#define	TDI_TRAFFIC_DISABLED	5

     /*
      * TYPEDEFS
      */

typedef int     		TDIHandle_t;            /* Identifies Tserver-Driver intf. */
typedef int     		TDIReturn_t;            /* Return type for TDI functions */
typedef int     		TDISecurity_t;          /* Security requested/client req. */
typedef int     		TDIBuf_flag_t;          /* Current buffer allocation info */
typedef int     		TDIPriority_t;          /* Message priority */
typedef char *			TDIVersion_t;			/* TSDI version */
typedef unsigned long 	TDIProtocol_t;			/* TSAPI protocol version */
typedef unsigned short	SessionID_t;			/* Connection ID */
typedef int				TDITrafficType_t;		/* Traffic Report Type */
typedef	int				TDIStatType_t;			/* Traffic Statistic Type */
typedef	int				TDIStatValue_t;			/* Traffic Report Type Value */

/* Buffer Descriptor */

typedef struct
{
	unsigned long   max_bytes;      /* Maximum number of bytes to allocate
					 				 * for this interface */
	unsigned long   hiwater_mark;   /* High water mark for buffer allocation
					 				 * on this interface */
} TDIBuf_info_t;

/* Queue Descriptor */

typedef struct
{
	int     queued_to_driver;       /* Number of bufs queued to driver */
	int     queued_to_tserver;      /* Number of bufs queued to tserver */
	int     allocd_by_driver;       /* Number of bufs allocated to driver */
	int     allocd_by_tserver;      /* Number of bufs allocated to tserver*/
} TDIQueue_info_t;

/* Mem Descriptor */

typedef struct
{
	unsigned long   bytes_queued_to_driver;		/* Number of bytes in message
						 					 	 * buffers queued to driver */
	unsigned long   bytes_queued_to_tserver;	/* Number of bytes in message
						 					  	 * buffers queued to tserver */
	unsigned long   bytes_allocd_by_driver; 	/* Number of bytes in message
						 						 * buffers allocated to driver*/
	unsigned long   bytes_allocd_by_tserver; 	/* Number of bytes in message
						 						 * buffers alloc'd to tserver */
} TDIMemAlloc_info_t;


#ifdef _NETWARE_NTS_
typedef struct 
{
	char year;
	char month;
	char date;
	char hour;
	char min;
	char sec;
	char day;
} LoginTime_t;
#endif

#ifdef _WINNT_NTS_
typedef struct 
{
	short year;
	short month;
	short date;
	short hour;
	short min;
	short sec;
	short day;
} LoginTime_t;

#endif

/* TDI Session ID structure */

typedef struct
{
	LoginID_t		loginID;			/* Login for this session */
	AppName_t		appName;			/* Application name for this session */
	unsigned long   network;			/* Network of worktop */
	unsigned char   node[6];			/* Node of worktop */
	LoginTime_t		timeOpened;			/* Time the ACS stream was opened */
	char			homeDeviceID[16]; 	/* Primary device ID of Home 
					   				     * WorkTop record 
					   				     */
	char			awayDeviceID[16]; 	/* Primary device ID of Away Worktop
					   				     * record.
					   				     */
} TDISessionID_t;


/* TDI Session Information structure */

typedef struct
{
	unsigned long   network;	/* Network of worktop */
	unsigned char   node[6];	/* Node of worktop */
} TDISPXAddr_t;

typedef struct
{
	unsigned long	addr;		/* 32 byte address (network order) */
} TDIIPAddr_t;

typedef struct
{
	LoginID_t			loginID;			/* Login for this session */
	AppName_t			appName;			/* Application name for this session */
	LoginTime_t			timeOpened;			/* Time the ACS stream was opened */
	char				homeDeviceID[16];	/* Primary device ID of Home 
					   						 * WorkTop record 
					   						 */
	char				awayDeviceID[16];	/* Primary device ID of Away Worktop
					   						 * record.
						   					 */
	unsigned short		transportType;		/* Transport type (see below)	*/
	union {
		char			pad[32];			/* struct padding	*/
		TDISPXAddr_t	spxAddress;			/* SPX/IPX address	*/
		TDIIPAddr_t		ipAddress;			/* IP address		*/
	} address;
} TDISessionInfo_t;

/* defines for transportType field */
#define TDI_SPX_IPX		1	  /* SPX/IPX transport		*/
#define TDI_TCP_IP		2	  /* TCP/IP transport		*/

typedef struct SetFlowControl_t {
    char           alternateCall;
    char           answerCall;
    char           callCompletion;
    char           clearCall;
    char           clearConnection;
    char           conferenceCall;
    char           consultationCall;
    char           deflectCall;
    char           pickupCall;
    char           groupPickupCall;
    char           holdCall;
    char           makeCall;
    char           makePredictiveCall;
    char           queryMwi;
    char           queryDnd;
    char           queryFwd;
    char           queryAgentState;
    char           queryLastNumber;
    char           queryDeviceInfo;
    char           reconnectCall;
    char           retrieveCall;
    char           setMwi;
    char           setDnd;
    char           setFwd;
    char           setAgentState;
    char           transferCall;
    char           eventReport;
    char	       routeRegister;
    char	       routeRegisterCancel;
    char           reRoute;
    char           routeSelect;
    char           monitorDevice;
    char           monitorCall;
    char           monitorCallsViaDevice;
    char           changeMonitorFilter;
    char           monitorStop;
    char           monitorEnded;
    char           snapshotDeviceReq;
    char           snapshotCallReq;
    char           escapeService;
    char           escapeServiceConf;
    char           sysStatReq;
    char           sysStatStart;
    char           sysStatStop;
    char           sysStatFilter;
    char           changeSysStatFilter;
    char           sysStatReqConf;
    char  	       acsOpenStream;
} SetFlowControl_t;

#pragma pack (4)
typedef struct TdiAbout_t
{
	char	aboutVer[20];  		/* Module version */
	char	aboutString[40];	/* Module name */
} TdiAbout_t;
#pragma pack ()

#ifdef __cplusplus
extern "C" {
#endif
     /*
      * FUNCTION PROTOTYPES
      */

TDILIBAPI TDIHandle_t tdiDriverRegister(
	const char			*service_name,          /* INPUT  */
	const char			*driver_name,           /* INPUT  */
	int					service_type,           /* INPUT  */
	TDIProtocol_t		protocol_descriptor,    /* INPUT  */
	const char			*vendor_name,           /* INPUT  */
	const TDIVersion_t	version,        		/* INPUT  */
	TDISecurity_t		driver_security,		/* INPUT  */
	const TDIBuf_info_t	*buffer_descriptor); 	/* INPUT  */

TDILIBAPI TDIReturn_t tdiDriverUnregister (
	TDIHandle_t     	driverID);     	/* INPUT */

TDILIBAPI TDIReturn_t tdiAllocBuffer (
	TDIHandle_t     driverID,	/* INPUT   */
	char            **bufptr,	/* OUTPUT */
	unsigned int    length,		/* INPUT   */
	TDIBuf_flag_t   *buf_flag);	/* OUTPUT */

TDILIBAPI TDIReturn_t tdiFreeBuffer (
	TDIHandle_t     driverID,      /* INPUT   */
	char            *bufptr);       /* INPUT   */


TDILIBAPI TDIReturn_t tdiReceiveFromTserver(
	TDIHandle_t     driverID,      	/* INPUT  */
	char            **bufptr);      /* OUTPUT */

TDILIBAPI TDIReturn_t tdiSendToTserver(
	TDIHandle_t     driverID,      	/* INPUT  */
	char            *bufptr,        /* INPUT  */
	TDIPriority_t   priority);      /* INPUT  */

TDILIBAPI TDIReturn_t tdiQueueSize (
	TDIHandle_t     driverID,      		/* INPUT  */
	TDIQueue_info_t *queue_descriptor); /* OUTPUT */

TDILIBAPI TDIReturn_t tdiGetTDISize (
	TDIHandle_t     driverID,      			/* INPUT  */
	TDIBuf_info_t	*buffer_descriptor);	/* OUTPUT  */

TDILIBAPI TDIReturn_t tdiMemAllocSize (
	TDIHandle_t     driverID,      			/* INPUT  */
	TDIMemAlloc_info_t *mem_descriptor);	/* OUTPUT */

TDILIBAPI TDIReturn_t tdiDriverSanity (
	TDIHandle_t     driverID);     			/* INPUT  */

TDILIBAPI TDIReturn_t tdiGetSessionIDInfo (
	TDIHandle_t		driverID,		/* INPUT  */
	SessionID_t		sessionID,		/* INPUT  */
	TDISessionID_t	*sessionIDInfo);/* OUTPUT */

TDILIBAPI TDIReturn_t tdiGetSessionInformation (
	TDIHandle_t			driverID,		/* INPUT  */
	SessionID_t			sessionID,		/* INPUT  */
	TDISessionInfo_t	*sessionInfo); /* OUTPUT */

TDILIBAPI TDIReturn_t tdiMapInvokeID(
	TDIHandle_t		driverID,		/* INPUT  */
	SessionID_t		sessionID,		/* INPUT  */
	InvokeID_t		invokeID,		/* INPUT  */
	InvokeID_t  	*appInvokeID);   /* OUTPUT */

TDILIBAPI TDIReturn_t tdiSetMessageFlowControl(
	TDIHandle_t			driverID,	/* INPUT */
	short	int			msgLevel,	/* INPUT */
	SetFlowControl_t	*cstaMsgs);	/* INPUT */

TDILIBAPI TDIReturn_t tdiGetMessageFlowControl(
	TDIHandle_t			driverID,	/* INPUT */
	short	int			*msgLevel,	/* INPUT */
	SetFlowControl_t	*cstaMsgs);	/* INPUT */

TDILIBAPI TDIReturn_t tdiGetTservVersion(
	char			*customer_version,	/* OUTPUT */
	char			*internal_version,	/* OUTPUT */
	TDIVersion_t	tsdi_version,		/* OUTPUT */
	int				service_type,		/* INPUT */
	TDIProtocol_t	*protocol_version);	/* OUTPUT */

typedef void	(*TrafficMeasCB) (TDIHandle_t driverID, int cbParam);

TDILIBAPI TDIReturn_t tdiTrafficRegister(
	TDIHandle_t			driverID,		/* INPUT */
	TDITrafficType_t	trafficType,	/* INPUT */
	TrafficMeasCB		callback ); 	/* INPUT */

TDILIBAPI TDIReturn_t tdiTrafficReport(
	TDIHandle_t			driverID,		/* INPUT */
	TDITrafficType_t	trafficType,	/* INPUT */
	TDIStatType_t		statType,		/* INPUT */
	TDIStatValue_t		statValue );	/* INPUT */

TDILIBAPI TDIReturn_t tdiTrafficUnregister (
	TDIHandle_t     	driverID,		/* INPUT */
	TDITrafficType_t	trafficType);	/* INPUT */

TDILIBAPI TDIReturn_t tdiGetAboutInfo(TdiAbout_t	*tdiAbout);

TDILIBAPI char* tdiGetPDUName(EventClass_t msgClass,EventType_t msgType);
 
#ifdef _WINNT_NTS_
/* This API only applies to the Windows NT platform */
TDILIBAPI TDIReturn_t tdiDriverUnload(const char	*driverName);
#endif

/*
 * Error Levels used by tdiLogError
 */
#undef TRACE
#undef ERROR
typedef enum error_level {
	TRACE 		= 0x1,		/* trace message for debugging */
	CAUTION 	= 0x2,		/* unexpected software error (non-fatal) */
	AUDIT_TRAIL = 0x4,		/* important (normal) event */
	WARNING 	= 0x8,		/* non-service-affecting condition */
	ERROR 		= 0x10,		/* non-fatal, service-affecting condition */
	FATAL 		= 0x20,		/* FATAL condition (calling module aborting) */

	/* FORCE_PRINTF is only used in the NetWare target */
	FORCE_PRINTF = 0x80,	/* If or'd in with one of the other levels,
				 			 * forces a ConsolePrintf regardless of how
				 			 * the system errlog settings are
				 			 */
	FORCE_LOG	= 0x100		/* Force the message into the error log
							 * regardless of the system error log settings.
							 */
} ElogLevel_t;

typedef enum error_level ElogLevelMask_t;
typedef int ElogDestMask_t;


TDILIBAPI void tdiLogError(
		const char      *module,        /* I - module name */
		ElogLevel_t     level,          /* I - TRACE, ERROR, FATAL,...*/
		int		location_code,  /* I - unique location number */
		int		error_code,     /* I - error code */
		const char      *format,        /* I - printf style format */
		...				/* I - optional arguments 
						 * (0 or more)   */
		);


#ifdef __cplusplus
}
#endif

/* Driver Service Type - passed in tdiDriverRegister() */
#define TDI_ST_OAM      1       
#define TDI_ST_CSTA     2
#define TDI_ST_SIM      3
#define TDI_ST_NMSRV	4
#define TDI_ST_TSRVOAM  5
#define TDI_ST_CSRVOAM  6
#define TDI_ST_SDBADMIN 7

#define CS_HOME_WORKTOP 1
#define CS_DEVICE_DEVICE 2
#define CS_DEVICE_CALL  3
#define CS_CALL_CALL    4
#define CS_CONTROL      5
#define CS_ROUTE        6

/* Driver Control Block Structure */
typedef struct {
    unsigned short              messageOffset;
    unsigned short              messageLength;
    unsigned short              privateOffset;
    unsigned short              privateLength;
    InvokeID_t                  invokeID;
    CSTAMonitorCrossRefID_t     monitorCrossRefID;
    SessionID_t              	sessionID;
    EventClass_t                messageClass;
    EventType_t                 messageType;
    short                       class_of_service;
} TDIDriverControlBlock_t;

#endif
