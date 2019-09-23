#include "core.h"

BOOL ChooseFile(HWND hwnd, TCHAR szFilePath[MAX_PATH])
{
	// ѡ���ļ��������ļ�·�������ȫ�ֱ���g_szFilePath��
	OPENFILENAME ofn = { 0, };
	TCHAR tempSzFilePath[MAX_PATH] = { 0, };

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.hInstance = GetModuleHandle(NULL);
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrInitialDir = TEXT(".");
	ofn.lpstrFile = tempSzFilePath;
	ofn.lpstrTitle = TEXT("Choose a PE file");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFilter = TEXT("*.*\0*.*");

	// GetOpenFileName���һ���Ի��򣬲���ȡ��Ӧ���ļ�
	if (!GetOpenFileName(&ofn)){
		return FALSE;
	}else{
		if (SUCCEEDED(StringCchPrintf(szFilePath, MAX_PATH, ofn.lpstrFile))){
			return TRUE;
		}else{
			return FALSE;
		}
	}
}

BOOL RoadFile(LPCTSTR szFileName, PMAP_FILE_STRUCT pMFS)
{
	HANDLE hFile;
	HANDLE hMapFile;
	LPVOID ImageBase;

	// ������ļ�
	hFile = CreateFile(
		szFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	// �������ļ�ӳ���ں˶���
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (!hMapFile){
		return FALSE;
	}

	ImageBase = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
	if (!ImageBase){
		return FALSE;
	}

	pMFS->hFile = hFile;
	pMFS->hMapping = hMapFile;
	pMFS->ImageBase = ImageBase;
	return TRUE;
}

BOOL IsPE32File(LPVOID ImageBase)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_FILE_HEADER pFH = &pNtH->FileHeader;

	if (!pDH){
		return FALSE;
	}
	if (pDH->e_magic != IMAGE_DOS_SIGNATURE){
		return FALSE;
	}

	if (pNtH->Signature != IMAGE_NT_SIGNATURE){
		return FALSE;
	}
	if (pFH->Machine == IMAGE_FILE_MACHINE_I386){
		return TRUE;
	}else{
		return FALSE;
	}
}

VOID UnloadFile(PMAP_FILE_STRUCT pMFS)
{
	if (pMFS->hMapping){
		UnmapViewOfFile(pMFS->ImageBase);
	}

	if (pMFS->ImageBase){
		CloseHandle(pMFS->hMapping);
	}
	if (pMFS->hFile){
		CloseHandle(pMFS->hFile);
	}
}

VOID GetFileHeaderInfo(LPVOID ImageBase, PIMAGE_FILE_HEADER pFH)
{
	if (ImageBase == NULL) {
		return;
	}
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	*pFH = pNtH->FileHeader;
}

VOID GetOptionalHeaderInfo(LPVOID ImageBase, PIMAGE_OPTIONAL_HEADER pOH)
{
	if (ImageBase == NULL) {
		return;
	}
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	*pOH = pNtH->OptionalHeader;
}

VOID GetSectionTableInfo(LPVOID ImageBase, SectionHeader* pSectionHeader)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_FILE_HEADER pFH = &pNtH->FileHeader;
	PIMAGE_SECTION_HEADER pSH = IMAGE_FIRST_SECTION(pNtH);
	
	unsigned short i;
	pSectionHeader->numberOfSections = pFH->NumberOfSections;

	for (i = 0; i < pFH->NumberOfSections; i++, pSH++){
		pSectionHeader->imageSectionHeaders[i] = *pSH;
	}
}

VOID GetDataDirectoryInfo(LPVOID ImageBase, PIMAGE_DATA_DIRECTORY pImageDataDirectory)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOH = &pNtH->OptionalHeader;
	// ���һ��Ϊ����λ�������壬����ȥ
	int i;
	for (i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES - 1; i++) {
		pImageDataDirectory[i] = pOH->DataDirectory[i];
	}
}

BOOL HasExportTable(LPVOID ImageBase)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDD = &pNtH->OptionalHeader.DataDirectory[0];

	if (0 == pDD->Size){
		return FALSE;
	}else{
		return TRUE;
	}
}

BOOL HasImportTable(LPVOID ImageBase)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDD = &pNtH->OptionalHeader.DataDirectory[1];

	if (0 == pDD->Size){
		return FALSE;
	}else{
		return TRUE;
	}
}

BOOL HasResourceTable(LPVOID ImageBase)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDD = &pNtH->OptionalHeader.DataDirectory[2];

	if (0 == pDD->Size)
	{
		return FALSE;
	}else{
		return TRUE;
	}
}

