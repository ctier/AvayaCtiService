// Tsapi.h : TSAPI header file
//

#ifndef	TSAPI_H_INCLUDE_GUARD
#define	TSAPI_H_INCLUDE_GUARD

#include "acs.h"
#include "csta.h"
#include "attpriv.h"
/////////////////////////////////////////////////////////////////////////////
// See Tsapi.cpp for the implementation of this class
//

// user-specific windows messages
#define WM_TSAPIMSG					WM_USER+2130
#define WM_TSAPIFAILURE				WM_USER+2131
#define WM_TSAPIACSUNSOLICITED		WM_USER+2132
#define WM_TSAPIACSCONFIRMATION		WM_USER+2133
#define WM_TSAPICSTAUNSOLICITED		WM_USER+2134
#define WM_TSAPICSTACONFIRMATION	WM_USER+2135

// this app will handle 1 2-party call at 1 device
#define MAX_CALLS_AT_DEVICE 10
#define MAX_DEVICES_IN_CALL 6

#define MAX_DEVICES 100
// this class is the device record. For each device the app supports, there will
//  be one instance of this class.
class CTsapiDevice
{
public:
	CTsapiDevice();
	// sets the device ID for this device record
	void SetDeviceID(DeviceID_t deviceID) { lstrcpy(m_DeviceID,deviceID); };
	// returns the device ID from this device record
	void GetDeviceID(DeviceID_t deviceID) { lstrcpy(deviceID, m_DeviceID); };
	// sets the calleddevice ID for this device record
	void SetCalledDeviceID(DeviceID_t deviceID) { lstrcpy(m_CalledDeviceID, deviceID); };
	// returns the calleddevice ID from this device record
	void GetCalledDeviceID(DeviceID_t deviceID) { lstrcpy(deviceID, m_CalledDeviceID); };

	// sets the window that is responsible for handling TSAPI events for this device
	void SetWndPtr(CWnd* pWnd) { m_pWnd = pWnd; };
	// returns the window that is responsigle for handling TSAPI events	for this device
	CWnd* GetWndPtr() { return m_pWnd; };
	// set the cross reference ID for the current monitoring session for this device
	void SetCrossRefID(CSTAMonitorCrossRefID_t monitorCrossRefID) { m_MonitorCrossRefID = monitorCrossRefID; };
	// returns the current cross reference ID
	CSTAMonitorCrossRefID_t GetMonitorCrossRefID() { return m_MonitorCrossRefID; };
	//get set agentID
	void SetAgentID(CString agentID) { m_AgentID = agentID; };
	CString GetAgentID() { return m_AgentID; };
	//get set agentState
	void SetAgentState(AgentState_t agentState) { m_AgentState = agentState; };
	AgentState_t GetAgentState() { return m_AgentState; };
	//get set Command
	void SetCommand(CString command) { m_Command = command; };
	CString GetCommand() { return m_Command; };

	CSTAMonitorCrossRefID_t GetCrossRefID() { return m_MonitorCrossRefID; };
	long CreateCallFromLocalConnection(ConnectionID_t & connID);
	long RemoveCallViaConnection(ConnectionID_t & connID);
	BOOL AddConnectionToCall(long callHandle, ConnectionID_t & connID);
	long RemoveConnectionFromCall(ConnectionID_t & connID);
	BOOL GetLocalConnection(long callHandle, ConnectionID_t & connID);
	BOOL IsLocalConnection(long callHandle, ConnectionID_t & connID);
	long GetCallHandle(ConnectionID_t & connID, BOOL exactMatch);



private:
	DeviceID_t m_DeviceID;
	DeviceID_t m_CalledDeviceID;
	long m_activeCall;
	long m_holdCall;
	bool m_Established;

	CString m_AgentID;
	AgentState_t m_AgentState;
	CString m_Command;

	CSTAMonitorCrossRefID_t m_MonitorCrossRefID;
	CWnd* m_pWnd;
	// if there were an unknown number of calls that could be at a device,
	//  the memory would be dynamically allocated as needed.
	ConnectionID_t m_ConnIDList[MAX_CALLS_AT_DEVICE][MAX_DEVICES_IN_CALL];
	//ConnectionID_t m_HeldConnIDList[MAX_CALLS_AT_DEVICE];
	//ConnectionID_t m_AlertingConnID;
	
	//CCallInfo m_CallInfo[MAX_CALLS_AT_DEVICE];
};

class CTsapiWnd : public CWnd
{
// Construction
public:
	CTsapiWnd();	// standard constructor  
 	virtual ~CTsapiWnd();

	// The window responsible for clean-up and stream failure handling
	CWnd* m_TsapiController;

	// stream variables
	ACSHandle_t m_AcsHandle;
	unsigned short m_EventBufSize;
	char m_EventBuf[2000];
	CSTAEvent_t* m_EventBufPtr;

	CTsapiDevice* CreateDeviceRecord(DeviceID_t deviceId);
	CTsapiDevice* GetDeviceRecord(DeviceID_t deviceId);
	CTsapiDevice* GetDeviceRecord(CSTAMonitorCrossRefID_t monitorCrossRefId);

// Implementation
	void DoCreate();
protected:

	LRESULT OnTsapiMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

private:
	// if the app was going to track an unknown number of devices, the
	//  memory would be dynamically allocated as needed, instead of being declared
	//  here
	//CTsapiDevice m_MyOneDevice;
	CTsapiDevice m_MyDevices[MAX_DEVICES];
};

#endif

/////////////////////////////////////////////////////////////////////////////
