/* TSAPIInterface.cpp
* This is implementation file for TSAPIInterface Class. This class invokes methods provided by TSAPI Client library 
* for example to establish a session with TSAPI Service, it calls acsOpenStream method. This class also receive and 
* process all events that are received from the TSAPI Service.
*
*	Specifically this class has following responsibility:
*	1. Establish communication channel with the AE Server:TSAPI Service and reports error if any
*	2. Process all the events received from the TSAPI Service and update AvayaCallCenterUserAgent/CallManager Class.
*	3. Forward request made from user to TSAPI Service e.g. changing agent state, answer/disconnect a call etc
*	4. Handles exception condition.
*/

#include "stdafx.h"
#include "AvayaCtiService.h"
#include "TSAPIInterface.h"
#include <windows.h>


// TSAPIInterface

IMPLEMENT_DYNAMIC(TSAPIInterface, CWnd)

// Constructor of the TSAPIInterface 
// initialising the Default Values
TSAPIInterface::TSAPIInterface()
{
	m_lAcsHandle = 0; // handle for the ACS stream
	
	// This Application creates ACS stream with Application generated invokeID's 
	// This is the first invokeID to be used.
	m_ulInvokeID = 1;		
	m_pProducerObject = new KafkaProducer();
	m_pProducerObject->PutBrokers("127.0.0.1:9092");
	m_pProducerObject->PutTopics("topics_1");
	m_pProducerObject->initKafka();
}

// Destructor of TSAPIInterface
// Destroying the handle for the stream
TSAPIInterface::~TSAPIInterface()
{
	delete m_pProducerObject;

	// closing the ACS Stream
	/*if ( m_lAcsHandle )
	{
	acsAbortStream(m_lAcsHandle,NULL);
	}
	*/

	
}


//////////////////////////////////////////////////////////
TSAPIInterface * TSAPIInterface :: m_pSelf = NULL;

// Creating a Single object of the class
// Returns one and only instance of this class
TSAPIInterface* TSAPIInterface::GetInstance()
{
	if ( m_pSelf == NULL )
	{
		m_pSelf = new TSAPIInterface();
		if(m_pSelf != NULL)
		{
			// memory has been allocated.
			m_pSelf->CreateEx(0, AfxRegisterWndClass(CS_GLOBALCLASS), "", 0, 0, 0, 0, 0, 0, 0);
		}
	}
	return m_pSelf;
}

BEGIN_MESSAGE_MAP(TSAPIInterface, CWnd)
	ON_MESSAGE(WM_TSAPIMSG,TSAPIMessageHandler)
END_MESSAGE_MAP()

// TSAPIInterface message handlers

/// <summary>
/// This method handles all the events, confirmatin and exception received from the TSAPI Service.
/// </summary>
/// <param name="wParam">Contains event information</param>
/// <param name="lParam">Contains event information</param>
/// <returns></returns>
LRESULT TSAPIInterface::TSAPIMessageHandler(WPARAM wParam, LPARAM lParam)
{
	m_usEventBufSize = sizeof(CSTAEvent_t);
	m_stPrivateData.length = ATT_MAX_PRIVATE_DATA;

	// Method for retrieving the entire response event structure

	m_nRetCode = acsGetEventBlock( m_lAcsHandle, (void *)&cstaEvent, &m_usEventBufSize, 
		(PrivateData_t *)&m_stPrivateData, NULL);

	// If there is error retriveing Event Structure 
	// further processing can not proceed, exit

	if ( m_nRetCode != ACSPOSITIVE_ACK )
	{
		MessageBox("Error is receiving Messages");
		exit(-1);
	}
	else
	{
		// Request is successful
		switch (m_nRetCode)
		{
			case ACSERR_BADHDL: // AcsHandle is Invalid;
			case ACSERR_UBUFSMALL: //User buffer size is smaller than the size of next available event
							// for ACS Stream
			default: break;
		}// end of switch
	}// end of else

	// Check for event type.
	switch( cstaEvent.eventHeader.eventClass )
	{
	case ACSCONFIRMATION:
	{
		// call the handleACSConfirmation function
		// for handling acs information
		HandleACSConfirmation(cstaEvent);

	}// end of inner switch
	break;
	case CSTACONFIRMATION:
	{
		// call the handleCSTAConfirmation function for processing
		// CSTA Confirmation Events
		HandleCSTAConfirmation(cstaEvent,m_stPrivateData);

	}// end of ctsaconfirmation
	break;
	case CSTAUNSOLICITED:
	{
		// call the handler for processing all the CSTAUNSOLICITED Event.
		HandleCSTAUnsolicited(cstaEvent);
	}// end of CSTAUNSOLICITED Events
	break;
	case CSTAEVENTREPORT:
	{
		// call the handler for processing all the CSTAEVENTREPORT Event.
		HandleCSTAEventReport(cstaEvent,m_stPrivateData);
	}//end of CSTAEVENTREPORT Events
	break;
	case CSTAREQUEST:
	{
		// call the handler for processing all the CSTAREQUEST Event.
		HandleCSTARequest(cstaEvent, m_stPrivateData);
	}//end of CSTAREQUEST Events
	break;
	default:{}
	}// end of outer switch

	return (FALSE);
}
/// <summary>
/// This Function will handle all CSTAREQUEST Events.
/// </summary>
/// <param name="cstaEvent">Event object that contain event information.</param>
/// <param name="privateData">PrivateData object that contain private data information.</param>
void TSAPIInterface::HandleCSTARequest(CSTAEvent_t cstaEvent, ATTPrivateData_t privateData)
{
	map<string, string> mes;//装标签key 和对应信息value
	string res;

	//信息不发送前端 只保存到数据库,发送到监控
	switch (cstaEvent.eventHeader.eventType)
	{
	case CSTA_ROUTE_REQUEST_EXT://请求呼叫相关的信息事件(TSAPI Version 2)
	{
		theApp.m_pAvayaCtiUIDlg->m_pRoutingObject->RouteRequestExtEvent(cstaEvent.event.cstaRequest.u.routeRequestExt, privateData);
		
	}//end of CSTA_ROUTE_REQUEST_EXT
	break;
	case CSTA_ROUTE_REQUEST://请求呼叫相关的信息事件(TSAPI Version 1)
	{
		/*
		RouteRegisterReqID_t routeRegisterReqID;
		RoutingCrossRefID_t routingCrossRefID;
		CalledDeviceID_t routeUsed;
		CallingDeviceID_t callingDevice;
		unsigned char domain;

		ATTEvent_t att_event;
		*/

	}//end of CSTA_ROUTE_REQUEST
	break;
	default: {break; }
	}

}


/// <summary>
/// This Function will handle all CSTAEVENTREPORT Events.
/// </summary>
/// <param name="cstaEvent">Event object that contain event information.</param>
/// <param name="privateData">PrivateData object that contain private data information.</param>
void TSAPIInterface::HandleCSTAEventReport(CSTAEvent_t cstaEvent, ATTPrivateData_t privateData)
{
	map<string, string> mes;
	string res;

	//信息不发送前端 只保存到数据库,发送到监控
	switch (cstaEvent.eventHeader.eventType)
	{
	case CSTA_ROUTE_END://路由结束事件
	//终止呼叫的路由会话,并通知呼叫路由结果(通用故障) 
	{
		theApp.m_pAvayaCtiUIDlg->m_pRoutingObject->RouteEndEvent(cstaEvent.event.cstaEventReport.u.routeEnd);
	}break;//end of CSTA_ROUTE_END
	case CSTA_ROUTE_REGISTER_ABORT://交换机取消路由注册会话事件
	{
		theApp.m_pAvayaCtiUIDlg->m_pRoutingObject->RouteRegisterAbortEvent(cstaEvent.event.cstaEventReport.u.registerAbort);
	}break;//end of CSTA_ROUTE_REGISTER_ABORT
	case CSTA_ROUTE_USED_EXT://路由目标提供事件
	{
		theApp.m_pAvayaCtiUIDlg->m_pRoutingObject->RouteUsedExtEvent(cstaEvent.event.cstaEventReport.u.routeUsedExt);

	}break;//end if CSTA_ROUTE_USED_EXT
	//case CSTA_ROUTE_USED:

	default: {break; }

	}
}


