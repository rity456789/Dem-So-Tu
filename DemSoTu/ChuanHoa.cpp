// Source này làm hàm chuẩn hóa, chẳng hạn như từ "học sinh" sẽ được đưa về "hoc sinh"
//	Mục tiêu duy nhất của source này là hỗ trợ hàm để xử lý từ láy

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "library.h"
#include <wchar.h>
#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()

wchar_t aList[18][3];
wchar_t eList[12][3];
wchar_t iList[6][3];
wchar_t uList[12][3];
wchar_t oList[18][3];



void CreateVowelList()
{
	FILE *p;
	p = _wfopen(L"a.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 18; i++)
	{
		fgetws(aList[i], 3, p);
	}
	fclose(p);

	p = _wfopen(L"e.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 12; i++)
	{
		fgetws(eList[i], 3, p);
	}
	fclose(p);

	p = _wfopen(L"i.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 6; i++)
	{
		fgetws(iList[i], 3, p);
	}
	fclose(p);

	p = _wfopen(L"u.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 12; i++)
	{
		fgetws(uList[i], 3, p);
	}
	fclose(p);

	p = _wfopen(L"o.txt", L"r,ccs=UTF-16LE");
	for (int i = 0; i < 18; i++)
	{
		fgetws(oList[i], 3, p);
	}
	fclose(p);
}

void ChuanHoa(wchar_t text[])
{
	for (int i = 0; text[i] != '\0'; i++)
	{
		for (int j = 0; j < 18; j++)	//check coi co phai kieu khac cua tu a ko
		{
			if (text[i] == aList[j][0]) text[i] = 'a';
		}

		for (int j = 0; j < 12; j++)	//check coi co phai kieu khac cua tu e ko
		{
			if (text[i] == eList[j][0]) text[i] = 'e';
		}
		
		for (int j = 0; j < 18; j++)	//check coi co phai kieu khac cua tu o ko
		{
			if (text[i] == oList[j][0]) text[i] = 'o';
		}

		for (int j = 0; j < 6; j++)	//check coi co phai kieu khac cua tu i ko
		{
			if (text[i] == iList[j][0]) text[i] = 'i';
		}

		for (int j = 0; j < 12; j++)	//check coi co phai kieu khac cua tu u ko
		{
			if (text[i] == uList[j][0]) text[i] = 'u';
		}
	}
}