BOOL HasRelocationTable(LPVOID ImageBase) {
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDD = &pNtH->OptionalHeader.DataDirectory[5];

	if (0 == pDD->Size)
	{
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL Rva2offset(LPVOID ImageBase, DWORD VirtualAddress, PDWORD dwOffset)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_SECTION_HEADER pSH = IMAGE_FIRST_SECTION(pNtH);

	// ����ѭ��ÿ���ڱ�
	size_t i = 0;
	for (i = 0; i < pNtH->FileHeader.NumberOfSections; i++, pSH++)
	{
		// �жϵ�ǰ����Ѱ�ҵ�VA�Ƿ��ڴ˽ڱ���
		if (pSH->VirtualAddress <= VirtualAddress && VirtualAddress < pSH->VirtualAddress + pSH->SizeOfRawData)
		{
			// ������ļ��ڵ�ƫ�Ƶ�ַ
			*dwOffset = VirtualAddress - pSH->VirtualAddress + pSH->PointerToRawData;
			return TRUE;
		}
	}

	*dwOffset = 0xFFFFFFFF;
	return FALSE;
}

VOID GetImportTableInfoF(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR* pPImageImportDescriptorFile, size_t* size)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	DWORD dwOffset;
	
	Rva2offset(ImageBase, pNtH->OptionalHeader.DataDirectory[1].VirtualAddress, &dwOffset);
	// �õ���������ļ��е�ƫ�Ƶ�ַ
	PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)ImageBase + dwOffset);
	*pPImageImportDescriptorFile = pID;

	size_t i = 0;
	while (0 != pID->Name){
		pID++;
		i++;
	}
	*size = i;
}

VOID GetImportFunctions(LPVOID ImageBase, PIMAGE_IMPORT_DESCRIPTOR pIID/* offa */, PIMAGE_THUNK_DATA32* pITD, size_t* ITDSize)
{
	PIMAGE_THUNK_DATA pTD = NULL;
	PIMAGE_IMPORT_BY_NAME pIBN = NULL;
	DWORD dwOffset;
	
	// ���OrignalFirstThunk�����ڣ��ŵ���FirstThunk
	Rva2offset(ImageBase, pIID->OriginalFirstThunk, &dwOffset);
	if (0 == *(PDWORD)((DWORD)ImageBase + dwOffset)){
		Rva2offset(ImageBase, pIID->FirstThunk, &dwOffset);
	}
	pTD = (PIMAGE_THUNK_DATA)((DWORD)ImageBase + dwOffset);
	*pITD = pTD;

	size_t i = 0;
	while (0 != pTD->u1.AddressOfData){
		i++;
		pTD++;
	}
	*ITDSize = i;
}

BOOL IsSnapByOrdinal(IMAGE_THUNK_DATA32 ITD){
	return IMAGE_SNAP_BY_ORDINAL(ITD.u1.Ordinal);
}

DWORD GetOrdinal(IMAGE_THUNK_DATA32 ITD) {
	if (IsSnapByOrdinal(ITD)) {
		return IMAGE_ORDINAL(ITD.u1.Ordinal);
	}
	return -1;
}

// IMAGE_IMPORT_BY_NAME
VOID GetIIBN(LPVOID ImageBase, PIMAGE_THUNK_DATA32 pITD, PIMAGE_IMPORT_BY_NAME* pIBN) {
	DWORD dwOffset;
	Rva2offset(ImageBase, pITD->u1.AddressOfData, &dwOffset);
	*pIBN = (PIMAGE_IMPORT_BY_NAME)((DWORD)ImageBase + dwOffset);
	return;
}

VOID GetExportTableInfo(LPVOID ImageBase, PIMAGE_EXPORT_DIRECTORY* pED)
{
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNth = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_DATA_DIRECTORY pDD = &pNth->OptionalHeader.DataDirectory[0];

	DWORD dwOffset;
	Rva2offset(ImageBase, pDD->VirtualAddress, &dwOffset);
	*pED = (PIMAGE_EXPORT_DIRECTORY)((DWORD)ImageBase + dwOffset);
}

