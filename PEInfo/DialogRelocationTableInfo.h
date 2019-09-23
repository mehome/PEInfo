#pragma once
#include "afxcmn.h"
#include "Core/core.h"

// CDialogRelocationTable �Ի���

class CDialogRelocationTableInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRelocationTableInfo)

public:
	CDialogRelocationTableInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogRelocationTableInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELOCATION_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	void SetRelocationTableItemInfo(PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount);
	void AddListCtrl1Info(PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount);
private:
	PRelocationTableItem m_pRelocationTableItem;
	size_t m_RelocationTableItemCount;

public:
	CListCtrl m_listCtrl1;
	CListCtrl m_listCtrl2;
	virtual BOOL OnInitDialog();
};
