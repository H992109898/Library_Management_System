
// Library_Management_SystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Library_Management_System.h"
#include "Library_Management_SystemDlg.h"
#include "afxdialogex.h"
#include "Dlg_Find.h"
#include "Dlg_Add.h"
#include "Dlg_Detail.h"
#include "object.h"
#include "sql_utils.h"
#include <vector>
#include <map>
#include "Dlg_Modify.h"
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long long CStr_to_ll(CString & tmp)
{
	long long res = 0;
	int cnt = 0;
	for (int i = tmp.GetLength() - 1; i >= 0; i--){
		res += (tmp.GetAt(i) - '0')*pow(10, cnt++);
	}
	return res;
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLibrary_Management_SystemDlg 对话框



CLibrary_Management_SystemDlg::CLibrary_Management_SystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLibrary_Management_SystemDlg::IDD, pParent)
	, m_num_obj(0)
	, m_num_book(0)
	, m_num_vedio(0)
	, m_num_picture(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CLibrary_Management_SystemDlg::~CLibrary_Management_SystemDlg()
{
	delete sql;
}

void CLibrary_Management_SystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_OBJ_TYPE, m_combo_obj_type);
	DDX_Control(pDX, IDC_LIST_SHOW, m_list_show);
	DDX_Text(pDX, IDC_EDIT_NUM_OBJ, m_num_obj);
	DDX_Text(pDX, IDC_EDIT_NUM_BOOK, m_num_book);
	DDX_Text(pDX, IDC_EDIT_NUM_VEDIO, m_num_vedio);
	DDX_Text(pDX, IDC_EDIT_NUM_PICTURE, m_num_picture);
}

BEGIN_MESSAGE_MAP(CLibrary_Management_SystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND2, &CLibrary_Management_SystemDlg::OnBnClickedButtonFind2)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CLibrary_Management_SystemDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SHOW, &CLibrary_Management_SystemDlg::OnNMClickListShow)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SHOW, &CLibrary_Management_SystemDlg::OnNMDblclkListShow)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CLibrary_Management_SystemDlg::OnBnClickedButtonModify)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CLibrary_Management_SystemDlg::OnBnClickedButtonDelete)
	ON_CBN_SELCHANGE(IDC_COMBO_OBJ_TYPE, &CLibrary_Management_SystemDlg::OnCbnSelchangeComboObjType)
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CLibrary_Management_SystemDlg::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_IN, &CLibrary_Management_SystemDlg::OnBnClickedButtonIn)
END_MESSAGE_MAP()

void CLibrary_Management_SystemDlg::show_list_by_type()
{
	int nSel;
	CString type;
	nSel = m_combo_obj_type.GetCurSel();
	count_number();

	if (nSel == -1){
		m_list_show.DeleteAllItems();
		return;
	}
	m_combo_obj_type.GetLBText(nSel, type);

	vector <object> res;
	if (type == L"视频光盘"){
		sql->searchByType(object::TYPE_VIDEO, res);
	}
	else if (type == L"图书"){
		sql->searchByType(object::TYPE_BOOK, res);
	}
	else if (type == L"图画"){
		sql->searchByType(object::TYPE_PICTURE, res);
	}
	else if (type == L"所有物品"){
		sql->showAll(res);
	}

	m_list_show.DeleteAllItems();

	CString tmp;
	for (int i = 0; i < res.size(); i++){

		tmp.Format(L"%lld", res[i].id);
		m_list_show.InsertItem(0, tmp);

		if (res[i].type == object::TYPE_BOOK)
			tmp = L"图书";
		else if (res[i].type == object::TYPE_PICTURE)
			tmp = L"图画";
		else
			tmp = L"视频文件";
		m_list_show.SetItemText(0, 1, tmp);

		tmp = res[i].author.c_str();
		m_list_show.SetItemText(0, 2, tmp);

		tmp = res[i].title.c_str();
		m_list_show.SetItemText(0, 3, tmp);

		if (res[i].classification == object::CLASSIFICATION_CHILDREN)
			tmp = L"儿童";
		else if (res[i].classification == object::CLASSIFICATION_ADULT)
			tmp = L"成人";
		else if (res[i].classification == object::CLASSIFICATION_NORMAL)
			tmp = L"普通";
		else
			tmp = L"未定级";
		m_list_show.SetItemText(0, 4, tmp);
	}
}

void CLibrary_Management_SystemDlg::count_number()
{
	map <int, int> res;
	sql->summary(res);
	
	m_num_book = res[object::TYPE_BOOK];
	m_num_vedio = res[object::TYPE_VIDEO];
	m_num_picture = res[object::TYPE_PICTURE];
	m_num_obj = m_num_book + m_num_vedio + m_num_picture;

	UpdateData(FALSE);
}

// CLibrary_Management_SystemDlg 消息处理程序

BOOL CLibrary_Management_SystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	init_combo_type();
	init_list_show();
	sql = new sql_utils();
	m_combo_obj_type.SetCurSel(1);
	show_list_by_type();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLibrary_Management_SystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLibrary_Management_SystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLibrary_Management_SystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLibrary_Management_SystemDlg::init_combo_type()
{
	m_combo_obj_type.AddString(L"图书");
	m_combo_obj_type.AddString(L"视频光盘");
	m_combo_obj_type.AddString(L"图画");
	m_combo_obj_type.AddString(L"所有物品");
}