VOID GetExportTableFunctionInfoFile(LPVOID pImageBase, PIMAGE_EXPORT_DIRECTORY pED, PExportTableFunctions pExportTableFunctionsOut, size_t maxExportTableFunctions, size_t* sizeOfExportTableFunctions) {
	DWORD dwOffset;
	BOOL bExportByName;	// �����Ƿ����������
	DWORD dwEAT;		// �����ַ��, ��һ��RVA����
	DWORD dwENT;		// ����������Ʊ�, ��һ��ָ��ASCII�ַ�����RVA����
	DWORD dwOrdinal;	// �������

	Rva2offset(pImageBase, pED->AddressOfFunctions, &dwOffset);
	dwEAT = (DWORD)pImageBase + dwOffset;

	Rva2offset(pImageBase, pED->AddressOfNames, &dwOffset);
	dwENT = (DWORD)pImageBase + dwOffset;

	Rva2offset(pImageBase, pED->AddressOfNameOrdinals, &dwOffset);
	dwOrdinal = (DWORD)pImageBase + dwOffset;

	//NumberofFunctions ���е�������������
	size_t maxNumberofFunctions = 0; // �ɴ�ŵ��������������
	if (pED->NumberOfFunctions > maxExportTableFunctions) {
		maxNumberofFunctions = maxExportTableFunctions;
	}else {
		maxNumberofFunctions = pED->NumberOfFunctions;
	}
	 
	for (size_t i = 0; i < maxNumberofFunctions; i++){

		pExportTableFunctionsOut[i].Ordinal = pED->Base + i;
		
		pExportTableFunctionsOut[i].RVA = *(PDWORD)(dwEAT + i * sizeof(DWORD));
		
		bExportByName = FALSE;
		size_t j;
		for (j = 0; j < pED->NumberOfNames; j++)
		{
			if (i == *(PWORD)(dwOrdinal + j * sizeof(WORD)))
			{
				bExportByName = TRUE;
				break;
			}
		}
		if (bExportByName){
			Rva2offset(pImageBase, *(PDWORD)(dwENT + j * sizeof(DWORD)), &dwOffset);
			pExportTableFunctionsOut[i].AddressOfName = (DWORD)pImageBase + dwOffset;
		}else{
			pExportTableFunctionsOut[i].AddressOfName = 0;
		}
	}
	*sizeOfExportTableFunctions = maxNumberofFunctions;
}

VOID GetRelocationTableItem(LPVOID ImageBase, PRelocationTableItem pRelocationTableItem,size_t* RelocationTableItemCount, size_t RelocationTableItemMaxCount) {

	// �ж��Ƿ�����ض�λ��
	if (!HasRelocationTable(ImageBase)) {
		return;
	}

	// ��ȡ�ض�λ����ļ�ƫ����Ϣ
	BYTE secName[9] = { 0 };
	DWORD dwOffset = 0;
	PIMAGE_DOS_HEADER pDH = (PIMAGE_DOS_HEADER)ImageBase;
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((DWORD)pDH + pDH->e_lfanew);
	PIMAGE_OPTIONAL_HEADER pOH = &pNtH->OptionalHeader;

	Rva2offset(ImageBase, pOH->DataDirectory[5].VirtualAddress,&dwOffset);
	//recָ���ض�λ���һ��IMAGE_BASE_RELOCATION�ṹ�壬��ȡ��Ӧ���ļ�ƫ�Ƶ�ַ
	IMAGE_BASE_RELOCATION * rec = (IMAGE_BASE_RELOCATION *)((DWORD)ImageBase + dwOffset);

	// ���������������ֱ�ӷ���
	if (rec->SizeOfBlock > RelocationTableItemMaxCount) {
		return;
	}

	// ���������Ϊ0���������ƫ��
	size_t i = 0;
	for (i = 0; rec->SizeOfBlock && rec->VirtualAddress; i++) {
		// ��Ҫ��ȡ��ǰ���ض�λ����ļ�ƫ��
		Rva2offset(ImageBase, rec->VirtualAddress, &dwOffset);
		DWORD foa = (DWORD)ImageBase + dwOffset;

		//ȷ���ýṹ�������ڣ�����ȡ������
		PIMAGE_SECTION_HEADER pSH = IMAGE_FIRST_SECTION(pNtH);
		for (int t = 0; t < pNtH->FileHeader.NumberOfSections; t++) {
			Rva2offset(ImageBase,pSH[t].VirtualAddress, &dwOffset);
			DWORD lower = (DWORD)ImageBase + dwOffset;
			DWORD upper = lower + pSH[t].Misc.VirtualSize;
			if (foa >= lower && foa <= upper) {
				memcpy(pRelocationTableItem[i].Item, pSH[t].Name, 8);
				pRelocationTableItem[i].SizeOfBlock = rec->SizeOfBlock;
				pRelocationTableItem[i].VirtualAddress = rec->VirtualAddress;
				break;
			}
		}
		//������һҳ���ж�
		rec = (IMAGE_BASE_RELOCATION *)((BYTE *)rec + rec->SizeOfBlock);
	}
	*RelocationTableItemCount = i;
}
