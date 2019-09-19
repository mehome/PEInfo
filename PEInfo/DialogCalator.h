#pragma once
#include "afxwin.h"


// CDialogCalator 对话框
#include "Core/core.h"

class CDialogCalator : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalator)

public:
	CDialogCalator(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogCalator();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALCULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetImageBase(LPVOID imageBase);
private:
	LPVOID m_ImageBase;
public:
	afx_msg void OnBnClickedButtonCalculate();
	CString m_edit_offset;
	CString m_edit_rva;
};