void CLibrary_Management_SystemDlg::init_list_show()
{
	CRect rect;
	m_list_show.GetClientRect(&rect);
	m_list_show.SetExtendedStyle(m_list_show.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_list_show.InsertColumn(0, _T("编号"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list_show.InsertColumn(1, _T("类别"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list_show.InsertColumn(2, _T("作者"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list_show.InsertColumn(3, _T("标题"), LVCFMT_CENTER, rect.Width() / 5, 0);
	m_list_show.InsertColumn(4, _T("评级"), LVCFMT_CENTER, rect.Width() / 5, 0);
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonFind2()
{
	m_list_show.DeleteAllItems();
	// TODO:  在此添加控件通知处理程序代码
	CDlg_Find find_dlg;

	
	CString type, info;
	if (find_dlg.DoModal() == IDOK){
		type = find_dlg.m_type;
		info = find_dlg.m_info;
	}
	vector<object> res;
	
	if (type == L"编号"){
		sql->searchById(CStr_to_ll(info), res);
		m_combo_obj_type.SetCurSel(-1);
	}
	else if (type == L"标题"){
		string tmp = (CStringA)info;
		sql->searchByTitle(tmp, res);
		m_combo_obj_type.SetCurSel(-1);
	}
	else {
		if (info == L"图书"){
			sql->searchByType(object::TYPE_BOOK, res);
			m_combo_obj_type.SetCurSel(3);
		}
		else if (info == L"图画"){
			sql->searchByType(object::TYPE_PICTURE, res);
			m_combo_obj_type.SetCurSel(2);
		}
		else if (info == L"视频文件"){
			sql->searchByType(object::TYPE_VIDEO, res);
			m_combo_obj_type.SetCurSel(0);
		}
	}

	CString tmp;
	for (int i = 0; i < res.size(); i++){

		tmp.Format(L"%lld", res[i].id);
		m_list_show.InsertItem(0, tmp);

		if (res[i].type == object::TYPE_BOOK)
			tmp = L"图书";
		else if (res[i].type == object::TYPE_PICTURE)
			tmp = L"图画";
		else
			tmp = L"视频文件";
		m_list_show.SetItemText(0, 1, tmp);

		tmp = res[i].author.c_str();
		m_list_show.SetItemText(0, 2, tmp);

		tmp = res[i].title.c_str();
		m_list_show.SetItemText(0, 3, tmp);

		if (res[i].classification == object::CLASSIFICATION_CHILDREN)
			tmp = L"儿童";
		else if (res[i].classification == object::CLASSIFICATION_ADULT)
			tmp = L"成人";
		else if (res[i].classification == object::CLASSIFICATION_NORMAL)
			tmp = L"普通";
		else
			tmp = L"未定级";
		m_list_show.SetItemText(0, 4, tmp);
		}
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonAdd()
{
	CDlg_Add add_dlg(sql);
	long m_id;
	CString m_title;
	CString m_author;
	CString m_rate;
	long m_ISBN;
	CString m_press;
	int m_pagenum;
	CString m_produce_name;
	CString m_produce_year;
	int m_vedio_time;
	CString m_nation;
	int m_length;
	int m_width;
	CString m_type;

	if (add_dlg.DoModal() == IDOK){
		m_type = add_dlg.type;
		m_id = add_dlg.m_id;
		m_title = add_dlg.m_title;
		m_author = add_dlg.m_author;
		m_rate = add_dlg.m_rate;
		m_ISBN = add_dlg.m_ISBN;
		m_press = add_dlg.m_press;
		m_pagenum = add_dlg.m_pagenum;
		m_produce_name = add_dlg.m_produce_name;
		m_produce_year = add_dlg.m_produce_year;
		m_vedio_time = add_dlg.m_vedio_time;
		m_nation = add_dlg.m_nation;
		m_length = add_dlg.m_length;
		m_width = add_dlg.m_width;
	}
	else
		return;

	object add_obj;
	add_obj.id = m_id;
	add_obj.title = (CStringA)m_title;
	add_obj.author = (CStringA)m_author;
	if (m_rate == L"未评级")
		add_obj.classification = object::CLASSIFICATION_UNDIFINE;
	else if (m_rate == L"儿童")
		add_obj.classification = object::CLASSIFICATION_CHILDREN;
	else if (m_rate == L"成人")
		add_obj.classification = object::CLASSIFICATION_ADULT;
	else
		add_obj.classification = object::CLASSIFICATION_NORMAL;
	add_obj.E_Resourse = 0;


	if (m_type == L"图书"){
		add_obj.type = object::TYPE_BOOK;
		add_obj.ISBN = lltos(m_ISBN);
		add_obj.publishingCompany = (CStringA)m_press;
		add_obj.page = m_pagenum;
		add_obj.hasVideoDisc = 0;	
	}
	else if (m_type == L"视频光盘"){
		add_obj.type = object::TYPE_VIDEO;
		add_obj.producer = (CStringA)m_produce_name;
		add_obj.production_time = (CStringA)m_produce_year;
		add_obj.duration = m_vedio_time;
	}
	else if (m_type == L"图画"){
		add_obj.type = object::TYPE_PICTURE;
		add_obj.width = m_width;
		add_obj.height = m_length;
		add_obj.productionNationality = (CStringA)m_nation;
	}

	sql->insert(add_obj);
	show_list_by_type();
}

//单击列表
void CLibrary_Management_SystemDlg::OnNMClickListShow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
	CString str_info;     
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem){
		str_info = m_list_show.GetItemText(pNMListView->iItem, 0);
	}
}

//双击列表
void CLibrary_Management_SystemDlg::OnNMDblclkListShow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;

	CString str_info;
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;

	if (-1 != pNMListView->iItem){
		str_info = m_list_show.GetItemText(pNMListView->iItem, 0);
	}
	else{
		return;
	}
	CDlg_Detail detail_dlg(CStr_to_ll(str_info), sql);
	if (detail_dlg.DoModal() == IDOK){
		
	}
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonModify()
{
	POSITION pos = m_list_show.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请选择要修改的项！", 0);
		return;
	}
	int nId = (int)m_list_show.GetNextSelectedItem(pos);
	CString info = m_list_show.GetItemText(nId, 0);

	int sql_id = CStr_to_ll(info);
	vector <object> old;
	sql->searchById(sql_id, old);

	CDlg_Modify modify_dlg(sql_id, sql);
	object add_obj;
	if (IDOK == modify_dlg.DoModal()){
		add_obj.id = CStr_to_ll(modify_dlg.m_id);
		add_obj.title = (CStringA)modify_dlg.m_title;
		add_obj.author = (CStringA)modify_dlg.m_author;
		if (modify_dlg.m_rate == L"未分类")
			add_obj.classification = object::CLASSIFICATION_UNDIFINE;
		else if (modify_dlg.m_rate == L"儿童")
			add_obj.classification = object::CLASSIFICATION_CHILDREN;
		else if (modify_dlg.m_rate == L"成人")
			add_obj.classification = object::CLASSIFICATION_ADULT;
		else
			add_obj.classification = object::CLASSIFICATION_NORMAL;
		add_obj.E_Resourse = 0;


		if (modify_dlg.m_type == L"图书"){
			add_obj.type = object::TYPE_BOOK;
			add_obj.ISBN = (CStringA)modify_dlg.m2;
			add_obj.publishingCompany = (CStringA)modify_dlg.m1;
			add_obj.page = CStr_to_ll(modify_dlg.m3);
			add_obj.hasVideoDisc = 0;
		}
		else if (modify_dlg.m_type == L"视频文件"){
			add_obj.type = object::TYPE_VIDEO;
			add_obj.producer = (CStringA)modify_dlg.m1;
			add_obj.production_time = (CStringA)modify_dlg.m2;
			add_obj.duration = CStr_to_ll(modify_dlg.m3);
		}
		else if (modify_dlg.m_type == L"图画"){
			add_obj.type = object::TYPE_PICTURE;
			add_obj.width = CStr_to_ll(modify_dlg.m3);
			add_obj.height = CStr_to_ll(modify_dlg.m2);
			add_obj.productionNationality = (CStringA)modify_dlg.m1;
		}
		sql->update(old[0], add_obj);
	}
	show_list_by_type();
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonDelete()
{
	POSITION pos = m_list_show.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(L"请选择要修改的项！", 0);
		return;
	}
	int nId = (int)m_list_show.GetNextSelectedItem(pos);
	CString info = m_list_show.GetItemText(nId, 0);

	sql->erase(CStr_to_ll(info));
	show_list_by_type();
}

void CLibrary_Management_SystemDlg::OnCbnSelchangeComboObjType()
{
	show_list_by_type();
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonOut()
{
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|Word文件(*.doc)|*.doc|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("doc"), _T("my"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString str_name;

	// 显示保存文件对话框   
	if (IDOK == fileDlg.DoModal()){
		str_name = fileDlg.GetPathName();
		vector <object> res;
		sql->showAll(res);
		string tmp = (CStringA)str_name;
		std::ofstream out(tmp.c_str());
		for (vector<object>::iterator it = res.begin(); it != res.end(); it++)
			out << it->toString() << std::endl;

		MessageBox(L"导出文件成功！", 0);
	}
}

void CLibrary_Management_SystemDlg::OnBnClickedButtonIn()
{
	m_combo_obj_type.SetCurSel(1);
	TCHAR szFilter[] = _T("文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString str_name;

	if (IDOK == fileDlg.DoModal()){   
		str_name = fileDlg.GetPathName();
		string tmp = (CStringA)str_name;
		std::ifstream in(tmp.c_str());

		char buffer[500];
		for (; in.eof() == false;){
			in.getline(buffer, 500);
			object obj(buffer);
			sql->insert(obj);
		}
		MessageBox(L"导入物品成功!", 0);
		show_list_by_type();
	}
}
