/***********************************************************/
/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/*
 *  sdb.h	SDB Events Defines
 *
 *  Header File Dependencies
 *   	sdbdefs.h, acs.h
 *
 */

#ifndef	SDB_H
#define	SDB_H

/* platform-dependent definitions */
#include "tsplatfm.h"

/* structure definitions for SDB messages */
#include "sdbdefs.h"


/***********************************************************
 * SDB event classes
 **********************************************************/
#define	SDBREQUEST			22
#define	SDBUNSOLICITED		23
#define	SDBCONFIRMATION		24     

typedef struct 
{
	InvokeID_t	invokeID;
	union 
	{
		SDBOpenConnConfEvent_t			openConn;
		SDBCloseConnConfEvent_t			closeConn;
		SDBInsertObjectConfEvent_t		insertObj;
		SDBInsertAttributeConfEvent_t	insertAttr;
		SDBDeleteObjectConfEvent_t		deleteObj;
		SDBDeleteAttributeConfEvent_t	deleteAttr;
		SDBSelectObjectConfEvent_t		selectObj;
		SDBOpenCursorConfEvent_t		openCursor;
		SDBFetchCursorConfEvent_t		fetchCursor;
		SDBCloseCursorConfEvent_t		closeCursor;
		SDBModifyObjectConfEvent_t		modifyObj;
		SDBStartTransConfEvent_t		startTrans;
		SDBCommitTransConfEvent_t		commitTrans;
		SDBRollbackTransConfEvent_t		rollbackTrans;
		SDBBackupDataBaseConfEvent_t	backupDatabase;
		SDBUpdateDataBaseConfEvent_t	updateDatabase;
		SDBCreateTemplateConfEvent_t	createTemplate;
		SDBQueryVersionsConfEvent_t		queryVers;
		SDBQueryFilesConfEvent_t		queryFiles;
		SDBQueryAttributesConfEvent_t	queryAttr;
		SDBSelectKeyConfEvent_t			selectKey;
		SDBBackupNdsDataBaseConfEvent_t	backupNdsDatabase;
		SDBUpdateNdsDataBaseConfEvent_t	updateNdsDatabase;
		SDBConvertDataBaseConfEvent_t	convertDatabase;
		SDBSetSdbLogOptionsConfEvent_t  setSdbLog;
		SDBGetSdbLogOptionsConfEvent_t  getSdbLog;
		SDBGetConnectionsConfEvent_t	getConns;
		SDBGetAboutConfEvent_t			getAbout;
		SDBGetAdminInfoConfEvent_t		getAdminInfo;
		SDBSetAdminInfoConfEvent_t		setAdminInfo;
		SDBGetTcpInfoConfEvent_t		getTcpInfo;
		SDBSetTcpInfoConfEvent_t		setTcpInfo;
		SDBUniversalFailureConfEvent_t	univFailure;
		
	} u;

} SDBConfirmationEvent;


#define SDB_MAX_HEAP	1024

typedef struct 
{
	ACSEventHeader_t	eventHeader;
	union 
	{
		ACSUnsolicitedEvent		acsUnsolicited;
		ACSConfirmationEvent	acsConfirmation;
		SDBConfirmationEvent	sdbConfirmation;
	} event;
	char	heap[SDB_MAX_HEAP];
} SDBEvent_t;
/***********************************************************
 * Successful return code
 **********************************************************/
#define SDB_SUCCESS			0


/***********************************************************
 * Supported databases
 **********************************************************/
#define VERSION_5_BTRV		"5.x"
#define	DATABASE_UNKNOWN	0
#define BTRV_VERS_5			1
#define BTRV_VERS_6			2
#define NDS_VERS_1			3

/***********************************************************
 * SDB Private Data for ACS Open Stream Conf
 **********************************************************/
#define VALIDATED_LOGIN		50
typedef struct TssdbPrivateData_t {
    char			vendor[32];
    unsigned short	length;
    char			data[VALIDATED_LOGIN];
} TssdbPrivateData_t;


/***********************************************************
 * SDB function prototypes
 **********************************************************/
