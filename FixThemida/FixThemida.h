#ifndef __FIXTHEMIDA_H__
#define __FIXTHEMIDA_H__

#include<Windows.h>
#include<ImageHlp.h>
#include<vector>

// OS��Win10�̏ꍇ�ɌÂ��o�[�W������themida��kernel32.dll��user32.dll��EAT���擾����ۂɊԈ�����A�h���X���擾���ăN���b�V��������̑Ή� (JMS v176�����Ŕ���)
class FixThemida {
private:
	// �ꉞ�����o����悤�ɂ��Ă���
	std::vector<DWORD> vAddress;
	std::vector<DWORD> vValue;
	bool Fix(HMODULE hDll);
	bool Write(DWORD dwAddress, DWORD dwValue);

public:
	bool Patch();
	bool Restore();
};

#endif