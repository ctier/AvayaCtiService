// AvayaCtiUI.cpp : 实现文件
//

#include "stdafx.h"
#include "AvayaCtiService.h"
#include "AvayaCtiUI.h"
#include "afxdialogex.h"
#include "Constant.h"
#include <windows.h>

//计算string的hash值 
typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str)
{
	hash_t ret{ basis };

	while (*str) {
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}

constexpr unsigned long long operator ""_hash(char const* p, size_t)
{
	return hash_compile_time(p);
}

// AvayaCtiUI 对话框

IMPLEMENT_DYNAMIC(AvayaCtiUI, CDialog)

AvayaCtiUI::AvayaCtiUI(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_AvayaCti, pParent)
	
	, m_message(_T(""))
	, m_strRouting(_T(""))
	, m_radioBtnGroup1(0)
	, m_radioBtnGroup2(0)
	, m_radioBtnGroup3(0)
	, m_radioBtnGroup4(0)
{
	m_pTSAPIInterface = NULL;
	m_pAgtObject = NULL;
}

BOOL AvayaCtiUI::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cbRoutingType.AddString("VIP");
	m_cbRoutingType.AddString("黑名单");
	m_cbRoutingType.AddString("重复报警");

	// This will get the window handler for AgentStateUI 
	theApp.m_hAgtStateUI = this->GetSafeHwnd();

	//引用类 初始化 //

	m_pTSAPIInterface = TSAPIInterface::GetInstance();
	if (m_pTSAPIInterface == NULL)
	{
		return FALSE;
	}
	//创建AvayaCallCenterUserAgent对象
	m_pAgtObject = new AvayaCallCenterUserAgent();//参数保留在前端，当请求时发送对应参数到kafka //CString deviceID,const CString agentID,const CString agentPassword, int agentWorkMode
	if (m_pAgtObject == NULL)
	{
		return FALSE;
	}
	
	//创建AvayaCallCenterRouting对象
	m_pRoutingObject = new AvayaCallCenterRouting();

	if (m_pRoutingObject == NULL)
	{
		return FALSE;
	}
	
	//创建StatusRecord对象
	 m_pStatusRecordObject = new StatusRecord();
	 if (m_pStatusRecordObject == NULL)
	 {
		 return FALSE;
	 }


	HINSTANCE hInst = AfxGetInstanceHandle();
	char szFileName[MAX_PATH];
	GetModuleFileName(hInst, szFileName, MAX_PATH);
	CString filename = szFileName;
	filename.TrimRight("AvayaCtiService.exe");
	filename.Append("Settings.ini");


	CFileFind fileFind;

	if (fileFind.FindFile(filename) == FALSE)
	{
		char msg[512];
		sprintf_s(msg, "%s%s", filename,
			FILE_NOT_FOUND);
		::MessageBox(NULL, msg, "File Not Found Error", MB_OK);
	}
	else
	{
		TCHAR m_szServerID[BUFFER_SIZE];		// AE Server
		TCHAR m_szLoginID[BUFFER_SIZE];		// LoginId for accessing AE Server
		TCHAR m_szPassword[BUFFER_SIZE];		// LoginID Password for AE Server

		// GetPrivateProfileString(...) is used for reteriving values from the Settings.ini file
		GetPrivateProfileString("AgentView", "CTILink", "", m_szServerID, sizeof(m_szServerID), filename);
		GetPrivateProfileString("AgentView", "CTIUserID", "", m_szLoginID, BUFFER_SIZE, filename);
		GetPrivateProfileString("AgentView", "CTIUserPassword", "", m_szPassword, sizeof(m_szPassword), filename);

		// This will call a method of TSAPIInterface class for opening the Communication Channel		
		if (m_pTSAPIInterface->OpenStream(m_szServerID, m_szLoginID, m_szPassword) == FALSE)
		{
			::MessageBox(NULL, ERR_OPEN_ACSSTREAM, OPEN_STREAM, MB_OK);
			return FALSE;
		}
	}
	const string brokers = "127.0.0.1:9092";
	const string topic_consumer = "topics_0";

	m_pConsumerObject = new KafkaConsumer(brokers, topic_consumer, "test");
	if (m_pConsumerObject == NULL)
	{
		return FALSE;
	}
	if (!m_pConsumerObject->initKafka()) {
		fprintf(stderr, "kafka server initialize error\n");
	}
	else {
		//m_pConsumerObject->consume_clear();
	}
	/*
	m_pProducerObject = new KafkaProducer(brokers, topic_producer);
	if (m_pProducerObject == NULL)
	{
		return FALSE;
	}
	*/
	// display the Agent Initial Configuration
	//InitializeDialog();



	UpdateData(FALSE);


	return TRUE;
}
void AvayaCtiUI::InitializeDialog()
{

}
AvayaCtiUI::~AvayaCtiUI()
{
	m_pTSAPIInterface->CloseStream();

	delete m_pTSAPIInterface;
	delete m_pAgtObject;
	delete m_pConsumerObject;
	//delete m_pCallManagerObject;
}

void AvayaCtiUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_VIEWSTATE, m_strAgentStatus);
	DDX_Control(pDX, IDC_VIEWSTATE, m_Status);

	DDX_Text(pDX, IDC_MESSAGE, m_message);
	DDX_Radio(pDX, IDC_WORKMODE_RADIO1, m_radioBtnGroup1);
	DDX_Radio(pDX, IDC_AM_NOTREADY_RADIO, m_radioBtnGroup2);
	DDX_Radio(pDX, IDC_PARTICIPATIONTYPE_RADIO1, m_radioBtnGroup3);
	DDX_Radio(pDX, IDC_ACTIVE_RADIO, m_radioBtnGroup4);

	DDX_Text(pDX, IDC_ROUTING_EDIT1, m_strRouting);

	DDX_Control(pDX, IDC_ROUTING_TYPE, m_cbRoutingType);
}

string AvayaCtiUI::GetTimeStr()//GetLocalTime  

{
	SYSTEMTIME time;

	GetLocalTime(&time);

	string year;
	string month;
	string day;

	year = to_string(time.wYear);
	month = to_string(time.wMonth);
	day = to_string(time.wDay);
	string strTime = year + "/" + month + "/" + day + " ";

	char* pTime = new char[30];
	string strFormat = "HH:mm:ss";
	GetTimeFormat(LOCALE_INVARIANT, LOCALE_USE_CP_ACP, &time, strFormat.c_str(), (LPSTR)pTime, 30);
	strTime += pTime;

	string milliseconds;
	milliseconds = to_string(time.wMilliseconds);
	strTime += "." + milliseconds;

	return strTime;
}

void AvayaCtiUI::MonitoringKafka()
{
	/*
	//while 循环
	string KafkaMessage;
	while (1) {
		KafkaMessage = m_pConsumerObject->consume();
		if (KafkaMessage != "")
		{
			m_strAgentStatus.Append(KafkaMessage.c_str());
			SelectTSAPIInterface(KafkaMessage);
		}

	}
	*/
	
}

