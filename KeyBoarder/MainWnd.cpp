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

	CPaintManagerUI::SetInstance(hInstance);//设置程序实例
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()
		+ _T("keyMon"));//实例句柄与渲染类关联,获得皮肤文件目录（加载皮肤文件在OnCreate之中）

	HRESULT Hr = ::CoInitialize(NULL);//初始化COM库, 为加载COM库提供支持
	if (FAILED(Hr))
		return 0;

	MainWnd* pMainFrame = new MainWnd;
	if (pMainFrame == NULL)
		return 0;
	//pMainFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE); WS_OVERLAPPEDWINDOW
	pMainFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME & ~WS_MAXIMIZEBOX, WS_EX_WINDOWEDGE);
	pMainFrame->InitWindow();
	pMainFrame->CenterWindow();//将窗口放到桌面中央
	pMainFrame->ShowWindow(true);//显示窗口

	// 启动消息循环
	CPaintManagerUI::MessageLoop();
	return (int)0;
}
