/* AvayaCallCenterUserAgent.h
* This class represent an Agent and contains functionality typically performed by an Agent like:
* 1. Login / Logout
* 2. Answer/ Disconnect Call
* 3. Change State. 
*/

#pragma once
#include "AgentStateObserver.h"
#include "TSAPIInterface.h"
#include "Cstadefs.h"

class AvayaCallCenterUserAgent 
{
	DECLARE_DYNAMIC(AvayaCallCenterUserAgent)

public:

	
	// This will be called to instantiate the Object for this class with Agent Details
	AvayaCallCenterUserAgent();



	// This function is used to call method of TSAPIInterface class for Logging the Agent.
	void AgentLogin(DeviceID_t, AgentID_t, AgentPassword_t, int);
	// This function is used to call method of TSAPIInterface class for Logging out the Agent
	bool AgentLogout(DeviceID_t , AgentID_t , AgentPassword_t );
	// This function is used to call method of TSAPIInterface class for changing the Agent State
	void AgentSetState(DeviceID_t , AgentID_t , AgentPassword_t , int , char* , bool);
	// This function is used to call method of TSAPIInterface class for querying the Agent State
	void AgentGetState(DeviceID_t );
	// This function is used to call method of TSAPIInterface class for Answering the call
	void AgentAnswerCall(DeviceID_t,long);
	// This function is used to call method of TSAPIInterface class for Disconnecting the call
	void AgentDisconnectCall(DeviceID_t, long);	// for Disconnecting the call

	//This function is used to Make the Call
	void AgentMakeCall(DeviceID_t, DeviceID_t);
	//This function is used to Hold the Call
	void AgentHoldCall(DeviceID_t, long);	// for hold a call
	//This function is used to Retrieve the Call
	void AgentRetrieveCall(DeviceID_t, long);//hold to connect
	//This function is used to Pickup the Call
	void AgentDeflectCall(DeviceID_t D1, long C1, DeviceID_t D3);//�绰ת�ƣ�δ�ӣ�
	//This function is used to Deflect the Call
	void AgentPickupCall(DeviceID_t D1, long C1, DeviceID_t D3);//�绰ת�ƣ�δ�ӣ�
	//This function is used to Transfer the Call
	void AgentTransferCall(DeviceID_t D1, long C1, long C2);//�绰ת�ƣ��ѽӣ����ɹ�ת��

	//This function is used to Conference the Call
	void AgentConferenceCall(DeviceID_t D1, long C1, long C2);//����ͨ��
	//�����绰���� //δд
	//This function is used to Consultation the Call
	void AgentConsultationCall(DeviceID_t D1, long C1, DeviceID_t D3);//���������绰
	//This function is used to Reconnect the Call  
	//activeCall (C2- D1)   heldCall (C1- D1)
	void AgentReconnectCall(DeviceID_t D1, long C1, long C2);//����������״̬�����绰

	// This funcion is used to Query the Agent State
	void QueryAgentStatus(DeviceID_t); // for polling Agent current status.


	// This function is used to call method of TSAPIInterface class for adding monitor on the Station Extension
	void AgentStartMonitor(DeviceID_t);//���Ӷ���ΪDeviceID_t
	// This function is used to call method of TSAPIInterface class for removing monitor on the Station Extension	  
	void AgentStopMonitor(CSTAMonitorCrossRefID_t);//�رռ��� ����Ϊ�����¼����ص�CSTAMonitorCrossRefID_t

	// Destructor of the class
	virtual ~AvayaCallCenterUserAgent();

private:
	// Pointer Array for maintaining the list of Observer for this class
	CPtrArray m_pAgtObserver;
	// This object will contain the TSAPIInterface Object
	TSAPIInterface *m_pTsapiInterfaceObject;
};


