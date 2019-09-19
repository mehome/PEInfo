// DialogCalator.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "DialogCalator.h"
#include "afxdialogex.h"


// CDialogCalator �Ի���

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


// CDialogCalator ��Ϣ�������

void CDialogCalator::OnBnClickedButtonCalculate(){
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	DWORD VirtualAddress;
	CString str;
	DWORD Offset;
	VirtualAddress = wcstol(m_edit_rva, NULL,16);
	Rva2offset(m_ImageBase,(DWORD)VirtualAddress,&Offset);
	m_edit_offset.Format(_T("%08X"), Offset);
	UpdateData(FALSE);
}
