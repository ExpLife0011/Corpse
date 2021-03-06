#include "stdafx.h"
#include "AboutDialog.h"
#include "../Utils/TimeInfo.h"

CAboutDialog::CAboutDialog(HWND hWnd)
{
	Create(hWnd,_T("系统信息查看工具"), WS_POPUP|UI_WNDSTYLE_DIALOG,WS_EX_TOOLWINDOW, 0, 0, 0, 0);
}

CAboutDialog::~CAboutDialog()
{

}

void CAboutDialog::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

void CAboutDialog::InitWindow()
{
	CLabelUI* pBuildTime = (CLabelUI*)m_PaintManager.FindControl(_T("BuildTime"));
	if (pBuildTime)
	{
		SYSTEMTIME BuildTime;
		if (GetBuildSystemTime(&BuildTime) != FALSE)
		{
			CDuiString strTipInfo;
			strTipInfo.Format(_T("编译时间:%d-%02d-%02d %02d:%02d:%02d"), 
							BuildTime.wYear, BuildTime.wMonth, BuildTime.wDay,
							BuildTime.wHour, BuildTime.wMinute, BuildTime.wSecond);

			pBuildTime->SetText(strTipInfo);
		}
	}

	CLabelUI* pCopyRight = (CLabelUI*)m_PaintManager.FindControl(_T("CopyRight"));
	if (pCopyRight)
	{
		SYSTEMTIME BuildTime;
		if (GetBuildSystemTime(&BuildTime) != FALSE)
		{
			CDuiString strTipInfo;
			strTipInfo.Format(_T("CopyRight © 2013-%d , All Rights Reserved"), BuildTime.wYear);

			pCopyRight->SetText(strTipInfo);
		}
	}

	CenterWindow();
}

void CAboutDialog::Notify(TNotifyUI &msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
		OnClick(msg);
}

CDuiString CAboutDialog::GetSkinFile()
{
	return _T("About.xml");
}

CDuiString CAboutDialog::GetSkinFolder()
{
	return _T("PCHunter");
}

LPCTSTR CAboutDialog::GetWindowClassName(void) const
{
	return _T("AboutDlg");
}

void CAboutDialog::OnClick(TNotifyUI& msg)
{
	CDuiString strSender = msg.pSender->GetName();
	if (strSender == _T("BtnClose"))
		Close(IDOK);
}

LRESULT CAboutDialog::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_ESCAPE)
	{
		Close();
		return TRUE;
	}
	return FALSE;
}