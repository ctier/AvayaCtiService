
/***********************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/*
 *  tdrvr.h    TSERVER Driver Events Defines
 *
 *  Header File Dependencies
 *   	drvrdefs.h
 *
 */

#ifndef _TDRVR_H_
#define _TDRVR_H_

/* platform-dependent definitions */
#include "tsplatfm.h"

/* structure definitions for driver OAM messages */
#include "drvrdefs.h"

#define	TDRVRREQUEST		7
#define	TDRVRUNSOLICITED	8
#define	TDRVRCONFIRMATION	9

typedef struct 
{
	union 
	{
		TSRVDriverOAMEvent_t		driverEvent;
	} u;
} TSRVDriverUnsolicitedEvent;

typedef struct 
{
	InvokeID_t	invokeID;
	union 
	{
		TSRVDriverOAMConfEvent_t	driverConf;
	} u;
} TSRVDriverConfirmationEvent;


#define TSRV_DRIVER_HEAP	1024

typedef struct 
{
	ACSEventHeader_t	eventHeader;
	union 
	{
		ACSUnsolicitedEvent			acsUnsolicited;
		ACSConfirmationEvent		acsConfirmation;
		TSRVDriverUnsolicitedEvent	driverUnsolicited;
		TSRVDriverConfirmationEvent	driverConfirmation;
	} event;
	char	heap[TSRV_DRIVER_HEAP];
	  
} TSRVDriverEvent_t;


/* function prototypes */

#ifdef __cplusplus
extern "C"
{
#endif  

TSAPI
tsrvDriverRequest (	ACSHandle_t						acsHandle,
					InvokeID_t						invokeID,
				    CONST_PARAM unsigned char FAR *	data,
				    _Int							length);

#ifdef __cplusplus
}
#endif  


#endif
