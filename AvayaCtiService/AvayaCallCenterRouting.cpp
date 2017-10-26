#include "stdafx.h"
#include "AvayaCallCenterRouting.h"
#include "AvayaCtiService.h"

AvayaCallCenterRouting::AvayaCallCenterRouting()
{
	init();
}
bool AvayaCallCenterRouting::init()
{
	//����MySQLInterface����
	m_pMySQLInterface = MySQLInterface::GetInstance();

	char* server = "localhost";
	char* username = "root";
	char* password = "9201"; 
	char* database = "ctidb"; 
	int port = 3306;
	m_pMySQLInterface->SetMySQLConInfo(server, username, password, database, port);
	// get the TSAPIInterface Object
	m_pTsapiInterfaceObject = TSAPIInterface::GetInstance();
	return true;
}

AvayaCallCenterRouting::~AvayaCallCenterRouting()
{
	m_pMySQLInterface->Close();
	delete m_pMySQLInterface;
}

//�� ʲôʱ�򷢣�˭����
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
	string Query = "INSERT INTO NUMBERLIST('NUMBER','TYPE') VALUES('";
	Query += telephonenumber;
	Query += "','";
	Query += type;
	Query += "')";
	return m_pMySQLInterface->Insert(Query);
}

string AvayaCallCenterRouting::DeleteNumber(const char *telephonenumber)
{
	string Query = "DELETE FROM NUMBERLIST WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->Delete(Query);
}

string AvayaCallCenterRouting::UpdataNumber(const char *telephonenumber, const char *type)
{
	string Query = "UPDATE NUMBERLIST SET TYPE = '";
	Query += type;
	Query += "' WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->Updata(Query);
}

string AvayaCallCenterRouting::SelectNumber(const char *telephonenumber, vector<string>& data)
{
	string Query = "SELECT * FROM NUMBERLIST WHERE NUMBER = '";
	Query += telephonenumber;
	Query += "'";
	return m_pMySQLInterface->SelectOneLine(Query, data);
}

void AvayaCallCenterRouting::RouteRequestExtEvent(CSTARouteRequestExtEvent_t routeRequestExt, ATTPrivateData_t privateData)
{
	RouteRegisterReqID_t routeRegisterReqID = routeRequestExt.routeRegisterReqID;//·�ɷ����·��ע��Ự�ľ��
	RoutingCrossRefID_t routingCrossRefID = routeRequestExt.routingCrossRefID;//·�ɻỰ��Ψһ���
	CalledDeviceID_t currentRoute = routeRequestExt.currentRoute;//ָ�����õ�Ŀ��
	CallingDeviceID_t callingDevice = routeRequestExt.callingDevice;//ָ��������ʼ�豸
	ConnectionID_t routedCall = routeRequestExt.routedCall;//ָ��Ҫ·�ɵĵ��õ� callID�� ����·���豸 connectionID ��·�ɵ��á�
	SelectValue_t routedSelAlgorithm = routeRequestExt.routedSelAlgorithm;//ָʾ�������·���㷨�����͡���������Ϊ SV_NORMAL��
	unsigned char priority = routeRequestExt.priority;//ָʾ���õ����ȼ�
	SetUpValues_t setupInformation = routeRequestExt.setupInformation;//���� ISDN ����������Ϣ

	ATTEvent_t att_event;

	if (attPrivateData((ATTPrivateData_t *)&privateData, &att_event) == ATT_ROUTE_REQUEST)
	{
		att_event.u.routeRequest;
	}

	//����  ָ��Ҫ·�ɵĵ��õ� callID  ,�����ݿ��в�ѯ��������Ե���callID���в���
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
	else if (data[2] == "������")
	{
		//��ѡ��
	}
	else//��ͨ
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

}

void AvayaCallCenterRouting::RouteEndEvent(CSTARouteEndEvent_t routeEnd)
{
	map<string, string> mes;

	RouteRegisterReqID_t routeRegisterReqID = routeEnd.routeRegisterReqID;
	RoutingCrossRefID_t routingCrossRefID = routeEnd.routingCrossRefID;//����·�ɵ�����ϯID,��CSTARouteRequestExtEvent���յ��þ��
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
	//д�����ݿ�  ���ͼ��

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
		char* destRoute = att_event.u.routeUsed.destRoute;//ָ���� PBX Ŀ�ĵص� TAC/ARS/AAR ��Ϣ��
	}
	*/

	//?����ȷ�� �¼� ����ʲô��
	//д�����ݿ�  ���ͼ��

}
