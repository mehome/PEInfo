#pragma once
#include "afxcmn.h"


// CDialogSectionTable �Ի���
#include "Core/core.h"

class CDialogSectionTable : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSectionTable)

public:
	CDialogSectionTable(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogSectionTable();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SECATIONTABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
