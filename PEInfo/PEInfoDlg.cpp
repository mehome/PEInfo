
// PEInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEInfoDlg �Ի���



CPEInfoDlg::CPEInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PEINFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPEInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPEInfoDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_FILE, &CPEInfoDlg::OnBnClickedButtonChooseFile)
	ON_BN_CLICKED(IDC_BUTTON_SECTIONTABLE, &CPEInfoDlg::OnBnClickedButtonSectiontable)
	ON_BN_CLICKED(IDC_BUTTON_DATADIRECTORY, &CPEInfoDlg::OnBnClickedButtonDatadirectory)
	ON_BN_CLICKED(IDC_BUTTON_CALCULATOR, &CPEInfoDlg::OnBnClickedButtonCalculator)
END_MESSAGE_MAP()


// CPEInfoDlg ��Ϣ�������

BOOL CPEInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPEInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPEInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPEInfoDlg::ShowFileHeaderInfo(IMAGE_FILE_HEADER * pFileHeader)
{
	CString strTemp;
	// - - - - - - - - - - - - - - - - -
	// FileHeader
	strTemp.Format(_T("%04X"), pFileHeader->Machine);
	SetDlgItemText(IDC_EDIT_MACHINE, strTemp);

	strTemp.Format(_T("%04X"), pFileHeader->NumberOfSections);
	SetDlgItemText(IDC_EDIT_NUMBERSIONOFSECTIONS, strTemp);

	strTemp.Format(_T("%08X"), pFileHeader->TimeDateStamp);
	SetDlgItemText(IDC_EDIT_TIMEDATESTAMP, strTemp);

	strTemp.Format(_T("%08X"), pFileHeader->PointerToSymbolTable);
	SetDlgItemText(IDC_EDIT_POINTERTOSYMBOLTABLE, strTemp);

	strTemp.Format(_T("%08X"), pFileHeader->NumberOfSymbols);
	SetDlgItemText(IDC_EDIT_NUMBEROFSYMBOLS, strTemp);

	strTemp.Format(_T("%04X"), pFileHeader->SizeOfOptionalHeader);
	SetDlgItemText(IDC_EDIT_SIZEOFOPTIONALHEADER, strTemp);

	strTemp.Format(_T("%04X"), pFileHeader->Characteristics);
	SetDlgItemText(IDC_EDIT_CHARACTERISTICS, strTemp);
}


void CPEInfoDlg::ShowOptionalHeaderInfo(IMAGE_OPTIONAL_HEADER* pOptionalHeader) {
	CString strTemp;

	// IMAGE_OPTIONAL_HEADER32
	// Standard fields
	strTemp.Format(_T("%04X"), pOptionalHeader->Magic);
	SetDlgItemText(IDC_EDIT_MAGIC, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MajorLinkerVersion);
	SetDlgItemText(IDC_EDIT_MAJORLINKVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MinorLinkerVersion);
	SetDlgItemText(IDC_EDIT_MINORLINKERVERSION, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfCode);
	SetDlgItemText(IDC_EDIT_SIZEOFCODE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfInitializedData);
	SetDlgItemText(IDC_EDIT_SIZEOFINITIALIZEDDATA, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfUninitializedData);
	SetDlgItemText(IDC_EDIT_SIZEOFUNINITIALIZEDDATA, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->AddressOfEntryPoint);
	SetDlgItemText(IDC_EDIT_ADDRESSOFENTRYPOINT, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->BaseOfCode);
	SetDlgItemText(IDC_EDIT_BASEOFCODE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->BaseOfData);
	SetDlgItemText(IDC_EDIT_BASEOFDATA, strTemp);

	//
	// NT additional fields.
	//

	strTemp.Format(_T("%08X"), pOptionalHeader->ImageBase);
	SetDlgItemText(IDC_EDIT_IMAGEBASE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SectionAlignment);
	SetDlgItemText(IDC_EDIT_SECTIONALIGNMENT, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->FileAlignment);
	SetDlgItemText(IDC_EDIT_FILEALIGNMENT, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MajorOperatingSystemVersion);
	SetDlgItemText(IDC_EDIT_MAJOROPERATINGSYSTEMVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MinorOperatingSystemVersion);
	SetDlgItemText(IDC_EDIT_MINOROPERATINGSYSTEMVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MajorImageVersion);
	SetDlgItemText(IDC_EDIT_MAJORIMAGEVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MinorImageVersion);
	SetDlgItemText(IDC_EDIT_MINORIMAGEVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MajorSubsystemVersion);
	SetDlgItemText(IDC_EDIT_MAJORSUBSYSTEMVERSION, strTemp);

	strTemp.Format(_T("%02X"), pOptionalHeader->MinorSubsystemVersion);
	SetDlgItemText(IDC_EDIT_MINORSUBSYSTEMVERSION, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->Win32VersionValue);
	SetDlgItemText(IDC_EDIT_WIN32VERSIONVALUE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfImage);
	SetDlgItemText(IDC_EDIT_SIZEOFIMAGE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfHeaders);
	SetDlgItemText(IDC_EDIT_SIZEOFHEADERS, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->CheckSum);
	SetDlgItemText(IDC_EDIT_CHECKSUM, strTemp);

	strTemp.Format(_T("%04X"), pOptionalHeader->Subsystem);
	SetDlgItemText(IDC_EDIT_SUBSYSTEM, strTemp);

	strTemp.Format(_T("%04X"), pOptionalHeader->DllCharacteristics);
	SetDlgItemText(IDC_EDIT_DLLCHARACTERISTICS, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfStackReserve);
	SetDlgItemText(IDC_EDIT_SIZEOFSTACKRESERVE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfStackCommit);
	SetDlgItemText(IDC_EDIT_SIZEOFSTACKCOMMIT, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfHeapReserve);
	SetDlgItemText(IDC_EDIT_SIZEOFHEAPRESERVE, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->SizeOfHeapCommit);
	SetDlgItemText(IDC_EDIT_SIZEOFHEAPCOMMIT, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->LoaderFlags);
	SetDlgItemText(IDC_EDIT_LOADERFLAGS, strTemp);

	strTemp.Format(_T("%04X"), pOptionalHeader->NumberOfRvaAndSizes);
	SetDlgItemText(IDC_EDIT_NUMBEROFRVAANDSIZES, strTemp);

	strTemp.Format(_T("%08X"), pOptionalHeader->DataDirectory);
	SetDlgItemText(IDC_EDIT_DATADIRECTORY, strTemp);

}

