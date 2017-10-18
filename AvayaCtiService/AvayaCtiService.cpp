
// AvayaCtiService.cpp : ����Ӧ�ó��������Ϊ��
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


// CAvayaCtiServiceApp ����

CAvayaCtiServiceApp::CAvayaCtiServiceApp()
{
	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("AvayaCtiService.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CAvayaCtiServiceApp ����

CAvayaCtiServiceApp theApp;


// CAvayaCtiServiceApp ��ʼ��

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
		SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
		LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

		m_pAvayaCtiUIDlg = new AvayaCtiUI();
		if (m_pAvayaCtiUIDlg == NULL)
		{
			return FALSE;
		}
		m_pMainWnd = m_pAvayaCtiUIDlg;

		INT_PTR nResponse = m_pAvayaCtiUIDlg->DoModal();

		//���� ����

		delete m_pAvayaCtiUIDlg;
	}
	InterlockedDecrement(&g_Counter);
	return FALSE;

}

int CAvayaCtiServiceApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	return CWinApp::ExitInstance();
}




