/* AvayaCallCenterUserAgent.cpp :
* This is implementation file for AvayaCallCenterUserAgent Class. This class will handle all the Agent 
* related functinality like:
* 1. Answer/Disconnecting Calls.
* 2. Changing Agent State
* 3. Retrieving Agent's State from TSAPIInterface class
* 4. Sending EnumAgentState to AgentStateUI for updating Agent State.
*/

#include "stdafx.h"
#include "AvayaCtiService.h"
#include "AvayaCallCenterUserAgent.h"



IMPLEMENT_DYNAMIC(AvayaCallCenterUserAgent, CWnd)


AvayaCallCenterUserAgent::AvayaCallCenterUserAgent()
{
	// get the TSAPIInterface Object
	m_pTsapiInterfaceObject = TSAPIInterface::GetInstance(); 
}

// Destructor for the class
AvayaCallCenterUserAgent::~AvayaCallCenterUserAgent()
{
	// This method will be called to stop the monitor when Agent has logged out.
	// AgentStopMonitor();
}

// This function will be called after every 20 sec for reteriving the Agent State
void AvayaCallCenterUserAgent ::AgentGetState(DeviceID_t m_szDeviceID)
{
	// This will call the QueryAgentStatus method for quering the Agent State
	m_pTsapiInterfaceObject->QueryAgentStatus(m_szDeviceID);
}

// Starting the Monitor, this method will be called in the constructor of this class
void AvayaCallCenterUserAgent ::AgentStartMonitor(DeviceID_t m_szDeviceID)
{
	// calling the TSAPIInterface method for starting the monitor 
	m_pTsapiInterfaceObject->StartMonitor(m_szDeviceID);
}

// Once the monitor is setup now login the Agent, this function is also called in the constructor of this class
void AvayaCallCenterUserAgent::AgentLogin(DeviceID_t m_szDeviceID, AgentID_t m_szAgentID, AgentPassword_t m_szAgentPassword, int m_nAgentWorkMode)
{
	// calling the TSAPIInterface method for Logging an Agent.
	m_pTsapiInterfaceObject->AgentLogin(m_szDeviceID,m_szAgentID,m_szAgentPassword,AM_LOG_IN, m_nAgentWorkMode);
}

// This function is called in the destructor of thie class when Agent has logged out.
void AvayaCallCenterUserAgent ::AgentStopMonitor(CSTAMonitorCrossRefID_t m_MonitorCrossRefID)
{
	// calling the TSAPIInterface method for removing the monitor
	m_pTsapiInterfaceObject->StopMonitor(m_MonitorCrossRefID);
}
// Log out the Agent
bool AvayaCallCenterUserAgent::AgentLogout(DeviceID_t m_szDeviceID, AgentID_t m_szAgentID,
	AgentPassword_t m_szAgentPassword)
{
	//if() agentlogout 写个返回值
	m_pTsapiInterfaceObject->AgentLogout(m_szDeviceID,m_szAgentID,m_szAgentPassword,AM_LOG_OUT);
	return (TRUE);
	
}
/// <summary>
/// This function is used to call method of TSAPIInterface class for changing the Agent State.
/// </summary>
/// <param name="agentState">Represent agent state</param>
/// <param name="enablePending">A boolean value, true or false as per user selection on UI.</param>
void AvayaCallCenterUserAgent::AgentSetState(DeviceID_t m_szDeviceID ,AgentID_t m_szAgentID ,
	AgentPassword_t m_szAgentPassword , int m_nAgentWorkMode ,
	char* agentState, bool enablePending)
{
	m_pTsapiInterfaceObject->AgentSetState(m_szDeviceID,m_szAgentID,m_szAgentPassword,
		m_nAgentWorkMode, agentState, enablePending);
}

//This function will be called when AnswerCall button is clicked
void AvayaCallCenterUserAgent ::AgentAnswerCall(DeviceID_t m_szDeviceID,long m_callID)
{	
	m_pTsapiInterfaceObject->AgentAnswerCall(m_szDeviceID,m_callID);
}

//This function will be called when ClearConnection button is clicked
void AvayaCallCenterUserAgent::AgentClearConnection(DeviceID_t m_szDeviceID, long m_callID)
{
	m_pTsapiInterfaceObject->AgentClearConnection(m_szDeviceID, m_callID);
}

