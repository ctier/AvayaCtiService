/************************************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved. */
/************************************************************************/
/*
 *  cdi.h    CSTA Services Driver Interface
 *
 *  Header File Dependencies:
 *      acs.h
 *      csta.h
 *	tdi.h
 */

#ifndef CDI__H
#define CDI__H

#if !defined(_CDILIB_)
#define CDILIBAPI __declspec(dllimport)
#else
#define CDILIBAPI __declspec(dllexport)
#endif

/*
 * DEFINES
 */

#define CDI_CSDI_VERSION_1	1	/* CSDI interface version */

#define CDI_PROTOCOL_VERSION_1	1	/* CSTA Protocol Version */

#define CDI_SUCCESS             1	/* CDI Function call completed OK */

#define CDI_MAX_SERVICE_NAME    TDI_MAX_SERVICE_NAME
					/* Max length of the service name */
#define CDI_MAX_DRIVER_NAME     TDI_MAX_DRIVER_NAME
					/* Max length of the driver name  */
#define CDI_MAX_VENDOR_NAME     TDI_MAX_VENDOR_NAME
					/* Max length of the vendor name  */
#define CDI_MAX_PRIV_DATA_VENDOR 32	/* Max length of the priv data vendor */
#define CDI_MAX_VERSION_STRING	TDI_MAX_VERSION_STRING
					/* Max length of version string */

#define CDI_MAX_REGISTRATIONS   TDI_MAX_REGISTRATIONS
					/* Max driver registerations per
					 * Cserver */
#define CDI_MAX_BUFFER_SIZE     (4096-12) /* Max size of buffers sent across
					   * the CDI (Netware 3.x only) */

/*
 * CDI Default buffer descriptor values
 */
#define CDI_MAX_BYTES_ALLOCATED TDI_MAX_BYTES_ALLOCATED
					 /* Default max bytes allocated per
					  * driver: 1.5 meg  */
#define CDI_MIN_BYTES_ALLOCATED TDI_MIN_BYTES_ALLOCATED
					 /* Default min bytes allocated per
					  * driver: 64K  */
#define CDI_BUFFER_HI_WATER_MARK (CDI_MAX_BYTES_ALLOCATED * 80 / 100)
					/* Default high water mark for
					 * allocated buffers */
#define CDI_BUFFER_LO_WATER_MARK (CDI_MAX_BYTES_ALLOCATED * 40 / 100)
					/* Default high water mark for
					 * allocated buffers */

/*
 * CDI Buffer allocation condition flags
 */
#define CDI_EXCEED_MAX_BYTES    0x01    /* Buffers allocated exceed max bytes
					 * allowed */ 
#define CDI_EXCEED_HIWATER_MARK 0x02    /* Buffers allocated exceed high water
					 * mark */
#define CDI_EXCEED_LOWATER_MARK 0x04    /* Buffers allocated exceed low water
					 * mark */

/*
 * CDI Security Checks per client request 
 */
#define CDI_CSTA_SECURITY       TDI_CSTA_SECURITY
					/* Security check per client req. */
#define CDI_LOGIN_SECURITY      TDI_LOGIN_SECURITY
					/* Security check on login */
#define CDI_NO_SECURITY         TDI_NO_SECURITY
					/* No security checks */

/*
 * CDI Defines for significant_octets field of CDIOctetStringMap_t
 */
#define CDI_FIRST_FOUR		0	/* first four octets are used */
#define CDI_LAST_FOUR		1	/* last four octets are used */

/*
 * CDI Defines for byte_order field of CDIOctetStringMap_t
 */
#define CDI_MSB_FIRST		0	/* most significant byte first order */
#define CDI_LSB_FIRST		1	/* least significant byte first order */

/*
 * CDI Message priority class
 */
#define CDI_NORMAL_MESSAGE      0	/* Send message normal class */
#define CDI_PRIORITY_MESSAGE    1	/* Send message priority class */

/*
 * CDI Error return codes
 */
