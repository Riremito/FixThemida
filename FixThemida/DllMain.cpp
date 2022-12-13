#include"FixThemida.h"

bool FixThemidaAccessViolation() {
	FixThemida ft;
	ft.Patch();
	return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);
		FixThemidaAccessViolation();
	}
	return TRUE;
}