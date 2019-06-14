#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "library.h"
#include <wchar.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#define max 1000
#define max_char 30



void main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	FILE * pFile = NULL;
	wchar_t line[max];

	pFile = _wfopen(L"Input.txt", L"r,ccs=UTF-16LE");
	GetSentence(pFile, line);
	fclose(pFile);
	wprintf(L"Chuỗi đầu vào: %s", line);

	ChuanHoaDau(line);

	wprintf(L"\nChuỗi sau khi chuẩn hóa: %s", line);

	pFile = _wfopen(L"Dictionary_File.txt", L"r,ccs=UTF-16LE");
	if (!pFile)
	{
		wprintf(L"ERROR: Dictionary is not avaible.\n");
		return;
	}
	int n = 0;
	wchar_t **String;
	fwscanf(pFile, L"%d\n", &n);
	String = new wchar_t*[n];
	for (int i = 0; i < n; i++)
	{
		String[i] = new wchar_t[max_char];
	}
	DocThuVien(pFile, String, n);
	fclose(pFile);

	int Word;
	int TuLay;
	int ComPoundWord = CompoundWord(line, String,TuLay, Word, n);

	wprintf(L"\nSố từ đơn là: %d", NumberOfSingleWord(line));
	wprintf(L"\nSố từ là: %d", Word);
	wprintf(L"\nSố từ ghép là: %d", ComPoundWord);
	wprintf(L"\nSố từ láy là: %d\n", TuLay);
	
	

	
	Destroy(String, n);
	_getch();
}

