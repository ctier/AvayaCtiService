#pragma once
#include "TSAPIInterface.h"
//#include "CallManager.h"
#include "AvayaCallCenterUserAgent.h"
#include "KafkaConsumer.h"
#include "rdkafkacpp.h"
#include "afxwin.h"
#include "json.h"
#include "json-forwards.h"

// AvayaCtiUI 对话框

class AvayaCtiUI : public CDialog//, public AgentStateObserver//, public CallStateObserver
{
	DECLARE_DYNAMIC(AvayaCtiUI)

public:
	AvayaCtiUI(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AvayaCtiUI(); 

	// Dialog Data
	enum { IDD = IDD_AvayaCti };
	/*
	void Notify(long lcallID, callState eCaState, connectionState eConState, char* szCalledDevID,
		char* szCallingDevID, char* szConferDevID);
	*/
	//void Notify(AgentState agentState, AgentTalkState  agentTalkState);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
	AvayaCallCenterUserAgent *m_pAgtObject;  // object of Agent Class
	//CallManager *m_pCallManagerObject;	 // object of CallManager Class
	TSAPIInterface* m_pTSAPIInterface;		 // Handle for handling all events

	KafkaConsumer* m_pConsumerObject; 
	//KafkaProducer* m_pProducerObject;

	virtual BOOL OnInitDialog();

	CString m_strAgentStatus;
private:
	void MonitoringKafka();
	bool SelectTSAPIInterface(string message);
	// variable attach with Current AgentStatus readonly EditBox.
	CEdit m_Status;
	void InitializeDialog();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedBegin();
	CString m_message;
};
