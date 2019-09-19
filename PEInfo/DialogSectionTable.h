#pragma once
#include "afxcmn.h"


// CDialogSectionTable 对话框
#include "Core/core.h"

class CDialogSectionTable : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSectionTable)

public:
	CDialogSectionTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogSectionTable();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECATIONTABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void AddListCtrlData(SectionHeader* pSectionHeader);
	void SetpSectionHeader(SectionHeader* pSectionHeader);
private:
	SectionHeader* pSectionHeader;
public:
	CListCtrl m_listCtrlSectionTable;
	virtual BOOL OnInitDialog();
};
