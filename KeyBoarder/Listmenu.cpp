#include "stdafx.h"
#include "Listmenu.h"

Listmenu::Listmenu()
{
	bIsLock = false;
}


Listmenu::~Listmenu()
{
}

void Listmenu::Notify(TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("LockBtn"))
		{
			bIsLock = true; 
			::PostMessage(s_handle, WM_LISTMENULOCKMESSAGEBOX, 1, 0);
			Close();
		}
		else if (msg.pSender->GetName() == _T("UnLockBtn"))
		{
			bIsLock = false;
			Close();
		}
	}
}

DuiLib::CDuiString Listmenu::GetSkinFile()
{
	return _T("Listmenu.xml");
}
DuiLib::CDuiString Listmenu::GetSkinFolder()
{
	return _T("Listmenu");
}

void Listmenu::Init(POINT pt)
{
	PopupPosition(pt);
}
void Listmenu::PopupPosition(POINT pt)
{
	DuiLib::CDuiRect rcWnd, rcWork;
	int nWidth, nHeight;
	MONITORINFO oMonitor;
	HWND hWndParent;
	GetWindowRect(this->m_hWnd, &rcWnd);
	nWidth = 50;
	nHeight = 60;
	rcWnd.left = pt.x + 1;
	rcWnd.top = pt.y + 1;
	rcWnd.right = pt.x + nWidth;
	rcWnd.bottom = pt.y + nHeight;
	memset(&oMonitor, 0, sizeof(MONITORINFO));;
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	rcWork = oMonitor.rcWork;
	if (rcWnd.bottom > rcWork.bottom)
	{
		if (nHeight >= rcWork.GetHeight())
		{
			rcWnd.top = 0;
			rcWnd.bottom = nHeight;
		}
		else
		{
			rcWnd.bottom = rcWork.bottom;
			rcWnd.top = rcWnd.bottom - nHeight;
		}
	}
	if (rcWnd.right > rcWork.right)
	{
		if (nWidth >= rcWork.GetWidth())
		{
			rcWnd.left = 0;
			rcWnd.right = nWidth;
		}
		else
		{
			rcWnd.left = rcWnd.right - nWidth;
			rcWnd.right = rcWork.right;
		}
	}
	::SetWindowPos(m_hWnd, NULL, rcWnd.left, rcWnd.top, rcWnd.GetWidth(), rcWnd.GetHeight(), SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	hWndParent = m_hWnd;
	while (::GetParent(hWndParent) != NULL)
	{
		hWndParent = ::GetParent(hWndParent);
	}
	::ShowWindow(m_hWnd, SW_SHOW);
	::SendMessage(hWndParent, WM_NCACTIVATE, TRUE, 0L);
}

