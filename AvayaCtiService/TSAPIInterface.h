#ifndef __TSAPIINTERFACE_H__
#define __TSAPIINTERFACE_H__
/* TSAPIInterface.h
* This class act as a wrapper to TSAPI client library. This class invokes methods provided by TSAPI Client library 
* for example to establish a session with TSAPI Service, it calls acsOpenStream method. This class also receive and 
* process all events that are received from the TSAPI Service.
*
*	Specifically this class has following responsibility:
*	1. Establish communication channel with the AE Server:TSAPI Service and reports error if any
*	2. Process all the events received from the TSAPI Service and update AvayaCallCenterUserAgent/CallManager Class.
*	3. Forward request made from user to TSAPI Service e.g. changing agent state, answer/disconnect a call etc
*	4. Handles exception condition.
*/

#pragma once

#include "string"
#include "map"
#include "acs.h"
#include "csta.h"
#include "attpriv.h"
#include "KafkaProducer.h"
#include "stdarg.h"


/* This defines the MSG name with which this Application 
* will be notified when TSAPI Service sends the MSG
*/

#define WM_TSAPIMSG	WM_USER+2130

//ACSUniversalFailure_t 
#define tserverBadPasswordOrLogin 25
#define tserverDeviceNotSupported 35
#define tserverDeviceNotOnCallControlList 50

//AgentState_t
#define agNotReady 0
#define agNull 1
#define agReady 2
#define agWorkNotReady 3
#define agWorkReady 4

//ATTTalkState_t
#define tsOnCall 0
#define tsIdle 1

//CSTAUniversalFailure_t
#define genericUnspecified 0
#define genericOperation 1
#define invalidCstaDeviceIdentifier 12
#define invalidObjectState 22
#define resourceBusy 33

//LocalConnectionState_t
#define csNone -1
#define csNull 0
#define csInitiate 1
#define csAlerting 2
#define csConnect 3
#define csHold 4
#define csQueued 5
#define csFail 6

//CSTAEventCause_t
#define ecNone -1 

using namespace std;

class TSAPIInterface : public CWnd
{
	DECLARE_DYNAMIC(TSAPIInterface)

public:

	static TSAPIInterface *GetInstance();	// This allows to create only a single Object for the TSAPIInterface class

	// This function is used to Open a communication Channel(in the form of ACS Stream) for the application to send csta request
	bool OpenStream(TCHAR* , TCHAR* , TCHAR* );		// for opening an ACS Stream
	// This function is used to closes the communication Channel opened for the application.
	bool CloseStream();		// for closing an ACS Stream


	// This function logs the Agent
	bool AgentLogin(DeviceID_t,AgentID_t,AgentPassword_t,AgentMode_t, int);	// for Logging an Agent on a Device with ( AutoIn or ManualIn)
	// This function logs out the Agent
	bool AgentLogout(DeviceID_t, AgentID_t,AgentPassword_t,AgentMode_t);		// for Logging out Agent 	
	// This function is used to changes the Agent State
	void AgentSetState(DeviceID_t, AgentID_t , AgentPassword_t ,int ,char *,bool);	// for changing Agent's State ( Ready / Busy ( work not ready) / Not Ready )
	
	// This function is used to Answer the Call
	void AgentAnswerCall(DeviceID_t, long); // for Answering call
	void AgentClearConnection(DeviceID_t deviceID, long callID);
	// This function is used to Disconnect the Call
	void AgentDisconnectCall(DeviceID_t, long);	// for Disconnect a call
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
	//This function is used to Transfer the Call
	void AgentEscapeService();//�����绰ת�ƣ��ѽӣ����ͷ�ת��////δʵ��


	//This function is used to Conference the Call
	void AgentConferenceCall(DeviceID_t D1, long C1, long C2);//����ͨ��
	//�����绰���� //δд
	//This function is used to Consultation the Call
	void AgentConsultationCall(DeviceID_t D1, long C1, DeviceID_t D3);//���������绰
	//This function is used to Reconnect the Call  
	// activeCall (C2- D1)   heldCall (C1- D1)
	void AgentReconnectCall(DeviceID_t D1, long C1, long C2);//����������״̬�����绰

	// This funcion is used to Query the Agent State
	void QueryAgentStatus(DeviceID_t); // for polling Agent current status.
	
	// This function is used to add the monitor on the Station  Extension
	void StartMonitor(DeviceID_t);			// for monitoring a device
	// This method is used to remove the monitor from the Station Extension
	void StopMonitor(CSTAMonitorCrossRefID_t m_lMonitorCrossRefID);		// for removing the monitor

	void SnapshotDevice(DeviceID_t deviceId);
	void SingleStepConferenceCall(DeviceID_t deviceId);

	//Routing Service   //CTI����  �����Ÿ�Agent  //������ô�ã�Ĭ�ϣ�
	void RouteEndInv(RouteRegisterReqID_t, RoutingCrossRefID_t);
	void RouteRegisterCancel(RouteRegisterReqID_t);
	void RouteRegister(DeviceID_t);
	void RouteSelectInv(RouteRegisterReqID_t,RoutingCrossRefID_t, DeviceID_t, RetryValue_t, SetUpValues_t, Boolean);





	~TSAPIInterface();

	/////��������Ϣ
	//string ReturnMes(string mes, ...);
	string ReturnMes(map<string,string>);
protected :

	// pointer to one and only instance of this class
	static TSAPIInterface *m_pSelf; 

	DECLARE_MESSAGE_MAP()
	
	// This function receives and process all events coming from TSAPI Service.
	LRESULT TSAPIMessageHandler(WPARAM,LPARAM);

private :
	KafkaProducer* m_pProducerObject;
	map<InvokeID_t, string> m_InvokeID2DeviceID;//������ID�������豸ID
	map<InvokeID_t, string> m_InvokeID2ActName;//������ID�������

	map<string, string> m_DeviceCallID;//�豸��CALLID


	ACSHandle_t m_lAcsHandle;	// Handle for ACS Stream
	RetCode_t m_nRetCode;			// code returned by the client library for success or failure of service request
	
	ATTPrivateData_t m_stPrivateData;	// Private Data for using extended features of TSAPI service
	InvokeID_t m_ulInvokeID;			// This application uses, Application generated InvokeID
	CSTAEvent_t cstaEvent; // CSTA event buffer required for reteriving the Event Structure
	unsigned short m_usEventBufSize; // CSTA event buffer size

	TSAPIInterface();
	// This function will process all ACS Confimation Events
	void HandleACSConfirmation(CSTAEvent_t);
	// This function will process all CSTA Confimation Events
	void HandleCSTAConfirmation(CSTAEvent_t, ATTPrivateData_t);
	// This function will process all CSTAUNSOLICITED Events
	void HandleCSTAUnsolicited(CSTAEvent_t);
	// This function will process all CSTAEVENTREPORT Events
	void HandleCSTAEventReport(CSTAEvent_t, ATTPrivateData_t);
	// This function will process all CSTAREQUEST Events
	void HandleCSTARequest(CSTAEvent_t, ATTPrivateData_t);

};

#endif