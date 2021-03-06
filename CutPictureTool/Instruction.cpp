// Instruction.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Instruction.h"
#include "afxdialogex.h"


// Instruction 对话框

IMPLEMENT_DYNAMIC(Instruction, CDialogEx)

Instruction::Instruction(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

Instruction::~Instruction()
{
}

void Instruction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_picture);
}


BEGIN_MESSAGE_MAP(Instruction, CDialogEx)
	ON_BN_CLICKED(IDOK, &Instruction::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Instruction::OnBnClickedButton1)
END_MESSAGE_MAP()


// Instruction 消息处理程序


BOOL Instruction::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_bitmap1.LoadBitmapW(IDB_BITMAP1);
	m_bitmap2.LoadBitmapW(IDB_BITMAP2);
	m_bitmap3.LoadBitmapW(IDB_BITMAP3);
	m_bitmap4.LoadBitmapW(IDB_BITMAP4);
	m_picture.SetBitmap((HBITMAP)m_bitmap1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Instruction::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	pic--;
	if (pic == 1 || pic == 2 || pic == 3||pic==4)
	{
		if (pic == 1)
			m_picture.SetBitmap((HBITMAP)m_bitmap1);
		if (pic == 2)
			m_picture.SetBitmap((HBITMAP)m_bitmap2);
		if (pic == 3)
			m_picture.SetBitmap((HBITMAP)m_bitmap3);
		if (pic == 4)
			m_picture.SetBitmap((HBITMAP)m_bitmap4);
	}
	else
	{
		MessageBox(_T("已经是第一页！"));
		pic = 1;
	}
}


void Instruction::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	pic++;
	if (pic == 1 || pic == 2 || pic == 3 || pic==4)
	{
		if (pic == 1)
			m_picture.SetBitmap((HBITMAP)m_bitmap1);
		if (pic == 2)
			m_picture.SetBitmap((HBITMAP)m_bitmap2);
		if (pic == 3)
			m_picture.SetBitmap((HBITMAP)m_bitmap3);
		if (pic == 4)
			m_picture.SetBitmap((HBITMAP)m_bitmap4);
	}
	else
	{
		MessageBox(_T("已经是最后一页！"));
		pic = 4;
	}
}
