#include "stdafx.h"
#include "KeyBoarder.h"
#include "MainWnd.h"
#include "Resource.h"
#include "Listmenu.h"
HWND g_hPareat = NULL;
MainWnd::MainWnd()
{
	m_pRoot = NULL;
	m_pHelloBtn = NULL;
}
DWORD WINAPI OpenAllWare(LPVOID pParam)
{
	MainWnd* pWare = (MainWnd*)pParam;
	ShellExecute(g_hPareat, _T("open"), "D:\\software\\perfectworldarena\\完美世界竞技平台.exe", "", "", SW_SHOWNORMAL);
	ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\WeChat\\WeChat.exe", "", "", SW_SHOWNORMAL);
	ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\QQMusic\\QQMusic.exe", "", "", SW_SHOWNORMAL);
	ShellExecute(g_hPareat, _T("open"), "D:\\software\\VS2013\\Common7\\IDE\\devenv.exe", "", "", SW_SHOWNORMAL);
	ShellExecute(g_hPareat, _T("open"), "D:\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe", "", "", SW_SHOWNORMAL);
	return 0;
}

LRESULT MainWnd::OnTrayIcon(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (lParam == WM_LBUTTONDOWN)
	{
		//Shell_NotifyIcon(NIM_DELETE, &m_trayIcon); 
		//显示主窗口
		ShowWindow(SW_SHOWNORMAL);
	}
	else if (lParam == WM_RBUTTONDOWN)
	{
		POINT pt; GetCursorPos(&pt);
		SetForegroundWindow(m_hWnd);
		HMENU hMenu;
		hMenu = CreatePopupMenu();
		AppendMenu(hMenu, MF_STRING, WM_CLOSE, _T("Exit"));
		int cmd = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, m_hWnd, NULL);
		if (cmd == WM_CLOSE)
		{
			m_trayIcon.hIcon = NULL;
			Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
			::PostQuitMessage(0);
		}
	}
	bHandled = true;
	return 0;
}
int MainWnd::KillProcess(TCHAR Kill_Name[])
{
	HANDLE hSnapshort = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshort == INVALID_HANDLE_VALUE)
	{
		printf("CreateToolhelp32Snapshot调用失败！\n");
		return -1;
	}
	PROCESSENTRY32 stcProcessInfo;
	stcProcessInfo.dwSize = sizeof(stcProcessInfo);
	BOOL  bRet = Process32First(hSnapshort, &stcProcessInfo);
	while (bRet)
	{
		if (strcmp(stcProcessInfo.szExeFile, Kill_Name) == 0)
		{
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, stcProcessInfo.th32ProcessID);	//获取进程句柄
			::TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
		}
		bRet = Process32Next(hSnapshort, &stcProcessInfo);
	}
	CloseHandle(hSnapshort);
	return 0;
}
void MainWnd::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("wareOpen"))
		{
			COptionUI* pOpen = static_cast<COptionUI*>(msg.pSender);
			//OpenWare(msg);
			if (!pOpen->IsSelected())
			{
				OpenWare(msg);
			}
			else
			{
				POINT pt = msg.ptMouse;
				ClientToScreen(m_hWnd, &pt);
				CContainerUI *pContainer = static_cast<CContainerUI*>(msg.pSender->GetParent());
				CLabelUI* pcLabel = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("warename")));
				CString name = pcLabel->GetText();
				KillProcess(name.GetBuffer());
			}
		}
		else if (msg.pSender->GetName() == _T("AllSelect"))
		{
			CloseHandle(CreateThread(NULL, 0, OpenAllWare, this, 0, NULL));
		}
	}
	else if (msg.sType == DUI_MSGTYPE_MENU)
	{
		Listmenu *pMenu = new Listmenu;
		POINT pt = { msg.ptMouse.x, msg.ptMouse.y };
		//CDuiRect rc = msg.pSender->GetPos();  
		pMenu->Init(pt);
		pMenu->ShowWindow(TRUE);
	}
}

void MainWnd::OpenWare(TNotifyUI& msg)
{
	POINT pt = msg.ptMouse;
	ClientToScreen(m_hWnd, &pt);
	CContainerUI *pContainer = static_cast<CContainerUI*>(msg.pSender->GetParent());
	CLabelUI* pcLabel = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("warename")));
	COptionUI* pcOpen = static_cast<COptionUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("wareOpen")));
	CString name = pcLabel->GetText();
	//string ware = "完美对战平台";
	if (strcmp(name.GetBuffer(), "完美世界竞技平台.exe") == 0)
	{
		ShellExecute(g_hPareat, _T("open"), "D:\\software\\perfectworldarena\\完美世界竞技平台.exe", "", "", SW_SHOWNORMAL);
	}
	else if (strcmp(name.GetBuffer(), "WeChat.exe") == 0)
	{
		ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\WeChat\\WeChat.exe", "", "", SW_SHOWNORMAL);
		
	}
	else if (strcmp(name.GetBuffer(), "qqMusic.exe") == 0)
	{
		ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\QQMusic\\QQMusic.exe", "", "", SW_SHOWNORMAL);
	
	}
	else if (strcmp(name.GetBuffer(), "vs2013.exe") == 0)
	{
		ShellExecute(g_hPareat, _T("open"), "D:\\software\\VS2013\\Common7\\IDE\\devenv.exe", "", "", SW_SHOWNORMAL);
	}
	else if (strcmp(name.GetBuffer(), "apex.exe") == 0)
	{
		ShellExecute(g_hPareat, _T("open"), "D:\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe", "", "", SW_SHOWNORMAL);
	}
