// Multiply.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Multiply.h"
#include "afxdialogex.h"
#include "Size.h"
#include "showTime.h"
#include "Suffix.h"


// Multiply 对话框

IMPLEMENT_DYNAMIC(Multiply, CDialogEx)

Multiply::Multiply(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_pass1(_T("请选择图片所在文件夹"))
	, m_pass2(_T("请选择保存处理后图片的文件夹"))
	, m_set(_T(""))
	, m_set1(_T(""))
{

}

Multiply::~Multiply()
{
}

void Multiply::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_pass1);
	DDX_Text(pDX, IDC_EDIT3, m_pass2);
	//DDX_Control(pDX, IDC_STATIC1, m_fout);
	DDX_Control(pDX, IDC_COMBO1, m_size);
	DDX_CBString(pDX, IDC_COMBO1, m_set);
	DDX_Control(pDX, IDC_COMBO2, m_suffix);
	DDX_Control(pDX, IDC_EDIT1, m_PASS1);
	DDX_Control(pDX, IDC_EDIT3, m_PASS2);
	DDX_CBString(pDX, IDC_COMBO2, m_set1);
}


BEGIN_MESSAGE_MAP(Multiply, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Multiply::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &Multiply::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &Multiply::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Multiply::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON3, &Multiply::OnBnClickedButton3)
END_MESSAGE_MAP()


// Multiply 消息处理程序


void Multiply::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectFolder(IDC_EDIT1, m_pass1); //选择图片所在文件夹
}


void Multiply::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectFolder(IDC_EDIT3, m_pass2);  //选择处理后的图片存储位置
}


