
// Library_Management_SystemDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "sql_utils.h"

// CLibrary_Management_SystemDlg 对话框
class CLibrary_Management_SystemDlg : public CDialogEx
{
// 构造
public:
	CLibrary_Management_SystemDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CLibrary_Management_SystemDlg();

// 对话框数据
	enum { IDD = IDD_LIBRARY_MANAGEMENT_SYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_obj_type;
	void init_combo_type();
	void init_list_show();
	CListCtrl m_list_show;
	afx_msg void OnBnClickedButtonFind2();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnNMClickListShow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListShow(NMHDR *pNMHDR, LRESULT *pResult);
	sql_utils* sql;
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnCbnSelchangeComboObjType();
	afx_msg void OnBnClickedButtonOut();
	afx_msg void OnBnClickedButtonIn();
	void show_list_by_type();
	void count_number();
	long m_num_obj;
	long m_num_book;
	long m_num_vedio;
	long m_num_picture;
};
