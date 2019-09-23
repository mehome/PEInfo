#pragma once

#include <windows.h>
#include <winerror.h>
// Ϊʹ��StringCchPrintf����
#include<strsafe.h>

// �ļ�����������
#define BUFFLENTH 8

// �ļ��ṹ
typedef struct _MAP_FILE_STRUCT
{
	HANDLE hFile;
	HANDLE hMapping;
	LPVOID ImageBase;
} MAP_FILE_STRUCT, *PMAP_FILE_STRUCT;

// ��ṹ
typedef struct _SectionTable{
	IMAGE_SECTION_HEADER imageSectionHeaders[64];
	unsigned short numberOfSections;
}SectionHeader;

// ���������ṹ
typedef struct _ExportTableFunctions {
	DWORD Ordinal;
	DWORD RVA;
	DWORD AddressOfName;
}ExportTableFunctions,*PExportTableFunctions;

// �ض������Ŀ
typedef struct _RelocationTableItem {
	DWORD VirtualAddress;
	DWORD SizeOfBlock;
	CHAR Item[BUFFLENTH];
}RelocationTableItem,* PRelocationTableItem;

// ѡ��PE�ļ�
BOOL ChooseFile(HWND hwnd, TCHAR szFilePath[MAX_PATH]);

// ���ļ�ӳ����Ϣװ�ص�ȫ�ֱ�����
BOOL RoadFile(LPCTSTR szFileName, PMAP_FILE_STRUCT pMFS);

// �ж��Ƿ�ΪPE�ļ�
BOOL IsPE32File(LPVOID ImageBase);

// ж���ڴ��е��ļ�
VOID UnloadFile(PMAP_FILE_STRUCT pMFS);

// ��ȡ�ļ�ͷ��Ϣ
VOID GetFileHeaderInfo(LPVOID ImageBase, PIMAGE_FILE_HEADER pFH);

// ��ȡ��ѡ�ļ�����Ϣ
VOID GetOptionalHeaderInfo(LPVOID ImageBase, PIMAGE_OPTIONAL_HEADER pOH);

// ��ȡ�ڱ���Ϣ
VOID GetSectionTableInfo(LPVOID ImageBase, SectionHeader* pSectionHeader);

// ��ȡ����Ŀ¼����Ϣ
VOID GetDataDirectoryInfo(LPVOID ImageBase, PIMAGE_DATA_DIRECTORY pImageDataDirectory);

// ��ȡ�������Ϣ
VOID GetImportTableInfoF(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR* pPImageImportDescriptorFile, size_t* size);

// ��ȡ�����ĺ�����Ϣ
VOID GetImportFunctions(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR pIID/* offa */, PIMAGE_THUNK_DATA32* pITD, size_t* ITDSize);

// �ж�ITD�ṹ�Ƿ�������ſ�ʼ��
BOOL IsSnapByOrdinal(IMAGE_THUNK_DATA32 ITD);

// ��ȡ���������
DWORD GetOrdinal(IMAGE_THUNK_DATA32 ITD);

// ��ȡIBN(IMAGE_IMPORT_BY_NAME)��Ϣ
VOID GetIIBN(LPVOID ImageBase, PIMAGE_THUNK_DATA32 pITD, PIMAGE_IMPORT_BY_NAME* pIBN);

// ��ȡ��������Ϣ
VOID GetExportTableInfo(LPVOID ImageBase, PIMAGE_EXPORT_DIRECTORY* pED);

// ��ȡ���������ĺ���
VOID GetExportTableFunctionInfoFile(LPVOID pImageBase, PIMAGE_EXPORT_DIRECTORY pED, PExportTableFunctions pExportTableFunctionsOut, size_t maxExportTableFunctions, size_t* sizeOfExportTableFunctions);

// ��ȡ�ض�λ����Ϣ
VOID GetRelocationTableItem(LPVOID ImageBase, PRelocationTableItem pRelocationTableItem, size_t* RelocationTableItemCount, size_t RelocationTableItemMaxCount);

// �Ƿ��е�����
BOOL HasExportTable(LPVOID ImageBase);

// �Ƿ��е����
BOOL HasImportTable(LPVOID ImageBase);

// �Ƿ�����Դ��
BOOL HasResourceTable(LPVOID ImageBase);

// �Ƿ����ض�λ��
BOOL HasRelocationTable(LPVOID ImageBase);

// RVAת��Ϊ�ļ�ƫ��
BOOL Rva2offset(LPVOID ImageBase, DWORD VirtualAddress, PDWORD dwOffset);