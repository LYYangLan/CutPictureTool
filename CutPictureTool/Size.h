#pragma once


// PicSize 对话框

class PicSize : public CDialogEx
{
	DECLARE_DYNAMIC(PicSize)

public:
	PicSize(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PicSize();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//控件变量
	//静态文本框
	CStatic m_fout;  
	//文本框
	CString m_Wide;
	CString m_Long;
	CEdit m_WideSize;
	CEdit m_LongSize;

	//按键函数&系统函数
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
