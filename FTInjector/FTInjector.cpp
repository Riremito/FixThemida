#include"../Share/Simple/Simple.h"

#define INJECTOR_NAME L"FTInjector"

#define INI_FILE_NAME INJECTOR_NAME".ini"
#define DLL_NAME L"FixThemida.dll"

bool Launcher(std::wstring wDroppedTarget) {
	Config conf(INI_FILE_NAME);
	std::wstring wTarget, wLoaderDLL, wMainDLL;
	bool check = true;

	if (wDroppedTarget.length()) {
		conf.Update(INJECTOR_NAME, L"TargetEXE", wDroppedTarget);

		std::wstring wDeafultLoaderDLL = DLL_NAME;
		conf.Update(INJECTOR_NAME, L"DLL", wDeafultLoaderDLL);
	}

	check &= conf.Read(INJECTOR_NAME, L"TargetEXE", wTarget);
	check &= conf.Read(INJECTOR_NAME, L"DLL", wLoaderDLL);

	if (!check) {
		return false;
	}

	std::wstring dir;
	if (!GetDir(dir)) {
		return false;
	}

	Injector injector(wTarget, dir + wLoaderDLL);
	return injector.Run();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	if (__argc < 2) {
		// create default ini file
		if (!Launcher(L"")) {
			MessageBoxW(NULL, L"Please check target exe file path", INJECTOR_NAME, MB_OK);
		}
	}
	else {
		// read config from ini file
		if (!Launcher(__wargv[1])) {
			MessageBoxW(NULL, L"Please drop target exe file", INJECTOR_NAME, MB_OK);
		}
	}

	return 0;
}