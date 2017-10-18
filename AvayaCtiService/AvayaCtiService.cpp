
// AvayaCtiService.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "AvayaCtiService.h"
#include "tchar.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LONG g_Counter = -1;

// CAvayaCtiServiceApp

BEGIN_MESSAGE_MAP(CAvayaCtiServiceApp, CWinApp)
	//ON_COMMAND(ID_APP_ABOUT, &CAvayaCtiServiceApp::OnAppAbout)
END_MESSAGE_MAP()


// CAvayaCtiServiceApp 构造

CAvayaCtiServiceApp::CAvayaCtiServiceApp()
{
	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AvayaCtiService.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CAvayaCtiServiceApp 对象

CAvayaCtiServiceApp theApp;


// CAvayaCtiServiceApp 初始化

BOOL CAvayaCtiServiceApp::InitInstance()
{
	bool bresult = FALSE;
	BOOL fFirstInstance = (InterlockedIncrement(&g_Counter) == 0);

	if (fFirstInstance == FALSE)
	{
		MessageBox(NULL, INST_ALREADY_RUNNING, ALERT, MB_OK | MB_ICONERROR);
		return FALSE;
	}
	else
	{
		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);
		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&InitCtrls);

		CWinApp::InitInstance();

		AfxEnableControlContainer();
		SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
		LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

		m_pAvayaCtiUIDlg = new AvayaCtiUI();
		if (m_pAvayaCtiUIDlg == NULL)
		{
			return FALSE;
		}
		m_pMainWnd = m_pAvayaCtiUIDlg;

		INT_PTR nResponse = m_pAvayaCtiUIDlg->DoModal();

		//服务 出口

		delete m_pAvayaCtiUIDlg;
	}
	InterlockedDecrement(&g_Counter);
	return FALSE;

}

int CAvayaCtiServiceApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	return CWinApp::ExitInstance();
}




