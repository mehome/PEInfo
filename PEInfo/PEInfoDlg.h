
// PEInfoDlg.h : ͷ�ļ�
//

#pragma once

#include "./Core/core.h"
#include "DialogSectionTable.h"
#include "DialogDataDirectory.h"
#include "DialogCalator.h"

// CPEInfoDlg �Ի���
class CPEInfoDlg : public CDialogEx
{
// ����
public:
	CPEInfoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// չʾ��ѡͷ��Ϣ
	void ShowFileHeaderInfo(IMAGE_FILE_HEADER* pFileHeader);
	// չʾ�ļ�ͷ��Ϣ
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
