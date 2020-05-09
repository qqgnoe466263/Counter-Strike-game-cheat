#include <iostream>
#include <stdio.h>
#include <Windows.h>

using namespace std;

int main(int argc, char** argv) 
{
	HWND hwnd = FindWindowA(NULL, "Counter-Strike");
	if (hwnd == NULL) {
		cout << "[!] FindWindowA error" << endl;
		system("pause");
		return 0;
	}
	DWORD pid = 0;
	GetWindowThreadProcessId(hwnd, &pid); 
	HANDLE hgame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	
	
	
	DWORD base = 0x025069bc;
	/* 1st weapon bullet offset*/
	DWORD off1 = 0x7c;
	DWORD off2 = 0x5d8;
	DWORD off3 = 0xcc;
	/* 2st weap bullet offset 
	 * off1 = 0x7c
	 * off2 = 0x5dc
	 * off3 = 0xcc
	 */
	DWORD buf = 0;
	DWORD first_weapon_bullet = 0;
	ReadProcessMemory(hgame, (LPVOID)base, &buf, sizeof(DWORD), 0);
	base = buf + off1;
	ReadProcessMemory(hgame, (LPVOID)base, &buf, sizeof(DWORD), 0);
	base = buf + off2;
	ReadProcessMemory(hgame, (LPVOID)base, &buf, sizeof(DWORD), 0);
	base = buf + off3;
	int count = 30;
	while(1) {
		ReadProcessMemory(hgame, (LPVOID)base, &first_weapon_bullet, sizeof(DWORD), 0);
		printf("[+] first weapon bullet count : %d\n", first_weapon_bullet);
		WriteProcessMemory(hgame, (LPVOID)base, &count, sizeof(int), 0);
		Sleep(50);
	}
	
	return 0;
}
