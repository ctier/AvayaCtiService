#include "stdafx.h"
#include "AvayaCallCenterRouting.h"
#include "AvayaCtiService.h"

AvayaCallCenterRouting::AvayaCallCenterRouting()
{
	init();
}
bool AvayaCallCenterRouting::init()
{
	//创建MySQLInterface对象
	m_pMySQLInterface = MySQLInterface::GetInstance();

	char* server = "localhost";
	char* username = "root";
	char* password = "6020561"; 
	char* database = "ctidb"; 
	int port = 3306;
	m_pMySQLInterface->SetMySQLConInfo(server, username, password, database, port);
	string mes = m_pMySQLInterface->Open();
	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + mes.c_str() + "\r\n";
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);


	// get the TSAPIInterface Object
	m_pTsapiInterfaceObject = TSAPIInterface::GetInstance();

	return true;
}

AvayaCallCenterRouting::~AvayaCallCenterRouting()
{
	m_pMySQLInterface->Close();
	delete m_pMySQLInterface;
}

//？ 什么时候发，谁调用
void AvayaCallCenterRouting::RouteEndInv(RouteRegisterReqID_t RouteRegisterReqID, RoutingCrossRefID_t RoutingCrossRefID)
{
	m_pTsapiInterfaceObject->RouteEndInv(RouteRegisterReqID, RoutingCrossRefID);
}

void AvayaCallCenterRouting::RouteRegisterCancel(RouteRegisterReqID_t RouteRegisterReqID)
{
	m_pTsapiInterfaceObject->RouteRegisterCancel(RouteRegisterReqID);
}

void AvayaCallCenterRouting::RouteRegister(DeviceID_t* routingDevice)
{
	m_pTsapiInterfaceObject->RouteRegister(routingDevice);
}

void AvayaCallCenterRouting::RouteSelectInv(RouteRegisterReqID_t routeRegisterReqID, RoutingCrossRefID_t routingCrossRefID,
	DeviceID_t *routeSelected, RetryValue_t remainRetry, SetUpValues_t *setupInformation, Boolean routeUsedReq, PrivateData_t *privateData)
{
	m_pTsapiInterfaceObject->RouteSelectInv(routeRegisterReqID, routingCrossRefID,
		routeSelected, remainRetry, setupInformation, routeUsedReq, privateData);
}

string AvayaCallCenterRouting::InsertNumber(const char *telephonenumber,const char *type)
{
	//,'ADDTIME'
	string Request = "INSERT INTO NUMBERLIST(NUMBER,TYPE,ADDTIME) VALUES('";
	string time = theApp.m_pAvayaCtiUIDlg->GetTimeStr();
	Request += telephonenumber;
	Request += "','";
	Request += type;
	Request += "','";
	Request += time;
	Request += "')";
	return m_pMySQLInterface->Insert(Request);
}

string AvayaCallCenterRouting::DeleteNumber(const char *telephonenumber)
{
	string Request = "DELETE FROM NUMBERLIST WHERE NUMBER = '";
	Request += telephonenumber;
	Request += "'";
	return m_pMySQLInterface->Delete(Request);
}

string AvayaCallCenterRouting::UpdataNumber(const char *telephonenumber, const char *type)
{
	string Request = "UPDATE NUMBERLIST SET TYPE = '";
	Request += type;
	Request += "' WHERE NUMBER = '";
	Request += telephonenumber;
	Request += "'";
	return m_pMySQLInterface->Updata(Request);
}

string AvayaCallCenterRouting::SelectNumber(const char *telephonenumber, vector<string>& data)
{
	string Request = "SELECT * FROM NUMBERLIST WHERE NUMBER = '";
	Request += telephonenumber;
	Request += "'";
	return m_pMySQLInterface->SelectOneLine(Request, data);
}

