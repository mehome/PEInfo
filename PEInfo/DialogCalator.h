#pragma once
#include "afxwin.h"


// CDialogCalator �Ի���
#include "Core/core.h"

class CDialogCalator : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogCalator)

public:
	CDialogCalator(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogCalator();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALCULATOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
