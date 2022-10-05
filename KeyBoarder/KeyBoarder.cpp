#include "stdafx.h"
#include "KeyBoarder.h"
#include "MainWnd.h"
#include "Resource.h"
#include "Listmenu.h"
#include <Commdlg.h>
#include "Title.h"
#include "../InjectDll/InjectDll.h"
HWND g_hPareat = NULL;
MainWnd::MainWnd()
{
	m_pRoot = NULL;
	m_pHelloBtn = NULL;
	m_sFilePath = "";
	m_pReadIni = NULL;
}

DWORD WINAPI ReadIniThread(LPVOID pParam)
{
	MainWnd* pRead = (MainWnd*)pParam;
	pRead->WriteIniFile("path1","ico1",1);
	pRead->WriteIniFile("path2", "ico2",2);
	pRead->WriteIniFile("path3", "ico3",3);
	return 0;
}

DWORD WINAPI OpenAllWare(LPVOID pParam)
{
	MainWnd* pWare = (MainWnd*)pParam;
	if (!pWare->m_pWareOpen->IsSelected())
	{
// 		ShellExecute(g_hPareat, _T("open"), "D:\\software\\perfectworldarena\\完美世界竞技平台.exe", "", "", SW_SHOWNORMAL);
// 		ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\WeChat\\WeChat.exe", "", "", SW_SHOWNORMAL);
// 		ShellExecute(g_hPareat, _T("open"), "C:\\SoftWare\\QQMusic\\QQMusic.exe", "", "", SW_SHOWNORMAL);
// 		ShellExecute(g_hPareat, _T("open"), "D:\\software\\VS2013\\Common7\\IDE\\devenv.exe", "", "", SW_SHOWNORMAL);
// 		ShellExecute(g_hPareat, _T("open"), "D:\\SteamLibrary\\steamapps\\common\\Apex Legends\\r5apex.exe", "", "", SW_SHOWNORMAL);
	}
	
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
DWORD WINAPI OpenFileBrowse(LPVOID pParam)
{
	MainWnd* pPath = (MainWnd*)pParam;
	pPath->m_sDynamAdd.clear();
	OPENFILENAME ofn;			// 公共对话框结构
	TCHAR szFile[MAX_PATH];		// 保存获取文件名称的缓冲区   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = "Image\0*.PNG;*.JPG\0Exe\0*.exe\0"; //过滤规则
	ofn.lpstrFilter = "Exe\0*.exe\0"; //过滤规则
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:\\Program Files";	//指定默认路径
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		string sFilePath = szFile;
		pPath->m_sDynamAdd.push_back(sFilePath);
		::PostMessage(g_hPareat, WM_SELECTEDICOPATH, 1, 0);
		return 0;
	}
	else
	{
		return -1;
	}
}
DWORD WINAPI OpenFileBrowseIco(LPVOID pParam)
{
	MainWnd* pPath = (MainWnd*)pParam;
	OPENFILENAME ofn;			// 公共对话框结构
	TCHAR szFile[MAX_PATH];		// 保存获取文件名称的缓冲区   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	//ofn.lpstrFilter = "Image\0*.PNG;*.JPG\0Exe\0*.exe\0"; //过滤规则
	ofn.lpstrFilter = "Image\0*.PNG;*.JPG\0"; //过滤规则
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "C:\\Program Files";	//指定默认路径
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn))
	{
		//string sIcoPath = pPath->TCHAR2STRING(szFile);
		string sIcoPath = szFile;
		pPath->m_sDynamAdd.push_back(sIcoPath);
		//::PostMessage(g_hPareat, WM_READINIFILE, 1, 0);
		return 0;
	}
	else
	{
		return -1;
	}
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
				int sel = m_pTablay->GetCurSel();
				OpenWare(msg, sel);
			}
			else
			{
				CContainerUI *pContainer = static_cast<CContainerUI*>(msg.pSender->GetParent());
				CLabelUI* pcLabel = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("warename")));
				CString name = pcLabel->GetText();
				KillProcess(name.GetBuffer());
			}
		}
		else if (msg.pSender->GetName() == _T("AllSelect"))
		{
			// 			int selec = m_pTablay->GetCurSel();
			// 			switch (selec)
			// 			{
			// 			case 0:
			// 				for (int i = 0; i < m_pGameList->GetCount(); i++)
			// 				{
			// 					CControlUI* pCont = m_pGameList->GetItemAt(i)->FindControl(FINDCONTROLPROC());
			// 					pCont->FindControl()
			// 				}
			// 				break;
			// 			}
			 //			CloseHandle(CreateThread(NULL, 0, OpenAllWare, this, 0, NULL));
		}
		else if (msg.pSender->GetName() == _T("AddListBtn"))
		{
			CloseHandle(CreateThread(NULL, 0, OpenFileBrowse, this, 0, NULL));
		}
		else if (msg.pSender->GetName() == _T("select1"))
		{
			m_pTablay->SelectItem(0);
			m_pSelect1->SetBkColor(0xff8EE5EE);
			m_pSelect2->SetBkColor(0xffffffff);
			m_pSelect3->SetBkColor(0xffffffff);
		}
		else if (msg.pSender->GetName() == _T("select2"))
		{
			m_pTablay->SelectItem(1);
			m_pSelect2->SetBkColor(0xff8EE5EE);
			m_pSelect1->SetBkColor(0xffffffff);
			m_pSelect3->SetBkColor(0xffffffff);
		}
		else if (msg.pSender->GetName() == _T("select3"))
		{
			m_pTablay->SelectItem(2);
			m_pSelect3->SetBkColor(0xff8EE5EE);
			m_pSelect1->SetBkColor(0xffffffff);
			m_pSelect2->SetBkColor(0xffffffff);
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

string MainWnd::TCHAR2STRING(TCHAR *STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0, (LPCWCH)STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen*sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, (LPCWCH)STR, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	delete chRtn;
	return str;
}

void MainWnd::OpenWare(TNotifyUI& msg, int sel)
{
	POINT pt = msg.ptMouse;
	ClientToScreen(m_hWnd, &pt);
	CContainerUI *pContainer = static_cast<CContainerUI*>(msg.pSender->GetParent());
	CLabelUI* pcLabel = static_cast<CLabelUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("warename")));
	CEditUI* pcEdit1 = static_cast<CEditUI*>(m_PaintManager.FindSubControlByName(pContainer, _T("rolledmux")));
	int sCount = 0;
	if (pcEdit1 != NULL)
	{
		sCount = _atoi64(pcEdit1->GetText());
	}
	CString name = pcLabel->GetText();

	int count = 0;
	if (sel == 0)
	{
		count = m_pGameList->GetCount();
		for (int i = 0; i < count; i++)
		{
			if (strcmp(name.GetBuffer(), m_sGameName[i].c_str()) == 0)
			{
				ShellExecute(g_hPareat, _T("open"), m_VecPath1[i].c_str(), "", "", SW_SHOWNORMAL);
			}
		}
	}
	else if (sel == 1)
	{
		count = m_pCommuncList->GetCount();
		for (int i = 0; i < count; i++)
		{
			if (strcmp(name.GetBuffer(), m_sCommonName[i].c_str()) == 0)
			{
				ShellExecute(g_hPareat, _T("open"), m_VecPath2[i].c_str(), "", "", SW_SHOWNORMAL);
			}
		}
	}
	else if (sel == 2)
	{
		count = m_pFileList->GetCount();
		for (int i = 0; i < count; i++)
		{
			if (strcmp(name.GetBuffer(), m_sFileName[i].c_str()) == 0)
			{
				ShellExecute(g_hPareat, _T("open"), m_VecPath3[i].c_str(), "", "", SW_SHOWNORMAL);
			}
		}
	}
	if (strcmp(name.GetBuffer(), "WeChat.exe") == 0)
	{
		string sPath = "";
		if (sel == 0)
		{
			for (int i = 0; i < count; i++)
			{
				if (strcmp(name.GetBuffer(), m_sGameName[i].c_str()) == 0)
				{
					sPath = m_VecPath1[i].c_str();
				}
			}
			
		}
		else if (sel == 1)
		{
			for (int i = 0; i < count; i++)
			{
				if (strcmp(name.GetBuffer(), m_sCommonName[i].c_str()) == 0)
				{
					sPath = m_VecPath2[i].c_str();
				}
			}
		}
		else if (sel == 2)
		{
			for (int i = 0; i < count; i++)
			{
				if (strcmp(name.GetBuffer(), m_sFileName[i].c_str()) == 0)
				{
					sPath = m_VecPath3[i].c_str();
				}
			}
		}
		if (sCount != 0)
		{
			StartHook();
			//CloseHandle(CreateThread(NULL, 0, CreateNewProcess, this, 0, NULL));
			char szCommandLine[] = "";
			STARTUPINFO si = { sizeof(si) };
			PROCESS_INFORMATION pi;
			si.dwFlags = STARTF_USESHOWWINDOW; // 指定wShowWindow成员有效
			si.wShowWindow = TRUE; // 此成员设为TRUE的话则显示新建进程的主窗
			while (sCount)
			{
				sCount--;
				BOOL bstr = CreateProcess(sPath.c_str(), szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
				if (!bstr)
				{
					MessageBox(NULL, "打开失败，请重试！", NULL, 0);
				}
			}
		}
	}
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
		POINT pt;
		GetCursorPos(&pt);
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
void MainWnd::AddTrayIcon()
{
	memset(&m_trayIcon, 0, sizeof(NOTIFYICONDATA));
	m_trayIcon.cbSize = sizeof(NOTIFYICONDATA);
	m_trayIcon.hIcon = ::LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL));
	m_trayIcon.hWnd = m_hWnd;
	lstrcpy(m_trayIcon.szTip, _T("Msg"));
	m_trayIcon.uCallbackMessage = WM_SYSTEMTRAY_NOTIFY;
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
	else if (uMsg == WM_SYSTEMTRAY_NOTIFY)
	{
		if (lParam == WM_LBUTTONDOWN)
		{
			ShowWindow(true);
		}
		
	}
	else if (uMsg == WM_NCLBUTTONDBLCLK)
	{
		return 1; 
	}
	else if (uMsg == WM_SELECTEDICOPATH)
	{
		Title* pT = new Title;
		pT->m_hwnds = g_hPareat;
		if (pT == NULL) 1;
		pT->Create(GetHWND(), _T("用户列表"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
		pT->CenterWindow();
		pT->ShowWindow(true);
	}
	else if (uMsg == WM_TITLESELECTEDCONFIG)
	{
		CloseHandle(CreateThread(NULL, 0, OpenFileBrowseIco, this, 0, NULL));
	}
	else if (uMsg == WM_READINIFILE)
	{
		//WriteIniFile();
		//WriteIniSelect();
	}
	else if (uMsg == WM_SOFTWARELIST)
	{
		//SoftWareList(m_pGameList);
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
void MainWnd::WriteIniSelect()
{
	if (NULL == m_pReadIni)return;
	m_pReadIni->ReadINI("Setting.ini");
	char sz[255];
	m_pReadIni->SetValue("path", m_sDynamAdd[0], m_sDynamAdd[1]);
	m_pReadIni->WriteINI("Setting.ini");

	char* ptr = "";
	char str[255];
	strcpy(str, m_sDynamAdd[0].c_str());
	ptr = strrchr(str, '\\');
	string name = "";
	string ico = "";
	if (NULL != ptr)
	{
		name = ptr + 1;
	}
	ptr = NULL;
	char itr[255];
	strcpy(itr, m_sDynamAdd[1].c_str());
	ptr = strrchr(itr, '\\');
	if (NULL != ptr)
	{
		ico = ptr - 6;
	}
}
void MainWnd::WriteIniFile(string path, string ico,int count)
{
	if (NULL == m_pReadIni)return;
	m_pReadIni->ReadINI("Setting.ini");

	m_sCountPath = m_pReadIni->GetValueCount(path);
	if (m_sCountPath > 0)
	{
		for (int i = 0; i < m_sCountPath; i++)
		{
			char sz[255];
			string paths = m_pReadIni->GetValue(path, _itoa(i, sz, 10));
			if (count == 1)
			{
				m_VecPath1.push_back(paths.c_str());
			}
			else if (count == 2)
			{
				m_VecPath2.push_back(paths.c_str());
			}
			else if (count == 3)
			{
				m_VecPath3.push_back(paths.c_str());
			}
		}
	}
	m_sCountIco = m_pReadIni->GetValueCount(ico);
	if (m_sCountIco >0)
	{
		for (int i = 0; i < m_sCountIco; i++)
		{
			char sz[255];
			string icos = m_pReadIni->GetValue(ico, _itoa(i, sz, 10));
			if (count == 1)
			{
				m_VecIco1.push_back(icos.c_str());
			}
			else if (count == 2)
			{
				m_VecIco2.push_back(icos.c_str());
			}
			else if (count == 3)
			{
				m_VecIco3.push_back(icos.c_str());
			}
		}
	}
	VecInfoInit(count);
}
//初始化数组
void MainWnd::VecInfoInit(int count)
{
	m_vecInfo.clear();
	listInfo info;
	char* ptr = "";
	if (count == 1)
	{
		for (int i = 0; i < m_VecPath1.size(); i++)
		{
			char str[255];
			strcpy(str, m_VecPath1[i].c_str());
			ptr = strrchr(str, '\\');
			if (NULL != ptr)
			{
				m_sGameName.push_back(ptr + 1);
				info.text = ptr + 1;
			}
			info.ico = m_VecIco1[i];
			m_vecInfo.push_back(info);
		}
		SoftWareList(m_pGameList);
	}
	else if (count == 2)
	{
		for (int i = 0; i < m_VecPath2.size(); i++)
		{
			char str[255];
			strcpy(str, m_VecPath2[i].c_str());
			ptr = strrchr(str, '\\');
			if (NULL != ptr)
			{
				m_sCommonName.push_back(ptr + 1);
				info.text = ptr + 1;
			}
			info.ico = m_VecIco2[i];
			m_vecInfo.push_back(info);
		}
		SoftWareList(m_pCommuncList);
	}
	else if (count == 3)
	{
		for (int i = 0; i < m_VecPath3.size(); i++)
		{
			char str[255];
			strcpy(str, m_VecPath3[i].c_str());
			ptr = strrchr(str, '\\');
			if (NULL != ptr)
			{
				m_sFileName.push_back(ptr + 1);
				info.text = ptr + 1;
			}
			info.ico = m_VecIco2[i];
			m_vecInfo.push_back(info);
		}
		SoftWareList(m_pFileList);
	}
	return;
}
void MainWnd::SoftWareList(CListUI* pList)
{
	int count = 0;
	if (pList == m_pGameList)
	{
		count = m_VecPath1.size();
	}
	else if (pList == m_pCommuncList)
	{
		count = m_VecPath2.size();
	}
	else if (pList == m_pFileList)
	{
		count = m_VecPath3.size();
	}
	if (NULL == pList)
		return;
	for (int i = 0; i < count; i++)
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
		pLab = static_cast<CEditUI*>(m_PaintManager.FindSubControlByName(pListElement, _T("rolledmux")));
		if (pLab != NULL)
		{
			if (strcmp(m_vecInfo[i].text.c_str(), "WeChat.exe") == 0)
			{
				pLab->SetVisible(true);
			}
			else
			{
				pLab->SetVisible(false);
			}
		}
		pListElement->SetFixedWidth(250);
		pListElement->SetFixedHeight(40);
		if (!pList->AddAt(pListElement, i))
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
	g_hPareat = GetHWND();
	m_pReadIni = new CReadIni;
	AddTrayIcon();
	CreateThread(NULL, 0, ReadIniThread, this, 0, NULL);
	m_pWareOpen = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("wareOpen")));
	m_pGameList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("gameList")));
	m_pCommuncList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("communcList")));
	m_pFileList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("fileList")));
	m_pTablay = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));
	m_pSelect1 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("select1")));
	m_pSelect2 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("select2")));
	m_pSelect3 = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("select3")));
	
	
}
