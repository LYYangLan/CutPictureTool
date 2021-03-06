#pragma once


// Select 对话框

class Select : public CDialogEx
{
	DECLARE_DYNAMIC(Select)

public:
	Select(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Select();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//变量
	//尺寸列表框
	CComboBox m_SelSize;
	CString m_SelSize1;
	//类型列表框
	CComboBox m_SelType;
	//图片路径编辑框
	CString m_SelPath;
	CEdit m_SelPathC;
	//存储图片路径编辑框
	CString m_AfPath;
	CEdit m_AfPathC;
	//其他变量
	int num1;

	//按钮函数
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();

	//其他函数
	int NumOfPicture1(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult);  //按类型搜索
	int NumOfPicture2(const TCHAR *szPath, const TCHAR *szFileName, CStringArray *paStrResult);  //按尺寸搜索
	void Save();  //保存图片
	void SelectFolder(UINT ID, CString pass);  //选择文件夹
};
