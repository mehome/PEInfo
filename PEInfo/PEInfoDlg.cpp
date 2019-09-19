
// PEInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PEInfo.h"
#include "PEInfoDlg.h"
#include "afxdialogex.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPEInfoDlg 对话框



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


// CPEInfoDlg 消息处理程序

BOOL CPEInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPEInfoDlg::OnPaint()
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
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilePath[MAX_PATH];	// 文件路径
	
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

	// 获取相关的文件信息
	IMAGE_FILE_HEADER file_header;		//  文件头
	IMAGE_OPTIONAL_HEADER op_header;	// 可选头
	GetOptionalHeaderInfo(m_mfs.ImageBase, &op_header);
	GetFileHeaderInfo(m_mfs.ImageBase, &file_header);

	// 展示可相关信息
	ShowOptionalHeaderInfo(&op_header);
	ShowFileHeaderInfo(&file_header);

	// 开启节表按扭
	((CButton*)GetDlgItem(IDC_BUTTON_SECTIONTABLE))->EnableWindow(TRUE);
	// 开启数据目录表按扭
	(CButton*)GetDlgItem(IDC_BUTTON_DATADIRECTORY)->EnableWindow(TRUE);
	// 开启计算机器按扭
	(CButton*)GetDlgItem(IDC_BUTTON_CALCULATOR)->EnableWindow(TRUE);
}


void CPEInfoDlg::OnBnClickedButtonSectiontable()
{
	// TODO: 在此添加控件通知处理程序代码
	SectionHeader sectionHeader;
	GetSectionTableInfo(m_mfs.ImageBase, &sectionHeader);
	m_SectionTableDialog.SetpSectionHeader(&sectionHeader);
	m_SectionTableDialog.DoModal();
}


void CPEInfoDlg::OnBnClickedButtonDatadirectory()
{
	// TODO: 在此添加控件通知处理程序代码
	IMAGE_DATA_DIRECTORY ImageDataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
	GetDataDirectoryInfo(m_mfs.ImageBase, ImageDataDirectory);

	m_DataDirectoryDialog.SetpImageDataDirectory(ImageDataDirectory);
	m_DataDirectoryDialog.SetpImageBase(m_mfs.ImageBase);
	m_DataDirectoryDialog.DoModal();
}


void CPEInfoDlg::OnBnClickedButtonCalculator()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DialogCalator.SetImageBase(m_mfs.ImageBase);
	m_DialogCalator.DoModal();
}
