// DialogExportDirectoryInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogExportDirectoryInfo.h"
#include "afxdialogex.h"


// CDialogExportDirectoryInfo �Ի���

IMPLEMENT_DYNAMIC(CDialogExportDirectoryInfo, CDialogEx)

CDialogExportDirectoryInfo::CDialogExportDirectoryInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_EXPORT_DIRECTORY_INFO, pParent)
{

}

CDialogExportDirectoryInfo::~CDialogExportDirectoryInfo()
{
}

void CDialogExportDirectoryInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

VOID CDialogExportDirectoryInfo::SetImageExportDescriptorInfo(LPVOID pImageBase, PIMAGE_EXPORT_DIRECTORY pImageExportDirectory)
{
	m_pImageExportDirectory = pImageExportDirectory;
	m_pImageBase = pImageBase;
}

VOID CDialogExportDirectoryInfo::SetExportFunctionsInfo(PExportTableFunctions pETF, size_t ETFSize)
{
	m_ETFSize = ETFSize;
	m_pETF = pETF;
}

VOID CDialogExportDirectoryInfo::AddImageExportDirectoryInfo(PIMAGE_EXPORT_DIRECTORY pImageExportDirectory)
{
	CString str;
	CHAR szBuffer[32];
	DWORD dwOffset;

	// Characteristics
	str.Format(_T("%08X"), pImageExportDirectory->Characteristics);
	SetDlgItemText(IDC_EDIT_CHARACTERISTICS, str);

	// TimeDateStamp
	str.Format(_T("%08X"), pImageExportDirectory->TimeDateStamp);
	SetDlgItemText(IDC_EDIT_TIMEDATESTAMP, str);

	// MajorVersion
	str.Format(_T("%04X"), pImageExportDirectory->MajorVersion);
	SetDlgItemText(IDC_EDIT_MAJORVERSION, str);

	// MinorVersion
	str.Format(_T("%04X"), pImageExportDirectory->MinorVersion);
	SetDlgItemText(IDC_EDIT_MINORVERSION, str);

	// Name
	Rva2offset(m_pImageBase, pImageExportDirectory->Name,&dwOffset);
	StringCchPrintfA(szBuffer, 32, "%s", (char*)((DWORD)m_pImageBase + dwOffset));
	str = szBuffer;
	SetDlgItemText(IDC_EDIT_NAME, str);

	// Base
	str.Format(_T("%08X"), pImageExportDirectory->Base);
	SetDlgItemText(IDC_EDIT_BASE, str);

	// NumberOfFunctions
	str.Format(_T("%08X"), pImageExportDirectory->NumberOfFunctions);
	SetDlgItemText(IDC_EDIT_NUMBEROFFUNCTIONS, str);

	// NumberOfNames

	str.Format(_T("%08X"), pImageExportDirectory->NumberOfNames);
	SetDlgItemText(IDC_EDIT_NUMBEROFNAMES, str);

	// AddressOfFunctions
	str.Format(_T("%08X"), pImageExportDirectory->AddressOfFunctions);
	SetDlgItemText(IDC_EDIT_ADDRESSOFFUNCTIONS, str);

	// AddressOfNames
	str.Format(_T("%08X"), pImageExportDirectory->AddressOfNames);
	SetDlgItemText(IDC_EDIT_ADDRESSOFNAMES, str);

	// AddressOfNameOrdinals
	str.Format(_T("%08X"), pImageExportDirectory->AddressOfNameOrdinals);
	SetDlgItemText(IDC_EDIT_ADDRESSOFNAMEORDINALS, str);

}


VOID CDialogExportDirectoryInfo::AddListCtrlDataInfo(PExportTableFunctions pETF, size_t ETFSize)
{
	CString str;
	CHAR szBuffer[32];

	for (size_t i = 0; i < ETFSize; i++) {

		m_listCtrl.InsertItem(i, _T("")); // ������

		str.Format(_T("%08X"), pETF[i].Ordinal);
		m_listCtrl.SetItemText(i, 1, str); 

		str.Format(_T("%08X"), pETF[i].RVA);
		m_listCtrl.SetItemText(i, 2, str);

		StringCchPrintfA(szBuffer, 32, "%s", (char*)pETF[i].AddressOfName);
		str = szBuffer;
		m_listCtrl.SetItemText(i, 3, str);

	}
}

BEGIN_MESSAGE_MAP(CDialogExportDirectoryInfo, CDialogEx)
END_MESSAGE_MAP()


// CDialogExportDirectoryInfo ��Ϣ�������


BOOL CDialogExportDirectoryInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	AddImageExportDirectoryInfo(m_pImageExportDirectory);

	// ��ʼ��list
	CRect rect;
	m_listCtrl.GetClientRect(&rect);
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_listCtrl.InsertColumn(1, _T("Ordinal"), LVCFMT_CENTER, rect.Width() / 3); // �����2�е�����
	m_listCtrl.InsertColumn(2, _T("RVA"), LVCFMT_CENTER, rect.Width() / 3-20); // �����3�е�����
	m_listCtrl.InsertColumn(3, _T("Name"), LVCFMT_CENTER, rect.Width() / 3); // �����4�е�����

	// �����������
	AddListCtrlDataInfo(m_pETF, m_ETFSize);

	UpdateData();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
