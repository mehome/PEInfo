// DialogDataDirectory.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogDataDirectory.h"
#include "afxdialogex.h"


// CDialogDataDirectory 对话框

IMPLEMENT_DYNAMIC(CDialogDataDirectory, CDialogEx)

CDialogDataDirectory::CDialogDataDirectory(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DATADIRECTORY, pParent)
{

}

CDialogDataDirectory::~CDialogDataDirectory()
{
}

void CDialogDataDirectory::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogDataDirectory, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT_DIRECTORY_INFO, &CDialogDataDirectory::OnBnClickedButtonExportDirectoryInfo)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT_DIRECTORY_INFO, &CDialogDataDirectory::OnClickedButtonImportDirectoryInfo)
END_MESSAGE_MAP()


// CDialogDataDirectory 消息处理程序


BOOL CDialogDataDirectory::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	AddDataDirectoryInfo(m_pImageDataDirectory);

	// 判断是否有导出表
	if (HasExportTable(m_pImageBase)) {
		(CButton*)GetDlgItem(IDC_BUTTON_EXPORT_DIRECTORY_INFO)->EnableWindow(TRUE);
	}
	// 判断是否有导入表
	if (HasImportTable(m_pImageBase)) {
		(CButton*)GetDlgItem(IDC_BUTTON_IMPORT_DIRECTORY_INFO)->EnableWindow(TRUE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CDialogDataDirectory::AddDataDirectoryInfo(PIMAGE_DATA_DIRECTORY pImageDataDirectory)
{
	CString str;

	// EXPORT_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[0].VirtualAddress);
	SetDlgItemText(IDC_EDIT_EXPORT_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[0].Size);
	SetDlgItemText(IDC_EDIT_EXPORT_DIRECTORY_SZ, str);

	// IMPORT_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[1].VirtualAddress);
	SetDlgItemText(IDC_EDIT_IMPORT_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[1].Size);
	SetDlgItemText(IDC_EDIT_IMPORT_DIRECTORY_SZ, str);

	// RESOURCE_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[2].VirtualAddress);
	SetDlgItemText(IDC_EDIT_RESOURCE_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[2].Size);
	SetDlgItemText(IDC_EDIT_RESOURCE_DIRECTORY_SZ, str);

	// EXCEPTION_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[3].VirtualAddress);
	SetDlgItemText(IDC_EDIT_EXCEPTION_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[3].Size);
	SetDlgItemText(IDC_EDIT_EXCEPTION_DIRECTORY_SZ, str);

	// SECURITY_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[4].VirtualAddress);
	SetDlgItemText(IDC_EDIT_SECURITY_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[4].Size);
	SetDlgItemText(IDC_EDIT_SECURITY_DIRECTORY_SZ, str);

	// BASE_RELOCATION_TABLE
	str.Format(_T("%08X"), pImageDataDirectory[5].VirtualAddress);
	SetDlgItemText(IDC_EDIT_BASE_RELOCATION_TABLE_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[5].Size);
	SetDlgItemText(IDC_EDIT_BASE_RELOCATION_TABLE_SZ, str);

	// DEBUG_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[6].VirtualAddress);
	SetDlgItemText(IDC_EDIT_DEBUG_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[6].Size);
	SetDlgItemText(IDC_EDIT_DEBUG_DIRECTORY_SZ, str);

	// COPYRIGHT
	str.Format(_T("%08X"), pImageDataDirectory[7].VirtualAddress);
	SetDlgItemText(IDC_EDIT_COPYRIGHT_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[7].Size);
	SetDlgItemText(IDC_EDIT_COPYRIGHT_DIRECTORY_SZ, str);

	// RVA_OF_GP
	str.Format(_T("%08X"), pImageDataDirectory[8].VirtualAddress);
	SetDlgItemText(IDC_EDIT_RVA_OF_GP_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[8].Size);
	SetDlgItemText(IDC_EDIT_RVA_OF_GP_SZ, str);

	// TLS_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[9].VirtualAddress);
	SetDlgItemText(IDC_EDIT_TLS_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[9].Size);
	SetDlgItemText(IDC_EDIT_TLS_DIRECTORY_SZ, str);

	// LOAD_CONFIGURATION_DIRECTORY
	str.Format(_T("%08X"), pImageDataDirectory[10].VirtualAddress);
	SetDlgItemText(IDC_EDIT_LOAD_CONFIGURATION_DIRECTORY_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[10].Size);
	SetDlgItemText(IDC_EDIT_LOAD_CONFIGURATION_DIRECTORY_SZ, str);

	// BOUND_IMPORT_DIRECTORY_IN_HEADERS
	str.Format(_T("%08X"), pImageDataDirectory[11].VirtualAddress);
	SetDlgItemText(IDC_EDIT_BOUND_IMPORT_DIRECTORY_IN_HEADERS_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[11].Size);
	SetDlgItemText(IDC_EDIT_BOUND_IMPORT_DIRECTORY_IN_HEADERS_SZ, str);

	// IMPORT_ADDRESS_TABLE
	str.Format(_T("%08X"), pImageDataDirectory[12].VirtualAddress);
	SetDlgItemText(IDC_EDIT_IMPORT_ADDRESS_TABLE_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[12].Size);
	SetDlgItemText(IDC_EDIT_IMPORT_ADDRESS_TABLE_SZ, str);

	// DELAY_LOAD_IMPORT_DESCRIPTORS
	str.Format(_T("%08X"), pImageDataDirectory[13].VirtualAddress);
	SetDlgItemText(IDC_EDIT_DELAY_LOAD_IMPORT_DESCRIPTORS_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[13].Size);
	SetDlgItemText(IDC_EDIT_DELAY_LOAD_IMPORT_DESCRIPTORS_SZ, str);

	// COM_RUNTIME_DESCRIPTOR
	str.Format(_T("%08X"), pImageDataDirectory[14].VirtualAddress);
	SetDlgItemText(IDC_EDIT_COM_RUNTIME_DESCRIPTOR_VA, str);
	str.Format(_T("%08X"), pImageDataDirectory[14].Size);
	SetDlgItemText(IDC_EDIT_COM_RUNTIME_DESCRIPTOR_SZ, str);
}

VOID CDialogDataDirectory::SetpImageDataDirectory(PIMAGE_DATA_DIRECTORY pImageDataDirectory)
{
	m_pImageDataDirectory = pImageDataDirectory;
}

VOID CDialogDataDirectory::SetpImageBase(LPVOID pImageBase){
	m_pImageBase = pImageBase;
}

void CDialogDataDirectory::OnBnClickedButtonExportDirectoryInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	PIMAGE_EXPORT_DIRECTORY pImageExportDirectory;
	ExportTableFunctions ETF[64];
	size_t sizeETF;

	GetExportTableInfo(m_pImageBase, &pImageExportDirectory);
	GetExportTableFunctionInfoFile(m_pImageBase, pImageExportDirectory, ETF, 64, &sizeETF);
	m_DialogExportDirectoryInfo.SetExportFunctionsInfo(ETF, sizeETF);
	m_DialogExportDirectoryInfo.SetImageExportDescriptorInfo(m_pImageBase, pImageExportDirectory);

	m_DialogExportDirectoryInfo.DoModal();
}


void CDialogDataDirectory::OnClickedButtonImportDirectoryInfo()
{
	// TODO: 在此添加控件通知处理程序代码
	PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor;
	size_t size;
	GetImportTableInfoF(m_pImageBase, &pImageImportDescriptor, &size);
	m_DialogImportDirectoryInfo.SetImageImportDescriptorInfo(pImageImportDescriptor, size, m_pImageBase);
	m_DialogImportDirectoryInfo.DoModal();
}
