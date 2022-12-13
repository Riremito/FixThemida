#include"FixThemida.h"

bool FixThemida::Write(DWORD dwAddress, DWORD dwValue) {
	DWORD old = 0;
	if (!VirtualProtect((void *)dwAddress, sizeof(DWORD), PAGE_READWRITE, &old)) {
		return false;
	}

	*(DWORD *)dwAddress = dwValue;

	if (!VirtualProtect((void *)dwAddress, sizeof(DWORD), old, &old)) {
		return false;
	}

	return true;
}

bool FixThemida::Fix(HMODULE hDll) {
	DWORD base = (DWORD)hDll;

	IMAGE_DOS_HEADER *idh = (decltype(idh))base;
	IMAGE_NT_HEADERS *inh = (decltype(inh))(base + idh->e_lfanew);
	IMAGE_SECTION_HEADER *ish = (decltype(ish))((DWORD)&inh->OptionalHeader + inh->FileHeader.SizeOfOptionalHeader);

	// ƒZƒNƒVƒ‡ƒ“î•ñ‚ğ‘‚«Š·‚¦‚é
	for (int i = 0; i < inh->FileHeader.NumberOfSections; i++) {
		vAddress.push_back((DWORD)&ish[i].PointerToRawData);
		vValue.push_back((DWORD)ish[i].PointerToRawData);
		Write((DWORD)&ish[i].PointerToRawData, ish[i].VirtualAddress);
	}

	return true;
}

bool FixThemida::Patch() {
	HMODULE hDll = GetModuleHandleW(L"kernel32.dll");
	if (hDll) {
		Fix(hDll);
	}
	hDll = GetModuleHandleW(L"user32.dll");
	if (!hDll) {
		hDll = LoadLibraryW(L"user32.dll");
	}
	if (hDll) {
		Fix(hDll);
	}
	return true;
}

bool FixThemida::Restore() {
	for (size_t i = 0; i < vAddress.size(); i++) {
		Write(vAddress[i], vValue[i]);
	}
	vAddress.clear();
	return true;
}