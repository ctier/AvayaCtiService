// Tsapi.cpp : interface to TSAPI Tserver.
//
// This file handles the hidden TSAPI window
//

#include "stdafx.h"
#include "windowsx.h"
#include "Tsapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// First, there are the CTsapiDevice methods.
// 
// This class is referenced by the TSAPI window class (CTsapiWnd).
// It handles:
//	1. tracking of the window that handles the TSAPI events for each device known
//		by the CTsapiWnd
//	3. tracking of the monitor cross reference ID for the current monitoring session
//		for each device known by the CTsapiWnd
//	2. tracking of all of the calls and connections for each device known by the
//		CTsapiWnd
//
// Note that this sample only implements 1 device tracking. The CTsapiWnd here can
//  only track a single device and this memory is hard-coded.
// Note that this sample hard-codes the number of calls and connections that the
//  device can support.

CTsapiDevice::CTsapiDevice()
{
	m_DeviceID[0] = '\0';
	m_MonitorCrossRefID = 0;
	m_pWnd = 0;
	for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
	{
		// an empty call ID indicates a free entry
		for(int j=0; j<MAX_DEVICES_IN_CALL; j++)
		{
			m_ConnIDList[i][j].callID = 0;
		} 
	}
}

// This method takes a connection ID and creates a call entry to track this
//  call. Note that the connection ID is assumed to be a Local connection ID.
//  This means that it is a connection ID that includes the device that is
//  stored in this record. It doesn't check to make sure this is true. It can't
//	check, because the connection ID may contain a dynamic device ID, which wouldn't
//  match the static device ID stored in this record.
// This method returns a "call handle" - this should be used in subsequent methods
//  to refer to the particular call created here. Callers of this method should NEVER
//  modify the call handle returned by this method.
long CTsapiDevice::CreateCallFromLocalConnection(ConnectionID_t & connID)
{
	// This could be replaced with dynamic memory allocation, but static memory
	//  makes the sample easier.
	for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
	{
		// Local connection info always goes into slot 0 for the call.
		// Slot 0 always has full connection IDs, so the device ID does not
		//  need to be checked.
		// An empty call ID indicates a free entry
		if(m_ConnIDList[i][0].callID == 0)
		{
			// place the new connection info into the call record
			m_ConnIDList[i][0].callID = connID.callID; 
			lstrcpy(m_ConnIDList[i][0].deviceID, connID.deviceID);
			m_ConnIDList[i][0].devIDType = connID.devIDType;
			return (long)(&(m_ConnIDList[i][0]));
		}
	}

	return 0;
}

// This method takes a connection ID, finds the call that it is in and
//  removes it from the device record. It returns the call handle that was
//  associated with that call, but that call handle no longer refers to an
//  active call.
long CTsapiDevice::RemoveCallViaConnection(ConnectionID_t & connID)
{
	// This could be replaced with dynamic memory deallocation, but static memory
	//  makes the sample easier.

	for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
	{
		for(int j=0; j<MAX_DEVICES_IN_CALL; j++)
		{
			if((m_ConnIDList[i][j].callID == connID.callID)	&&
				(lstrcmp(m_ConnIDList[i][j].deviceID, connID.deviceID) == 0) &&
				(m_ConnIDList[i][j].devIDType == connID.devIDType))
			{
				// connection found - go back to first connection in call and
				//  free all of the connections.
				for(int k=0; k<MAX_DEVICES_IN_CALL; k++)
				{
					// an empty call ID indicates a free entry
					m_ConnIDList[i][k].callID = 0;
				} 
				return (long)(&(m_ConnIDList[i][0]));
			}
		}
	}

	return 0;
}

// This method takes a call handle and a connection ID and associates the connection ID
//	with that call handle. Subsequent requests for a call handle based on this connection ID
//  can now be satisfied.
// This method returns TRUE if the connection is successfully added to the call, otherwise
//  it returns FALSE.  
BOOL CTsapiDevice::AddConnectionToCall(long callHandle, ConnectionID_t & connID)
{
	ConnectionID_t* pConnIDList = (ConnectionID_t*)callHandle;

	// Do some validation of the handle - not perfect, but we won't crash!
	if((pConnIDList < &m_ConnIDList[0][0]) ||
		(pConnIDList > &m_ConnIDList[MAX_CALLS_AT_DEVICE][0]) ||
		(pConnIDList->callID == 0))
	{
		return FALSE;
	}

	// skip the 0 entry	- this is strictly for the local connection ID and 
	//  should be added with CreateCallFromLocalConnection()
	pConnIDList++;

	// attempt to place connection in call 
	for(int j=1; j<MAX_DEVICES_IN_CALL; j++, pConnIDList++)
	{
		// an empty call ID indicates a free entry
		if(pConnIDList->callID == 0)
		{
			// place the new connection info into the call record
			pConnIDList->callID = connID.callID; 
			lstrcpy(pConnIDList->deviceID, connID.deviceID);
			pConnIDList->devIDType = connID.devIDType;
			return TRUE;
		}
	}

	return FALSE;
}

