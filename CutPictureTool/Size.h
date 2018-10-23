#pragma once


// Size 对话框

class Size : public CDialogEx
{
	DECLARE_DYNAMIC(Size)

public:
	Size(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Size();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_fout;
	virtual BOOL OnInitDialog();
	CString m_Wide;
	CString m_Long;
	CEdit m_WideSize;
	CEdit m_LongSize;
	afx_msg void OnBnClickedOk();
};
