#pragma once


// Suffix 对话框

class Suffix : public CDialogEx
{
	DECLARE_DYNAMIC(Suffix)

public:
	Suffix(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Suffix();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Su;
	CString m_Su1;
	afx_msg void OnBnClickedOk();
};
