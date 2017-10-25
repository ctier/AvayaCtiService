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
{
	m_pTSAPIInterface = NULL;
	m_pAgtObject = NULL;
}

BOOL AvayaCtiUI::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	DDX_Text(pDX, IDC_ROUTING_EDIT1, m_strRouting);
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
		m_pAgtObject->AgentConferenceCall(&receive_message["DeviceID"][0], stoi(receive_message["heldCall"]), stoi(receive_message["activeCall"]));
		break;
	}
	case "AgentConsultationCall"_hash:
	{
		m_pAgtObject->AgentConsultationCall(&receive_message["DeviceID"][0], stoi(receive_message["activeCall"]), &receive_message["calledDevice"][0]);
		break;
	}
	case "AgentReconnectCall"_hash:
	{
		m_pAgtObject->AgentReconnectCall(&receive_message["DeviceID"][0], stoi(receive_message["heldCall"]), stoi(receive_message["activeCall"]));
		break;
	}
	//Routing Service  不开放给客户端
	/*
	case "RouteEnd"_hash://
	{
		break;
	}
	case "RouteRegisterCancel"_hash://
	{
		break;
	}
	case "RouteRegister"_hash://
	{
		break;
	}
	case "RouteSelectInv"_hash://
	{
		break;
	}
	case "RouteSelect"_hash://
	{
		break;
	}
	*/
	//
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
	ON_BN_CLICKED(IDC_ROUTING_INSERT, &AvayaCtiUI::OnBnClickedRoutingInsert)
	ON_BN_CLICKED(IDC_ROUTING_DELETE, &AvayaCtiUI::OnBnClickedRoutingDelete)
	ON_BN_CLICKED(IDC_ROUTING_SELECT, &AvayaCtiUI::OnBnClickedRoutingSelect)
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


void AvayaCtiUI::OnBnClickedRoutingInsert()
{
	UpdateData(TRUE);//m_strRouting
	
}


void AvayaCtiUI::OnBnClickedRoutingDelete()
{

}


void AvayaCtiUI::OnBnClickedRoutingSelect()
{

}
