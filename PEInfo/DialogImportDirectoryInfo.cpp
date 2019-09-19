// DialogImportDirectoryInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogImportDirectoryInfo.h"
#include "afxdialogex.h"


// CDialogImportDirectoryInfo 对话框

IMPLEMENT_DYNAMIC(CDialogImportDirectoryInfo, CDialogEx)

CDialogImportDirectoryInfo::CDialogImportDirectoryInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_IMPORT_DIRECTORY_INFO, pParent)
{

}

CDialogImportDirectoryInfo::~CDialogImportDirectoryInfo()
{
}

void CDialogImportDirectoryInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl2);
}


BEGIN_MESSAGE_MAP(CDialogImportDirectoryInfo, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CDialogImportDirectoryInfo::OnClickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CDialogImportDirectoryInfo::OnItemchangedList1)
END_MESSAGE_MAP()


// CDialogImportDirectoryInfo 消息处理程序


BOOL CDialogImportDirectoryInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// list1 所有导入表的基本信息
	m_listCtrl.GetClientRect(&rect);
	//m_listCtrl.GetHeaderCtrl()->EnableWindow(false); 使标头可拖动
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

	m_listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrl.InsertColumn(1, _T("Name"), LVCFMT_CENTER, rect.Width() / 5);
	m_listCtrl.InsertColumn(2, _T("OriginalFirstThunk"), LVCFMT_CENTER, rect.Width() / 5);
	m_listCtrl.InsertColumn(3, _T("TimeDateStamp"), LVCFMT_CENTER, rect.Width() / 5); 
	m_listCtrl.InsertColumn(4, _T("ForwarderChain"), LVCFMT_CENTER, rect.Width() / 5);
	m_listCtrl.InsertColumn(5, _T("FirstThunk"), LVCFMT_CENTER, rect.Width() / 5 - 18);
	AddListCtrl1Data(m_pImageImportDescriptor,m_ImageImportDescriptorSize);

	// list2 选中导入表的详细信息
	m_listCtrl2.GetClientRect(&rect);
	//m_listCtrl2.GetHeaderCtrl()->EnableWindow(false); 使标头可拖动
	m_listCtrl2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); // 整行选择、网格线

	m_listCtrl2.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrl2.InsertColumn(1, _T("Hint"), LVCFMT_CENTER, rect.Width() / 2);
	m_listCtrl2.InsertColumn(2, _T("API"), LVCFMT_CENTER, rect.Width() / 2-30);

	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialogImportDirectoryInfo::AddListCtrl1Data(PIMAGE_IMPORT_DESCRIPTOR  pImageImportDescriptor, size_t ImageImportDescriptorSize)
{
	CString str;
	CHAR szBuffer[64];
	DWORD dwOffset;
	for (size_t i = 0; i < ImageImportDescriptorSize; i++) {
		m_listCtrl.InsertItem(i, _T("")); // 插入行

		// Name
		Rva2offset(m_pImageBase, pImageImportDescriptor[i].Name, &dwOffset);
		StringCchPrintfA(szBuffer, 64, "%s", (char*)((DWORD)m_pImageBase+dwOffset));
		str = szBuffer;
		m_listCtrl.SetItemText(i, 1, str);

		// OriginalFirstThunk
		str.Format(_T("%08X"), pImageImportDescriptor[i].OriginalFirstThunk);
		m_listCtrl.SetItemText(i, 2, str);

		//TimeDateStamp
		str.Format(_T("%08X"), pImageImportDescriptor[i].TimeDateStamp);
		m_listCtrl.SetItemText(i, 3, str); 

		//ForwarderChain
		str.Format(_T("%08X"), pImageImportDescriptor[i].ForwarderChain);
		m_listCtrl.SetItemText(i, 4, str); 

		//FirstThunk
		str.Format(_T("%08X"), pImageImportDescriptor[i].FirstThunk);
		m_listCtrl.SetItemText(i, 5, str);
	}
}

void CDialogImportDirectoryInfo::AddListCtrl2Data(PIMAGE_THUNK_DATA32 pITD, size_t ITDSize)
{
	//TODO: 判断此结构是名字还是索引，依次进行操作
	CString str;
	PIMAGE_IMPORT_BY_NAME pIIBN;
	CHAR szBuffer[32];

	for (size_t i = 0; i < ITDSize; i++) {
		m_listCtrl2.InsertItem(i, _T("")); // 插入行
		if (IsSnapByOrdinal(pITD[i])) {
	
			str.Format(_T("%08X"), GetOrdinal(pITD[i]));
			m_listCtrl2.SetItemText(i, 1, str);

			str = _T("NULL");
			m_listCtrl2.SetItemText(i, 2, str);
		}else {
			GetIIBN(m_pImageBase,pITD+i, &pIIBN);

			str.Format(_T("%08X"), pIIBN->Hint);
			m_listCtrl2.SetItemText(i, 1, str);

			StringCchPrintfA(szBuffer, 32, "%s", (char*)pIIBN->Name);
			str = szBuffer;
			m_listCtrl2.SetItemText(i, 2, str);
		}
	}
}

void CDialogImportDirectoryInfo::SetImageImportDescriptorInfo(PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor, size_t ImageImportDescriptorSize, LPVOID pImageBase)
{
	m_pImageImportDescriptor = pImageImportDescriptor;
	m_ImageImportDescriptorSize = ImageImportDescriptorSize;
	m_pImageBase = pImageBase;
}

void CDialogImportDirectoryInfo::OnClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl2.DeleteAllItems();
	int nIndex = pNMItemActivate->iItem;
	PIMAGE_THUNK_DATA32 pITD = NULL;
	size_t ITDSize;
	GetImportFunctions(m_pImageBase, m_pImageImportDescriptor + nIndex, &pITD, &ITDSize);
	AddListCtrl2Data(pITD, ITDSize);
	*pResult = 0;
}

void CDialogImportDirectoryInfo::OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	m_listCtrl2.DeleteAllItems();
	int nIndex = pNMLV->iItem;
	PIMAGE_THUNK_DATA32 pITD = NULL;
	size_t ITDSize;
	GetImportFunctions(m_pImageBase, m_pImageImportDescriptor + nIndex, &pITD, &ITDSize);
	AddListCtrl2Data(pITD, ITDSize);
	*pResult = 0;
}
