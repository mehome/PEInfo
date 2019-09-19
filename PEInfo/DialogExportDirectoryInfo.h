#pragma once


// CDialogExportDirectoryInfo �Ի���
#include "Core/core.h"
#include "afxcmn.h"

class CDialogExportDirectoryInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogExportDirectoryInfo)

public:
	CDialogExportDirectoryInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogExportDirectoryInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EXPORT_DIRECTORY_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	VOID SetImageExportDescriptorInfo(LPVOID pImageBase, PIMAGE_EXPORT_DIRECTORY pImageExportDirectory);
	VOID SetExportFunctionsInfo(PExportTableFunctions pETF, size_t ETFSize);
	VOID AddImageExportDirectoryInfo(PIMAGE_EXPORT_DIRECTORY pImageExportDirectory);
	VOID AddListCtrlDataInfo(PExportTableFunctions pETF, size_t ETFSize);
private:
	PIMAGE_EXPORT_DIRECTORY m_pImageExportDirectory;
	LPVOID m_pImageBase;
	PExportTableFunctions m_pETF;
	size_t m_ETFSize;

public:
	virtual BOOL OnInitDialog();
	CListCtrl m_listCtrl;
};