// This method takes a connection ID, finds the call that it is in and
//  removes that connection ID from the call. It returns the call handle that is
//  associated with that call.
long CTsapiDevice::RemoveConnectionFromCall(ConnectionID_t & connID)
{
	for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
	{
		for(int j=0; j<MAX_DEVICES_IN_CALL; j++)
		{
			if((m_ConnIDList[i][j].callID == connID.callID)	&&
				(lstrcmp(m_ConnIDList[i][j].deviceID, connID.deviceID) == 0) &&
				(m_ConnIDList[i][j].devIDType == connID.devIDType))
			{
				// connection found
				// an empty call ID indicates a free entry
				m_ConnIDList[i][j].callID = 0; 
				return (long)(&(m_ConnIDList[i][0]));
			}
		}
	}

	return 0;
}

// This method takes a call handle and returns the associated local connection ID.
// If the local connection ID is returned, the return value is TRUE, else it is
// FALSE and the connID argument should not be referenced.
BOOL CTsapiDevice::GetLocalConnection(long connHandle, ConnectionID_t & connID)
{
	ConnectionID_t* pConnIDList = (ConnectionID_t*)connHandle;

	// Do some validation of the handle - not perfect, but we won't crash!
	if((pConnIDList < &m_ConnIDList[0][0]) ||
		(pConnIDList > &m_ConnIDList[MAX_CALLS_AT_DEVICE][0]) ||
		(pConnIDList->callID == 0))
	{
		return FALSE;
	}

	// return connection info
	connID.callID = pConnIDList->callID; 
	lstrcpy(connID.deviceID, pConnIDList->deviceID);
	connID.devIDType = pConnIDList->devIDType;

	return TRUE;
}

// This method takes a call handle and connection ID and determines if the connection ID
//  is the local connection ID or not.
// If it is, the return value is TRUE, else it is FALSE.
// An invalid call handle also returns FALSE.
BOOL CTsapiDevice::IsLocalConnection(long connHandle, ConnectionID_t & connID)
{
	ConnectionID_t* pConnIDList = (ConnectionID_t*)connHandle;

	// Do some validation of the handle - not perfect, but we won't crash!
	if((pConnIDList < &m_ConnIDList[0][0]) ||
		(pConnIDList > &m_ConnIDList[MAX_CALLS_AT_DEVICE][0]) ||
		(pConnIDList->callID == 0))
	{
		return FALSE;
	}

	if((pConnIDList->callID == connID.callID)	&&
		(lstrcmp(pConnIDList->deviceID, connID.deviceID) == 0) &&
		(pConnIDList->devIDType == connID.devIDType))
	{
		return TRUE;
	}

	return FALSE;
}

