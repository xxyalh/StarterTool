#include "StdAfx.h"
#include "MainWnd.h"
#include "KeyBoarder.h"


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CPaintManagerUI::SetInstance(hInstance);//���ó���ʵ��
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()
		+ _T("keyMon"));//ʵ���������Ⱦ�����,���Ƥ���ļ�Ŀ¼������Ƥ���ļ���OnCreate֮�У�

	HRESULT Hr = ::CoInitialize(NULL);//��ʼ��COM��, Ϊ����COM���ṩ֧��
	if (FAILED(Hr))
		return 0;

	MainWnd* pMainFrame = new MainWnd;
	if (pMainFrame == NULL)
		return 0;
	//pMainFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE); WS_OVERLAPPEDWINDOW
	pMainFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME & ~WS_MAXIMIZEBOX, WS_EX_WINDOWEDGE);
	pMainFrame->InitWindow();
	pMainFrame->CenterWindow();//�����ڷŵ���������
	pMainFrame->ShowWindow(true);//��ʾ����

	// ������Ϣѭ��
	CPaintManagerUI::MessageLoop();
	return (int)0;
}
