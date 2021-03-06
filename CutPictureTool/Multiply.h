#pragma once


// Multiply 对话框

class Multiply : public CDialogEx
{
	DECLARE_DYNAMIC(Multiply)

public:
	Multiply(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Multiply();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//变量
	//图片路径编辑框
	CString m_pass1;
	CEdit m_PASS1;
	//存储处理后图片路径编辑框
	CString m_pass2;
	CEdit m_PASS2;
	//尺寸列表
	CComboBox m_size;
	CString m_set;
	//格式列表
	CComboBox m_suffix;
	CString m_set1;

	//按键函数&系统函数
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton3();

	//功能函数
	virtual BOOL OnInitDialog();
	void SelectFolder(UINT ID, CString pass); // 选择文件夹以及创建新文件夹
	int NumOfPicture(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult);  // 搜索指定文件夹下的所有图片，并返回图片数量
	static UINT ChangeProcessBox(LPVOID pParam); // 控制进度条变化
	static UINT Cut(LPVOID pParam); // 批量裁剪图片，实现多线程，内核是全局变量单图片裁剪函数
};