#define CDI_ERR_ESYS            -1      /* System Error occurred */
#define CDI_ERR_BAD_DRVRID      -2      /* Unregistered driverID */
#define CDI_ERR_DUP_DRVR        -3      /* Service name already registered */
#define CDI_ERR_NO_MEM          -4      /* Unable to allocate memory */
#define CDI_ERR_MAX_DRVR        -5      /* Max  number of drivers exceeded */
#define CDI_ERR_EINVAL          -6      /* Invalid parameter to CDI call */
#define CDI_ERR_NO_BUFFERS      -7      /* No  buffers available to allocate */
#define CDI_ERR_BADLENGTH       -8      /* Requested length > max buf size */
#define CDI_ERR_BAD_BUF         -9      /* Buffer supplied is invalid */
#define	CDI_ERR_NOT_YOUR_BUFFER	-10	/* trying to free someone else's buf */
#define CDI_ERR_DRVR_UNREGISTERED -11   /* The Driver unregistered */
#define CDI_ERR_BAD_VERSION	-12   	/* Bad csdi version to registration */
#define CDI_ERR_BAD_SECURITY 	-13   	/* Bad drvr security to registration */
#define CDI_ERR_BAD_SRVC_NAME 	-14   	/* Bad service name to registration */
#define CDI_ERR_BAD_VENDOR_NAME	-15   	/* Bad vendor name to registration */
#define CDI_ERR_BAD_DRVR_NAME 	-16   	/* Bad driver name to registration */
#define CDI_ERR_BAD_SESSIONID 	-17   	/* Bad session ID */
#define CDI_ERR_BAD_INVOKEID 	-18   	/* Bad invoke ID */
#define CDI_ERR_BAD_SEM 	-19   	/* Bad semaphore from on WaitLocal*/
#define CDI_ERR_BAD_PROTOCOL	-20	/* Bad protocol vers to registration */
#define CDI_ERR_BAD_PRIVDATA_VNDR -21	/* Bad priv data vndr to registration */
#define CDI_ERR_BAD_MAPPING_DESC -22	/* Bad mapping descriptor */
#define CDI_ERR_BAD_DRVR_CAPS	-23	/* Bad driver caps */

/*
 * TYPEDEFS
 */

typedef int		CDIHandle_t;	/* Identifies Cserver-Driver intf. */
typedef int		CDIReturn_t;	/* Return type for CDI functions */
typedef int		CDISecurity_t;	/* Security requested/client req. */
typedef int		CDIBuf_flag_t;	/* Current buffer allocation info */
typedef int		CDIPriority_t;	/* Message priority */
typedef unsigned long	CDIVersion_t;	/* Identifies CSDI version */
typedef unsigned long	CDIProtocol_t;	/* Identifies protocol version */

typedef struct
{
	unsigned char	significant_octets;	/* CDI_FIRST_FOUR or
						 * CDI_LAST_FOUR	*/
	unsigned char	byte_order;		/* CDI_MSB_FIRST or
						 * CDI_LSB_FIRST	*/
	unsigned char	min_length;		/* minimum length octet string
						 * encoding (1-4)	*/
	unsigned char	max_length;		/* maximum length octet string
						 * encoding (1-4)	*/
	Boolean		strip_null;		/* strip null bytes flag */
} CDIOctetStringMap_t;

typedef struct
{
	CDIOctetStringMap_t	callID_map;	/* Mapping of callID's
						 * on this interface. */
	CDIOctetStringMap_t	monitorCrossRefID_map;	/* Mapping of
						 * monitorCrossRefId's
						 * on this interface. */
	CDIOctetStringMap_t	routingCrossRefID_map;	/* Mapping of
						 * routingCrossRefId's
						 * on this interface. */
} CDIMapping_info_t;

typedef struct
{
	unsigned long   max_bytes;	/* Maximum number of bytes to allocate
					 * for this interface */
	unsigned long   hiwater_mark;	/* High water mark for buffer
					 * allocation on this interface */
	unsigned long   lowater_mark;	/* Low water mark for buffer
					 * allocation on this interface */
} CDIBuf_info_t;

typedef struct
{
	int	queued_to_driver;	/* Number of bufs queued to driver */
	int	queued_to_csta;		/* Number of bufs queued to cserver */
	int	allocd_by_driver;	/* Number of bufs alloc'd to driver */
	int	allocd_by_csta;		/* Number of bufs alloc'd to cserver */
} CDIQueue_info_t;

typedef struct
{
	unsigned long   bytes_queued_to_driver; /* Number of bytes in message
						 * buffers queued to driver */
	unsigned long   bytes_queued_to_csta;   /* Number of bytes in message
						 * buffers queued to cserver */
	unsigned long   bytes_allocd_by_driver; /* Number of bytes in message
						 * buffers allocated to driver*/
	unsigned long   bytes_allocd_by_csta;   /* Number of bytes in message
						 * buffers alloc'd to cserver */
} CDIMemAlloc_info_t;

