#ifndef __FIXTHEMIDA_H__
#define __FIXTHEMIDA_H__

#include<Windows.h>
#include<ImageHlp.h>
#include<vector>

// OSがWin10の場合に古いバージョンのthemidaがkernel32.dllとuser32.dllのEATを取得する際に間違ったアドレスを取得してクラッシュする問題の対応 (JMS v176未満で発生)
class FixThemida {
private:
	// 一応復元出来るようにしておく
	std::vector<DWORD> vAddress;
	std::vector<DWORD> vValue;
	bool Fix(HMODULE hDll);
	bool Write(DWORD dwAddress, DWORD dwValue);

public:
	bool Patch();
	bool Restore();
};

#endif