void CPEInfoDlg::OnBnClickedButtonChooseFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilePath[MAX_PATH];	// �ļ�·��
	
	if (ChooseFile(GetSafeHwnd(), szFilePath)) {
		SetDlgItemText(IDC_EDIT_PATH, szFilePath);
	}
	if (!RoadFile(szFilePath, &m_mfs)) {
		MessageBox(TEXT("Cannot load the file!"), _T("warning"), MB_ICONERROR | MB_OK);
		return;
	}
	if (!IsPE32File(m_mfs.ImageBase))
	{
		UnloadFile(&m_mfs);
		MessageBox(TEXT("Not a valid PE32 file!"), TEXT("warning"), MB_ICONERROR | MB_OK);
		return;
	}

	// ��ȡ��ص��ļ���Ϣ
	IMAGE_FILE_HEADER file_header;		//  �ļ�ͷ
	IMAGE_OPTIONAL_HEADER op_header;	// ��ѡͷ
	GetOptionalHeaderInfo(m_mfs.ImageBase, &op_header);
	GetFileHeaderInfo(m_mfs.ImageBase, &file_header);

	// չʾ�������Ϣ
	ShowOptionalHeaderInfo(&op_header);
	ShowFileHeaderInfo(&file_header);

	// �����ڱ�Ť
	((CButton*)GetDlgItem(IDC_BUTTON_SECTIONTABLE))->EnableWindow(TRUE);
	// ��������Ŀ¼��Ť
	(CButton*)GetDlgItem(IDC_BUTTON_DATADIRECTORY)->EnableWindow(TRUE);
	// �������������Ť
	(CButton*)GetDlgItem(IDC_BUTTON_CALCULATOR)->EnableWindow(TRUE);
}


void CPEInfoDlg::OnBnClickedButtonSectiontable()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SectionHeader sectionHeader;
	GetSectionTableInfo(m_mfs.ImageBase, &sectionHeader);
	m_SectionTableDialog.SetpSectionHeader(&sectionHeader);
	m_SectionTableDialog.DoModal();
}


void CPEInfoDlg::OnBnClickedButtonDatadirectory()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	IMAGE_DATA_DIRECTORY ImageDataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
	GetDataDirectoryInfo(m_mfs.ImageBase, ImageDataDirectory);

	m_DataDirectoryDialog.SetpImageDataDirectory(ImageDataDirectory);
	m_DataDirectoryDialog.SetpImageBase(m_mfs.ImageBase);
	m_DataDirectoryDialog.DoModal();
}


void CPEInfoDlg::OnBnClickedButtonCalculator()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DialogCalator.SetImageBase(m_mfs.ImageBase);
	m_DialogCalator.DoModal();
}
