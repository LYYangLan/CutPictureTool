// shoeTime.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "showTime.h"
#include "afxdialogex.h"


// shoeTime 对话框

IMPLEMENT_DYNAMIC(showTime, CDialogEx)

showTime::showTime(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, c_number(_T(""))
{

}

showTime::~showTime()
{
}

void showTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_process);
	DDX_Text(pDX, IDC_STATIC1, c_number);
	DDX_Control(pDX, IDC_STATIC1, m_number);
}


BEGIN_MESSAGE_MAP(showTime, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// shoeTime 消息处理程序


BOOL showTime::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Font.CreatePointFont(120, _T("SimSun"), NULL);
	m_number.SetFont(&m_Font, true);
	m_process.SetRange(0, num);  //初始化进度条范围

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void showTime::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	m_process.SetPos(k);
	CString number;
	CString number1;
	number.Format(_T("%d"), k);
	number1.Format(_T("%d"), num);
	c_number = _T("已完成：") + number + _T("/") + number1;
	GetDlgItem(IDC_STATIC1)->SetWindowTextW(c_number);
	if (k == num)
		OnOK();
}


void showTime::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 在此处添加消息处理程序代码
	this->KillTimer(1);
	this->SetTimer(1, 0.00000000001, NULL);
}