void AvayaCallCenterRouting::RouteRequestExtEvent(CSTARouteRequestExtEvent_t routeRequestExt, ATTPrivateData_t privateData)////
{
	CallingDeviceID_t callingDevice = routeRequestExt.callingDevice;//指定调用起始设备
	string callingDeviceID = callingDevice.deviceID;//主叫号码
	CalledDeviceID_t currentRoute = routeRequestExt.currentRoute;//指定调用的目标
	string calledDeviceID = currentRoute.deviceID;//被叫号码


	//RouteRegisterReqID_t routeRegisterReqID = routeRequestExt.routeRegisterReqID;//路由服务的路由注册会话的句柄
	routeRegisterReqID = routeRequestExt.routeRegisterReqID;
	//routeRegisterReqID = 	theApp.m_pAvayaCtiUIDlg->m_pTSAPIInterface->m_DeviceID2RouteRegisterReqID[callingDevice];

	RoutingCrossRefID_t routingCrossRefID = routeRequestExt.routingCrossRefID;//路由会话的唯一句柄
	ConnectionID_t routedCall = routeRequestExt.routedCall;//指定要路由的调用的 callID。 这是路由设备 connectionID 的路由调用。
	SelectValue_t routedSelAlgorithm = routeRequestExt.routedSelAlgorithm;//指示所请求的路由算法的类型。它被设置为 SV_NORMAL。
	unsigned char priority = routeRequestExt.priority;//指示调用的优先级
	SetUpValues_t setupInformation = routeRequestExt.setupInformation;//包含 ISDN 呼叫设置消息

	ATTEvent_t att_event;
	/*
	if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ATT_ROUTE_REQUEST)
	{
		att_event.u.routeRequest;
	}
	*/
	//根据  指定要路由的调用的 callID  ,在数据库中查询，分情况对调用callID进行操作
	string callID = to_string(routedCall.callID);
	const char* telephonenumber = callID.c_str();
	vector<string> data;
	string error = SelectNumber(telephonenumber, data);
	ATTPrivateData_t m_stPrivateData;	

	if (data[2] == "VIP")
	{
		//RetCode_t m_nRetCode = attV6RouteSelect(&m_stPrivateData, WM_AUTO_IN, 0, TRUE);

		RouteSelectInv(
			routeRegisterReqID,
			routingCrossRefID,
			(DeviceID_t *)currentRoute.deviceID,
			1,
			&setupInformation,
			TRUE,
			NULL);
			//(PrivateData_t *)&m_stPrivateData);
	}
	else if (data[2] == "黑名单")
	{
		//不选？
	}
	else//普通
	{

		RouteSelectInv(
			routeRegisterReqID,
			routingCrossRefID,
			(DeviceID_t *)currentRoute.deviceID,
			1,
			&setupInformation,
			TRUE,
			NULL);
	}
//	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + DeviceID.c_str() + " : 注册成功" + "\r\n";
//	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);

}

void AvayaCallCenterRouting::RouteEndEvent(CSTARouteEndEvent_t routeEnd)
{
	map<string, string> mes;

	RouteRegisterReqID_t routeRegisterReqID = routeEnd.routeRegisterReqID;
	RoutingCrossRefID_t routingCrossRefID = routeEnd.routingCrossRefID;//请求路由到的坐席ID,在CSTARouteRequestExtEvent中收到该句柄
	CSTAUniversalFailure_t errorValue = routeEnd.errorValue;
	if (errorValue == 0)
	{
		mes["error"] = "GENERIC_UNSPECIFIED";
	}
	else if (errorValue == 41)
	{
		mes["error"] = "GENERIC_SUBSCRIBED_RESOURCE_AVAILABILITY";
	}//...

}


void AvayaCallCenterRouting::RouteRegisterAbortEvent(CSTARouteRegisterAbortEvent_t registerAbort)
{
	RouteRegisterReqID_t routeRegisterReqID = registerAbort.routeRegisterReqID;
	//写入数据库  发送监控

}

void AvayaCallCenterRouting::RouteUsedExtEvent(CSTARouteUsedExtEvent_t routeUsedExt)
{
	RouteRegisterReqID_t routeRegisterReqID = routeUsedExt.routeRegisterReqID;
	RoutingCrossRefID_t routingCrossRefID = routeUsedExt.routingCrossRefID;
	CalledDeviceID_t routeUsed = routeUsedExt.routeUsed;
	CallingDeviceID_t callingDevice = routeUsedExt.callingDevice;
	unsigned char domain = routeUsedExt.domain;
	/*
	ATTEvent_t att_event;
	
	if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ATT_ROUTE_USED)
	{
		char* destRoute = att_event.u.routeUsed.destRoute;//指定非 PBX 目的地的 TAC/ARS/AAR 信息。
	}
	*/

	//?除了确认 事件 还有什么用
	//写入数据库  发送监控

}

