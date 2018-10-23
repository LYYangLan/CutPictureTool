#pragma once


// Single 对话框

class Single : public CDialogEx
{
	DECLARE_DYNAMIC(Single)

public:
	Single(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Single();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_pass;
	afx_msg void OnBnClickedOk();
	CComboBox m_size1;
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	void SelectFolder1(UINT ID, CString pass);
	CString m_pass1;
	CString m_set;
	afx_msg void OnBnClickedButton4();
	CEdit M_PASS;
	CEdit M_PASS1;
};
