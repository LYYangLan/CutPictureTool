// Select.cpp: 实现文件
//

#include "stdafx.h"
#include "CutPictureTool.h"
#include "Select.h"
#include "afxdialogex.h"
#include "Suffix.h"
#include "Size.h"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
// Select 对话框

IMPLEMENT_DYNAMIC(Select, CDialogEx)

Select::Select(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, m_SelSize1(_T(""))
	, m_SelPath(_T("请选择图片所在文件夹"))
	, m_AfPath(_T("请选择保存筛选出来的图片的文件夹"))
{

}

Select::~Select()
{
}

void Select::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SelSize);
	DDX_Control(pDX, IDC_COMBO2, m_SelType);
	DDX_CBString(pDX, IDC_COMBO1, m_SelSize1);
	DDX_Text(pDX, IDC_EDIT1, m_SelPath);
	DDX_Text(pDX, IDC_EDIT2, m_AfPath);
	DDX_Control(pDX, IDC_EDIT1, m_SelPathC);
	DDX_Control(pDX, IDC_EDIT2, m_AfPathC);
}


BEGIN_MESSAGE_MAP(Select, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Select::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Select::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Select::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Select::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &Select::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &Select::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Select::OnBnClickedButton4)
END_MESSAGE_MAP()


// Select 消息处理程序


void Select::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("尺寸单位：像素"));
	m_SelSize.ShowDropDown(TRUE);   //弹出组合框列表
}


void Select::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_SelType.ShowDropDown(TRUE);   //弹出组合框列表
}


