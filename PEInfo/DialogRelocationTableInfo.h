#pragma once
#include "afxcmn.h"
#include "Core/core.h"

// CDialogRelocationTable 对话框

class CDialogRelocationTableInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogRelocationTableInfo)

public:
	CDialogRelocationTableInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogRelocationTableInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RELOCATION_TABLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void SetRelocationTableItemInfo(LPVOID pImageBase,PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount);
	void AddListCtrl1Info(PRelocationTableItem pRelocationTableItem, size_t RelocationTableItemCount);
	void AddListCtrl2Info(PRelocationTableItemInfo pRelocationTableItemInfo, DWORD SizeOfRelocationTableItemInfo);
private:
	PRelocationTableItem m_pRelocationTableItem;
	LPVOID m_pImageBase;
	size_t m_RelocationTableItemCount;

public:
	CListCtrl m_listCtrl1;
	CListCtrl m_listCtrl2;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
