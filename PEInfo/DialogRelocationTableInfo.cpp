// DialogRelocationTable.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogRelocationTableInfo.h"
#include "afxdialogex.h"


// CDialogRelocationTable 对话框

IMPLEMENT_DYNAMIC(CDialogRelocationTableInfo, CDialogEx)

CDialogRelocationTableInfo::CDialogRelocationTableInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RELOCATION_TABLE, pParent)
{

}

CDialogRelocationTableInfo::~CDialogRelocationTableInfo()
{
}

void CDialogRelocationTableInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl1);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl2);
}

void CDialogRelocationTableInfo::SetRelocationTableItemInfo(LPVOID pImageBase,PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount)
{
	m_pRelocationTableItem = pRelocationTableItem;
	m_RelocationTableItemCount = RelocationTableItemCount;
	m_pImageBase = pImageBase;
}

void CDialogRelocationTableInfo::AddListCtrl1Info(PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount)
{
	CString str;
	CHAR szBuffer[32];

	for (size_t i=0; i<RelocationTableItemCount; i++)
	{
		m_listCtrl1.InsertItem(i, _T("")); // 插入行

		str.Format(_T("%d"),i+1);
		m_listCtrl1.SetItemText(i, 1, str);

		str.Format(_T("%08X"), pRelocationTableItem[i].VirtualAddress);
		m_listCtrl1.SetItemText(i, 2, str);

		str.Format(_T("%08X"), pRelocationTableItem[i].SizeOfBlock);
		m_listCtrl1.SetItemText(i, 3, str);

		StringCchPrintfA(szBuffer, 32, "%s", (char*)pRelocationTableItem[i].Item);
		str = szBuffer;
		m_listCtrl1.SetItemText(i, 4, str);

	}
}

void CDialogRelocationTableInfo::AddListCtrl2Info(PRelocationTableItemInfo pRelocationTableItemInfo, DWORD SizeOfRelocationTableItemInfo)
{
	CString str;

	for (size_t i = 0; i < SizeOfRelocationTableItemInfo; i++)
	{
		m_listCtrl2.InsertItem(i, _T("")); // 插入行

		str.Format(_T("%d"), i + 1);
		m_listCtrl2.SetItemText(i, 1, str);

		str.Format(_T("%08X"), pRelocationTableItemInfo[i].Offset);
		m_listCtrl2.SetItemText(i, 2, str);

		str.Format(_T("%d"), pRelocationTableItemInfo[i].Type);
		m_listCtrl2.SetItemText(i, 3, str);
	}
}


BEGIN_MESSAGE_MAP(CDialogRelocationTableInfo, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDialogRelocationTableInfo::OnClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogRelocationTableInfo::OnItemchangedList1)
END_MESSAGE_MAP()


// CDialogRelocationTable 消息处理程序


BOOL CDialogRelocationTableInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 初始化list
	// 列表一的初始化工作
	CRect rect;
	m_listCtrl1.GetClientRect(&rect);
	m_listCtrl1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl1.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrl1.InsertColumn(1, _T("Index"), LVCFMT_CENTER, rect.Width() / 4 - 30);
	m_listCtrl1.InsertColumn(2, _T("VA"), LVCFMT_CENTER, rect.Width() / 4);
	m_listCtrl1.InsertColumn(3, _T("SizeOfBlock"), LVCFMT_CENTER, rect.Width() / 4);
	m_listCtrl1.InsertColumn(4, _T("Item"), LVCFMT_CENTER, rect.Width() / 4);

	// 列表二的初始化工作
	m_listCtrl2.GetClientRect(&rect);
	m_listCtrl2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl2.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrl2.InsertColumn(1, _T("Index"), LVCFMT_CENTER, rect.Width() / 3);
	m_listCtrl2.InsertColumn(2, _T("Offset"), LVCFMT_CENTER, rect.Width() / 3 - 20);
	m_listCtrl2.InsertColumn(3, _T("Type"), LVCFMT_CENTER, rect.Width() / 3);

	// 给列表一添加信息
	AddListCtrl1Info(m_pRelocationTableItem,m_RelocationTableItemCount);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialogRelocationTableInfo::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl2.DeleteAllItems();
	int nIndex = pNMItemActivate->iItem;
	DWORD sizeOfRelocationTableItemInfo;
	RelocationTableItemInfo relocationTableItemInfo[256];
	GetRelocationTableItemInfo(m_pRelocationTableItem + nIndex, relocationTableItemInfo,
		&sizeOfRelocationTableItemInfo, 256);
	AddListCtrl2Info(relocationTableItemInfo, sizeOfRelocationTableItemInfo);
	*pResult = 0;
}


void CDialogRelocationTableInfo::OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl2.DeleteAllItems();
	int nIndex = pNMLV->iItem;
	DWORD sizeOfRelocationTableItemInfo;
	RelocationTableItemInfo relocationTableItemInfo[256];
	GetRelocationTableItemInfo(m_pRelocationTableItem + nIndex, relocationTableItemInfo,
		&sizeOfRelocationTableItemInfo, 256);
	AddListCtrl2Info(relocationTableItemInfo, sizeOfRelocationTableItemInfo);
	*pResult = 0;
}
