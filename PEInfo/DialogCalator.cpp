// DialogCalator.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogCalator.h"
#include "afxdialogex.h"


// CDialogCalator 对话框

IMPLEMENT_DYNAMIC(CDialogCalator, CDialogEx)

CDialogCalator::CDialogCalator(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_edit_offset(_T(""))
	, m_edit_rva(_T(""))
{

}

CDialogCalator::~CDialogCalator()
{
}

void CDialogCalator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_OFFSET, m_edit_offset);
	DDX_Text(pDX, IDC_EDIT_RVA, m_edit_rva);
}

void CDialogCalator::SetImageBase(LPVOID imageBase)
{
	m_ImageBase = imageBase;
}


BEGIN_MESSAGE_MAP(CDialogCalator, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATE, &CDialogCalator::OnBnClickedButtonCalculate)
END_MESSAGE_MAP()


// CDialogCalator 消息处理程序

void CDialogCalator::OnBnClickedButtonCalculate(){
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	DWORD VirtualAddress;
	CString str;
	DWORD Offset;
	VirtualAddress = wcstol(m_edit_rva, NULL,16);
	Rva2offset(m_ImageBase,(DWORD)VirtualAddress,&Offset);
	m_edit_offset.Format(_T("%08X"), Offset);
	UpdateData(FALSE);
}
