
// PEInfoDlg.h : 头文件
//

#pragma once

#include "./Core/core.h"
#include "DialogSectionTable.h"
#include "DialogDataDirectory.h"
#include "DialogCalator.h"

// CPEInfoDlg 对话框
class CPEInfoDlg : public CDialogEx
{
// 构造
public:
	CPEInfoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 展示可选头信息
	void ShowFileHeaderInfo(IMAGE_FILE_HEADER* pFileHeader);
	// 展示文件头信息
	void ShowOptionalHeaderInfo(IMAGE_OPTIONAL_HEADER * pOptionalHeader);
private:
	CDialogSectionTable m_SectionTableDialog;
	CDialogDataDirectory m_DataDirectoryDialog;
	CDialogCalator m_DialogCalator;
	MAP_FILE_STRUCT m_mfs;
public:
	afx_msg	void OnBnClickedButtonChooseFile();
	afx_msg void OnBnClickedButtonSectiontable();
	afx_msg void OnBnClickedButtonDatadirectory();
	afx_msg void OnBnClickedButtonCalculator();
};
