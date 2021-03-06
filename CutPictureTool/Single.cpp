// Single.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Single.h"
#include "afxdialogex.h"
#include "size.h"


// Single 对话框

IMPLEMENT_DYNAMIC(Single, CDialogEx)

Single::Single(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_pass(_T("请选择要处理的图片"))
	, m_pass1(_T("请选择保存处理后图片的文件夹"))
	, m_set(_T(""))
{

}

Single::~Single()
{
}

void Single::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_pass);
	DDX_Control(pDX, IDC_COMBO1, m_size1);
	DDX_Text(pDX, IDC_EDIT4, m_pass1);
	DDX_CBString(pDX, IDC_COMBO1, m_set);
	DDX_Control(pDX, IDC_EDIT1, M_PASS);
	DDX_Control(pDX, IDC_EDIT4, M_PASS1);
}


BEGIN_MESSAGE_MAP(Single, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Single::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &Single::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &Single::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &Single::OnBnClickedButton4)
END_MESSAGE_MAP()


// Single 消息处理程序


void Single::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog BMOpenFile(1, 0, 0, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, _T("JPEG(*.jpg)|*.jpg|BMP(*.bmp)|*.bmp|GIF(*.gif)|*.gif|PNG(*.png)|*png||"));//生成一个对话框
	if (BMOpenFile.DoModal() == IDOK)//假如点击对话框确定按钮
	{
		m_pass = BMOpenFile.GetPathName();  //得到打开文件的路径
		GetDlgItem(IDC_EDIT1)->SetWindowTextW(m_pass);     //在窗口标题上显示路径
	}
	delete BMOpenFile;    //释放分配的对话框
}


void Single::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	M_PASS.GetWindowTextW(m_pass);    //获取编辑框内的内容
	M_PASS1.GetWindowTextW(m_pass1);    //获取编辑框内的内容

	if (m_pass == _T("请选择要处理的图片"))
	{
		MessageBox(_T("未选择图片！"));
		return;
	}
	CString name = m_pass;
	if (m_pass1 == _T("请选择保存处理后图片的文件夹"))
	{
		MessageBox(_T("未选择存储处理后图片的文件夹！"));
		return;
	}
	m_SavePass = m_pass1;   //动态变量存储到静态变量中（分割后图片存储）
	if (m_size1.GetCurSel() == CB_ERR)
	{
		MessageBox(_T("未选择分割尺寸！"));
		return;
	}

	int nIndex = m_size1.GetCurSel();    //获取分割尺寸列表中选择的内容
	//CString strCBText;
	m_size1.GetLBText(nIndex, m_SIZE);
	if (m_SIZE == _T("自定义"))
	{
		PicSize dlg2;
		dlg2.DoModal();
		if ((m_WideS1 != _T("a")) && (m_LongS1 != _T("a")))  //确保用户自定义了尺寸
		{
			m_set = m_WideS1 + _T("×") + m_LongS1;
			GetDlgItem(IDC_COMBO1)->SetWindowTextW(m_set);     //在窗口标题上显示路径
		}
		m_SIZE = m_set;
	}
	//m_namePic = paStrResult;

	CutPicture(name, m_SavePass, m_SIZE,0); //分割一个图片//分割图片
	
	k3 = k3 + k; //更新k3
	CString ss;
	CString ss2;
	CString ss3;
	CString ss4;
	ss2.Format(_T("%d"), k1);
	ss3.Format(_T("%d"), k2);
	ss4.Format(_T("%d"), k3);
	ss = _T("本次处理：1张图片；共分割为：") + ss2 + _T("张图片\n累计处理：") + ss4 + _T("张图片；共分割为：") + ss3 + _T("张图片");
	MessageBox(ss);
	k = 0;  //更新k
	k1 = 0; //更新k1
}


void Single::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_size1.ShowDropDown(TRUE);   //弹出组合框列表
}


BOOL Single::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	//初始化尺寸列表
	m_size1.AddString(_T("5×5"));
	m_size1.AddString(_T("10×10"));
	m_size1.AddString(_T("20×20"));
	m_size1.AddString(_T("30×30"));
	m_size1.AddString(_T("40×40"));
	m_size1.AddString(_T("48×48"));
	m_size1.AddString(_T("64×64"));
	m_size1.AddString(_T("128×128"));
	m_size1.AddString(_T("自定义"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Single::SelectFolder1(UINT ID, CString pass)  // 选择文件夹以及创建新文件夹
{
	// TODO: 在此处添加实现代码.
	BROWSEINFO PictureOpenFile; //创建一个可以指定文件夹的结构体

	PictureOpenFile.hwndOwner = NULL;
	PictureOpenFile.pidlRoot = CSIDL_DESKTOP;//文件夹的根目录，此处为桌面
	PictureOpenFile.pszDisplayName = NULL;
	PictureOpenFile.lpszTitle = NULL;//显示位于对话框左上部的提示信息
	PictureOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//有新建文件夹按钮
	PictureOpenFile.lpfn = NULL;
	PictureOpenFile.iImage = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&PictureOpenFile);//调用选择对话框

	if (pidl == NULL)
	{
		MessageBox(_T("请重新选择存储处理后的图片路径！"));

		CoTaskMemFree((LPVOID)pidl);   //释放pidl指向的内存空间
		return;
	}

	TCHAR strFolder[1024];
	SHGetPathFromIDList(pidl, strFolder);
	pass = strFolder;
	GetDlgItem(ID)->SetWindowTextW(pass);     //在窗口标题上显示路径

	CoTaskMemFree((LPVOID)pidl); //释放pidl指向的内存空间
}


void Single::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectFolder1(IDC_EDIT4, m_pass1);
}
