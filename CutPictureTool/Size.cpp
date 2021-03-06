// PicSize.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Size.h"
#include "afxdialogex.h"


// PicSize 对话框

IMPLEMENT_DYNAMIC(PicSize, CDialogEx)

PicSize::PicSize(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_Wide(_T("在此输入宽度"))
	, m_Long(_T("在此输入长度"))
{

}

PicSize::~PicSize()
{
}

void PicSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_fout);
	DDX_Text(pDX, IDC_EDIT1, m_Wide);
	DDX_Text(pDX, IDC_EDIT2, m_Long);
	DDX_Control(pDX, IDC_EDIT1, m_WideSize);
	DDX_Control(pDX, IDC_EDIT2, m_LongSize);
}


BEGIN_MESSAGE_MAP(PicSize, CDialogEx)
	//ON_BN_CLICKED(IDOK, &PicSize::OnBnClickedOk)
	ON_BN_CLICKED(IDOK, &PicSize::OnBnClickedOk)
END_MESSAGE_MAP()


// PicSize 消息处理程序


BOOL PicSize::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_fout.SetWindowTextW(_T("×"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void PicSize::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	
	char c;
	for (int i = 0; i < m_Wide.GetLength(); i++)
	{
		c = m_Wide.GetAt(i);
		if (!(c >= '0'&&c <= '9'))
		{
			MessageBox(_T("请输入正确的宽度！"));
			return;
		}
	}
	for (int i = 0; i < m_Long.GetLength(); i++)
	{
		c = m_Long.GetAt(i);
		if (!(c >= '0'&&c <= '9'))
		{
			MessageBox(_T("请输入正确的长度！"));
			return;
		}
	}
	m_WideSize.GetWindowTextW(m_WideS1);
	m_LongSize.GetWindowTextW(m_LongS1);
}