BOOL Select::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//初始化尺寸列表
	m_SelSize.AddString(_T("5×5"));
	m_SelSize.AddString(_T("10×10"));
	m_SelSize.AddString(_T("20×20"));
	m_SelSize.AddString(_T("30×30"));
	m_SelSize.AddString(_T("40×40"));
	m_SelSize.AddString(_T("48×48"));
	m_SelSize.AddString(_T("64×64"));
	m_SelSize.AddString(_T("128×128"));
	m_SelSize.AddString(_T("自定义"));

	//初始化图片格式列表
	m_SelType.AddString(_T(".jpg"));
	m_SelType.AddString(_T(".bmp"));
	m_SelType.AddString(_T(".gif"));
	m_SelType.AddString(_T(".png"));
	m_SelType.AddString(_T("自定义"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Select::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	m_SelPathC.GetWindowTextW(m_SelPath);    //获取编辑框内的内容

	if (m_SelPath == _T("请选择图片所在文件夹"))
	{
		MessageBox(_T("未选择图片所在文件夹！"));
		return;
	}
	if ((m_SelSize.GetCurSel() == CB_ERR)&& (m_SelType.GetCurSel() == CB_ERR))
	{
		MessageBox(_T("请至少选择一种筛选规则：尺寸或类型！"));
		return;
	}

	if (m_SelSize.GetCurSel() != CB_ERR)
	{
		//尺寸自定义
		int nIndex = m_SelSize.GetCurSel();    //获取分割尺寸列表中选择的内容
		//CString strCBText;
		m_SelSize.GetLBText(nIndex, m_SIZE);
	}
	if (m_SIZE == _T("自定义"))
	{
		PicSize dlg2;
		dlg2.DoModal();
		if ((m_WideS1 != _T("a")) && (m_LongS1 != _T("a")))  //确保用户自定义了尺寸
		{
			m_SelSize1 = m_WideS1 + _T("×") + m_LongS1;
			GetDlgItem(IDC_COMBO1)->SetWindowTextW(m_SelSize1);     //在窗口标题上显示路径
		}
		else
			return;
		m_SIZE = m_SelSize1;
	}
	

	if (m_SelType.GetCurSel() != CB_ERR)
	{
		//格式自定义
		int nIndex1 = m_SelType.GetCurSel();   //获取图片格式列表中选择的内容
		m_SelType.GetLBText(nIndex1, m_suff);
	}
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

	MessageBox(_T("请耐心等待，出现未响应也不要慌张，等待片刻即可"));
	//统计图片数量
	TCHAR *szPath;      //待处理图片所在文件夹
	TCHAR *szFileName;  //待处理图片类型
	//CStringArray paStrResult;  //处理后图片存储路径

	szPath = m_SelPath.GetBuffer(m_SelPath.GetLength());  //初始化路径
	m_SelPath.ReleaseBuffer();  //释放锁定

	szFileName = m_suff.GetBuffer(m_suff.GetLength());  //初始化文件后缀
	m_suff.ReleaseBuffer();  //释放锁定

	if (m_namePic.GetSize() != 0)   //防止多次点击确定按钮，造成图片与实际数目不符
		m_namePic.RemoveAll();
	//如果指定了类型
	if (m_SelType.GetCurSel() != CB_ERR)
	{
		num1 = NumOfPicture1(szPath, szFileName, &m_namePic);
	}

	//如果指定了大小
	if (m_SelSize.GetCurSel() != CB_ERR)
	{
		num1 = NumOfPicture2(szPath, szFileName, &m_namePic);
	}

	if (num1 == 0)
	{
		MessageBox(_T("没有满足要求的图片！"));
		return;
	}
	CString ss;
	ss.Format(_T("%d"), num1);
	ss = _T("共找到") + ss + _T("张图片，按“保存”另存所找到的图片，按“返回”回退上一步");
	MessageBox(ss);

	//m_namePic = paStrResult;

}


int Select::NumOfPicture1(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult)
//搜索指定文件夹下的指定类型的所有图片，并返回图片数量
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

		if (finder.IsDirectory() && !finder.IsDots()) //略去缺省目录

		{

			NumOfPicture1(StrPath + finder.GetFileName(), StrFileName, paStrResult);

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


int Select::NumOfPicture2(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult)
//搜索指定文件夹下的指定尺寸的所有图片，并返回图片数量
//第一个参数为要搜索的路径，比如"c:\\dir\\"或"c:\\dir"则在包括此目录的所有子目录下搜索
//第二个参数为要搜索的文件,比如"qq.txt"，需要提供文件后缀，大小写不敏感  
//第三个参数用于保存搜索到的文件的全路径，请构造一个CStringArray对象并传入地址
{
	// TODO: 在此处添加实现代码.
	ASSERT(paStrResult != NULL);

	//如果没指定类型，则所搜指定文件夹下所有的文件，并存储路径
	if (m_SelType.GetCurSel() == CB_ERR)
	{
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

			if (finder.IsDirectory() && !finder.IsDots()) //略去缺省目录

			{

				NumOfPicture1(StrPath + finder.GetFileName(), StrFileName, paStrResult);

			}

			//如果找到了文件，将绝对路径添加进字符串数组,大小写不敏感  
			else if(!finder.IsDots())
			{
				paStrResult->Add(finder.GetFilePath());
			}

		}
	}
	
	//判断文件是否是图片，如果是图片，判断尺寸是否满足要求
	CString name;
	CString WIDE = m_SIZE.Left(m_SIZE.Find(_T("×"))); //获得分割后的小图片的宽度
	CString HIGH = m_SIZE.Right(m_SIZE.GetLength() - m_SIZE.Find(_T("×")) - 1); //获得分割后的小图像的高度
	//将获取的高度宽度转换为整型
	int WiDe = _ttoi(WIDE);
	int HiGh = _ttoi(HIGH);
	for (int i = 0; i < (paStrResult->GetSize()); i++)
	{
		name = m_namePic.GetAt(i); //获取图片名字及路径
		string Name(CW2A(name.GetBuffer()));  //CString转string，图片名字初始化
		
		Mat imgSel = imread(Name, -1);

		if ((imgSel.empty()) || (imgSel.cols != WiDe) || (imgSel.rows != HiGh))
		{
			paStrResult->RemoveAt(i);
			i--;
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


void Select::Save()    //保存满足要求的图片
{
	// TODO: 在此处添加实现代码.
	MessageBox(_T("请耐心等待，出现未响应也不要慌张，等待片刻即可"));
	if (num1 == 0)
	{
		MessageBox(_T("没有满足要求的图片！"));
		return;
	}
	m_AfPathC.GetWindowTextW(m_AfPath);    //获取编辑框内的内容
	if (m_AfPath == _T("请选择保存筛选出来的图片的文件夹"))
	{
		MessageBox(_T("未选择存储筛选出来的图片的文件夹！"));
		return;
	}
	m_SavePass = m_AfPath;   //动态变量存储到静态变量中（筛选后图片存储）

	CString name;
	CString name1;
	for (int i = 0; i < num1; i++)
	{
		name1 = m_namePic.GetAt(i);
		string Name1(CW2A(name1.GetBuffer()));  //CString转string，图片名字初始化
		Mat imgSel = imread(Name1, -1);
		name1 = name1.Right(name1.GetLength() - name1.ReverseFind('\\'));  //获取图片名字
		name = m_AfPath + name1; //保存路径
		
		string Name(CW2A(name.GetBuffer()));  //CString转string，图片名字初始化

		
		//imshow("1", imgSel);
		//waitKey();
		imwrite(Name, imgSel);

	}
	m_namePic.RemoveAll(); //初始化存储图片名字的数组
	MessageBox(_T("已完成！"));
}


void Select::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	m_namePic.RemoveAll();
}


void Select::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	Save();
}


void Select::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectFolder(IDC_EDIT1, m_SelPath);
}


void Select::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	SelectFolder(IDC_EDIT2, m_AfPath);
}


void Select::SelectFolder(UINT ID, CString pass)   //选择文件夹对话框
{
	// TODO: 在此处添加实现代码.
	BROWSEINFO PictureOpenFile; //创建一个可以指定文件夹的结构体

	PictureOpenFile.hwndOwner = NULL;
	PictureOpenFile.pidlRoot = CSIDL_DESKTOP;//文件夹的根目录，此处为桌面
	PictureOpenFile.pszDisplayName = NULL;
	PictureOpenFile.lpszTitle = NULL;//显示位于对话框左上部的提示信息
	if (ID == IDC_EDIT1)
		PictureOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;//无新建文件夹按钮
	else
		PictureOpenFile.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;//有新建文件夹按钮
	PictureOpenFile.lpfn = NULL;
	PictureOpenFile.iImage = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&PictureOpenFile);//调用选择对话框

	if (pidl == NULL)
	{
		if (ID == IDC_EDIT1)
			MessageBox(_T("请重新选择图片所在文件夹！"));
		else
			MessageBox(_T("请重新选择保存筛选后图片的路径！"));

		CoTaskMemFree((LPVOID)pidl);   //释放pidl指向的内存空间
		return;
	}

	TCHAR strFolder[1024];
	SHGetPathFromIDList(pidl, strFolder);
	pass = strFolder;
	GetDlgItem(ID)->SetWindowTextW(pass);     //在窗口标题上显示路径

	CoTaskMemFree((LPVOID)pidl); //释放pidl指向的内存空间
}
