// DialogSectionTable.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogSectionTable.h"
#include "afxdialogex.h"


// CDialogSectionTable 对话框

IMPLEMENT_DYNAMIC(CDialogSectionTable, CDialogEx)

CDialogSectionTable::CDialogSectionTable(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SECATIONTABLE, pParent)
{

}

CDialogSectionTable::~CDialogSectionTable()
{
}

void CDialogSectionTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SECTIONTABLE, m_listCtrlSectionTable);
}


BEGIN_MESSAGE_MAP(CDialogSectionTable, CDialogEx)
END_MESSAGE_MAP()


// CDialogSectionTable 消息处理程序


void CDialogSectionTable::AddListCtrlData(SectionHeader* pSectionHeader)
{
	CString str;
	for (unsigned short i = 0; i <pSectionHeader->numberOfSections; i++) {
		m_listCtrlSectionTable.InsertItem(i,_T(""));

		CHAR szBuffer[128];
		StringCchPrintfA(szBuffer, 128, "%s", (char*)pSectionHeader->imageSectionHeaders[i].Name);
		str = szBuffer;
		m_listCtrlSectionTable.SetItemText(i, 1, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].Misc.VirtualSize);
		m_listCtrlSectionTable.SetItemText(i, 2, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].VirtualAddress);
		m_listCtrlSectionTable.SetItemText(i, 3, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].SizeOfRawData);
		m_listCtrlSectionTable.SetItemText(i, 4, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].PointerToRawData);
		m_listCtrlSectionTable.SetItemText(i, 5, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].PointerToRelocations);
		m_listCtrlSectionTable.SetItemText(i, 6, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].PointerToLinenumbers);
		m_listCtrlSectionTable.SetItemText(i, 7, str);

		str.Format(_T("%04X"), pSectionHeader->imageSectionHeaders[i].NumberOfRelocations);
		m_listCtrlSectionTable.SetItemText(i, 8, str);

		str.Format(_T("%04X"), pSectionHeader->imageSectionHeaders[i].NumberOfLinenumbers);
		m_listCtrlSectionTable.SetItemText(i, 9, str);

		str.Format(_T("%08X"), pSectionHeader->imageSectionHeaders[i].Characteristics);
		m_listCtrlSectionTable.SetItemText(i, 10, str);
	}
}

void CDialogSectionTable::SetpSectionHeader(SectionHeader* pSectionHeader)
{
	this->pSectionHeader = pSectionHeader;
}

BOOL CDialogSectionTable::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	m_listCtrlSectionTable.GetClientRect(&rect);
	m_listCtrlSectionTable.GetHeaderCtrl()->EnableWindow(false);
	m_listCtrlSectionTable.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线


	m_listCtrlSectionTable.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrlSectionTable.InsertColumn(1, _T("Name"), LVCFMT_CENTER, rect.Width() / 10 - 30);
	m_listCtrlSectionTable.InsertColumn(2, _T("VirtualSize"), LVCFMT_CENTER, rect.Width() / 10 - 30); 
	m_listCtrlSectionTable.InsertColumn(3, _T("VirtualAddress"), LVCFMT_CENTER, rect.Width() / 10);
	m_listCtrlSectionTable.InsertColumn(4, _T("SizeOfRawData"), LVCFMT_CENTER, rect.Width() / 10);
	m_listCtrlSectionTable.InsertColumn(5, _T("PointerToRawData"), LVCFMT_CENTER, rect.Width() / 10);
	m_listCtrlSectionTable.InsertColumn(6, _T("PointerToRelocations"), LVCFMT_CENTER, rect.Width() / 10 + 10);
	m_listCtrlSectionTable.InsertColumn(7, _T("PointerToLinenumbers"), LVCFMT_CENTER, rect.Width() / 10 + 15);
	m_listCtrlSectionTable.InsertColumn(8, _T("NumberOfRelocations"), LVCFMT_CENTER, rect.Width() / 10 + 20);
	m_listCtrlSectionTable.InsertColumn(9, _T("NumberOfLinenumbers"), LVCFMT_CENTER, rect.Width() / 10 + 20);
	m_listCtrlSectionTable.InsertColumn(10, _T("Characteristics"), LVCFMT_CENTER, rect.Width() / 10);
	AddListCtrlData(pSectionHeader);
	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
