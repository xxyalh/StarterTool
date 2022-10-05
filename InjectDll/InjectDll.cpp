// InjectDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "InjectDll.h"
#include <stdio.h>  
#include <cstdlib>
#include "ProcessHandleHelper.h"
#include <string>

const int WM_CORE_WECHAT_MESSAGE_ = WM_USER + 1;
const int WM_CORE_WECHAT_EXIT_MESSAGE = WM_USER + 2;	//��Ӧ�Ĵ��ڹر���

bool IsWeChat();
void CloseWxHandle(HANDLE mutex);
void UnHookLib();
bool isWechatClose();
void HandleFirstHook();
void HandleExitMessage(HWND hw);

// ���ǵ���������һ��ʾ��
INJECTDLL_API int nInjectDll=0;

// ���ǵ���������һ��ʾ����
INJECTDLL_API int fnInjectDll(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� InjectDll.h
CInjectDll::CInjectDll()
{
	return;
}

void HandleWxInstanceMutex();
void CloseWxHandle(HANDLE mutex);

extern HMODULE g_Module;
HHOOK g_Hook = 0;
bool isKilled = false;			//�Ƿ�Ѿ��ɱ��
bool g_is_init = false;


//���ӻص�����
LRESULT CALLBACK HOOKProc(
							  _In_  int code,
							  _In_  WPARAM wParam,
							  _In_  LPARAM lParam
							  )
{
	if(IsWeChat()){
		HandleWxInstanceMutex();
		PMSG pmsg = (PMSG)lParam;
		if (pmsg->message == WM_CLOSE){
			//���ڹر�ж�ع���
			//OutputDebugString(L"΢�Ŵ��ڹر���");
			HandleExitMessage(pmsg->hwnd);
			UnHook();
		}else
		{
			if(pmsg->message != WM_DESTROY){
				HandleFirstHook();
			}
			
		}

		
		return CallNextHookEx(g_Hook, code, wParam, lParam);
	}else{


		//UnHook();
		return FALSE;
	}
}

bool StartHook()
{
	if (g_Hook == 0)
	{
		g_Hook = SetWindowsHookEx(WH_GETMESSAGE, HOOKProc, g_Module, 0);
		int error = GetLastError();

		wchar_t exeName[300] = {0};
		WCHAR szInfo[512] = { 0 };
		//swprintf_s(szInfo, _countof(szInfo), L"����ʧ������:%d\r\n", error);
		//�����������debug��Ϣ��
		//OutputDebugString(szInfo);

		return true;
	}
	return false;
}

bool UnHook()
{
	if (g_Hook!=0)
	{
		return UnhookWindowsHookEx(g_Hook) ? true : false;
	}
	return false;
}

/*
 *	�������΢�ŵľ��ͷŵ�---�����ڻص��ͷţ�ֻ������Ϣ������ܰ�
 */
void UnHookLib(){
	if(!IsWeChat()){
		FreeLibrary(g_Module);
	}
}

/*
 *	�Ƿ�΢�Ž���
 */
bool IsWeChat(){
	wchar_t exeName[300] = {0};
	GetModuleFileName(NULL,exeName, 300);
	if(wcsstr(exeName, L"WeChat.exe") != NULL){
		return true;

	}else{
		return false;
	}
}

void HandleWxInstanceMutex(){
	if(IsWeChat()){
		if(!isWechatClose()){
			//_WeChat_App_Instance_Identity_Mutex_Name
			HANDLE hmutex = OpenMutex(NULL,TRUE,L"_WeChat_App_Instance_Identity_Mutex_Name");
			CloseWxHandle(hmutex);
			CloseHandle(hmutex);
			isKilled = true;
		}
	}
}


bool isWechatClose(){
	bool ret = true;
	HANDLE hmutex = CreateMutex(NULL,TRUE,L"_WeChat_App_Instance_Identity_Mutex_Name");
	int err = GetLastError();
	if (err == ERROR_ALREADY_EXISTS)
	{
		ret = false;
	}

	CloseHandle(hmutex);
	return ret;
}

void CloseWxHandle(HANDLE mutex){ 

	//CloseProcessHandleEx(mutex);
	OutputDebugString(L"ɱ��΢��APP");
	CloseProcessHandle(GetCurrentProcessId(), L"_WeChat_App_Instance_Identity_Mutex_Name");
	//int err = GetLastError();
	//WCHAR buffer[256] = {0};
	//wsprintf(buffer, L"������:%d", err );
	//OutputDebugString(buffer);
}

HWND FindWechatMessageUI(){
	return ::FindWindow(NULL, L"CORE_MESSAGE_WX_WND");
}

//��һ��Hook΢�����ĳ�ʼ������
void HandleFirstHook(){
	HWND hw =  GetForegroundWindow();
	WCHAR text[256] = {0};
	GetWindowText(hw,text, 256);
	//OutputDebugString(text);

	GetClassName(hw,text, 256);
	std::wstring class_name = text;
	//OutputDebugString(text);
	//WeChatLoginWndForPC
	//WeChatMainWndForPC
	std::wstring check_class_name = L"WeChatMainWndForPC";
	if(class_name == check_class_name){
		HWND core_hwnd = FindWechatMessageUI();
		if(core_hwnd !=NULL){
			PostMessage(core_hwnd, WM_CORE_WECHAT_MESSAGE_, 0, (LPARAM)hw);
		}else{
			//OutputDebugString(L"û���ҵ�����");
		}
	}
}

void HandleExitMessage(HWND hw){
	//WM_CORE_WECHAT_EXIT_MESSAGE
	HWND core_hwnd = FindWechatMessageUI();
	WCHAR text[256] = {0};
	if(core_hwnd !=NULL){
		swprintf_s(text,_countof(text), L"��������Ϣ-�ر���Ϣ:%d\r\n", hw);
		OutputDebugString(text);
		PostMessage(core_hwnd, WM_CORE_WECHAT_EXIT_MESSAGE, (WPARAM)hw, 0);	//��һ�����Ĺرմ��ڹر���
	}else{
		OutputDebugString(L"û���ҵ�����");
	}
}

//���浱ǰ���㴰�ھ��
void SaveWechatHWND(){
	//
}


//��ȡҵ����Ϣ��ϢHWND
HWND GetSuperMessageHWND(){
	return 0;
}