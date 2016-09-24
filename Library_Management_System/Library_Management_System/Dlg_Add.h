#pragma once
#include "afxwin.h"
#include "sql_utils.h"

// CDlg_Add 对话框

class CDlg_Add : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg_Add)

public:
	CDlg_Add(sql_utils *sql, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_Add();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog();
	void init_add_combo();
	CString type;
	CComboBox m_type;
	long m_id;
	CString m_title;
	CString m_author;
	CString m_rate;
	long m_ISBN;
	CString m_press;
	int m_pagenum;
	
	
	int m_vedio_time;
	CString m_nation;
	int m_width;
	int m_length;
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboObjType();
	CString m_produce_year;
	CComboBox m_combo_rate;
	void init_rate_combo();
	afx_msg void OnCbnSelchangeComboRate();
	CString m_produce_name;

	sql_utils *sql;
};
