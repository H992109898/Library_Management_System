// Dlg_Find.cpp : 实现文件
//

#include "stdafx.h"
#include "Library_Management_System.h"
#include "Dlg_Find.h"
#include "afxdialogex.h"


// CDlg_Find 对话框

IMPLEMENT_DYNAMIC(CDlg_Find, CDialogEx)

CDlg_Find::CDlg_Find(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_Find::IDD, pParent)
	, m_info(_T(""))
{

}

BOOL CDlg_Find::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	init_combo_obj_type();
	return TRUE;
}

CDlg_Find::~CDlg_Find()
{
}

void CDlg_Find::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo_obj_type);
	DDX_Text(pDX, IDC_EDIT_INFO, m_info);
}


BEGIN_MESSAGE_MAP(CDlg_Find, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &CDlg_Find::OnBnClickedOk)
END_MESSAGE_MAP()

void CDlg_Find::init_combo_obj_type()
{
	m_combo_obj_type.AddString(_T("标题"));
	m_combo_obj_type.AddString(_T("编号"));
	m_combo_obj_type.AddString(_T("类别"));
}

// CDlg_Find 消息处理程序




void CDlg_Find::OnBnClickedOk()
{
	int nSel;
	nSel = m_combo_obj_type.GetCurSel();
	m_combo_obj_type.GetLBText(nSel, m_type);
	UpdateData();

	if (m_type.GetLength() == 0)
		MessageBox(L"请选择查找类型", 0);
	else if (m_info.GetLength() == 0)
		MessageBox(L"请输入查找信息", 0);
	else
		CDialogEx::OnOK();

}
