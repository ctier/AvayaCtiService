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

	HINSTANCE hInst = AfxGetInstanceHandle();
	char szFileName[MAX_PATH];
	GetModuleFileName(hInst, szFileName, MAX_PATH);
	CString filename = szFileName;
	filename.TrimRight("AvayaCtiService.exe");
	filename.Append("Settings.ini");


	CFileFind fileFind;

	char* server;
	char* username;
	char* password;
	char* database;
	int port;

	if (fileFind.FindFile(filename) == FALSE)
	{
		char msg[512];
		sprintf_s(msg, "%s%s", filename,
			FILE_NOT_FOUND);
		::MessageBox(NULL, msg, "File Not Found Error", MB_OK);
	}
	else
	{
		TCHAR m_szServerID[BUFFER_SIZE];		// ServerID of CtiDB
		TCHAR m_szUsername[BUFFER_SIZE];		// Username for accessing CtiDB
		TCHAR m_szPassword[BUFFER_SIZE];		// Username Password for CtiDB
		TCHAR m_szDatabase[BUFFER_SIZE];		// CtiDB
		TCHAR m_szPort[BUFFER_SIZE];			// port

		// GetPrivateProfileString(...) is used for reteriving values from the Settings.ini file
		GetPrivateProfileString("RoutingDB", "server", "", m_szServerID, sizeof(m_szServerID), filename);
		GetPrivateProfileString("RoutingDB", "username", "", m_szUsername, sizeof(m_szUsername), filename);
		GetPrivateProfileString("RoutingDB", "password", "", m_szPassword, sizeof(m_szPassword), filename);
		GetPrivateProfileString("RoutingDB", "database", "", m_szDatabase, sizeof(m_szDatabase), filename);
		GetPrivateProfileString("RoutingDB", "port", "", m_szPort, sizeof(m_szPort), filename);

		server = m_szServerID;
		username = m_szUsername;
		password = m_szPassword;
		database = m_szDatabase;
		port = atoi(m_szPort);
	}

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


void AvayaCallCenterRouting::RouteEndInv(RouteRegisterReqID_t RouteRegisterReqID, RoutingCrossRefID_t RoutingCrossRefID)
{
	m_pTsapiInterfaceObject->RouteEndInv(RouteRegisterReqID, RoutingCrossRefID);
}

void AvayaCallCenterRouting::RouteRegisterCancel(DeviceID_t routingDevice)
{
	m_pTsapiInterfaceObject->RouteRegisterCancel(routingDevice);
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
	RouteRegisterReqID_t routeRegisterReqID = routeRequestExt.routeRegisterReqID;

	RoutingCrossRefID_t routingCrossRefID = routeRequestExt.routingCrossRefID;//路由会话的唯一句柄
	m_DeviceID2RoutingCrossRefID[calledDeviceID] = to_string(routingCrossRefID);

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
			(DeviceID_t *)currentRoute.deviceID,//被叫号码
			1,
			&setupInformation,
			TRUE,
			NULL);
			//(PrivateData_t *)&m_stPrivateData);
	}
	else if (data[2] == "黑名单")
	{
		//
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

void AvayaCallCenterRouting::RouteEndEvent(CSTAEvent_t cstaEvent)
{
	map<string, string> mes;
	string DeviceID = theApp.m_pAvayaCtiUIDlg->m_pTSAPIInterface->m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];

	RouteRegisterReqID_t routeRegisterReqID = cstaEvent.event.cstaEventReport.u.routeEnd.routeRegisterReqID;
	RoutingCrossRefID_t routingCrossRefID = cstaEvent.event.cstaEventReport.u.routeEnd.routingCrossRefID;//请求路由到的坐席ID,在CSTARouteRequestExtEvent中收到该句柄
	CSTAUniversalFailure_t errorValue = cstaEvent.event.cstaEventReport.u.routeEnd.errorValue;
	if (errorValue == 0)
	{
		mes["error"] = "GENERIC_UNSPECIFIED";
	}
	else if (errorValue == 41)
	{
		mes["error"] = "GENERIC_SUBSCRIBED_RESOURCE_AVAILABILITY";
	}//...
	string res = theApp.m_pAvayaCtiUIDlg->m_pTSAPIInterface->ReturnMes(mes);

	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + res.c_str() + "\r\n";
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
	m_DeviceID2RoutingCrossRefID.erase(DeviceID);
}


void AvayaCallCenterRouting::RouteRegisterAbortEvent(CSTAEvent_t& cstaEvent)
{
	string DeviceID = theApp.m_pAvayaCtiUIDlg->m_pTSAPIInterface->m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];
	m_DeviceID2RouteRegisterReqID.erase(DeviceID);
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

	//写入数据库  发送监控

}

void AvayaCallCenterRouting::RouteRequestReqConfEvent(CSTAEvent_t cstaEvent, ATTPrivateData_t privateData)
{
	RouteRegisterReqID_t m_routeRegisterReqID = cstaEvent.event.cstaConfirmation.u.routeRegister.registerReqID;
	string DeviceID = theApp.m_pAvayaCtiUIDlg->m_pTSAPIInterface->m_InvokeID2DeviceID[cstaEvent.event.cstaConfirmation.invokeID];
	m_DeviceID2RouteRegisterReqID[DeviceID] = to_string(m_routeRegisterReqID);//
	theApp.m_pAvayaCtiUIDlg->m_strAgentStatus = theApp.m_pAvayaCtiUIDlg->m_strAgentStatus + DeviceID.c_str() + " : 注册成功" + "\r\n";
	theApp.m_pAvayaCtiUIDlg->UpdateData(FALSE);
}