// 	if (pcOpen != NULL)
// 	{
// 		pcOpen->Selected(false);
// 	}
	
}

void MainWnd::AddTrayIcon()
{
	memset(&m_trayIcon, 0, sizeof(NOTIFYICONDATA));
	m_trayIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_trayIcon.hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL));
	m_trayIcon.hWnd = m_hWnd;
	lstrcpy(m_trayIcon.szTip, _T("Msg"));
	m_trayIcon.uCallbackMessage = WM_SHOWWINDOW;
	m_trayIcon.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD, &m_trayIcon);
	ShowWindow(SW_HIDE);
}

DuiLib::CDuiString MainWnd::GetSkinFile()
{
	return _T("keyMon.xml");
}

DuiLib::CDuiString MainWnd::GetSkinFolder()
{
	return _T("keyMon");
}

LRESULT MainWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		m_PaintManager.Init(m_hWnd);
		//从xml中加载界面
		CDialogBuilder builder;
		m_pRoot = builder.Create("keyMon.xml", (UINT)0, NULL, &m_PaintManager);
		m_PaintManager.AttachDialog(m_pRoot);
		m_PaintManager.AddNotifier(this);				//添加控件等消息响应，这样消息就会传达到duilib的消息循环
		return lRes;
	}
	else if (uMsg == WM_NCLBUTTONDBLCLK)
	{
		return 1; 
	}
	else if (uMsg == WM_PAINT)
	{

	}
	else if (uMsg == WM_DESTROY) {
		m_trayIcon.hIcon = NULL;
		Shell_NotifyIcon(NIM_DELETE, &m_trayIcon);
		::PostQuitMessage(0L);
	}
	else if (uMsg == WM_ERASEBKGND) 
	{
		return 1;
	}
	lRes = 0;
	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
		return lRes;

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
//初始化数组
DWORD WINAPI VecInfoInit(LPVOID pParam)
{
	MainWnd* pInit = (MainWnd*)pParam;
	listInfo info;
	info.ico = "keyMon\\perfect.png";
	info.text = "完美世界竞技平台.exe";
	pInit->m_vecInfo.push_back(info);
	info.ico = "keyMon\\WeChat.png";
	info.text = "WeChat.exe";
	pInit->m_vecInfo.push_back(info);
	info.ico = "keyMon\\qqmusic.png";
	info.text = "QQMusic.exe";
	pInit->m_vecInfo.push_back(info);
	info.ico = "keyMon\\vs.png";
	info.text = "devenv.exe";
	pInit->m_vecInfo.push_back(info);
	info.ico = "keyMon\\apex.png";
	info.text = "r5apex.exe";
	pInit->m_vecInfo.push_back(info);
	return 0;
}
void MainWnd::SoftWareList()
{
	WaitForSingleObject(m_handle, INFINITE);
	CListUI* WareList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("softwareList")));
	if (NULL == WareList)
		return;
	for (int i = 0; i < m_vecInfo.size(); i++)
	{
		CListContainerElementUI* pListElement = new CListContainerElementUI();
		CDialogBuilder  nBuilderList;
		if (!nBuilderList.GetMarkup()->IsValid())
		{
			pListElement = static_cast<CListContainerElementUI*>(nBuilderList.Create(_T("ListSy.xml"), (UINT)0, NULL, &m_PaintManager));
		}
		else
		{
			pListElement = static_cast<CListContainerElementUI*>(nBuilderList.Create((UINT)0, &m_PaintManager));
		}
		if (pListElement == NULL)
			return;
		CControlUI* pLab = static_cast<CControlUI*>(m_PaintManager.FindSubControlByName(pListElement, _T("UserIconCtl")));
		if (pLab != NULL)
		{
			pLab->SetBkImage(m_vecInfo[i].ico.c_str());
		}
		pLab = NULL;
		pLab = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pListElement, _T("warename")));
		if (pLab != NULL)
		{
			pLab->SetText(m_vecInfo[i].text.c_str());
		}
		pLab = NULL;
		pListElement->SetFixedWidth(200);
		pListElement->SetFixedHeight(40);
		if (!WareList->AddAt(pListElement, i))
		{
			delete pListElement;
			return;
		}
	}
	return;
}

void MainWnd::InitWindow()
{
	SetProp(m_hWnd, _T("MainWnd"), (HANDLE)1);
	SetIcon(IDI_WARE_ICON);
	AddTrayIcon();
	m_handle = CreateThread(NULL, 0, VecInfoInit, this, 0, NULL);
	SoftWareList();

	m_pWareOpen = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("wareOpen")));
	g_hPareat = GetHWND();

	
}
