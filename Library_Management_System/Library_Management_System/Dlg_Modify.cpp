// Dlg_Modify.cpp : 实现文件
//

#include "stdafx.h"
#include "Library_Management_System.h"
#include "Dlg_Modify.h"
#include "afxdialogex.h"
#include <vector>
#include "object.h"

using namespace std;
// CDlg_Modify 对话框

IMPLEMENT_DYNAMIC(CDlg_Modify, CDialogEx)

CDlg_Modify::CDlg_Modify(long long id, sql_utils* sql, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlg_Modify::IDD, pParent)
	, m_type(_T(""))
	, m_id(_T(""))
	, m_title(_T(""))
	, m_author(_T(""))
	, m_rate(_T(""))
	, m1(_T(""))
	, m2(_T(""))
	, m3(_T(""))
{
	this->id = id;
	this->sql = sql;
}


BOOL CDlg_Modify::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	vector <object> res;
	sql->searchById(id, res);

	CString tmp;

	tmp.Format(L"%lld", res[0].id);
	m_id = tmp;

	if (res[0].type == object::TYPE_BOOK)
		tmp = L"图书";
	else if (res[0].type == object::TYPE_PICTURE)
		tmp = L"图画";
	else
		tmp = L"视频文件";
	m_type = tmp;

	tmp = res[0].author.c_str();
	m_author = tmp;

	tmp = res[0].title.c_str();
	m_title = tmp;

	if (res[0].classification == object::CLASSIFICATION_CHILDREN)
		tmp = L"儿童";
	else if (res[0].classification == object::CLASSIFICATION_ADULT)
		tmp = L"成人";
	else if (res[0].classification == object::CLASSIFICATION_NORMAL)
		tmp = L"普通";
	else
		tmp = L"未定级";
	m_rate = tmp;

	if (m_type == L"图书"){
		SetDlgItemText(IDC_MODIFY_M1, L"出版社  :");
		SetDlgItemText(IDC_MODIFY_M2, L"ISBN号  :");
		SetDlgItemText(IDC_MODIFY_M3, L"页数  :");
		m1 = res[0].publishingCompany.c_str();
		m2 = res[0].ISBN.c_str();
		m3.Format(L"%d", res[0].page);
	}
	else if (m_type == L"视频文件"){
		SetDlgItemText(IDC_MODIFY_M1, L"出品人 :");
		SetDlgItemText(IDC_MODIFY_M2, L"出品年份  :");
		SetDlgItemText(IDC_MODIFY_M3, L"视频时长 :");
		m1 = res[0].producer.c_str();
		m2 = res[0].production_time.c_str();
		m3.Format(L"%d", res[0].duration);
	}
	else if (m_type == L"图画"){
		SetDlgItemText(IDC_MODIFY_M1, L"出品国籍  :");
		SetDlgItemText(IDC_MODIFY_M2, L"图画的长 :");
		SetDlgItemText(IDC_MODIFY_M3, L"图画的宽  :");
		m1 = res[0].productionNationality.c_str();
		m2.Format(L"%d",res[0].height);
		m3.Format(L"%d", res[0].width);
	}

	UpdateData(FALSE);
	return TRUE;
}

CDlg_Modify::~CDlg_Modify()
{

}

void CDlg_Modify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MD_TYPE, m_type);
	DDX_Text(pDX, IDC_EDIT_MD_ID, m_id);
	DDX_Text(pDX, IDC_EDIT_MD_TITLE, m_title);
	DDX_Text(pDX, IDC_EDIT_MD_AUTHOR, m_author);
	DDX_Text(pDX, IDC_EDIT_MD_RATE, m_rate);
	DDX_Text(pDX, IDC_EDIT_MD_M1, m1);
	DDX_Text(pDX, IDC_EDIT_MD_M2, m2);
	DDX_Text(pDX, IDC_EDIT_MD_M3, m3);
}


BEGIN_MESSAGE_MAP(CDlg_Modify, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlg_Modify::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlg_Modify 消息处理程序
long long CStr_to_ll2(CString & tmp)
{
	long long res = 0;
	int cnt = 0;
	for (int i = tmp.GetLength() - 1; i >= 0; i--){
		res += (tmp.GetAt(i) - '0')*pow(10, cnt++);
	}
	return res;
}


void CDlg_Modify::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (!object::checkDate(m2)){
		MessageBox(L"输入日期格式为yyyy-mm-dd 或 yyyy/mm/dd!");
		return;
	}
	long long new_id = CStr_to_ll2(m_id);
	if (sql->isExistId(new_id) && new_id != id){
		MessageBox(L"该编号已存在，请重新选择编号！", 0);
		return;
	}

	CDialogEx::OnOK();
}