void AvayaCallCenterUserAgent :: AgentDisconnectCall(DeviceID_t m_szDeviceID, long m_callID)
{
	m_pTsapiInterfaceObject->AgentDisconnectCall(m_szDeviceID,m_callID);
}

//This function is used to Make the Call
void AvayaCallCenterUserAgent::AgentMakeCall(DeviceID_t callingDevice, DeviceID_t calledDevice)
{
	m_pTsapiInterfaceObject->AgentMakeCall(callingDevice, calledDevice);
}  
//This function is used to Hold the Call
void AvayaCallCenterUserAgent::AgentHoldCall(DeviceID_t deviceID, long callID)	// for hold a call
{
	m_pTsapiInterfaceObject->AgentHoldCall(deviceID, callID);
}
//This function is used to Retrieve the Call
void AvayaCallCenterUserAgent::AgentRetrieveCall(DeviceID_t deviceID, long callID)//hold to connect
{
	m_pTsapiInterfaceObject->AgentRetrieveCall(deviceID, callID);
}

//This function is used to Pickup the Call
void AvayaCallCenterUserAgent::AgentDeflectCall(DeviceID_t deviceID, long activeCall, DeviceID_t calledDevice)//电话转移（未接）
{
	m_pTsapiInterfaceObject->AgentDeflectCall(deviceID, activeCall, calledDevice);
}
//This function is used to Deflect the Call
void AvayaCallCenterUserAgent::AgentPickupCall(DeviceID_t deviceID, long activeCall, DeviceID_t calledDevice)//电话转移（未接）
{
	m_pTsapiInterfaceObject->AgentPickupCall(deviceID, activeCall, calledDevice);

}
//This function is used to Transfer the Call
void AvayaCallCenterUserAgent::AgentTransferCall(DeviceID_t deviceID, long heldCall, long activeCall)//电话转移（已接）（成功转）
{
	m_pTsapiInterfaceObject->AgentTransferCall(deviceID, heldCall, activeCall);
}
//This function is used to Conference the Call
void AvayaCallCenterUserAgent::AgentConferenceCall(DeviceID_t checkedDevice, DeviceID_t deviceID)//三方通话
{
	m_pTsapiInterfaceObject->AgentConferenceCall(checkedDevice, deviceID);
}
//This function is used to Consultation the Call
void AvayaCallCenterUserAgent::AgentConsultationCall(DeviceID_t deviceID,DeviceID_t calledDevice)//两方求助电话
{
	m_pTsapiInterfaceObject->AgentConsultationCall(deviceID,calledDevice);

}
//This function is used to Reconnect the Call  
//activeCall (C2- D1)   heldCall (C1- D1)
void AvayaCallCenterUserAgent::AgentReconnectCall(DeviceID_t deviceID, long heldCall, long activeCall)//从两方求助状态重连电话
{
	m_pTsapiInterfaceObject->AgentReconnectCall(deviceID, heldCall, activeCall);
}
//通话监听、强插

void AvayaCallCenterUserAgent::AgentMonitorCall(DeviceID_t checkedDevice, DeviceID_t deviceID,string type)//从两方求助状态重连电话
{
	//m_pTsapiInterfaceObject->AgentReconnectCall(deviceID, heldCall, activeCall);
	//m_pTsapiInterfaceObject->SnapshotDevice(checkedDevice);
	ATTParticipationType_t participationType;
	if (type == "PT_ACTIVE") {
		participationType = PT_ACTIVE;
	}
	else if(type == "PT_SILENT")
	{
		participationType = PT_SILENT;
	}
	else
	{
		return;
	}
	m_pTsapiInterfaceObject->SingleStepConferenceCall(checkedDevice, deviceID, participationType);
}

void AvayaCallCenterUserAgent::SnapshotDevice(DeviceID_t checkedDevice) {
	m_pTsapiInterfaceObject->SnapshotDevice(checkedDevice);
}


//单步转移、强接
void AvayaCallCenterUserAgent::AgentSingleStepTransferCall(DeviceID_t calledDevice, DeviceID_t checkedDevice) {
	m_pTsapiInterfaceObject->SingleStepTransferCall(calledDevice,checkedDevice);
}

