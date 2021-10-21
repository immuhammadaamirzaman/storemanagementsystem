#pragma once
#ifndef Functions_h
#define Functions_h

#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<Psapi.h>
using namespace std;
#define passwd "123456"

void Mem(){
	PROCESS_MEMORY_COUNTERS memCounter;
	BOOL result = GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));//k32getprocess can be used
	std::cout << "Program Memory in RAM:" << ((float)memCounter.WorkingSetSize / 10000000) << " MB\n";
}
void SetFonts(){

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 24;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Menu(){
	SetFonts();
	system("color 30");
	Sleep(300);

	cout << "\t\t\t!!!***********************!!!\n";
	cout << "\t\t\t   STORE MANAGEMENT SYSTEM\n";
	cout << "\t\t\t!!!***********************!!!\n\n";
	Sleep(200);
	cout << "\n\nDEVELOPED BY:\n";
	Sleep(1500);
	system("color 60");
	Sleep(500);
	cout << "\t\t\tMUHAMMAD AAMIR ZAMAN\n\n";
	Sleep(450);
	cout << "\n\t\t      !!!-----------------XXX-----------------!!!\n";
	Sleep(500);
	system("cls");
}
void Loading(){
	system("cls");
	for (short i = 0; i < 3; i++){
		cout << "\nLoading Database... Please Wait!\n";
		Sleep(500);
		cout << " .";
		Sleep(500);
		cout << " .";
		Sleep(500);
		cout << " .";
		system("cls");
	}
}
void Login(){
Try:
	system("cls");
	Sleep(300);
	cout << "\t\tENTER ADMIN PASSWORD : ";
	char pass[20];
	char ch; //input
	short x = 0;
	 //stored password
	while (1)
	{
		ch = _getch();//in
		if (ch <= 'z'&& ch >= 'a' || ch <= 'Z' && ch >= 'A' || ch >= '0'&& ch <= '9'){//alphanumeric only in
			if (x <= 8){
				pass[x] = ch;
				cout << "*";
				x++;
			}
			else {
				cout << "\nToo much length for Password!!!\n";
				Sleep(1000);
				goto Try;
			}
		}
		if (ch == '\b'&& x >= 1){
			cout << "\b \b";
			x--;
		}
		if (ch == '\r'){//enter key
			if (x >= 6){
				pass[x] = '\0';
				break;
			}
			else{
				system("cls");
				Sleep(500);
				cout << "\n\tInvalid Password!!!";
				Sleep(1000);
				goto Try;
			}
		}
	}
	bool chk = 0;
	for (short i = 0; i < x; i++){
		if (pass[i] != passwd[i]){
			chk = 1;
		}
	}
	if (!chk){
		system("cls");
		Sleep(500);
		cout << "Password is Correct!";
		Sleep(500);
		Loading();
	}
	else{
		system("cls");
		Sleep(500);
		cout << "\n\tInvalid Password!!!";
		Sleep(1000);
		goto Try;
	}
}
#endif