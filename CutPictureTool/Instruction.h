#pragma once


// Instruction 对话框

class Instruction : public CDialogEx
{
	DECLARE_DYNAMIC(Instruction)

public:
	Instruction(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Instruction();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_picture;
	CBitmap m_bitmap1, m_bitmap2, m_bitmap3, m_bitmap4; //位图变量
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