void Multiply::SelectFolder(UINT ID, CString pass)  // 选择文件夹以及创建新文件夹
{
	// TODO: 在此处添加实现代码.
	BROWSEINFO PictureOpenFile; //创建一个可以指定文件夹的结构体
	
	PictureOpenFile.hwndOwner = NULL;
	PictureOpenFile.pidlRoot = CSIDL_DESKTOP;//文件夹的根目录，此处为桌面
	PictureOpenFile.pszDisplayName = NULL;
	PictureOpenFile.lpszTitle = NULL;//显示位于对话框左上部的提示信息
	if(ID==IDC_EDIT1)
		PictureOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;//无新建文件夹按钮
	else
		PictureOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//有新建文件夹按钮
	PictureOpenFile.lpfn = NULL;
	PictureOpenFile.iImage = 0;
	
	LPITEMIDLIST pidl = SHBrowseForFolder(&PictureOpenFile);//调用选择对话框

	if (pidl == NULL)
	{
		if (ID==IDC_EDIT1)
			MessageBox(_T("请重新选择图片所在文件夹！"));
		else
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


BOOL Multiply::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_Fout.CreatePointFont(95, _T("SimSun"), NULL);  //宋体，95大小
	//m_fout.SetFont(&m_Fout, true);
	//m_fout.SetWindowTextW(_T("分割大小"));

	//初始化尺寸列表
	m_size.AddString(_T("5×5"));
	m_size.AddString(_T("10×10"));
	m_size.AddString(_T("20×20"));
	m_size.AddString(_T("30×30"));
	m_size.AddString(_T("40×40"));
	m_size.AddString(_T("48×48"));
	m_size.AddString(_T("64×64"));
	m_size.AddString(_T("128×128"));
	m_size.AddString(_T("自定义"));
	
	//初始化图片格式列表
	m_suffix.AddString(_T(".jpg"));
	m_suffix.AddString(_T(".bmp"));
	m_suffix.AddString(_T(".gif"));
	m_suffix.AddString(_T(".png"));
	m_suffix.AddString(_T("自定义"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Multiply::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("尺寸单位：像素"));
	m_size.ShowDropDown(TRUE);   //弹出组合框列表
}


void Multiply::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	m_PASS1.GetWindowTextW(m_pass1);    //获取编辑框内的内容
	m_PASS2.GetWindowTextW(m_pass2);    //获取编辑框内的内容

	if (m_pass1 == _T("请选择图片所在文件夹"))
	{
		MessageBox(_T("未选择图片所在文件夹！"));
		return;
	}
	if (m_pass2 == _T("请选择保存处理后图片的文件夹"))
	{
		MessageBox(_T("未选择存储处理后图片的文件夹！"));
		return;
	}
	m_SavePass = m_pass2;   //动态变量存储到静态变量中（分割后图片存储）
	if (m_size.GetCurSel() == CB_ERR)
	{
		MessageBox(_T("未选择分割尺寸！"));
		return;
	}
	if (m_suffix.GetCurSel() == CB_ERR)
	{
		MessageBox(_T("未选择图片格式！"));
		return;
	}

	//尺寸自定义
	int nIndex = m_size.GetCurSel();    //获取分割尺寸列表中选择的内容
	//CString strCBText;
	m_size.GetLBText(nIndex, m_SIZE);
	if (m_SIZE == _T("自定义"))
	{
		PicSize dlg2;
		dlg2.DoModal();
		if ((m_WideS1 != _T("a")) && (m_LongS1 != _T("a")))  //确保用户自定义了尺寸
		{
			m_set = m_WideS1 + _T("×") + m_LongS1;
			GetDlgItem(IDC_COMBO1)->SetWindowTextW(m_set);     //在窗口标题上显示路径
		}
		else
			return;
		m_SIZE = m_set;
	}

	//格式自定义
	int nIndex1 = m_suffix.GetCurSel();   //获取图片格式列表中选择的内容
	m_suffix.GetLBText(nIndex1, m_suff);
	if (m_suff == _T("自定义"))
	{
		MessageBox(_T("注意：需按照“.后缀”的方式输入自定义的图片类型，例如：“.jpg”，引号不需要输入"));
		Suffix dlg7;
		dlg7.DoModal();
		if (m_suff != _T("自定义"))  //确保用户自定义了尺寸
		{
			GetDlgItem(IDC_COMBO2)->SetWindowTextW(m_suff);     //在窗口标题上显示路径
		}
		else
			return;
	}

	//统计图片数量
	TCHAR *szPath;      //待处理图片所在文件夹
	TCHAR *szFileName;  //待处理图片类型
	//CStringArray paStrResult;  //处理后图片存储路径

	szPath = m_pass1.GetBuffer(m_pass1.GetLength());  //初始化路径
	m_pass1.ReleaseBuffer();  //释放锁定

	szFileName = m_suff.GetBuffer(m_suff.GetLength());  //初始化文件后缀
	m_suff.ReleaseBuffer();  //释放锁定

	num=NumOfPicture(szPath, szFileName, &m_namePic);
	CString ss;
	ss.Format(_T("%d"), num);
	ss = _T("共找到") + ss + _T("张图片，按确定继续");
	MessageBox(ss);
	
	//m_namePic = paStrResult;

	//分割图片，双线程
	if (num != 0)
	{
		AfxBeginThread(Cut, this);
		AfxBeginThread(ChangeProcessBox, this);
		showTime dlg35;
		dlg35.DoModal();
		k3 = k3 + k; //更新k3
		CString ss1;
		CString ss2;
		CString ss3;
		CString ss4;
		ss1.Format(_T("%d"), k);
		ss2.Format(_T("%d"), k1);
		ss3.Format(_T("%d"), k2);
		ss4.Format(_T("%d"), k3);
		ss = _T("本次处理：") + ss1 + _T("张图片；共分割为：") + ss2 + _T("张图片\n累计处理：") + ss4 + _T("张图片；共分割为：") + ss3 + _T("张图片");
		MessageBox(ss);
		k = 0;  //更新k
		k1 = 0; //更新k1
		m_namePic.RemoveAll(); //初始化存储图片名字的数组
	}
	else
	{
		MessageBox(_T("文件夹中没有指定类型的图片！请重试！"));
		return;
	}
}



int Multiply::NumOfPicture(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult)
//搜索指定文件夹下的所有图片，并返回图片数量
//第一个参数为要搜索的路径，比如"c:\\dir\\"或"c:\\dir"则在包括此目录的所有子目录下搜索
//第二个参数为要搜索的文件,比如"qq.txt"，需要提供文件后缀，大小写不敏感  
//第三个参数用于保存搜索到的文件的全路径，请构造一个CStringArray对象并传入地址
{
	// TODO: 在此处添加实现代码.
	ASSERT(paStrResult != NULL);

	CString StrPath(szPath);

	CString StrFileName(szFileName);

	//检查路径字符串的最后一个字符是不是'\',不是则加上  

	if (StrPath[StrPath.GetLength() - 1] != _T('\\'))

		StrPath += _T('\\');


	CString StrFindPath = StrPath + _T("*.*");

	//开始查找  

	CFileFind finder;
	BOOL bWorking = finder.FindFile(StrFindPath);

	while (bWorking)

	{

		bWorking = finder.FindNextFile();

		//如果找到的是文件夹，递归进去  

		if (finder.IsDirectory() && !finder.IsDots())

		{

			NumOfPicture(StrPath + finder.GetFileName(), StrFileName, paStrResult);

		}

		//如果找到了文件，将绝对路径添加进字符串数组,大小写不敏感  

		if (finder.GetFileName().Right(4).MakeLower().CompareNoCase(StrFileName) == 0)

		{

			paStrResult->Add(finder.GetFilePath());

		}
	}


	//将字符串数组中的内容存储到字符串中
	int iden = paStrResult->GetSize();
	//CString load;
	/*
	if (iden == 0)
	{
		load = _T("1");
	}
	else if (iden > 1)
	{
		load = _T("2");
	}
	else
	{
		for (int i = 0; i < iden; i++)
		{
			load = load + paStrResult->GetAt(i);
		}
	}
	*/
	return iden;
}


void Multiply::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_suffix.ShowDropDown(TRUE);   //弹出组合框列表
}


UINT Multiply::ChangeProcessBox(LPVOID pParam)  // 控制进度条变化
{
	// TODO: 在此处添加实现代码.
	while (k != num)
	{
		for (int i = 0; i < 10; i++)
		{
			//空循环保持线程不销毁
		}
	}
	return 0;
}


// 批量裁剪图片，实现多线程，内核是全局变量单图片裁剪函数
UINT Multiply::Cut(LPVOID pParam)
{
	// TODO: 在此处添加实现代码.
	CString name;
	for (int i = 0; i < num; i++)
	{
		name = m_namePic.GetAt(i); //获取图片名字及路径
		CutPicture(name, m_SavePass, m_SIZE, k2); //分割一个图片
	}
	return 0;
}
