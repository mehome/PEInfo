#pragma once
#include "afxcmn.h"


// CDialogImportDirectoryInfo 对话框
#include "Core/core.h"

class CDialogImportDirectoryInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogImportDirectoryInfo)

public:
	CDialogImportDirectoryInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogImportDirectoryInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_IMPORT_DIRECTORY_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void AddListCtrl1Data(PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor, size_t ImageImportDescriptorSize);
	void AddListCtrl2Data(PIMAGE_THUNK_DATA32 pITD, size_t ITDSize);
	void SetImageImportDescriptorInfo(PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor, size_t ImageImportDescriptorSize, LPVOID pImageBase);

private:
	PIMAGE_IMPORT_DESCRIPTOR m_pImageImportDescriptor;
	size_t m_ImageImportDescriptorSize;
	LPVOID m_pImageBase;

public:
	CListCtrl m_listCtrl;
	CListCtrl m_listCtrl2;

	virtual BOOL OnInitDialog();
	
	afx_msg void OnClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};
