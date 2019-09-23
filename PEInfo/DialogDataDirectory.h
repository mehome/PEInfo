#pragma once

#include "./Core/core.h"
#include "DialogImportDirectoryInfo.h"
#include "DialogExportDirectoryInfo.h"
#include "DialogRelocationTableInfo.h"

// CDialogDataDirectory 对话框

class CDialogDataDirectory : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDataDirectory)

public:
	CDialogDataDirectory(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogDataDirectory();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DATADIRECTORY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	VOID AddDataDirectoryInfo(PIMAGE_DATA_DIRECTORY pImageDataDirectory);
	VOID SetpImageDataDirectory(PIMAGE_DATA_DIRECTORY pImageDataDirectory);
	VOID SetpImageBase(LPVOID pImageBase);

private:
	PIMAGE_DATA_DIRECTORY m_pImageDataDirectory;
	LPVOID m_pImageBase;
	CDialogImportDirectoryInfo m_DialogImportDirectoryInfo;
	CDialogExportDirectoryInfo m_DialogExportDirectoryInfo;
	CDialogRelocationTableInfo m_DialogReclocationTableInfo;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonExportDirectoryInfo();
	afx_msg void OnClickedButtonImportDirectoryInfo();
	afx_msg void OnClickedButtonRelocationTableInfo();
};