/// <summary>
/// This Function will handle all ACSConfirmation Events.
/// </summary>
/// <param name="cstaEvent">Event object that contain event information.</param>
void TSAPIInterface ::HandleACSConfirmation(CSTAEvent_t cstaEvent)
{
	map<string, string> mes;//装标签key 和对应信息value
	mes["ActName"] = m_InvokeID2ActName[cstaEvent.event.cstaConfirmation.invokeID];
	mes["DeviceID"] = m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];
	string res;
	switch (cstaEvent.eventHeader.eventType)
	{
	case ACS_OPEN_STREAM_CONF : //打开流
	{
		if ( m_stPrivateData.length > 0 && strcmp(m_stPrivateData.vendor,ECS_VENDOR_STRING) == 0 )
		{
			res.clear();
			mes["ActName"] = "OpenStream";
			//Kafka返回消息的类
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
		else
		{
			//MessageBox(PRIVATE_DATA_NOT_CORRECTLY_NEGOTIATED);
			acsAbortStream(m_lAcsHandle,NULL);
			exit(-1);
		}
	}break; 

	case ACS_CLOSE_STREAM_CONF:
	{	// Confirmation event after closing stream
		//Kafka返回消息的类
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;

	case ACS_UNIVERSAL_FAILURE_CONF://ACS错误不发送 只打印到日志
	{
		// This Event is generated when ACS Stream is not correctly opened.
		// Get the Error cause
		int nError = cstaEvent.event.acsConfirmation.u.failureEvent.error;
			
		switch( nError )
		{
		case TSERVER_BAD_PASSWORD_OR_LOGIN:
		{
			mes["Error"] = nError;
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);

		}break;
		case TSERVER_DEVICE_NOT_SUPPORTED:
		{
			mes["Error"] = nError;
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		case TSERVER_DEVICE_NOT_ON_CALL_CONTROL_LIST:
		{
			mes["Error"] = nError;
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		default:{break;}
		}// End of switch
	}break;// End of ACS Failure Event
	default:{}
	}// End of main switch

	 //删除map key invokeID对应映射
	m_InvokeID2DeviceID.erase(cstaEvent.event.cstaConfirmation.invokeID);
	m_InvokeID2ActName.erase(cstaEvent.event.cstaConfirmation.invokeID);

}// End of function

/// <summary>
/// This function will handle all CSTAConfirmation Events.
/// </summary>
/// <param name="cstaEvent">Event object that contain event information.</param>
/// <param name="privateData">PrivateData object that contain private data information.</param>
void TSAPIInterface::HandleCSTAConfirmation(CSTAEvent_t cstaEvent, ATTPrivateData_t privateData)
{
	map<string, string> mes;//装标签key 和对应信息value
	string res;

	string ActName = m_InvokeID2ActName[cstaEvent.event.cstaConfirmation.invokeID];
	string DeviceID = m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];
	mes["ActName"] = ActName;
	mes["DeviceID"] = DeviceID;

	switch (cstaEvent.eventHeader.eventType)
	{
	case CSTA_MONITOR_CONF://开启监控返回事件  
	{	
		// retrived the monitor cross reference ID  
		CSTAMonitorCrossRefID_t m_lMonitorCrossRefID = cstaEvent.event.cstaConfirmation.u.monitorStart.monitorCrossRefID;
		mes["MonitorCrossRefID"] = to_string(m_lMonitorCrossRefID);
		//m_MonitorDevice[to_string(m_lMonitorCrossRefID)] = DeviceID;//add monitor device 2 map.it will be removed when run function StopMonitor 
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;

	case CSTA_MONITOR_STOP_CONF ://关闭监控服务返回事件
	{
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;

	case CSTA_SET_AGENT_STATE_CONF://改变坐席状态  login ,logout ,setstate
	{
		// Get the Agent State to take appropriate Action.	
		// 向DeviceID传递事件成功消息
		if (ActName == "AgentLogin" || ActName == "AgentLogout"|| ActName == "AgentSetState")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());//本地打印 
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);//向DeviceID对应的kafka分支发送消息
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}

	}break;
		
	case CSTA_ANSWER_CALL_CONF://应答 AgentAnswerCall
	{
		// Get the Agent State to take appropriate Action.	
		// 向DeviceID传递事件成功消息
		if (ActName == "AgentAnswerCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}

	}break;
	case CSTA_CLEAR_CONNECTION_CONF://挂机 AgentDisconnectCall
	{
		// 向DeviceID传递事件成功消息
		if (ActName == "AgentDisconnectCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_MAKE_CALL_CONF://呼出 AgentMakeCall
	{
		if (ActName == "AgentMakeCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_HOLD_CALL_CONF://保持 AgentHoldCall
	{
		if (ActName == "AgentHoldCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_RETRIEVE_CALL_CONF://保持恢复 AgentRetrieveCall
	{
		if (ActName == "AgentRetrieveCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_DEFLECT_CALL_CONF://电话转移 AgentDeflectCall
	{
		if (ActName == "AgentDeflectCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_PICKUP_CALL_CONF://电话代接 AgentPickupCall
	{
		if (ActName == "AgentPickupCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_TRANSFER_CALL_CONF://电话转移 成功转
	{

		if (ActName == "AgentTransferCall")//?返回什么内容
		{
			ConnectionID_t   newCall = cstaEvent.event.cstaConfirmation.u.transferCall.newCall;
			ConnectionList_t connList = cstaEvent.event.cstaConfirmation.u.transferCall.connList;

			////
			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				char*  ucid = att_event.u.transferCall.ucid;
				//mes["ucid"] = ucid;
			}
			mes["newCall_callID"] = newCall.callID;
			mes["newCall_deviceID"] = newCall.deviceID;

			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	//CSTA_ESCAPE_SVC_CONF  //电话转移 释放转
	case CSTA_CONFERENCE_CALL_CONF://三方会议
	{

		if (ActName == "AgentConferenceCall")
		{
			ConnectionID_t   newCall = cstaEvent.event.cstaConfirmation.u.conferenceCall.newCall;
			ConnectionList_t connList = cstaEvent.event.cstaConfirmation.u.conferenceCall.connList;

			////
			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				char*  ucid = att_event.u.conferenceCall.ucid;
			}
			mes["newCall_callID"] = newCall.callID;
			mes["newCall_deviceID"] = newCall.deviceID;

			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_CONSULTATION_CALL_CONF://二方求助
	{
		if (ActName == "AgentConsultationCall")
		{
			//The client is returned with the connection newCall(C2 - D1).
			ConnectionID_t   newCall = cstaEvent.event.cstaConfirmation.u.consultationCall.newCall;

			////
			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				//char*  ucid = att_event.u.conferenceCall.ucid;
			}
			mes["newCall_callID"] = newCall.callID;
			mes["newCall_deviceID"] = newCall.deviceID;

			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_RECONNECT_CALL_CONF:
	{
		if (ActName == "AgentReconnectCall")
		{
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_QUERY_AGENT_STATE_CONF://查询坐席状态 QueryAgentStatus
	{
		// Retrieving the agent State
		AgentState_t agentState = cstaEvent.event.cstaConfirmation.u.queryAgentState.agentState;

		// In TSAPI, Agent remains in Ready State even when Agent is active on a call
		// to reterieve the actual state of the Agent, Private Data parameter 
		// talkState is used.

		ATTEvent_t att_event ; // used for reteriving the current Talk State of Agent

		// Check the Agent's State
		switch (agentState)
		{
		case agNotReady:
		{
			mes["AgentState"] = "agNotReady";
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;

		case agReady:
		{
			// Ready Sate of the Agent does not correctly identifies
			// whether Agent is busy on a call or is Idle.
			// Private Parameter talkState is used for determine Agent's actual State.

			// attPrivateData() method is used for decoding the private data information received  from the events
			// this check is done to ensure that there is no error while decoding the private data.
			if ( attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK )
			{
				// reterieving actual state after decoding from attPrivateData mehtod.
				// v5queryAgentState is used as this is retained for 
				// Private Data version 8 also

				// Retrieving the Agent's Talk State
				int talk_state = att_event.u.v5queryAgentState.talkState;

				if ( talk_state == tsOnCall)
				{	
					//发送tsOnCall Ready DeviceID  ActName 信息
					mes["AgentState"] = "agReady";
					mes["TalkState"] = "tsOnCall";

					res = ReturnMes(mes);
					//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
					//m_pProducerObject->produce(res, stoi(DeviceID)%10);
					theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
					theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
				}
				else if ( talk_state == tsIdle)
				{// Agent is Idle 
					// update the AvayaCallCenterUserAgentClass with Agent State as Ready
					// and talkState as Idle
					//发送tsIdle Ready DeviceID  ActName 信息
					mes["AgentState"] = "agReady";
					mes["TalkState"] = "tsIdle";

					res = ReturnMes(mes);
					//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
					//m_pProducerObject->produce(res, stoi(DeviceID)%10);
					theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
					theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
				}
			}
		}break;

		case agWorkNotReady:
		{
			//agent asWorkNotReady,talkState atsIdle
			mes["AgentState"] = "agWorkNotReady";
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;

		case  agNull:
		{
			if(false)// m_bIsAgtManuallyLogout
			{}
			else
			{
				mes["AgentState"] = "agNull";
				res = ReturnMes(mes);
				//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
				//m_pProducerObject->produce(res, stoi(DeviceID)%10);
				theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
				theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
			}
		}break;
		}// end of switch
	}// end of Query Agent State
	break;
	case CSTA_SNAPSHOT_DEVICE_CONF:
	{
		if (ActName == "AgentSnapshotDevice") {
			ConnectionID_t   callIdentifier = cstaEvent.event.cstaConfirmation.u.snapshotDevice.snapshotData.info->callIdentifier;
			CSTACallState_t localCallState = cstaEvent.event.cstaConfirmation.u.snapshotDevice.snapshotData.info->localCallState;
			int callCount = localCallState.count;
			LocalConnectionState_t callState = *localCallState.state;

			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				char*  ucid = att_event.u.ssconference.ucid;
				//mes["ucid"] = ucid;
			}

			int count = cstaEvent.event.cstaConfirmation.u.snapshotDevice.snapshotData.count;
			mes["count"] = to_string(count);
			mes["callId"] = to_string(callIdentifier.callID);
			mes["calldevice"] = to_string(callCount);
			mes["callState"] = to_string(callState);
			m_activeCall[DeviceID]= callIdentifier;//save the device's ConnectionID_t to map
			res = ReturnMes(mes);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_ESCAPE_SVC_CONF:
	{
		if (ActName == "SingleStepConferenceCall") {
			/*ConnectionID_t   newCall = cstaEvent.event.cstaConfirmation.u.transferCall.newCall;
			ConnectionList_t connList = cstaEvent.event.cstaConfirmation.u.transferCall.connList;*/

			////
			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				char*  ucid = att_event.u.ssconference.ucid;
				//mes["ucid"] = ucid;
			}
			
			ConnectionID_t newCall = att_event.u.ssconference.newCall;
			ConnectionList_t connList = att_event.u.ssconference.connList;

			mes["newCall_callID"] = to_string(newCall.callID);
			mes["newCall_deviceID"] = to_string((char)newCall.deviceID);

			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
		if (ActName == "AgentSingleStepTransferCall")
		{

			////
			ATTEvent_t att_event;

			if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ACSPOSITIVE_ACK)
			{
				char*  ucid = att_event.u.ssconference.ucid;
				//mes["ucid"] = ucid;
			}
			
			ConnectionID_t newCall = att_event.u.ssconference.newCall;
			ConnectionList_t connList = att_event.u.ssconference.connList;

			mes["newCall_callID"] = to_string(newCall.callID);
			mes["newCall_deviceID"] = to_string((char)newCall.deviceID);

			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}
	}break;
	case CSTA_UNIVERSAL_FAILURE_CONF :
	{
		// Universal Failure Event is received.
		// A Exception has occurred.

		// Look for error code
		int error = cstaEvent.event.cstaConfirmation.u.universalFailure.error ;

		// check the error code
		switch (error)
		{	// Generic Exception exception when invalid AgentID/Station is provided
		case  invalidCstaDeviceIdentifier :// INVALID_CSTA_DEVICE_-IDENTIFIER  cstaErrorString()返回事件
		{
			mes["error"] = "invalidCstaDeviceIdentifier";//可以放数字 或 string
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		} 
		break;
		// exception when invalid Agent password is provided.
		case genericUnspecified :
		{
			// When Agent Password is wrong.
			mes["error"] = "genericUnspecified";
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		// exception when invalid Agent is already logged in some other extension
		case invalidObjectState :
		{		
			mes["error"] = "invalidObjectState";
			res = ReturnMes(mes);
		//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		// This exception might occur for various reason which are beyond the scope of this application
		// providing information for this exception 
		// Device is off or Agent is already Logged in some other location.
		case genericOperation :
		{
			mes["error"] = "genericOperation";
			res = ReturnMes(mes);
			//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		case resourceBusy :
		{	// When Extension is busy and Agent tries to Login
			mes["error"] = "resourceBusy";
			res = ReturnMes(mes);
		//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
			//m_pProducerObject->produce(res, stoi(DeviceID)%10);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		//a required parameter is missing from the request or an out - of - range value has been specified
		case VALUE_OUT_OF_RANGE:
		{
			mes["error"] = "VALUE_OUT_OF_RANGE";
			res = ReturnMes(mes);
			theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
			theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
		}break;
		default:{break;}
				
		}
	}//end of CSTA_UNIVERSAL_FAILURE_CONF Switch
	}// end of cstaConfirmation Switch	
	//删除map key invokeID对应映射
	m_InvokeID2DeviceID.erase(cstaEvent.event.cstaConfirmation.invokeID);
	m_InvokeID2ActName.erase(cstaEvent.event.cstaConfirmation.invokeID);

}// end of function

/// <summary>
/// This function handles all the CSTAUnsolicited responses from the TSAPI Service.
/// </summary>
/// <param name="cstaEvent">Event object that contain event information.</param>
void TSAPIInterface::HandleCSTAUnsolicited(CSTAEvent_t cstaEvent)
{	
	//int DeviceID = m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];
	//string ActName = m_InvokeID2ActName[cstaEvent.event.cstaConfirmation.invokeID];
	map<string, string> mes;//装标签key 和对应信息value
	string res;
	string DeviceID;//事件返回的设备ID

	WORD usCallID = 0;
	switch(cstaEvent.eventHeader.eventType)
	{

	case CSTA_SERVICE_INITIATED ://Service Initiated Event  服务启动
	{
		long callID = cstaEvent.event.cstaUnsolicited.u.serviceInitiated.initiatedConnection.callID;
		char *initiated_devID = cstaEvent.event.cstaUnsolicited.u.serviceInitiated.initiatedConnection.deviceID;
		//输出启动服务的 callID 与 devID
		int a = callID;
		mes["callID"] = to_string(a);
		mes["initiated_devID"] = initiated_devID;
		DeviceID = initiated_devID;
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		//m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;

	case CSTA_ORIGINATED://Originated Event  建立连接
	{
		// This event is generated in sequence after the tehe CSTA_SERVICE_INITIATED_EVENT
		// when Agent makes a call

		// When Agent makes request to logs out manaully , This event is not generated
		usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.originated.originatedConnection.callID;
		char *called_devID = cstaEvent.event.cstaUnsolicited.u.originated.calledDevice.deviceID;
		char *calling_devID = cstaEvent.event.cstaUnsolicited.u.originated.callingDevice.deviceID;

		//输出连接的呼叫双方
		mes["callID"] = to_string(usCallID);
		mes["called_devID"] = called_devID;
		mes["calling_devID"] = calling_devID;
		DeviceID = called_devID;
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		//m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;

	case CSTA_CONNECTION_CLEARED://Connection Cleared Event  清除连接
	{

		// This event is generated when Agent Logged out manually
		//if else



		// This event is received when Call is disconnected by Agent or
		// by the Other Party involved in the call, at this time 
		// delete the CallID of the active call.

		// update the CallManager class and Agent Class for change of Agent and call/ Connection State
		usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.connectionCleared.droppedConnection.callID;
		//char *releaseDevID = cstaEvent.event.cstaUnsolicited.u.connectionCleared.droppedConnection.deviceID;//?
		mes["callID"] = to_string(usCallID);
		mes["deviceID"] = to_string(*cstaEvent.event.cstaUnsolicited.u.connectionCleared.droppedConnection.deviceID);
		DeviceID = cstaEvent.event.cstaUnsolicited.u.connectionCleared.droppedConnection.deviceID;
		
		//输出清除的设备号，呼叫号和当时设备状态
		switch (cstaEvent.event.cstaUnsolicited.u.connectionCleared.localConnectionInfo)//本地连接状态
		{
		case csAlerting:
		{
			mes["LocalConnectionState_t"] = "csAlerting";

		}break;// End of Alerting
		case csConnect:
		{
			// This event is generted when in conference some other party drops the call.

			// 1. Delete the Call the Call Object
			// 2. Create a Call Object with the same CallID with connectionState as csConnect
			mes["LocalConnectionState_t"] = "csConnect";

		}break;// End of csConnect
		case csNull:
		{
			if ( cstaEvent.event.cstaUnsolicited.u.connectionCleared.cause == ecNone)
			{
				mes["LocalConnectionState_t"] = "csNull";

			}// End of If
		}break;// End of csNull
		case csHold:
		{
			mes["LocalConnectionState_t"] = "csHold";

		}break; //End of Hold
		case csNone:
		{
			mes["LocalConnectionState_t"] = "csNone";

		}break;//End of None
		default:
		{
			break; 
		}

		}
		res = ReturnMes(mes);
		//theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
		//m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}break;
	case CSTA_RETRIEVED://CSTARetrievedEvent 恢复连接事件
	{// This event is received when held call is retrieved.
		usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.retrieved.retrievedConnection.callID;
		char *retrieved_devID = cstaEvent.event.cstaUnsolicited.u.retrieved.retrievedConnection.deviceID;
		//删除held map 元素
		if (m_heldCall[to_string(*retrieved_devID)].callID > 0) {
			m_heldCall.erase(cstaEvent.event.cstaUnsolicited.u.retrieved.retrievedConnection.deviceID);
		}
		//添加active map 元素
		m_activeCall[cstaEvent.event.cstaUnsolicited.u.retrieved.retrievedConnection.deviceID] = cstaEvent.event.cstaUnsolicited.u.retrieved.retrievedConnection;

		//输出恢复连接的设备号
		mes["callID"] = usCallID;
		mes["retrieved_devID"] = retrieved_devID;
		DeviceID = retrieved_devID;
		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}// end of csta Retrived Event
	break;

	case CSTA_DELIVERED: //Delivered Event  电话送递事件 （振铃）
	{
		WORD callID =0;
		callID = (WORD)cstaEvent.event.cstaUnsolicited.u.delivered.connection.callID;//正发出振铃的callID
		char *called_devID = cstaEvent.event.cstaUnsolicited.u.delivered.alertingDevice.deviceID;
		char *calling_devID = cstaEvent.event.cstaUnsolicited.u.delivered.callingDevice.deviceID;
		if ( cstaEvent.event.cstaUnsolicited.u.delivered.localConnectionInfo == csConnect)//CS_CONNECT
		{
			//输出 callID ，called_devID，calling_devID，//电话状态eCaState caActive（空闲，工作）//,被连接设备状态 CS_CONNECT
			mes["localConnectionInfo"] = "csConnect";

		}
		else if ( cstaEvent.event.cstaUnsolicited.u.delivered.localConnectionInfo == csAlerting )
		{
			//输出 callID ，called_devID，calling_devID，电话状态eCaState caActive（空闲，工作）,被连接设备状态 CS_ALERTING
			mes["localConnectionInfo"] = "csAlerting";

		}
		// preserving the DeviceID type, This is an mandatary parameter required for answering the call.
		ConnectionID_Device_t devIDType = cstaEvent.event.cstaUnsolicited.u.delivered.connection.devIDType;
		mes["devIDType"] = devIDType;
		mes["called_devID"] = called_devID;
		mes["calling_devID"] = calling_devID;
		mes["callID"] = to_string(callID);

		DeviceID = called_devID;
		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}// end of Delivered Event
	break;

	case CSTA_ESTABLISHED: //通知已建立连接事件
	{
		usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.established.establishedConnection.callID;
		char *m_answeringdevID = cstaEvent.event.cstaUnsolicited.u.established.answeringDevice.deviceID;
		char *m_callingDevID = cstaEvent.event.cstaUnsolicited.u.established.callingDevice.deviceID;
		//输出 callid ，answeringdevID,callingDevID
		DeviceID = m_answeringdevID;
		mes["answeringDevice"] = m_answeringdevID;
		mes["callingDevice"] = m_callingDevID;
		mes["callID"] = to_string(usCallID);

		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}// end of Established Event
		break;

	case CSTA_TRANSFERRED: //Transferred Event  
	{
		// update the call Manager class and update the Agent class
		// for updates in the Agent and the Call state

		// Update the CallManager
		//分不清这几个
		long lPrimaryCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.transferred.primaryOldCall.callID;
		long lSecondryCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.transferred.secondaryOldCall.callID;//保留的callID
		char *transferring_devID = cstaEvent.event.cstaUnsolicited.u.transferred.transferringDevice.deviceID;
		char *transferred_devID = cstaEvent.event.cstaUnsolicited.u.transferred.transferredConnections.connection[1].party.deviceID;//D3 指定设备数量的计数以及从转移中产生的 connectionIDs 和 deviceIDs 的列表 ，其中connection[1].party.deviceID为新连接的设备ID
		//char *transferred_devID = cstaEvent.event.cstaUnsolicited.u.transferred.transferredDevice.deviceID;//删除的老的D1
		if ( cstaEvent.event.cstaUnsolicited.u.transferred.localConnectionInfo == csNull )
		{
			//输出 关闭的call lPrimaryCallID，保留的 lSecondryCallID，提出转移操作的设备transferring_devID，
			//转移到的设备transferred_devID，转移到的设备的状态localConnectionInfo
			mes["localConnectionInfo"] = "csNull";

		}
		else if(  cstaEvent.event.cstaUnsolicited.u.transferred.localConnectionInfo == csConnect )
		{
			// This is generated When the other party tranfer the call
			// 1. Remove the Old Call. by calling the updateCall with old call id
			// 通知D1 与 D3 连接已断
	

			// 2. Add a new call Object for the new connection with New callID
			// 通知D2 与 D3 已连接
			/*
			usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.transferred.secondaryOldCall.callID;
			char *transfered_DevID = cstaEvent.event.cstaUnsolicited.u.transferred.transferredDevice.deviceID;
			transferring_devID = cstaEvent.event.cstaUnsolicited.u.transferred.transferredConnections.connection[1].party.deviceID;
			theApp.m_pAvayaCtiUIDlg->m_pCallManagerObject->UpdateCallManager((WORD)lSecondryCallID,caActive,conInitiate, transfered_DevID,transferring_devID,"");
			*/
			mes["localConnectionInfo"] = "csConnect";

		}
		DeviceID = transferred_devID;
		mes["primaryOldCall"] = lPrimaryCallID;
		mes["secondaryOldCall"] = lSecondryCallID;
		mes["transferringDevice"] = transferring_devID;
		mes["transferredConnections"] = transferred_devID;

		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}//end of Transferred Event
	break;
	case CSTA_CONFERENCED://Conferenced Event 会议开启事件
	{
		// This event is generated whenever Agent performs the Conference 
		// or anyother party performs conference

		// 1. When Agent Performs the Conference Call
		// - remove the old call Object 
		// - Add the New call Object
		char *called_devID = cstaEvent.event.cstaUnsolicited.u.conferenced.conferenceConnections.connection[0].party.deviceID;
		char *calling_devID = cstaEvent.event.cstaUnsolicited.u.conferenced.conferenceConnections.connection[2].party.deviceID;
		char *confer_devID = cstaEvent.event.cstaUnsolicited.u.conferenced.conferenceConnections.connection[1].party.deviceID;
		if ( cstaEvent.event.cstaUnsolicited.u.conferenced.localConnectionInfo == csConnect )
		{
			WORD newCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.conferenced.conferenceConnections.connection->party.callID;
			WORD oldCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.conferenced.primaryOldCall.callID;
			mes["newCallID"] = to_string(newCallID);
			mes["oldCallID"] = to_string(oldCallID);

		}
		DeviceID = called_devID;
		mes["called_devID"] = called_devID;
		mes["calling_devID"] = calling_devID;
		mes["confer_devID"] = confer_devID;

		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	}// end of Conferenced Event
	break;
	case CSTA_HELD :
	{
		usCallID = (WORD)cstaEvent.event.cstaUnsolicited.u.held.heldConnection.callID;
		char * holding_DevID = cstaEvent.event.cstaUnsolicited.u.held.heldConnection.deviceID;

		//删除active call map
		m_activeCall.erase(cstaEvent.event.cstaUnsolicited.u.held.heldConnection.deviceID);
		//添加held call map
		m_heldCall[cstaEvent.event.cstaUnsolicited.u.held.heldConnection.deviceID] = cstaEvent.event.cstaUnsolicited.u.held.heldConnection;

		if ( cstaEvent.event.cstaUnsolicited.u.held.localConnectionInfo == csHold)
		{
			//theApp.m_pAvayaCtiUIDlg->m_pCallManagerObject->UpdateCall(usCallID,caActive,conHold,holding_DevID,"","");
			mes["localConnectionInfo"] = "csHold";

		}
		DeviceID = holding_DevID;
		mes["usCallID"] = to_string(usCallID);
		mes["holding_DevID"] = holding_DevID;

		res = ReturnMes(mes);
	//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus.Append(res.c_str());
	//	m_pProducerObject->produce(res, stoi(DeviceID) % 10);
		theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
		theApp.m_pAvayaCtiUIDlg->	UpdateData(FALSE);
	}
	break;
	case CSTA_FAILED:
	{
		/*
		m_bIsAgtManuallyLogout = FALSE;
		if (m_bIsFailedEvent == FALSE)
		{
			MessageBox(CHK_DIALED_NUMBER);
		}
		else
		{
			MessageBox(CANT_LOGOUT_AGT);
		}
		*/
	}break;
	default:{}
	}// end of CSTAUNSOLICITED Switch
}




/// <summary>
// This function creates/opens an ACS Stream for the
// the application to interact with the TSAPI Service.
/// </summary>
/// <param name="serverID">AE Services Server ID</param>
/// <param name="loginID">LoginId for accessing AE Server</param>
/// <param name="password">LoginID Password for AE Server</param>
/// <returns></returns>
bool TSAPIInterface::OpenStream(TCHAR* serverID, TCHAR* loginID, TCHAR* password)
{
	bool bResult = FALSE;
	// attempt to open a stream to the selected AE server

	// A special function is used to convert version string into the format 
	// required by the acsOpenStream function.

	// The application can send a range (say ?-8? which specifies that 
	// the application is willing to work with the provided range of private Data
	// versions. The AE Server picks the highest version it can support and 
	// returns to the application

	strcpy_s(m_stPrivateData.vendor,"VERSION");
	m_stPrivateData.data[0]=PRIVATE_DATA_ENCODING;

	if(attMakeVersionString("3-8",&(m_stPrivateData.data[1])) > 0 )
	{
		m_stPrivateData.length = (unsigned short)strlen(&m_stPrivateData.data[1]) + 2;
	}
	else
	{
		m_stPrivateData.length = 0;
	}

	// Opening the ACS Stream, private data must be properly prepared before
	// using in acsOpenStream(...) method
	// The TSAPI service checks whether the requested version is supported or not. 
	// If it is not supported, then the TSAPI Service sends any private data in the acs confirmation event. 

	m_nRetCode = acsOpenStream(&m_lAcsHandle			// Handle for ACS Stream 
		, APP_GEN_ID			// APP_GEN_ID indicates Application generated invokeID's
		, (InvokeID_t)m_ulInvokeID  // By default 1
		, ST_CSTA
		, (ServerID_t *)(serverID)  // AE Server Name
		, (LoginID_t *)(loginID)	// CTI LoginID
		, (Passwd_t *)(password)  // CTI LoginID password
		, (AppName_t *)"TSAPI_AgentView"
		, ACS_LEVEL1
		, (Version_t *) "TS1-2" // private Data version in use 8 in our case
		, 10
		, 5 
		, 50
		, 5
		, (PrivateData_t *)&m_stPrivateData); // private Data.

	// no conf events are being processed yet, so don't wait for it yet...

	// set up event notification on this acs stream

	if (m_nRetCode < 0)
	{	
		//	m_ulInvokeID = 0;
		switch( m_nRetCode)
		{
		case ACSERR_BADHDL:	// ACS Handle (m_lAcsHandle) is Invalid
		case ACSERR_APIVERDENIED: // API version is invalid
		case ACSERR_BADPARAMETER:// One or more parameter is Invalid
		default: break;
		}
		bResult = false ;
	}
	else
	{
		// Method call is successful.

		// acsNotify method provides a mechanism for a window
		// based application to post a TSAPI message on the 
		// application message queue.
		
		m_nRetCode = acsEventNotify(m_lAcsHandle,		// Handle returned by acsOpenStream()
									this->GetSafeHwnd(),// The Handle of the window that 
														// will receive WM_TSAPIMSG Windows Messages.
									WM_TSAPIMSG,		// the type of Windows message to be
														// posted when an incoming event becomes
														// available.
									TRUE);				// if set to TRUE indicates that the 
													    // TSAPI Client library should send a 							     
														// WM_TSAPIMSG message per TSAPI event 
														// i.e., a message will be posted for 							     
														// every event. A FALSE would indicate 
														// that the TSAPI Client library would
														// post the message only when the event 
														// queue status changes from empty to 
														// non-empty

									
	
		if ( m_nRetCode == ACSPOSITIVE_ACK)
		{
			bResult = true ;
			// mehtod call is successful
		}
		else
		{
			switch(m_nRetCode)
			{
				// TSAPI CLient Library has rejected the request.
				// some error occured.
				// Error code is in m_nRetCode
				// handle error
			case ACSERR_BADHDL:
				{
					// Acshandle is Invalid
					bResult = false;
				}break;
			default:{bResult = false;}
			}
		}
	}
	
	return (bResult);
}// end of openStream function

// Closind the ACS Stream
// As invokeID is generated by Application.
// invokeID used in this function is the last invokeID used for the application.
bool TSAPIInterface ::CloseStream()
{
	bool bReturnValue = false;
	// If acsCloseStream() method is used then we will get confirmation or failure event, 
	// however in this case we do not want to receive confirmation event as our application
	// is going to exit.
	//m_nRetCode = acsCloseStream(m_lAcsHandle,++m_ulInvokeID,NULL);


	// If acsAbortStream() method is used we will not receive confirmation or failure event,
	// which is appropriate in this case as our application is getting closed.
	m_nRetCode = acsAbortStream(m_lAcsHandle, NULL);
	
	if ( m_nRetCode < 0 )
	{
		MessageBox(ERR_CLOSE_ACSSTREAM);
		switch(m_nRetCode)
			{
				// TSAPI CLient Library has rejected the request.
				// some error occured.
				// Error code is in m_nRetCode
				// handle error
			case ACSERR_BADHDL:
				{
					// AcsHandle is Invaslid
				}break;
			default:{break;}
			}
	}
	else
	{
		bReturnValue = true;
	}
	return bReturnValue;
}

/// <summary>
/// AgentState(Workode):
/// WorkMode defines in which mode agent's logs in 
/// Application allow two work mode Auto In and Manual
/// for Agent to log in.
/// In manual mode agent state become busy after clearing call
/// whereas in AutoIn mode Agent state remains to Ready state even after 
/// Agent clears the call.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID in this variable.</param>
///	<param name="agentID">Calling object will pass agent ID in this variable.</param>
/// <param name="agentPassword">Calling object will pass agent password in this variable.</param>
/// <param name="agentMode">Calling object will pass agent mode in this variable.</param>
/// <param name="workMode">Calling object will pass agent Work Mode in this variable.</param>
/// <returns>If successful returns true otherwise false.</returns>
bool TSAPIInterface::AgentLogin(DeviceID_t deviceID, AgentID_t agentID, AgentPassword_t agentPassword,
								AgentMode_t agentMode, int workMode)
{


	// this function is used here to set the work mode for Agent
	bool bResult = FALSE;
	if ( workMode == WM_AUTO_IN)
	{	// work mode used for logging an Agent with workMode Auto In
		m_nRetCode = attV6SetAgentState(&m_stPrivateData   // Private Data Buffer is prepared here
										,WM_AUTO_IN	       // Work Mode for the Agent, (Auto In)
										,0				   // Reason, code, this parameter is ignored 
														   // agentMode is AM_LOG_IN				
										,FALSE);		   // EnablePending flag, by default value is FALSE;
	}
	else if ( workMode == WM_MANUAL_IN )
	{	// work mode used for logging an Agent with workMode Manual
		m_nRetCode = attV6SetAgentState(&m_stPrivateData
											,WM_MANUAL_IN	// Manual In Work Mode
											,0
											,TRUE);
	}
	if (m_nRetCode == 0 ) 
	{
		m_nRetCode =  cstaSetAgentState(m_lAcsHandle				// handle returned by acsOpenStream
										,(InvokeID_t)++m_ulInvokeID // applicaiton generated invokedID
										,(DeviceID_t *)deviceID     // Extension on which Agent logs at
										,agentMode					// Agent mode (AM_LOG_IN)
										,(AgentID_t *)agentID		// ID with which Agent logs in
										,(AgentGroup_t *)""			// Huntgroup Extension (optional)
										,(AgentPassword_t *)agentPassword // Password with which Agent logs in
										,(PrivateData_t *)&m_stPrivateData); // private Data buffer, prepared above

		//binding InvokeID_t and deviceID,ActName
		m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;//(int)atoi()
		m_InvokeID2ActName[m_ulInvokeID] = "AgentLogin";

		if ( m_nRetCode < 0 )
		{
			bResult = false;
		}
		else
		{
			// Some error occurred while sending a request.
			// Error Code is in m_nRetCode.
			bResult = true;
		}

	}
	else
	{
		MessageBox(ERR_AGT_WORKMODE);
	}

	return (bResult);
}

/// <summary>
/// This method will logs out the Agent.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID in this variable.</param>
/// <param name="agentID">Calling object will pass agent ID in this variable.</param>
/// <param name="agentPassword">Calling object will pass agent password in this variable.</param>
/// <param name="agentMode">Calling object will pass agent mode in this variable.</param>
bool TSAPIInterface::AgentLogout(DeviceID_t deviceID, AgentID_t agentID, AgentPassword_t agentPassword, 
								 AgentMode_t agentMode)
{
	bool bResult;
	m_nRetCode =  cstaSetAgentState(m_lAcsHandle,(InvokeID_t)++m_ulInvokeID,(DeviceID_t *)deviceID,
		agentMode,(AgentID_t *)agentID, (AgentGroup_t *)"",(AgentPassword_t *)agentPassword,NULL);

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentLogout";

	if ( m_nRetCode < 0 )
	{
		// TSAPI client has rejected the request.
		switch(m_nRetCode)
		{
		case ACSERR_BADHDL: 
			{ 
				// AcsHandle is Invalid
				bResult = false;
			}break;
		default:
			{
				bResult = false;
			}break;
		}
	} // end of else
	else
	{
		// request is successful
		bResult = true;
	}
	return (bResult);
}

/// <summary>
/// This function helps in changing the Agent State from Ready to busy/Work Not Ready or vice-versa.
/// It also uses enablePending flag, that help in changing Agent's State to Busy or Work Not Ready
/// while Agent is attending a call.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID in this variable.</param>
/// <param name="agentID">Calling object will pass agent ID in this variable.</param>
/// <param name="agentPassword">Calling object will pass agent password in this variable.</param>
/// <param name="workMode">Calling object will pass agent Work Mode in this variable.</param>
/// <param name="agtMode">Calling object will pass agent mode in this variable.</param>
/// <param name="enablePending">Contain a true or false value depending on user selection on UI.</param>
void TSAPIInterface::AgentSetState(DeviceID_t deviceID,AgentID_t agentID, AgentPassword_t agentPassword, 
								   int workMode,char* agtMode, bool enablePending)
{

	// Setting enablePending Flag to TRUE/FALSE 
	// as per the user selection
	if ( enablePending )
	{
		m_nRetCode = attV6SetAgentState(&m_stPrivateData,(ATTWorkMode_t)workMode,1,enablePending);

		if ( m_nRetCode < 0 )
		{
			MessageBox("Error Setting the Enable Flag");
			//	return ;
		}
	}
	// Code snippet for Setting the Agent State to Ready / Not Ready / Busy( Work Not Ready)

	// READY is a string constant, thus cant be compared using Switch Case
	if ( strcmp(agtMode,READY) == 0 )
	{
		if ( workMode == WM_AUTO_IN)
		{
			// work mode used for logging an Agent with work mode Auto In
			m_nRetCode = attV6SetAgentState(&m_stPrivateData, WM_AUTO_IN, 0, TRUE);
		}
		else if (workMode == WM_MANUAL_IN )
		{	 // work mode used for logging an Agent with work mode Manual
			m_nRetCode = attV6SetAgentState(&m_stPrivateData,WM_MANUAL_IN, 0, TRUE);			
		}

		// Setting the work mode to Auto In

		if ( m_nRetCode == 0)
		{
			m_nRetCode =  cstaSetAgentState(m_lAcsHandle,(InvokeID_t)++m_ulInvokeID,(DeviceID_t *)deviceID,
				AM_READY,(AgentID_t *)agentID, (AgentGroup_t *)"",(AgentPassword_t *)agentPassword,
				(PrivateData_t *)&m_stPrivateData);

			if ( m_nRetCode < 0 )
			{
				MessageBox(ERR_AGT_SETSTATE);
				//	return;
			}
			else
			{
				// error occurred while changing Agent State
			}
		}
		else
		{
			// some error occurred while setting Agent's WorkMode.
		}
	}

	else if ( strcmp(agtMode,NOT_READY)==0 )
	{

		m_nRetCode =  cstaSetAgentState(m_lAcsHandle,(InvokeID_t)++m_ulInvokeID,(DeviceID_t *)deviceID,
			AM_NOT_READY,(AgentID_t *)agentID, (AgentGroup_t *)"",(AgentPassword_t *)agentPassword,
			(PrivateData_t *)&m_stPrivateData);

		if ( m_nRetCode < 0 )
		{
			MessageBox(ERR_AGT_SETSTATE);
			//	return;
		}
	}
	else if ( strcmp(agtMode,BUSY)==0)
	{
		m_nRetCode =  cstaSetAgentState(m_lAcsHandle,(InvokeID_t)++m_ulInvokeID,(DeviceID_t *)deviceID,
			AM_WORK_NOT_READY,(AgentID_t *)agentID, (AgentGroup_t *)"",(AgentPassword_t *)agentPassword,
			(PrivateData_t *)&m_stPrivateData);

		if ( m_nRetCode < 0 )
		{
			MessageBox(ERR_AGT_SETSTATE);
			//	return;
		}
	}

	// invokeID's are generated by the Application, using this
	// invokeID for checking the correct Agent State.
	// 暂时不校验返回事件
	//m_nAgtStateChangeInvokeID = m_ulInvokeID;
	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentSetState";
}


/// <summary>
/// This function helps in Answering an incoming call.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID of device where call has come in this variable.</param>
/// <param name="callID">Calling object will pass call ID which it want to answer in this variable.</param>
void TSAPIInterface ::AgentAnswerCall(DeviceID_t deviceID, long callID)
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = callID;
	m_nRetCode = cstaAnswerCall(m_lAcsHandle			// handle return by acsOpenStream method
								,(InvokeID_t)++m_ulInvokeID // application generated InvokedID
								,(ConnectionID_t *)&m_stConnectionID // Connection Identifier
								,NULL);					// Private Data is optional and set as NULL here
	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentAnswerCall";

	if ( m_nRetCode < 0)
	{
		// TSAPI Client Library has rejected the request.
		// either one or More parameter bad or AcsHandle is Invalid
		switch(m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// Acshandle is Invalid
		}break;
		case ACSERR_BADPARAMETER:
			{
				// One or More parameter is Invalid.
			}
		default:{break;}
		}
	}
	else
	{
		// TSAPI Client has accepted the Request
	}

}

/// <summary>
/// This function helps in clear device in a call connection.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID of device where call has come in this variable.</param>
/// <param name="callID">Calling object will pass call ID which it want to answer in this variable.</param>
void TSAPIInterface::AgentClearConnection(DeviceID_t deviceID, long callID)
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = callID;
	m_nRetCode = cstaClearConnection(m_lAcsHandle			// handle return by acsOpenStream method
		, (InvokeID_t)++m_ulInvokeID // application generated InvokedID
		, (ConnectionID_t *)&m_stConnectionID // Connection Identifier
		, NULL);					// Private Data is optional and set as NULL here
	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentClearConnection";

	if (m_nRetCode < 0)
	{
		// TSAPI Client Library has rejected the request.
		// either one or More parameter bad or AcsHandle is Invalid
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// Acshandle is Invalid
		}break;
		case ACSERR_BADPARAMETER:
		{
			// One or More parameter is Invalid.
		}
		default: {break; }
		}
	}
	else
	{
		// TSAPI Client has accepted the Request
	}

}

/// <summary>
/// This function helps in disconnecting established call.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID of device where call has come in this variable.</param>
/// <param name="callID">Calling object will pass call ID which it want to answer in this variable.</param>
void TSAPIInterface::AgentDisconnectCall(DeviceID_t deviceID, long callID)
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = callID;
	m_nRetCode = cstaClearConnection(m_lAcsHandle	// handle returned by the acsOpenStream()
									,(InvokeID_t)++m_ulInvokeID // application generated invokeID
									,(ConnectionID_t *)&m_stConnectionID // connection Identifier of connected call
									,NULL); // private data is optional and is set as NULL here.

	// preserve the Invoke for matching with the confirmation event.
	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentDisconnectCall";

	if ( m_nRetCode < 0 )
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch(m_nRetCode)
		{
		case ACSERR_BADHDL:
			{// AcsHandle is Invalid
			}
		default:{MessageBox(ERR_DISCONNECT_CALL);}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
}


void TSAPIInterface::AgentMakeCall(DeviceID_t callingDevice, DeviceID_t calledDevice)
{
	m_nRetCode = cstaMakeCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		//, (DeviceID_t *)&callingDevice 
		//, (DeviceID_t *)&calledDevice 
		, (DeviceID_t *)callingDevice
		, (DeviceID_t *)calledDevice
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = callingDevice;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentMakeCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default: 
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
}

void TSAPIInterface::AgentHoldCall(DeviceID_t deviceID, long callID)
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = callID;

	m_nRetCode = cstaHoldCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		, (ConnectionID_t *)&m_stConnectionID
		, true
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentHoldCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
}

void TSAPIInterface::AgentRetrieveCall(DeviceID_t deviceID, long callID)//hold to connect
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = callID;

	m_nRetCode = cstaRetrieveCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		, (ConnectionID_t *)&m_stConnectionID
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentRetrieveCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
}

void TSAPIInterface::AgentConferenceCall(DeviceID_t checkedDeivce , DeviceID_t deviceId)
{
	//ConnectionID_t m_heldConnectionID;
	//strcpy((char *)&m_heldConnectionID.deviceID, (char *)deviceID);
	//m_heldConnectionID.callID = heldCall;
	//m_heldConnectionID.devIDType = STATIC_ID;
	ConnectionID_t m_heldConnectionID = m_heldCall[checkedDeivce];
	//ConnectionID_t m_activeConnectionID;
	//strcpy((char *)&m_activeConnectionID.deviceID, (char *)deviceID);
	//m_activeConnectionID.callID = activeCall;
	//m_activeConnectionID.devIDType = STATIC_ID;
	ConnectionID_t m_activeConnectionID = m_activeCall[checkedDeivce];
	m_nRetCode = cstaConferenceCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, ++m_ulInvokeID // application generated invokeID
		, &m_heldConnectionID
		, &m_activeConnectionID
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = to_string(*checkedDeivce);
	m_InvokeID2ActName[m_ulInvokeID] = "AgentConferenceCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}

}

void TSAPIInterface::AgentConsultationCall(DeviceID_t deviceId ,DeviceID_t calledDevice)//两方求助电话
{

	//ConnectionID_t m_stConnectionID;
	//m_stConnectionID.devIDType = STATIC_ID;
	//strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	//m_stConnectionID.callID = activeCall;
	ConnectionID_t m_stConnectionID = m_activeCall[deviceId];

	m_nRetCode = cstaConsultationCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, ++m_ulInvokeID // application generated invokeID
		, &m_stConnectionID
		, (DeviceID_t *)calledDevice    //calledDevice
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceId;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentConsultationCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}

}

void TSAPIInterface::AgentDeflectCall(DeviceID_t deviceID, long activeCall, DeviceID_t calledDevice)//电话转移
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;
	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	m_stConnectionID.callID = activeCall;

	m_nRetCode = cstaDeflectCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		, (ConnectionID_t *)&m_stConnectionID
		, (DeviceID_t *)&calledDevice    //calledDevice
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentDeflectCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
		//打印请求成功消息

	}
}

void TSAPIInterface::AgentPickupCall(DeviceID_t deviceID, long activeCall, DeviceID_t calledDevice)//电话代接
{
	ConnectionID_t m_stConnectionID;
	m_stConnectionID.devIDType = STATIC_ID;// DYNAMIC_ID;
//	strcpy((char *)&m_stConnectionID.deviceID, (char *)deviceID);
	lstrcpy(m_stConnectionID.deviceID, deviceID);
	m_stConnectionID.callID = activeCall;


	ConnectionID_t *connectionId = &m_stConnectionID;
	DeviceID_t *newDevice;
	newDevice = (DeviceID_t*)calledDevice;

	m_nRetCode = cstaPickupCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, ++m_ulInvokeID // application generated invokeID
		, connectionId
		, newDevice    //calledDevice
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentPickupCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
		//打印请求成功消息

	}
}

void TSAPIInterface::AgentTransferCall(DeviceID_t deviceID, long heldCall, long activeCall)//电话转移（已接）（成功转）
{
	ConnectionID_t m_heldConnectionID;
	strcpy((char *)&m_heldConnectionID.deviceID, (char *)deviceID);
	m_heldConnectionID.callID = heldCall;

	ConnectionID_t m_activeConnectionID;
	strcpy((char *)&m_activeConnectionID.deviceID, (char *)deviceID);
	m_activeConnectionID.callID = activeCall;

	m_nRetCode = cstaReconnectCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		, (ConnectionID_t *)&m_heldConnectionID
		, (ConnectionID_t *)&m_activeConnectionID
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentTransferCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
		//打印请求成功消息

	}
}

void TSAPIInterface::AgentReconnectCall(DeviceID_t deviceID, long heldCall, long activeCall)//从两方求助状态重连电话
{
	ConnectionID_t m_heldConnectionID;
	strcpy((char *)&m_heldConnectionID.deviceID, (char *)deviceID);
	m_heldConnectionID.callID = heldCall;

	ConnectionID_t m_activeConnectionID;
	strcpy((char *)&m_activeConnectionID.deviceID, (char *)deviceID);
	m_activeConnectionID.callID = activeCall;

	m_nRetCode = cstaReconnectCall(m_lAcsHandle	// handle returned by the acsOpenStream()
		, (InvokeID_t)++m_ulInvokeID // application generated invokeID
		, (ConnectionID_t *)&m_heldConnectionID
		, (ConnectionID_t *)&m_activeConnectionID
		, NULL); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentReconnectCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
		//打印请求成功消息

	}

}
/// <summary>
/// This function help to retrieve the Current Status of the Agent.
/// Agent State of Agent can be 
/// i) Ready ii) Not Ready iii) Busy
/// </summary>
/// <param name="deviceID">Calling object will pass device ID of device whose status it wants to query
/// in this variable.</param>
void TSAPIInterface:: QueryAgentStatus(DeviceID_t deviceID)
{
	m_nRetCode = cstaQueryAgentState(m_lAcsHandle // handle returned by the acsOpenStream
									,(InvokeID_t)++m_ulInvokeID // Application generated InvokeID
									, (DeviceID_t *)deviceID // Id of device on which Agent logs.
									, NULL); // private data is optional and set as NUll here.

	m_InvokeID2DeviceID[m_ulInvokeID] = deviceID;
	m_InvokeID2ActName[m_ulInvokeID] = "QueryAgentStatus";

	if( m_nRetCode < 0 )
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch(m_nRetCode)
		{
		case ACSERR_BADHDL:
			{// AcsHandle is Invalid
			}
		default:{MessageBox(ERR_QUERY_AGTSTATE);}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
		
}

/// <summary>
/// Function for adding the monitor at the Agent Terminal.
/// </summary>
/// <param name="deviceID">Calling object will pass device ID of device where monitor needs to be added
/// in this variable.</param>

void TSAPIInterface :: StartMonitor(DeviceID_t deviceID)
{
	// The Agent Filter, Feature Filter, and Maintenance Filter are not supported 
	// in Avaya CSTA implementation. If one of these is present, it will be 
	// ignored.
	CSTAMonitorFilter_t m_noFilter;

	m_noFilter.call = 0;
	// By setting no private filter, all private Events will be received
	m_noFilter.privateFilter = 0;

	// Storage for the Return code from the method

	m_nRetCode = cstaMonitorDevice(m_lAcsHandle,  // handle returned by acsOpenStream method.
									(InvokeID_t)++m_ulInvokeID, // application generated invokeID
									(DeviceID_t *)deviceID,		// ID of the device(Station) to be monitored
									&m_noFilter,  // Filter setting that will apply on the monitor. Set to 0
											      // to receive all events 
									NULL);        // This Private Data Parameter is optional here, and passed as NULL here.
	
	// store the Invoked associated with the monitor request.
	if( m_nRetCode < 0)
	{
		// Some error occurred, TSAPI Client Library rejected the request.
		
		switch( m_nRetCode )
		{
		case ACSERR_BADHDL:
			{ 
				// m_lAcsHandle is Invalid 
			}break;
		case ACSERR_BADPARAMETER:
			{
				// One or More parameter are Invalid
			}break;
		default:{break;}
		}// End of Switch

		MessageBox(ERR_ADD_MONITOR);
		// handle error
	}
	else
	{
		// Method call is successfull, 
		// TSAPI Client Library has accepted the request.
	}
}

// This function removes the monitor
void TSAPIInterface::StopMonitor(CSTAMonitorCrossRefID_t m_lMonitorCrossRefID)
{
	m_nRetCode = cstaMonitorStop (m_lAcsHandle		// handle returned by the acsOpenStream
								,(InvokeID_t)++m_ulInvokeID // application generated invokeID
								,m_lMonitorCrossRefID // Reference ID of the active monitor
								,NULL); // This Private Data Parameter is optional here, and passed as NULL here.

	if ( m_nRetCode < 0 )
	{
		switch( m_nRetCode )
		{
		case ACSERR_BADHDL:
			{ 
				// m_lAcsHandle is Invalid 
			}break;
		default:{break;}
		}
	}
	else {
	
	}
}

//This function get the device  information about calls associated with a given CSTA device
void TSAPIInterface::SnapshotDevice(DeviceID_t deviceId) {
	/* cstaSnapshotDeviceReq() - Service Request */
	DeviceID_t *snapshotObj;
	snapshotObj = (DeviceID_t*)deviceId;



	m_nRetCode = cstaSnapshotDeviceReq(
		m_lAcsHandle,
		++m_ulInvokeID, // application generated invokeID
		snapshotObj,
		NULL);

	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else {

	}
	m_InvokeID2DeviceID[m_ulInvokeID] = deviceId;//(int)atoi()
	m_InvokeID2ActName[m_ulInvokeID] = "AgentSnapshotDevice";
}

//This function monitor the talking device 
void TSAPIInterface::SingleStepConferenceCall(DeviceID_t checkedDevice,DeviceID_t device, ATTParticipationType_t type) {
	/* cstaSnapshotDeviceReq() - Service Request */
	DeviceID_t* deviceToBeJoin=(DeviceID_t*)device;

	ConnectionID_t *activeCall =&(m_activeCall[checkedDevice]);

	m_nRetCode = attSingleStepConferenceCall(
		&m_stPrivateData,
		activeCall, /* mandatory */
		deviceToBeJoin, /* mandatory */
		type,
		0);

	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else {
		m_nRetCode =  cstaEscapeService(
			m_lAcsHandle,
			++m_ulInvokeID,
			(PrivateData_t *)&m_stPrivateData);
	}
	m_InvokeID2DeviceID[m_ulInvokeID] = device;//(int)atoi()
	m_InvokeID2ActName[m_ulInvokeID] = "SingleStepConferenceCall";
}

void TSAPIInterface::SingleStepTransferCall(DeviceID_t calledDevice, DeviceID_t checkedDevice) {
	
	ConnectionID_t *activeCall = &(m_activeCall[checkedDevice]);
	m_nRetCode = attSingleStepTransferCall(
		&m_stPrivateData,
		activeCall,
		(DeviceID_t *)calledDevice
	);
	if (m_nRetCode < 0)
	{
		MessageBox("Error Setting the Private Data");
		return;
	}

	m_nRetCode = cstaEscapeService(m_lAcsHandle	// handle returned by the acsOpenStream()
		,++m_ulInvokeID // application generated invokeID
		, (PrivateData_t *)&m_stPrivateData
	); // private data is optional and is set as NULL here.

	m_InvokeID2DeviceID[m_ulInvokeID] = checkedDevice;
	m_InvokeID2ActName[m_ulInvokeID] = "AgentSingleStepTransferCall";

	if (m_nRetCode < 0)
	{
		// TSAPI Client has rejected the request.
		// The error code is in m_nRetCode;
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{// AcsHandle is Invalid
		}
		default:
		{

		}
		}
	}
	else
	{
		// TSAPI Client has accepted the request.
	}
}

void TSAPIInterface::RouteEndInv(RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID)
{
	m_nRetCode = cstaRouteEndInv(
		m_lAcsHandle,
		(InvokeID_t)++m_ulInvokeID, // application generated invokeID
		routeRegisterReqID,//
		routingCrossRefID,//This is the routing dialog that the application is terminating.
		(CSTAUniversalFailure_t)GENERIC_UNSPECIFIED,//errorValue,
		NULL);// private data is optional and is set as NULL here.


	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else {

	}
	m_InvokeID2DeviceID[m_ulInvokeID] = routingCrossRefID;//terminating 
	m_InvokeID2ActName[m_ulInvokeID] = "RouteEndInv";
}

void TSAPIInterface::RouteRegisterCancel(RouteRegisterReqID_t routeRegisterReqID)
{
	m_nRetCode = cstaRouteRegisterCancel(
		m_lAcsHandle,
		(InvokeID_t)++m_ulInvokeID, // application generated invokeID
		routeRegisterReqID,
		NULL);// private data is optional and is set as NULL here.
	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else {

	}
	m_InvokeID2DeviceID[m_ulInvokeID] = routeRegisterReqID; 
	m_InvokeID2ActName[m_ulInvokeID] = "RouteRegisterCancel";
}


void TSAPIInterface::RouteRegister(DeviceID_t * routingDevice)
{

	m_nRetCode = cstaRouteRegisterReq(
		m_lAcsHandle,
		(InvokeID_t)++m_ulInvokeID, // application generated invokeID
		routingDevice,
		NULL);// private data is optional and is set as NULL here.


	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else {

	}
	m_InvokeID2DeviceID[m_ulInvokeID] = *routingDevice; 
	m_InvokeID2ActName[m_ulInvokeID] = "RouteRegister";
}

void TSAPIInterface::RouteSelectInv(RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID, 
	DeviceID_t *routeSelected, RetryValue_t remainRetry, SetUpValues_t *setupInformation, Boolean routeUsedReq, PrivateData_t *privateData)
{
	m_nRetCode = cstaRouteSelectInv(
		m_lAcsHandle,
		(InvokeID_t)++m_ulInvokeID, // application generated invokeID
		routeRegisterReqID,//包含应用程序提供路由服务的路由注册会话的句柄。 路由服务器应用程序在 cstaRouteRegisterReq () 请求的 CSTARouteRegister ReqConfEvent 确认中接收到此句柄。
		routingCrossRefID,//包含此调用的路由会话的句柄。应用程序以前在调用的 CSTARoute-RequestExtEvent 中接收到此句柄。
		routeSelected, //指定调用的目标。
		remainRetry,//指定当交换机需要请求备用路由时, 应用程序愿意接收此调用的 CSTARouteRequestExtEvent 的次数。
		setupInformation,//包含一个已修改的 ISDN 呼叫设置消息, 交换机将使用它来路由呼叫。
		routeUsedReq,//指示接收 CSTARoute UsedExtEvent 的请求。
		privateData);


	if (m_nRetCode < 0)
	{
		switch (m_nRetCode)
		{
		case ACSERR_BADHDL:
		{
			// m_lAcsHandle is Invalid 
		}break;
		default: {break; }
		}
	}
	else 
	{

	}
	m_InvokeID2DeviceID[m_ulInvokeID] = *routeSelected;
	m_InvokeID2ActName[m_ulInvokeID] = "RouteSelectInv";
}


////
string TSAPIInterface::ReturnMes(map<string, string>mes)
{
	Json::Value value;
	Json::FastWriter writer;
	string res;
	if (mes.empty())
	{
		//打印错误
		return res;
	}
	else
	{
		for (auto iter = mes.begin(); iter != mes.end(); iter++)
		{
			value[iter->first] = iter->second;
		}
		res = writer.write(value);
	}
	return res;
}