// This method takes a connection ID and returns the call handle for the call that
//  it is in.
// IF exactMatch is TRUE, the full connection ID is used to find the call.
// IF exactMatch is FALSE, only the call ID member of the connection ID is used to
//  find the call. 
// Should use the exactMatch = TRUE case whenever possbile. The non-exactMatch
//  case assumes that the call ID is the same for all connections in the call. This
//  is not always safe to do (as not all PBX Drivers guarantee this), but is
//	sometimes necessary.
long CTsapiDevice::GetCallHandle(ConnectionID_t & connID, BOOL exactMatch)
{
	if(exactMatch)
	{
		for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
		{
			for(int j=0; j<MAX_DEVICES_IN_CALL; j++)
			{
				if((m_ConnIDList[i][j].callID == connID.callID)	&&
					(lstrcmp(m_ConnIDList[i][j].deviceID, connID.deviceID) == 0) &&
					(m_ConnIDList[i][j].devIDType == connID.devIDType))
				{
					return (long)(&(m_ConnIDList[i][0]));
				}
			}
		}
	}
	else
	{
		for(int i=0; i<MAX_CALLS_AT_DEVICE; i++)
		{
			if(m_ConnIDList[i][0].callID == connID.callID)
			{
				return (long)(&(m_ConnIDList[i][0]));
			}
		}
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTsapiWnd object

CTsapiWnd theTsapiWnd;

// For non-MFC folks, this map replaces the large "switch" statement found in
//  straight C Windows programs. The ON_MESSAGE() line can be read as
//  "when a message of type {first argument} is recieved, call
//   the method {second argument}"
BEGIN_MESSAGE_MAP(CTsapiWnd, CWnd)
	ON_MESSAGE(WM_TSAPIMSG, OnTsapiMsg)
END_MESSAGE_MAP()

CTsapiWnd::CTsapiWnd()
{
	m_AcsHandle = 0;
	m_EventBufPtr = (CSTAEvent_t*)&m_EventBuf;
	m_EventBufSize = sizeof(CSTAEvent_t);
}

CTsapiWnd::~CTsapiWnd()
{
	// free any allocated memory            
	if(m_EventBufPtr != (CSTAEvent_t*)&m_EventBuf)
	{ 
		GlobalFreePtr(m_EventBufPtr);   
	}
	// terminate the stream connection
	if(m_AcsHandle)
	{
		acsAbortStream(m_AcsHandle, 0);
	}
}

// public interface to the private CreateEx() method
void CTsapiWnd::DoCreate()
{
	CreateEx(0, AfxRegisterWndClass(CS_GLOBALCLASS), "", 0, 0, 0, 0, 0, 0, 0);
}

// This method is called when a TSAPI message (WM_TSAPIMSG) is received.
// The WM_TSAPIMSG is just a notification that there is a message waiting in the
//  CSTA DLL. Use acsGetEventPoll() to retrieve the actual message.
//
// If the static buffer is too small for the message, dynamically allocate a buffer
//  that is big enough. Debug tracing should be used to fine tune the size of the
//  static buffer such that a dynamic buffer doesn't need to be created every time.
// The event is then forwarded to the appropriate window.
// If there are more events waiting (numEvents > 0), then post ourselves another
//  WM_TSAPIMSG.  This is done instead of a while(numEvents >0) loop to allow for
//  processing of other windows events and to allow for the TSAPI event to process-to-
//  completion
LRESULT CTsapiWnd::OnTsapiMsg(WPARAM wParam, LPARAM lParam)
{
	RetCode_t rc;
	unsigned short numEvents;

	// free any previously allocated memory before continuing            
	if(m_EventBufPtr && (m_EventBufPtr != (CSTAEvent_t*)&m_EventBuf))
	{ 
		GlobalFreePtr(m_EventBufPtr);
		m_EventBufPtr = 0;   
	}

	// attempt to retrieve the event from the CSTA DLL	
	m_EventBufSize = sizeof(m_EventBuf);
	rc = acsGetEventPoll(m_AcsHandle, &m_EventBuf, &m_EventBufSize, 0, &numEvents);
	if(rc != 0)
	{
		// check if rc indicates no messages to get - that is ok
		if(rc == ACSERR_NOMESSAGE)
		{
			return 0;
		}
		else if(rc == ACSERR_UBUFSMALL)	// static buffer too small - allocate larger one
		{ 
			// space required is in the return parameter
		    m_EventBufPtr = (CSTAEvent_t*)GlobalAllocPtr(GHND, m_EventBufSize);
			if(!m_EventBufPtr)
			{
				m_TsapiController->PostMessage(WM_TSAPIFAILURE, rc, 0);
				return (LRESULT)rc;
			}

			// try to get the event out of the queue again, into the newly allocated memory                     
			rc = acsGetEventPoll(m_AcsHandle, m_EventBufPtr, &m_EventBufSize, 0, &numEvents);
			if(rc != 0)
			{
				// not you can do here...
				// free the allocated memory
				GlobalFreePtr(m_EventBufPtr);
				m_EventBufPtr = 0;   
				m_TsapiController->PostMessage(WM_TSAPIFAILURE, rc, 0);
				return (LRESULT)rc;
			}                                       
		}
		else 
		{
			// not much you can do here...
			m_TsapiController->PostMessage(WM_TSAPIFAILURE, rc, 0);
			return (LRESULT)rc;
		}
	}
	else
	{
		m_EventBufPtr = (CSTAEvent_t*)&m_EventBuf;
	}

	// handle each class of events slightly differently		
	switch(m_EventBufPtr->eventHeader.eventClass)
	{
	 case ACSUNSOLICITED:
		// ACS Unsolicited events are all handled by the TSAPI controller - the
		//  window that wants to be responsible for memory clean-up and stream failure
		//  handling. Forward all of these events to the controller.

		// this is a sendmessage(), not a postmessage() because the operation has to
		//  process to completion - or at least until the event buffer is not needed
		m_TsapiController->SendMessage(WM_TSAPIACSUNSOLICITED, 0, 0);
		break;
	 case ACSCONFIRMATION:
	 {
		// ACS Confirmation events are all handled by the window that is passed in via
		//  the invoke ID. Forward all of these events to that window.

		// get CWnd pointer out of invokeID, send message
		CWnd* pWnd = (CWnd*)m_EventBufPtr->event.acsConfirmation.invokeID;
		// make sure the window is still there
		if(::IsWindow(pWnd->m_hWnd))
		{
			// this is a sendmessage(), not a postmessage() because the operation has to
			//  process to completion - or at least until the event buffer is not needed
			pWnd->SendMessage(WM_TSAPIACSCONFIRMATION, 0, 0);
		}
		break;
	 }
	 case CSTACONFIRMATION:
	 {
		// CSTA Confirmation events are all handled by the window that is associated with
		//  the device whose device record is passed in via the invoke ID. Forward all of
		//  these events to that window.

		// get CTsapiDevice pointer and CWnd pointer out of invokeID, send message
		CTsapiDevice* pTsapi = (CTsapiDevice*)m_EventBufPtr->event.acsConfirmation.invokeID;
		// get the CWnd pointer out of CTsapiDevice and make sure the window is still there
		if(::IsWindow(pTsapi->GetWndPtr()->m_hWnd))
		{
			// this is a sendmessage(), not a postmessage() because the operation has to
			//  process to completion - or at least until the event buffer is not needed
			pTsapi->GetWndPtr()->SendMessage(WM_TSAPICSTACONFIRMATION, 0, (LPARAM)pTsapi);
		}
		break;
	 }
	 case CSTAUNSOLICITED:
	 {
		// CSTA Unsolicited events are all handled by the window that is associated with
		//  the device whose monitor cross reference ID matches the one received in this
		//  event. Forward all of these events to that window.

		// get CTsapiDevice pointer by looking for a matching monitor cross reference ID
		CTsapiDevice* pTsapi = GetDeviceRecord(m_EventBufPtr->event.cstaUnsolicited.monitorCrossRefId);
		// get the CWnd pointer out of CTsapiDevice and make sure the window is still there
		if(pTsapi && pTsapi->GetWndPtr() && ::IsWindow(pTsapi->GetWndPtr()->m_hWnd))
		{
			// this is a sendmessage(), not a postmessage() because the operation has to
			//  process to completion - or at least until the event buffer is not needed
			pTsapi->GetWndPtr()->SendMessage(WM_TSAPICSTAUNSOLICITED, 0, (LPARAM)pTsapi);
		}
		break;
	 }
	 default:
		break;
	}

	// If there are additional TSAPI events to process, post ourselves another message.
	if(numEvents > 0)
	{
		PostMessage(WM_TSAPIMSG, 0, 0);
	}                              

	return 0;
}

// this method creates a device record for the given device ID and returns a pointer
//  to that device record. It should return NULL if it couldn't create the device
//  record (can't happen here).
CTsapiDevice* CTsapiWnd::CreateDeviceRecord(DeviceID_t deviceId)
{
	// if more than 1 device were allowed, then dynamic allocation
	//  could happen here

	// now place the new device info into the device record
	//m_MyOneDevice.SetDeviceID(deviceId);
	DeviceID_t myDevID;
	for (int i = 0; i < MAX_DEVICES; i++) {		
		m_MyDevices[i].GetDeviceID(myDevID);
		if (myDevID == '\0') {
			m_MyDevices[i].SetDeviceID(deviceId);
			return &m_MyDevices[i];
		}
	}
	return NULL;
}

// this method returns a pointer to the given device's device record or NULL if
//  a record is not found. 
CTsapiDevice* CTsapiWnd::GetDeviceRecord(DeviceID_t deviceID)
{
	// if more than 1 device were allowed, then all of the device structures
	//  would be searched for the deviceID specified
	DeviceID_t myDevID;
	//m_MyOneDevice.GetDeviceID(myDevID);
	for (int i = 0; i < MAX_DEVICES; i++) {
		m_MyDevices[i].GetDeviceID(myDevID);
		if (lstrcmp(myDevID, deviceID) == 0)
		{
			return &m_MyDevices[i];
		}
	}
	

	return NULL;
}

// this method returns a pointer to the device record associated with the given
//  cross reference ID or NULL if a record is not found.
CTsapiDevice* CTsapiWnd::GetDeviceRecord(CSTAMonitorCrossRefID_t monitorCrossRefID)
{
	// if more than 1 device were allowed, then all of the device structures
	//  would be searched for the cross ref ID specified

	for (int i = 0; i < MAX_DEVICES; i++) {
		if (m_MyDevices[i].GetCrossRefID() == monitorCrossRefID)
		{
			return &m_MyDevices[i];
		}
	}

	return NULL;
}
