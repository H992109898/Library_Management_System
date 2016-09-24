// Dlg_Add.cpp : 实现文件
//

#include "stdafx.h"
#include "Library_Management_System.h"
#include "Dlg_Add.h"
#include "afxdialogex.h"
#include "object.h"

// CDlg_Add 对话框

IMPLEMENT_DYNAMIC(CDlg_Add, CDialogEx)

CDlg_Add::CDlg_Add(sql_utils *sql, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_Add::IDD, pParent)
	, m_id(0)
	, m_title(_T(""))
	, m_author(_T(""))
	, m_rate(_T(""))
	, m_ISBN(0)
	, m_press(_T(""))
	, m_pagenum(0)
	, m_vedio_time(0)
	, m_nation(_T(""))
	, m_width(0)
	, m_length(0)
	, m_produce_year(_T(""))
	, m_produce_name(_T(""))
{
	this->sql = sql;
}

CDlg_Add::~CDlg_Add()
{
}

void CDlg_Add::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OBJ_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_author);

	DDX_Text(pDX, IDC_EDIT_ISBN, m_ISBN);
	DDX_Text(pDX, IDC_EDIT_PRESS, m_press);

	DDX_Text(pDX, IDC_EDIT_PAGENUM, m_pagenum);
	DDX_Text(pDX, IDC_EDIT1_VEDIO_TIME, m_vedio_time);
	DDX_Text(pDX, IDC_EDIT1_PRODECE_NATION, m_nation);
	DDX_Text(pDX, IDC_EDIT1_WIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT1_LENGTH, m_length);
	DDX_Text(pDX, IDC_EDIT1_PRODUCE_YEAR, m_produce_year);
	DDX_Control(pDX, IDC_COMBO_RATE, m_combo_rate);
	DDX_Text(pDX, IDC_EDIT_PRODUCE_NAME, m_produce_name);
}

BOOL CDlg_Add::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	init_add_combo();
	init_rate_combo();
	return TRUE;
}

void CDlg_Add::init_add_combo()
{
	m_type.AddString(_T("图书"));
	m_type.AddString(_T("视频光盘"));
	m_type.AddString(_T("图画"));
	GetDlgItem(IDC_EDIT_ISBN)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PAGENUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PRODUCE_NAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1_PRODUCE_YEAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1_VEDIO_TIME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1_PRODECE_NATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1_LENGTH)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT1_WIDTH)->EnableWindow(FALSE);
}

void CDlg_Add::init_rate_combo()
{
	m_combo_rate.AddString(L"未评级");
	m_combo_rate.AddString(L"一般");
	m_combo_rate.AddString(L"成人");
	m_combo_rate.AddString(L"儿童");
	m_combo_rate.SetCurSel(2);
	m_rate = L"未评级";
}

BEGIN_MESSAGE_MAP(CDlg_Add, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg_Add::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_OBJ_TYPE, &CDlg_Add::OnCbnSelchangeComboObjType)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE, &CDlg_Add::OnCbnSelchangeComboRate)
END_MESSAGE_MAP()


// CDlg_Add 消息处理程序


void CDlg_Add::OnBnClickedOk()
{
	UpdateData();
	if (type.GetLength() == 0){
		MessageBox(L"请选择类型", 0);
		return;
	}
	if (sql->isExistId(m_id)){
		MessageBox(L"该编号已存在！", 0);
		return;
	}
	if (m_id == 0 || m_title.GetLength() == 0 ||
		m_author.GetLength() == 0 || m_rate.GetLength() == 0){
		MessageBox(L"请输入基本参数！");
		return;
	}

	if (type == L"图书"){
		if (m_ISBN == 0 || m_press.GetLength() == 0 ||
			m_pagenum == 0){
			MessageBox(L"请输入图书的参数！", 0);
			return;
		}
	}

	if (type == L"视频光盘"){
		if (m_produce_name.GetLength() == 0 || m_produce_year.GetLength() == 0 ||
			m_vedio_time == 0){
			MessageBox(L"请输入视频光盘的参数！", 0);
			return;
		}
		if (!object::checkDate(m_produce_year)){
			MessageBox(L"输入日期格式为yyyy-mm-dd 或 yyyy/mm/dd!");
			return;
		}
	}
	
	if (type == L"图画"){
		if (m_nation.GetLength() == 0 ||
			m_length == 0 || m_width == 0){
			MessageBox(L"请输入图画的参数！", 0);
			return;
		}
	}
	
	CDialogEx::OnOK();
}


void CDlg_Add::OnCbnSelchangeComboObjType()
{
	int nSel = m_type.GetCurSel();

	m_type.GetLBText(nSel, type);

	if (type == L"图书"){
		GetDlgItem(IDC_EDIT_ISBN)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRESS)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PAGENUM)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_PRODUCE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_PRODUCE_YEAR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_VEDIO_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_PRODECE_NATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_LENGTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_WIDTH)->EnableWindow(FALSE);
	}
	else if (type == L"视频光盘"){
		GetDlgItem(IDC_EDIT_ISBN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PAGENUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRODUCE_NAME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1_PRODUCE_YEAR)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1_VEDIO_TIME)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1_PRODECE_NATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_LENGTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_WIDTH)->EnableWindow(FALSE);
	}
	else{
		GetDlgItem(IDC_EDIT_ISBN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRESS)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PAGENUM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_PRODUCE_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_PRODUCE_YEAR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_VEDIO_TIME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT1_PRODECE_NATION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1_LENGTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT1_WIDTH)->EnableWindow(TRUE);
	}
}


void CDlg_Add::OnCbnSelchangeComboRate()
{
	int nSel = m_combo_rate.GetCurSel();

	m_combo_rate.GetLBText(nSel, m_rate);
}