bool AvayaCtiUI::SelectTSAPIInterface(string message)
{
	Json::Reader reader;
	Json::Value root;
	map<string, string> receive_message;
	if (!reader.parse(message, root))
	{
		cerr << "json parse failed\n";
		return false;
	}
	Json::Value::Members mem = root.getMemberNames();
	for (Json::Value::Members::iterator iter = mem.begin(); iter != mem.end(); iter++)
	{
		if (root[*iter].isString()) //string
		{
			receive_message[*iter] = root[*iter].asString();
		}
		else
		{
			cerr << "have element not in string\n";
			return false;
		}
	}
	string method = receive_message["method"];
	switch (hash_(method.c_str())) {

	//Set Feature Service Group
	case "AgentLogin"_hash:
	{
		m_pAgtObject->AgentLogin(&receive_message["DeviceID"][0], &receive_message["AgentID"][0]
			, &receive_message["AgentPassword"][0], stoi(receive_message["WorkMode"]));
		break;
	}
	case "AgentLogout"_hash:
	{
		m_pAgtObject->AgentLogout(&receive_message["DeviceID"][0], &receive_message["AgentID"][0]
			, &receive_message["AgentPassword"][0]);

		break;
	}
	case "AgentSetState"_hash:
	{
		m_pAgtObject->AgentSetState(&receive_message["DeviceID"][0], &receive_message["AgentID"][0]
			, &receive_message["AgentPassword"][0], stoi(receive_message["WorkMode"])
			, &receive_message["agentState"][0], stoi(receive_message["enablePending"]));

		break;
	}
	case "AgentGetState"_hash:
	{
		m_pAgtObject->AgentGetState(&receive_message["DeviceID"][0]);
		break;
	}
	case "AgentAnswerCall"_hash:
	{
		m_pAgtObject->AgentAnswerCall(&receive_message["DeviceID"][0], stoi(receive_message["callID"]));
		break;
	}
	case "AgentClearConnection"_hash:
	{
		m_pAgtObject->AgentClearConnection(&receive_message["DeviceID"][0], stoi(receive_message["callID"]));
		break;
	}
	case "AgentDisconnectCall"_hash:
	{
		m_pAgtObject->AgentDisconnectCall(&receive_message["DeviceID"][0], stoi(receive_message["callID"]));

		break;
	}

	//
	case "AgentStartMonitor"_hash:
	{
		m_pAgtObject->AgentStartMonitor(&receive_message["DeviceID"][0]);
		break;
	}
	case "AgentStopMonitor"_hash:
	{
		m_pAgtObject->AgentStopMonitor(stoi(receive_message["MonitorCrossRefID"]));
		break;
	}
	case "AgentMakeCall"_hash:
	{
		m_pAgtObject->AgentMakeCall(&receive_message["callingDevice"][0], &receive_message["calledDevice"][0]);
		break;
	}
	case "AgentHoldCall"_hash:
	{
		m_pAgtObject->AgentHoldCall(&receive_message["DeviceID"][0], stoi(receive_message["callID"]));
		break;
	}
	case "AgentRetrieveCall"_hash:
	{
		m_pAgtObject->AgentRetrieveCall(&receive_message["DeviceID"][0], stoi(receive_message["callID"]));
		break;
	}
	case "AgentDeflectCall"_hash:
	{
		m_pAgtObject->AgentDeflectCall(&receive_message["DeviceID"][0], stoi(receive_message["activeCall"]), &receive_message["calledDevice"][0]);
		break;
	}
	case "AgentPickupCall"_hash:
	{
		m_pAgtObject->AgentPickupCall(&receive_message["DeviceID"][0], stoi(receive_message["activeCall"]), &receive_message["calledDevice"][0]);
		break;
	}
	case "AgentTransferCall"_hash:
	{
		m_pAgtObject->AgentTransferCall(&receive_message["DeviceID"][0], stoi(receive_message["heldCall"]), stoi(receive_message["activeCall"]));
		break;
	}
	case "AgentConferenceCall"_hash:
	{
		m_pAgtObject->AgentConferenceCall(&receive_message["CheckedDevice"][0], &receive_message["CalledDevice"][0]);
		break;
	}
	case "AgentConsultationCall"_hash:
	{
		m_pAgtObject->AgentConsultationCall(&receive_message["DeviceID"][0], &receive_message["CalledDevice"][0]);
		break;
	}
	case "AgentReconnectCall"_hash:
	{
		m_pAgtObject->AgentReconnectCall(&receive_message["DeviceID"][0], stoi(receive_message["heldCall"]), stoi(receive_message["activeCall"]));
		break;
	}
	case "SnapshotDevice"_hash:
	{
		m_pAgtObject->SnapshotDevice(&receive_message["CheckedDevice"][0]);
		break;
	}
	case "AgentMonitorCall"_hash:
	{
		m_pAgtObject->AgentMonitorCall(&receive_message["CheckedDevice"][0], &receive_message["DeviceID"][0],&receive_message["ParticipationType"][0]);
		break;
	}
	case "AgentSingleStepConferenceCall"_hash:
	{
		m_pAgtObject->AgentMonitorCall( &receive_message["CheckedDevice"][0], &receive_message["CalledDevice"][0], &receive_message["ParticipationType"][0]);
		break;
	}
	case "AgentSingleStepTransferCall"_hash:
	{
		m_pAgtObject->AgentSingleStepTransferCall(&receive_message["CalledDevice"][0], &receive_message["CheckedDevice"][0]);
		break;
	}
	default:
	{
		cerr << "without this interface : " << method << endl;
		return false;
	}
	}
		
	return true;
}

