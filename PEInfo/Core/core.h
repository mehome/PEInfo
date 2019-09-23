#pragma once

#include <windows.h>
#include <winerror.h>
// 为使用StringCchPrintf函数
#include<strsafe.h>

// 文件缓冲区长度
#define BUFFLENTH 8

// 文件结构
typedef struct _MAP_FILE_STRUCT
{
	HANDLE hFile;
	HANDLE hMapping;
	LPVOID ImageBase;
} MAP_FILE_STRUCT, *PMAP_FILE_STRUCT;

// 表结构
typedef struct _SectionTable{
	IMAGE_SECTION_HEADER imageSectionHeaders[64];
	unsigned short numberOfSections;
}SectionHeader;

// 导出表函数结构
typedef struct _ExportTableFunctions {
	DWORD Ordinal;
	DWORD RVA;
	DWORD AddressOfName;
}ExportTableFunctions,*PExportTableFunctions;

// 重定向表条目
typedef struct _RelocationTableItem {
	DWORD VirtualAddress;
	DWORD SizeOfBlock;
	CHAR Item[BUFFLENTH];
}RelocationTableItem,* PRelocationTableItem;

// 选择PE文件
BOOL ChooseFile(HWND hwnd, TCHAR szFilePath[MAX_PATH]);

// 将文件映射信息装载到全局变量中
BOOL RoadFile(LPCTSTR szFileName, PMAP_FILE_STRUCT pMFS);

// 判断是否为PE文件
BOOL IsPE32File(LPVOID ImageBase);

// 卸载内存中的文件
VOID UnloadFile(PMAP_FILE_STRUCT pMFS);

// 获取文件头信息
VOID GetFileHeaderInfo(LPVOID ImageBase, PIMAGE_FILE_HEADER pFH);

// 获取可选文件件信息
VOID GetOptionalHeaderInfo(LPVOID ImageBase, PIMAGE_OPTIONAL_HEADER pOH);

// 获取节表信息
VOID GetSectionTableInfo(LPVOID ImageBase, SectionHeader* pSectionHeader);

// 获取数据目录表信息
VOID GetDataDirectoryInfo(LPVOID ImageBase, PIMAGE_DATA_DIRECTORY pImageDataDirectory);

// 获取导入表信息
VOID GetImportTableInfoF(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR* pPImageImportDescriptorFile, size_t* size);

// 获取导入表的函数信息
VOID GetImportFunctions(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR pIID/* offa */, PIMAGE_THUNK_DATA32* pITD, size_t* ITDSize);

// 判断ITD结构是否是以序号开始的
BOOL IsSnapByOrdinal(IMAGE_THUNK_DATA32 ITD);

// 获取导出表序号
DWORD GetOrdinal(IMAGE_THUNK_DATA32 ITD);

// 获取IBN(IMAGE_IMPORT_BY_NAME)信息
VOID GetIIBN(LPVOID ImageBase, PIMAGE_THUNK_DATA32 pITD, PIMAGE_IMPORT_BY_NAME* pIBN);

// 获取导出表信息
VOID GetExportTableInfo(LPVOID ImageBase, PIMAGE_EXPORT_DIRECTORY* pED);

// 获取导出表导出的函数
VOID GetExportTableFunctionInfoFile(LPVOID pImageBase, PIMAGE_EXPORT_DIRECTORY pED, PExportTableFunctions pExportTableFunctionsOut, size_t maxExportTableFunctions, size_t* sizeOfExportTableFunctions);

// 获取重定位表信息
VOID GetRelocationTableItem(LPVOID ImageBase, PRelocationTableItem pRelocationTableItem, size_t* RelocationTableItemCount, size_t RelocationTableItemMaxCount);

// 是否有导出表
BOOL HasExportTable(LPVOID ImageBase);

// 是否有导入表
BOOL HasImportTable(LPVOID ImageBase);

// 是否有资源表
BOOL HasResourceTable(LPVOID ImageBase);

// 是否有重定位表
BOOL HasRelocationTable(LPVOID ImageBase);

// RVA转换为文件偏移
BOOL Rva2offset(LPVOID ImageBase, DWORD VirtualAddress, PDWORD dwOffset);