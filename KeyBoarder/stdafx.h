// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib.lib")
#   endif
#endif


#define WM_LISTMENULOCKMESSAGEBOX (WM_USER + 1001)
#define WM_SELECTEDICOPATH			(WM_USER + 1002)
#define WM_TITLESELECTEDCONFIG		(WM_USER + 1003)
#define WM_READINIFILE				(WM_USER + 1004)
#define WM_SOFTWARELIST				(WM_USER + 1005)
#define WM_SYSTEMTRAY_NOTIFY		(WM_USER + 1006)
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