typedef struct
{
	short    alternateCall;
	short    answerCall;
	short    callCompletion;
	short    clearCall;
	short    clearConnection;
	short    conferenceCall;
	short    consultationCall;
	struct {
		short	deflect;
		short	pickup;
		short	group;
	} divertCall;
	short    holdCall;
	short    makeCall;
	short    makePredictiveCall;
	struct {
		short	msgWaiting;
		short	doNotDisturb;
		short	forward;
		short	lastDialedNumber;
		short	deviceInfo;
		short	agentState;
	} queryDevice;
	short    reconnectCall;
	short    retrieveCall;
	struct {
		short	msgWaiting;
		short	doNotDisturb;
		short	forward;
		short	agentState;
	} setFeature;
	short    transferCall;
	short    eventReport;
	short    callClearedEvent;
	short    conferencedEvent;
	short    connectionClearedEvent;
	short    deliveredEvent;
	short    divertedEvent;
	short    establishedEvent;
	short    failedEvent;
	short    heldEvent;
	short    networkReachedEvent;
	short    originatedEvent;
	short    queuedEvent;
	short    retrievedEvent;
	short    serviceInitiatedEvent;
	short    transferredEvent;
	short    callInformationEvent;
	short    doNotDisturbEvent;
	short    forwardingEvent;
	short    messageWaitingEvent;
	short    loggedOnEvent;
	short    loggedOffEvent;
	short    notReadyEvent;
	short    readyEvent;
	short    workNotReadyEvent;
	short    workReadyEvent;
	short    backInServiceEvent;
	short    outOfServiceEvent;
	struct {
		short	driverInvoked;
		short	applInvoked;
	} privateEvent;
	short    routeRequest;
	short    reRouteRequest;
	short    routeSelectRequest;
	short    routeUsedRequest;
	struct {
		short	driverInvoked;
		short	applInvoked;
	} routeEndRequest;
	struct {
		short	driverInvoked;
		short	applInvoked;
	} escapeService;
	struct {
		short	driverInvoked;
		short	applInvoked;
	} systemStatus;
	struct {
		short	device;
		short	call;
		short	callsViaDevice;
	} monitorStart;
	short    changeMonitorFilter;
	struct {
		short	driverInvoked;
		short	applInvoked;
	} monitorStop;
	short    snapshotDevice;
	short    snapshotCall;
} CDIDriverCaps_t;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * FUNCTION PROTOTYPES
 */

CDILIBAPI	CDIHandle_t cdiDriverRegister(
CDIVersion_t			csdi_version,		/* INPUT  */
CDIProtocol_t			protocol_version,	/* INPUT  */
const char			*vendor_name,		/* INPUT  */
const char			*driver_name,		/* INPUT  */
const char			*service_name,		/* INPUT  */
CDISecurity_t			driver_security,	/* INPUT  */
const CDIBuf_info_t		*buffer_descriptor,	/* INPUT  */
const CDIMapping_info_t		*mapping_descriptor,	/* INPUT  */
const char			*priv_data_vendor,	/* INPUT  */
const CDIDriverCaps_t		*driver_caps);		/* INPUT  */

CDILIBAPI	CDIReturn_t cdiDriverUnregister(
CDIHandle_t			driverID);		/* INPUT */

CDILIBAPI	CDIReturn_t cdiAllocBuffer(
CDIHandle_t			driverID,		/* INPUT  */
char				**bufptr,		/* OUTPUT */
unsigned int			length,			/* INPUT  */
CDIBuf_flag_t			*buf_flag);		/* OUTPUT */

CDILIBAPI	CDIReturn_t cdiFreeBuffer(
CDIHandle_t			driverID,		/* INPUT   */
char				*bufptr);		/* INPUT   */

CDILIBAPI	CDIReturn_t cdiReceiveFromCSTA(
CDIHandle_t			driverID,		/* INPUT  */
char				**bufptr);		/* OUTPUT */

CDILIBAPI	CDIReturn_t cdiSendToCSTA(
CDIHandle_t			driverID,		/* INPUT  */
char				*bufptr,		/* INPUT  */
CDIPriority_t			priority);		/* INPUT  */

CDILIBAPI	CDIReturn_t cdiQueueSize(
CDIHandle_t			driverID,		/* INPUT  */
CDIQueue_info_t			*queue_descriptor);	/* OUTPUT */

CDILIBAPI	CDIReturn_t cdiGetCDISize(
CDIHandle_t			driverID,		/* INPUT  */
CDIBuf_info_t			*buffer_descriptor);	/* OUTPUT  */

CDILIBAPI	CDIReturn_t cdiMemAllocSize(
CDIHandle_t			driverID,		/* INPUT  */
CDIMemAlloc_info_t		*mem_descriptor);	/* OUTPUT */

CDILIBAPI	CDIReturn_t cdiDriverSanity(
CDIHandle_t			driverID);		/* INPUT  */

CDILIBAPI	CDIReturn_t cdiGetCSTAVersion(
char				*customer_version,	/* OUTPUT */
char				*internal_version,	/* OUTPUT */
CDIVersion_t			*csdi_version,		/* OUTPUT */
CDIProtocol_t			*protocol_version);	/* OUTPUT */


#ifdef __cplusplus
}
#endif

#endif