BEGIN_MESSAGE_MAP(AvayaCtiUI, CDialog)
	ON_BN_CLICKED(IDC_Begin, &AvayaCtiUI::OnBnClickedBegin)
	ON_BN_CLICKED(IDC_LOGIN_BTN, &AvayaCtiUI::OnBnClickedLoginBtn)
	ON_BN_CLICKED(IDC_WORKMODE_RADIO1, &AvayaCtiUI::OnBnClickedRadioBtnGroup1)
	ON_BN_CLICKED(IDC_WORKMODE_RADIO2, &AvayaCtiUI::OnBnClickedRadioBtnGroup1)
	ON_BN_CLICKED(IDC_AM_NOTREADY_RADIO, &AvayaCtiUI::OnBnClickedRadioBtnGroup2)
	ON_BN_CLICKED(IDC_AM_READY_RADIO, &AvayaCtiUI::OnBnClickedRadioBtnGroup2)
	ON_BN_CLICKED(IDC_AM_BUSY_RADIO, &AvayaCtiUI::OnBnClickedRadioBtnGroup2)
	ON_BN_CLICKED(IDC_LOGOUT_BTN, &AvayaCtiUI::OnBnClickedLogoutBtn)
	ON_BN_CLICKED(IDC_STATE_CHANGE_BTN, &AvayaCtiUI::OnBnClickedStateChangeBtn)
	ON_BN_CLICKED(IDC_CHKSTATE_BTN, &AvayaCtiUI::OnBnClickedChkstateBtn)
	ON_BN_CLICKED(IDC_CALL_BTN, &AvayaCtiUI::OnBnClickedCallBtn)
	ON_BN_CLICKED(IDC_MONITOR_START_BTN, &AvayaCtiUI::OnBnClickedMonitorStartBtn)
	ON_BN_CLICKED(IDC_MONITOR_STOP_BTN, &AvayaCtiUI::OnBnClickedMonitorStopBtn)
	ON_BN_CLICKED(IDC_ANSWER_BTN, &AvayaCtiUI::OnBnClickedAnswerBtn)
	ON_BN_CLICKED(IDC_CLEARCON_BTN, &AvayaCtiUI::OnBnClickedClearconBtn)
	ON_BN_CLICKED(IDC_HOLD_BTN, &AvayaCtiUI::OnBnClickedHoldBtn)
	ON_BN_CLICKED(IDC_CANCELHOLD_BTN, &AvayaCtiUI::OnBnClickedCancelholdBtn)
	ON_BN_CLICKED(IDC_PICKUP_BTN, &AvayaCtiUI::OnBnClickedPickupBtn)
	ON_BN_CLICKED(IDC_MonitorCall_btn, &AvayaCtiUI::OnBnClickedMonitorcallbtn)
	ON_BN_CLICKED(IDC_SNAPSHOT_BTN, &AvayaCtiUI::OnBnClickedSnapshotBtn)
	ON_BN_CLICKED(IDC_PARTICIPATIONTYPE_RADIO1, &AvayaCtiUI::OnBnClickedRadioBtnGroup3)
	ON_BN_CLICKED(IDC_PARTICIPATIONTYPE_RADIO2, &AvayaCtiUI::OnBnClickedRadioBtnGroup3)
	ON_BN_CLICKED(IDC_CONSULT_BTN, &AvayaCtiUI::OnBnClickedConsultBtn)
	ON_BN_CLICKED(IDC_SNAPSHOT_BTN2, &AvayaCtiUI::OnBnClickedSnapshotBtn2)
	ON_BN_CLICKED(IDC_CONF_BTN, &AvayaCtiUI::OnBnClickedConfBtn)
	ON_BN_CLICKED(IDC_TRANSFER_BTN, &AvayaCtiUI::OnBnClickedTransferBtn)
	ON_BN_CLICKED(IDC_ACTIVE_RADIO, &AvayaCtiUI::OnBnClickedRadioBtnGroup4)
	ON_BN_CLICKED(IDC_HELD_RADIO, &AvayaCtiUI::OnBnClickedRadioBtnGroup4)
	
	ON_BN_CLICKED(IDC_ROUTING_INSERT, &AvayaCtiUI::OnBnClickedRoutingInsert)
	ON_BN_CLICKED(IDC_ROUTING_DELETE, &AvayaCtiUI::OnBnClickedRoutingDelete)
	ON_BN_CLICKED(IDC_ROUTING_SELECT, &AvayaCtiUI::OnBnClickedRoutingSelect)
	ON_CBN_SELCHANGE(IDC_ROUTING_TYPE, &AvayaCtiUI::OnCbnSelchangeRoutingType)
	ON_BN_CLICKED(IDC_ROUTING_UPDATA, &AvayaCtiUI::OnBnClickedRoutingUpdata)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &AvayaCtiUI::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_ROUTING_REGISTER, &AvayaCtiUI::OnBnClickedRoutingRegister)
	ON_BN_CLICKED(IDC_ROUTING_REGISTERCANCEL, &AvayaCtiUI::OnBnClickedRoutingRegistercancel)