#ifdef __cplusplus
extern "C"
{
#endif  


TSAPI
sdbOpenConnection ( ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBContext_t	FAR *context,
					SDBLoginName_t	FAR *login);

TSAPI
sdbCloseConnection (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID);

TSAPI
sdbInsertObject	   (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					struct SDBAttributeList_t	FAR *attrList);

TSAPI
sdbInsertAttribute (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					struct SDBAttributeList_t	FAR	*keyList,
					struct SDBAttributeList_t	FAR	*attrList);
TSAPI
sdbDeleteObject    (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID,
					SDBFileType_t		fileType,
					struct SDBAttributeList_t	FAR	*keyList);

TSAPI
sdbDeleteAttribute (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					struct SDBAttributeList_t		FAR	*keyList,
					struct SDBAttributeList_t	FAR	*attrList);

TSAPI
sdbSelectObject	   (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					SDBSelectOpcodes_t		opcode,
					struct SDBAttributeList_t		FAR	*keyList,
					struct SDBSelectAttrList_t		FAR *attrList,
					SDBReturnedCount_t		retrnCnt,
					SDBBufferSize_t			bufSize);

TSAPI
sdbOpenCursor      (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID);

TSAPI
sdbFetchCursor     (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID,     
					SDBReturnedCount_t	retrnCnt,
					SDBBufferSize_t		bufSize);

TSAPI
sdbCloseCursor     (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID);

TSAPI
sdbModifyObject    (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					struct SDBAttributeList_t	FAR	*keyList,
					struct SDBAttributeList_t	FAR	*attrList);

TSAPI
sdbStartTrans	   (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID);

TSAPI
sdbCommitTrans	   (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID);
					
TSAPI
sdbRollbackTrans   (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBConnectionID_t	connID);

TSAPI
sdbBackupDataBase  (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBFileName_t	FAR	*fileNm,
					SDBComments_t	FAR	*comments);

	
TSAPI
sdbUpdateDataBase  (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBFlatFileName_t	FAR	*flatFile,
					SDBSimpleFileName_t	FAR	*simpleFile,
					SDBErrorFileName_t	FAR	*errorFile,
					SDBOptions_t			options);

TSAPI
sdbCreateTemplate	(ACSHandle_t		acsHandle,
					InvokeID_t			invokeID,
					SDBFlatFileName_t	FAR	*flatFile,
					SDBSimpleFileName_t	FAR	*simpleFile);

TSAPI
sdbQueryVersions   (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);

TSAPI
sdbQueryFiles      (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBBufferSize_t		bufSize);


TSAPI
sdbQueryAttributes (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBFileType_t		fileType,
					SDBBufferSize_t		bufSize,
					SDBReturnedCount_t	retrnCnt);

TSAPI
sdbSelectKey	   (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBConnectionID_t		connID,
					SDBFileType_t			fileType,
					SDBAttributeID_t		key,
					SDBAttrHdr_t		FAR	*filter,
					SDBBufferSize_t			bufSize);
					
TSAPI
sdbBackupNdsDataBase  (ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBFileName_t	FAR	*fileNm,
					SDBComments_t	FAR	*comments,
					SDBContext_t	FAR *context);
	
TSAPI
sdbUpdateNdsDataBase  (ACSHandle_t				acsHandle,
					InvokeID_t				invokeID,
					SDBFlatFileName_t	FAR	*flatFile,
					SDBSimpleFileName_t	FAR	*simpleFile,
					SDBErrorFileName_t	FAR	*errorFile,
					SDBOptions_t			options,
					SDBContext_t		FAR *context); 
TSAPI
sdbConvertDataBase  (ACSHandle_t			acsHandle,
					InvokeID_t				invokeID,
					SDBFlatFileName_t	FAR	*flatFile,
					SDBFlatFileName_t	FAR	*finalFile,
					SDBErrorFileName_t	FAR	*errorFile,
					SDBConvertOptions_t		options,
					SDBContext_t		FAR *context); 
					
TSAPI					
sdbSetSdbLogOptions(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
    				Boolean         	logSdbChanges,
    				SDBLogPath_t FAR *	logPath,
    				long            	sdbLogSize);
TSAPI					
sdbGetSdbLogOptions(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);
					
TSAPI					
sdbGetConnections(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);
					
TSAPI					
sdbGetAboutInfo(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);										

TSAPI					
sdbGetAdminInfo(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);

TSAPI					
sdbSetAdminInfo(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					Boolean				workStation,
					Boolean				autoAdmin);
					
TSAPI					
sdbGetTcpInfo(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID);

TSAPI					
sdbSetTcpInfo(ACSHandle_t			acsHandle,
					InvokeID_t			invokeID,
					SDBIPNameFormat_t	tcpNameFormat);
					
					

#ifdef __cplusplus
}
#endif  

#endif

