// Suffix.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Suffix.h"
#include "afxdialogex.h"


// Suffix 对话框

IMPLEMENT_DYNAMIC(Suffix, CDialogEx)

Suffix::Suffix(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
	, m_Su1(_T("在此处输入图片的后缀"))
{

}

Suffix::~Suffix()
{
}

void Suffix::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Su);
	DDX_Text(pDX, IDC_EDIT1, m_Su1);
}


BEGIN_MESSAGE_MAP(Suffix, CDialogEx)
	ON_BN_CLICKED(IDOK, &Suffix::OnBnClickedOk)
END_MESSAGE_MAP()


// Suffix 消息处理程序


void Suffix::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	char c;
	c = m_Su1.GetAt(0);
	if (c != '.')
	{
		MessageBox(_T("请在后缀前加“.”，引号不需要输入"));
		return;
	}
	for (int i = 1; i < m_Su1.GetLength(); i++)
	{
		c = m_Su1.GetAt(i);
		if (!(c >= 'a'&&c <= 'z'))
		{
			MessageBox(_T("请输入正确的后缀！"));
			return;
		}
	}
	
	m_Su.GetWindowTextW(m_suff);
}