END_MESSAGE_MAP()


void AvayaCtiUI::OnBnClickedBegin()
{
	//MonitoringKafka();
	UpdateData(TRUE);

	string KafkaMessage = m_message;
	m_strAgentStatus = m_strAgentStatus + KafkaMessage.c_str() + "\r\n";
	UpdateData(FALSE);

	SelectTSAPIInterface(KafkaMessage);

}

CString workmode = "3";
CString agentmode = "Not Ready";
CString participationType = "PT_ACTIVE";
CString snapshotType = "active";
string message;


void AvayaCtiUI::OnBnClickedLoginBtn()
{
	// TODO: Agent login 
	CString loginId,deviceId;
	GetDlgItem(IDC_AGENT_EDIT)->GetWindowTextA(loginId);
	GetDlgItem(IDC_DEVICE_EDIT)->GetWindowTextA(deviceId);

	message = "{ \"method\":\"AgentLogin\",\"DeviceID\" : \"" + deviceId + "\",\"AgentID\" : \"" + loginId + "\",\"AgentPassword\": \"\",\"WorkMode\": \"" + workmode + "\" }";
	//m_strAgentStatus = message.c_str();
	//UpdateData(FALSE);
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	//SelectTSAPIInterface(message);
	//MessageBox(loginId, _T("程序运行结果"), MB_OK);
	loginId.ReleaseBuffer();
	deviceId.ReleaseBuffer();
	
}
void AvayaCtiUI::OnBnClickedLogoutBtn()
{
	// TODO: Agent logout
	CString loginId, deviceId;
	GetDlgItem(IDC_AGENT_EDIT)->GetWindowTextA(loginId);
	GetDlgItem(IDC_DEVICE_EDIT)->GetWindowTextA(deviceId);

	message = "{\"method\":\"AgentLogout\", \"DeviceID\" : \"" + deviceId + "\", \"AgentID\" : \"" + loginId + "\", \"AgentPassword\" : \"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	//SelectTSAPIInterface(message);
	loginId.ReleaseBuffer();
	deviceId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedRadioBtnGroup1()
{
	// TODO: set work mode
	UpdateData(true);
	switch (m_radioBtnGroup1)
	{
	case 0://auto in	
		workmode = "3";
		MessageBox("3");
		break;
	case 1://manual in
		workmode = "4";
		MessageBox("4");
		break;
	}
}

void AvayaCtiUI::OnBnClickedRadioBtnGroup2()
{
	// TODO: set agent mode
	UpdateData(true);
	switch (m_radioBtnGroup2)
	{
	case 0://agent not ready
		agentmode = "Not Ready";
		MessageBox("Not Ready");
		break;
	case 1://agent ready
		agentmode = "Ready";
		MessageBox("Ready");
		break;
	case 2://agent work not ready(busy)
		agentmode = "Busy";
		MessageBox("Busy");
		break;
	}
}

void AvayaCtiUI::OnBnClickedRadioBtnGroup3()
{
	// TODO: set work mode
	UpdateData(true);
	switch (m_radioBtnGroup3)
	{
	case 0://auto in	
		participationType = "PT_ACTIVE";
		MessageBox("PT_ACTIVE");
		break;
	case 1://manual in
		participationType = "PT_SILENT";
		MessageBox("PT_SILENT");
		break;
	}
}

void AvayaCtiUI::OnBnClickedRadioBtnGroup4()
{
	// TODO: set work mode
	UpdateData(true);
	switch (m_radioBtnGroup4)
	{
	case 0://auto in	
		snapshotType = "active";
		MessageBox("GET Active ConnectionID");
		break;
	case 1://manual in
		snapshotType = "hold";
		MessageBox("GET HOLD ConnectionID");
		break;
	}
}


void AvayaCtiUI::OnBnClickedStateChangeBtn()
{
	// TODO: change agent mode
	CString agentId, deviceId;
	GetDlgItem(IDC_AGENT_EDIT2)->GetWindowTextA(agentId);
	GetDlgItem(IDC_DEVICE_EDIT2)->GetWindowTextA(deviceId);

	message = "{ \"method\":\"AgentSetState\",\"DeviceID\":\""+deviceId+"\",\"AgentID\":\""+agentId+"\",\"AgentPassword\":\"\",\"agentState\":\""+agentmode+"\",\"enablePending\":\"1\",\"WorkMode\":\""+workmode+"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	//SelectTSAPIInterface(message);
	agentId.ReleaseBuffer();
	deviceId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedChkstateBtn()
{
	// TODO: check agent state
	CString deviceId;
	GetDlgItem(IDC_DEVICE_EDIT2)->GetWindowTextA(deviceId);

	message = "{\"method\":\"AgentGetState\",\"DeviceID\":\""+deviceId+"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedCallBtn()
{
	// TODO: make call
	CString callingDevice, calledDevice;
	GetDlgItem(IDC_CALLINGDEVICE_EDIT)->GetWindowTextA(callingDevice);
	GetDlgItem(IDC_CALLEDDEVICE_EDIT)->GetWindowTextA(calledDevice);

	message = "{\"method\":\"AgentMakeCall\",\"callingDevice\":\""+callingDevice +"\",\"calledDevice\":\""+ calledDevice +"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	callingDevice.ReleaseBuffer();
	calledDevice.ReleaseBuffer();

}


void AvayaCtiUI::OnBnClickedMonitorStartBtn()
{
	// TODO: start device monitor
	CString deviceId;
	GetDlgItem(IDC_DEVICE_EDIT3)->GetWindowTextA(deviceId);

	message = "{\"method\":\"AgentStartMonitor\",\"DeviceID\":\""+deviceId+"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedMonitorStopBtn()
{
	// TODO: stop device monitor
	CString deviceId;
	GetDlgItem(IDC_DEVICE_EDIT3)->GetWindowTextA(deviceId);

	message = "{\"method\":\"AgentStopMonitor\",\"MonitorCrossRefID\":\""+deviceId+"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedAnswerBtn()
{
	// TODO: answer call
	CString deviceId, callId;
	GetDlgItem(IDC_DEVICE_EDIT4)->GetWindowTextA(deviceId);
	GetDlgItem(IDC_CALLID_EDIT)->GetWindowTextA(callId);

	message = "{\"method\":\"AgentAnswerCall\",\"DeviceID\":\""+deviceId+"\",\"callID\":\""+callId+"\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	callId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedClearconBtn()
{
	// TODO: clear connection
	CString deviceId, callId;
	GetDlgItem(IDC_DEVICE_EDIT5)->GetWindowTextA(deviceId);
	GetDlgItem(IDC_CALLID_EDIT2)->GetWindowTextA(callId);

	message = "{\"method\":\"AgentClearConnection\",\"DeviceID\":\"" + deviceId + "\",\"callID\":\"" + callId + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	callId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedHoldBtn()
{
	// TODO: hold call
	CString deviceId, callId;
	GetDlgItem(IDC_DEVICE_EDIT6)->GetWindowTextA(deviceId);
	GetDlgItem(IDC_CALLID_EDIT3)->GetWindowTextA(callId);

	message = "{\"method\":\"AgentHoldCall\",\"DeviceID\":\"" + deviceId + "\",\"callID\":\"" + callId + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	callId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedCancelholdBtn()
{
	// TODO: cancel hold (RetrieveCall)
	CString deviceId, callId;
	GetDlgItem(IDC_DEVICE_EDIT7)->GetWindowTextA(deviceId);
	GetDlgItem(IDC_CALLID_EDIT4)->GetWindowTextA(callId);

	message = "{\"method\":\"AgentRetrieveCall\",\"DeviceID\":\"" + deviceId + "\",\"callID\":\"" + callId + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	callId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedPickupBtn()
{
	// TODO: pick up
	CString deviceId, callId, calledDevice;
	GetDlgItem(IDC_DEVICE_EDIT8)->GetWindowTextA(deviceId);
	GetDlgItem(IDC_CALLID_EDIT5)->GetWindowTextA(callId);
	GetDlgItem(IDC_CALLEDDEVICE_EDIT2)->GetWindowTextA(calledDevice);

	message = "{\"method\":\"AgentPickupCall\",\"DeviceID\":\"" + deviceId + "\",\"activeCall\":\"" + callId + "\",\"calledDevice\":\"" + calledDevice + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	callId.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedMonitorcallbtn()
{
	// TODO: Monitor Call
	CString deviceId, checkedDevice,callId;
	GetDlgItem(IDC_DEVICE_EDIT9)->GetWindowTextA(checkedDevice);
	GetDlgItem(IDC_DEVICE_EDIT10)->GetWindowTextA(deviceId);
	
	
	message = "{\"method\":\"AgentMonitorCall\",\"DeviceID\":\"" + deviceId + "\",\"CheckedDevice\":\"" + checkedDevice + "\",\"ParticipationType\":\"" + participationType + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	deviceId.ReleaseBuffer();
	checkedDevice.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedSnapshotBtn()
{
	// TODO: snapshout connection info
	CString  checkedDevice;
	GetDlgItem(IDC_DEVICE_EDIT9)->GetWindowTextA(checkedDevice);
	message = "{\"method\":\"SnapshotDevice\",\"CheckedDevice\":\"" + checkedDevice + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	checkedDevice.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedConsultBtn()
{
	// TODO: 
	CString deviceId, calledDevice;
	GetDlgItem(IDC_CALLEDDEVICE_EDIT3)->GetWindowTextA(calledDevice);
	GetDlgItem(IDC_DEVICE_EDIT12)->GetWindowTextA(deviceId);

	message = "{\"method\":\"AgentConsultationCall\",\"DeviceID\":\"" + deviceId + "\",\"CalledDevice\":\"" + calledDevice + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	calledDevice.ReleaseBuffer();

}


void AvayaCtiUI::OnBnClickedSnapshotBtn2()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: snapshout connection info
	CString  checkedDevice;
	GetDlgItem(IDC_DEVICE_EDIT12)->GetWindowTextA(checkedDevice);
	message = "{\"method\":\"SnapshotDevice\",\"CheckedDevice\":\"" + checkedDevice + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	checkedDevice.ReleaseBuffer();
}


void AvayaCtiUI::OnBnClickedConfBtn()
{
	// TODO: conference call
	CString deviceId, checkedDevice;
	GetDlgItem(IDC_DEVICE_EDIT12)->GetWindowTextA(checkedDevice);
	GetDlgItem(IDC_CALLEDDEVICE_EDIT3)->GetWindowTextA(deviceId);
	CString type = "PT_ACTIVE";
	if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) {
	

		message = "{\"method\":\"AgentSingleStepConferenceCall\",\"CalledDevice\":\"" + deviceId + "\",\"CheckedDevice\":\"" + checkedDevice + "\",\"ParticipationType\":\"" + type + "\"}";
		GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
		AvayaCtiUI::OnBnClickedBegin();
		deviceId.ReleaseBuffer();
		checkedDevice.ReleaseBuffer();
	}
	else {
		message = "{\"method\":\"AgentConferenceCall\",\"CalledDevice\":\"" + deviceId + "\",\"CheckedDevice\":\"" + checkedDevice + "\",\"ParticipationType\":\"" + type + "\"}";
		GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
		AvayaCtiUI::OnBnClickedBegin();
		deviceId.ReleaseBuffer();
		checkedDevice.ReleaseBuffer();
	}

	

}


void AvayaCtiUI::OnBnClickedTransferBtn()
{
	// TODO: transfer call
	CString calledDevice, checkedDevice;
	GetDlgItem(IDC_DEVICE_EDIT12)->GetWindowTextA(checkedDevice);
	GetDlgItem(IDC_CALLEDDEVICE_EDIT3)->GetWindowTextA(calledDevice);

	message = "{\"method\":\"AgentSingleStepTransferCall\",\"CalledDevice\":\"" + calledDevice + "\",\"CheckedDevice\":\"" + checkedDevice + "\"}";
	GetDlgItem(IDC_MESSAGE)->SetWindowTextA(message.c_str());
	AvayaCtiUI::OnBnClickedBegin();
	calledDevice.ReleaseBuffer();
	checkedDevice.ReleaseBuffer();

}



void AvayaCtiUI::OnBnClickedRoutingInsert()
{
	UpdateData(TRUE);//m_strRouting
	string message = m_pRoutingObject->InsertNumber(m_strRouting.GetBuffer(m_strRouting.GetLength()),
		m_strRoutingType.GetBuffer(m_strRoutingType.GetLength()));
	UpdataViewStatus(message);
}


void AvayaCtiUI::OnBnClickedRoutingDelete()
{
	UpdateData(TRUE);//m_strRouting
	string message = m_pRoutingObject->DeleteNumber(m_strRouting.GetBuffer(m_strRouting.GetLength()));
	UpdataViewStatus(message);
}


void AvayaCtiUI::OnBnClickedRoutingUpdata()
{
	UpdateData(TRUE);//m_strRouting
	string message = m_pRoutingObject->UpdataNumber(m_strRouting.GetBuffer(m_strRouting.GetLength()),
		m_strRoutingType.GetBuffer(m_strRoutingType.GetLength()));
	UpdataViewStatus(message);
}

void AvayaCtiUI::OnBnClickedRoutingSelect()
{
	UpdateData(TRUE);//m_strRouting
	vector<string> data;
	string message = m_pRoutingObject->SelectNumber(m_strRouting.GetBuffer(m_strRouting.GetLength()),data);
	UpdataViewStatus(message);
	message.clear();
	if (!data.empty())
	{
		for (auto iter = data.begin(); iter != data.end(); iter++)
		{
			message += *iter;
			message += "\t";
		}
	}
	UpdataViewStatus(message);
}



void AvayaCtiUI::OnCbnSelchangeRoutingType()
{
	int com_num = m_cbRoutingType.GetCurSel();
	if (com_num != LB_ERR)
	{
		m_cbRoutingType.GetLBText(com_num, m_strRoutingType);
	}
}





void AvayaCtiUI::OnBnClickedClearBtn()
{
	m_strAgentStatus.Empty();
	UpdateData(FALSE);
}

void AvayaCtiUI::UpdataViewStatus(string mes)
{
	//UpdateData(TRUE);
	m_strAgentStatus = m_strAgentStatus + mes.c_str() + "\r\n";
	UpdateData(FALSE);
}

void AvayaCtiUI::OnBnClickedRoutingRegister()
{
	UpdateData(TRUE);//m_strRouting
	char* message = (LPSTR)(LPCTSTR)m_strRouting;
	m_pRoutingObject->RouteRegister((DeviceID_t*)message);//DeviceID_t 需要路由的电话ID 如110,119
}


void AvayaCtiUI::OnBnClickedRoutingRegistercancel()
{
	UpdateData(TRUE);//m_strRouting
	char* message = (LPSTR)(LPCTSTR)m_strRouting;

	m_pRoutingObject->RouteRegisterCancel(message);
}
