#pragma once
#include "afxwin.h"


// CDlg_Find 对话框

class CDlg_Find : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Find)

public:
	CDlg_Find(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Find();

// 对话框数据
	enum { IDD = IDD_DIALOG_FIND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	BOOL OnInitDialog();
	void init_combo_obj_type();
	CComboBox m_combo_obj_type;
	CString m_info;
	CString m_type;

	afx_msg void OnBnClickedOk();
};
